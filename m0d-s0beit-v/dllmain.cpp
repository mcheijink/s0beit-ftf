#include "stdafx.h"
#include "GTA5_NativeUpdater.h"

MODULEINFO g_MainModuleInfo = { 0 };

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		Log::Init(hModule);
		DEBUGOUT("m0d-s0beit-v loaded"); 

		if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &g_MainModuleInfo, sizeof(g_MainModuleInfo))) {
			Log::Fatal("Unable to get MODULEINFO from GTA5.exe");
		}

		DEBUGOUT("GTA5 [0x%I64X][0x%X]", g_MainModuleInfo.lpBaseOfDll, g_MainModuleInfo.SizeOfImage);

		GetNativeHashes(); //Grab the hashes for natives.h from the EXE.
		SpawnScriptHook(); //Hook that shit.
		BypassOnlineModelRequestBlock(); //This allows us to spawn models on the LE XD INTERNET
	}

	return TRUE;
}

