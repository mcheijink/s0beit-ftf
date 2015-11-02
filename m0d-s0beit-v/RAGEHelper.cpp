#include "stdafx.h"

DWORD64 dwRegistrationTablePtr = 0;
DWORD64 dwThreadCollectionPtr = 0;

NativeRegistration** GetRegistrationTable()
{
	if (!dwRegistrationTablePtr) {
		dwRegistrationTablePtr = Pattern::Scan(g_MainModuleInfo, "76 61 49 8B 7A 40 48 8D 0D");

		if (!dwRegistrationTablePtr) {
			Log::Fatal("Unable to find Native Registration Table");
		}

		dwRegistrationTablePtr += 6;

		DWORD64 dwAddressOfRegistrationTable = dwRegistrationTablePtr + *(DWORD*)(dwRegistrationTablePtr + 3) + 7;

		if (!dwAddressOfRegistrationTable ||
			dwAddressOfRegistrationTable < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfRegistrationTable >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading Native Registration Table opcode (0x%I64X)", dwAddressOfRegistrationTable);
		}

		dwRegistrationTablePtr = dwAddressOfRegistrationTable;
		DEBUGOUT("dwRegistrationTablePtr = 0x%I64X", dwRegistrationTablePtr);
	}

	return (NativeRegistration**)dwRegistrationTablePtr;
}

NativeHandler GetNativeHandler(UINT64 hash)
{
	NativeRegistration** registrationTable = GetRegistrationTable();

	if (!registrationTable)
		return nullptr;

	NativeRegistration* table = registrationTable[hash & 0xFF];

	for (; table; table = table->nextRegistration)
	{
		for (UINT32 i = 0; i < table->numEntries; i++)
		{
			if (hash == table->hashes[i])
			{
				return table->handlers[i];
			}
		}
	}

	return nullptr;
}

void NativeInvoke::Invoke(NativeContext *cxt, UINT64 hash)
{
	auto fn = GetNativeHandler(hash);

	if (fn != 0)
	{
		fn(cxt);
	}
}

rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection(BlipList*& pBlipList)
{
	if (!dwThreadCollectionPtr) {
		dwThreadCollectionPtr = Pattern::Scan(g_MainModuleInfo, "48 8B 05 ? ? ? ? 8B CA 4C 8B 0C C8 45 39 51 08");

		if (!dwThreadCollectionPtr) {
			Log::Fatal("Unable to find GTA Thread Pool");
		}

		DWORD64 dwAddressOfThreadCollection = dwThreadCollectionPtr + *(DWORD*)(dwThreadCollectionPtr + 3) + 7;

		if (!dwAddressOfThreadCollection ||
			dwAddressOfThreadCollection < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfThreadCollection >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading GTA Thread Pool opcode (0x%I64X)", dwAddressOfThreadCollection);
		}

		dwThreadCollectionPtr = dwAddressOfThreadCollection;
		DEBUGOUT("dwThreadCollectionPtr = 0x%I64X", dwThreadCollectionPtr);

		DWORD64 blipCollectionSignature = Pattern::Scan(g_MainModuleInfo, "4C 8D 05 ? ? ? ? 0F B7 C1");

		pBlipList = (BlipList*)(blipCollectionSignature + *(DWORD*)(blipCollectionSignature + 3) + 7);

		DEBUGOUT("pBlipList = 0x%I64X", pBlipList);
	}

	return (rage::pgPtrCollection<GtaThread>*) dwThreadCollectionPtr;
}

//https://s-media-cache-ak0.pinimg.com/236x/a5/32/43/a5324394baa368ef5273ef2e95a2976c.jpg
rage::scrThread* GetActiveThread()
{
	char* moduleTls = *(char**)__readgsqword(88);

	return *reinterpret_cast<rage::scrThread**>(moduleTls + 2096); //citizenMP sigs this offset. It's been the same for 3 versions. Not worth it.
}
//I won't even begin to claim that I know what the fuck is going on here. ~gir489
void SetActiveThread(rage::scrThread* thread)
{
	char* moduleTls = *(char**)__readgsqword(88);

	*reinterpret_cast<rage::scrThread**>(moduleTls + 2096) = thread;
}

void CheckPlayer(int& iPlayer, bool direction)
{
	int iOriginalPlayer = iPlayer;
	if (iPlayer > MAX_PLAYERS) {
		iPlayer = 0;
	}
	else if (iPlayer < 0) {
		iPlayer = MAX_PLAYERS;
	}
	while (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(iPlayer)) == FALSE)
	{
		if (iPlayer > MAX_PLAYERS)
		{
			iPlayer = 0;
			break;
		}
		else if (iPlayer < 0)
		{
			iPlayer = MAX_PLAYERS;
			break;
		}
		direction ? iPlayer++ : iPlayer--;
	}
	if (iPlayer != iOriginalPlayer)
		ReleaseKeys(); //This is so you don't continue to blow up the server under someone's name if they leave.
}

void BypassOnlineModelRequestBlock()
{
	DWORD64 dwGetModelTableFunctionAddress = Pattern::Scan(g_MainModuleInfo, "48 8B C8 FF 52 30 84 C0 74 05 48");
	if (dwGetModelTableFunctionAddress != NULL)
		*(unsigned short*)(dwGetModelTableFunctionAddress + 0x8) = 0x9090;
	else
	{
		#ifndef __DEBUG
		Log::Error("Failed to find model table signature");
		#else
		Log::Debug("Failed to find model table signature");
		#endif
	}
}

void NoIntro()
{
	DWORD64 dwSplashScreen = Pattern::Scan(g_MainModuleInfo, "72 1F E8 ? ? ? ? 8B 0D");
	if (dwSplashScreen == NULL)  //If the module is still encrypted at the time of injection, run the No Intro code.
	{
		while (dwSplashScreen == NULL)
		{
			Sleep(10);
			dwSplashScreen = Pattern::Scan(g_MainModuleInfo, "72 1F E8 ? ? ? ? 8B 0D");
		}

		if (dwSplashScreen != NULL)
			*(unsigned short*)(dwSplashScreen) = 0x9090; //NOP out the check to make it think it's time to stop.

		DWORD64 dwRockStarLogo = Pattern::Scan(g_MainModuleInfo, "70 6C 61 74 66 6F 72 6D 3A");
		int iCounter = 0;
		while (dwRockStarLogo == NULL)
		{
			Sleep(10);
			dwRockStarLogo = Pattern::Scan(g_MainModuleInfo, "70 6C 61 74 66 6F 72 6D 3A");
		}

		if (dwRockStarLogo != NULL)
			*(unsigned char*)(dwRockStarLogo) = 0x71; //Replace the P with some garbage so it won't find the file.

		Sleep(15000); //Wait until the logo code has finished running.
		//Restore the EXE to its original state.
		*(unsigned char*)(dwRockStarLogo) = 0x70;
		*(unsigned short*)(dwSplashScreen) = 0x1F72;
	}
}