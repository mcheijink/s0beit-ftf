#include "stdafx.h"

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

bool isKeyPressedOnce(bool& bIsPressed, DWORD vk)
{
	if (GetAsyncKeyState(vk) & 0x8000)
	{
		if (bIsPressed == false)
		{
			bIsPressed = true;
			return true;
		}
	}
	else if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	return false;
}

void ReleaseKeys()
{
	keybd_event(VK_NUMPAD1, 0, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_SUBTRACT, 0, KEYEVENTF_KEYUP, 0);
}

char* radioNames[] = { "RADIO_01_CLASS_ROCK", "RADIO_02_POP", "RADIO_03_HIPHOP_NEW", "RADIO_04_PUNK", "RADIO_05_TALK_01", "RADIO_06_COUNTRY", "RADIO_07_DANCE_01", "RADIO_08_MEXICAN", "RADIO_09_HIPHOP_OLD", "RADIO_12_REGGAE", "RADIO_13_JAZZ", "RADIO_14_DANCE_02", "RADIO_15_MOTOWN", "RADIO_20_THELAB", "RADIO_16_SILVERLAKE", "RADIO_17_FUNK", "RADIO_18_90S_ROCK", "RADIO_19_USER", "RADIO_11_TALK_02", "HIDDEN_RADIO_AMBIENT_TV_BRIGHT", "OFF" };


void CheckPlayer(int& iPlayer, bool direction)
{
	int iOriginalPlayer = iPlayer;
	if (iPlayer > 30) {
		iPlayer = 0;
	}
	else if (iPlayer < 0) {
		iPlayer = 30;
	}
	while (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(iPlayer)) == FALSE)
	{
		if (iPlayer > 30)
		{
			iPlayer = 0;
			break;
		}
		else if (iPlayer < 0)
		{
			iPlayer = 30;
			break;
		}
		direction ? iPlayer++ : iPlayer--;
	}
	if (iPlayer != iOriginalPlayer)
		ReleaseKeys(); //This is so you don't continue to blow up the server under someone's name if they leave.
}

DWORD64 g_dwRegistrationTablePtr = 0;
NativeRegistration** GetRegistrationTable() {
	if (!g_dwRegistrationTablePtr) {
		g_dwRegistrationTablePtr = Pattern::Scan(g_MainModuleInfo, "76 61 49 8B 7A 40 48 8D 0D");

		if (!g_dwRegistrationTablePtr) {
			Log::Fatal("Unable to find Native Registration Table");
		}

		g_dwRegistrationTablePtr += 6;

		DWORD64 dwAddressOfRegistrationTable = g_dwRegistrationTablePtr + *(DWORD*)(g_dwRegistrationTablePtr + 3) + 7;

		if (!dwAddressOfRegistrationTable ||
			dwAddressOfRegistrationTable < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfRegistrationTable > (DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading Native Registration Table opcode (0x%I64X)", dwAddressOfRegistrationTable);
		}

		g_dwRegistrationTablePtr = dwAddressOfRegistrationTable;
		DEBUGOUT("g_dwRegistrationTablePtr = 0x%I64X", g_dwRegistrationTablePtr);
	}

	return (NativeRegistration**)g_dwRegistrationTablePtr;
}

NativeHandler GetNativeHandler(UINT64 hash) {
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

DWORD64 g_dwThreadCollectionPtr = 0;
BlipList* g_blipList;
rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection() {
	if (!g_dwThreadCollectionPtr) {
		g_dwThreadCollectionPtr = Pattern::Scan(g_MainModuleInfo, "48 8B ? ? ? ? ? 8B CA 4C 8B 0C C8");

		if (!g_dwThreadCollectionPtr) {
			Log::Fatal("Unable to find GTA Thread Pool");
		}

		DWORD64 dwAddressOfThreadCollection = g_dwThreadCollectionPtr + *(DWORD*)(g_dwThreadCollectionPtr + 3) + 7;

		if (!dwAddressOfThreadCollection ||
			dwAddressOfThreadCollection < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfThreadCollection >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading GTA Thread Pool opcode (0x%I64X)", dwAddressOfThreadCollection);
		}

		g_dwThreadCollectionPtr = dwAddressOfThreadCollection;
		DEBUGOUT("g_dwThreadCollectionPtr = 0x%I64X", g_dwThreadCollectionPtr);

		DWORD64 blipCollectionSignature = Pattern::Scan(g_MainModuleInfo, "4C 8D 05 ? ? ? ? 0F B7 C1");

		g_blipList = (BlipList*)(blipCollectionSignature + *(DWORD*)(blipCollectionSignature + 3) + 7);

		DEBUGOUT("g_blipList = 0x%I64X", g_blipList);
	}

	return (rage::pgPtrCollection<GtaThread>*) g_dwThreadCollectionPtr;
}

GtaThread_VTable gGtaThreadOriginal;
GtaThread_VTable gGtaThreadNew;

HANDLE mainFiber;
DWORD wakeAt;

void WAIT(DWORD ms)
{
#ifndef __DEBUG
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
#endif
}

eThreadState Trampoline(GtaThread* This)
{
	rage::scrThread* runningThread = GetActiveThread();
	SetActiveThread(This);
#ifdef  __DEBUG 
	Run(); //We don't want to also call RunUnlireable, since it's expecting WAIT() to work, which it doesn't in debug mode. #depechemode
#else
	Tick();
#endif
	SetActiveThread(runningThread);
	return gGtaThreadOriginal.Run(This);
}

void __stdcall ReliableScriptFunction(LPVOID lpParameter)
{
	try
	{
		while (1)
		{
			Run();
			SwitchToFiber(mainFiber);
		}
	}
	catch (...)
	{
		Log::Fatal("Failed scriptFiber");
	}
}

void __stdcall HeavyWaitFunction(LPVOID lpParameter)
{
	try
	{
		while (1)
		{
			RunUnreliable();
			SwitchToFiber(mainFiber);
		}
	}
	catch (...)
	{
		Log::Fatal("Failed scriptFiber");
	}
}

void Tick()
{
	if (mainFiber == nullptr)
		mainFiber = ConvertThreadToFiber(nullptr);

	static HANDLE reliableFiber;
	if (reliableFiber)
		SwitchToFiber(reliableFiber);
	else
		reliableFiber = CreateFiber(NULL, ReliableScriptFunction, nullptr);

	if (timeGetTime() < wakeAt)
		return;

	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, HeavyWaitFunction, nullptr);
}

void RunUnreliable() //Put functions that don't really need to be run every frame that can cause heavy wait times for the function here.
{
	
}

void Run() //Only call WAIT(0) here. The Tick() function will ignore wakeAt and call this again regardless of the specified wakeAt time.
{
#ifdef __DEBUG
	static bool bQuit, F12 = false;
	if (isKeyPressedOnce(F12, VK_F12)){ bQuit = true; }
	if (bQuit) { return; }
#endif
	//Run your natives here.

	//Anything after here is fair game for you to run whatever natives you want.
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	//var init
	static bool bGodmodeActive, bGodmodeSwitchset, bF7Pressed, bMoneyDropActive, bSubtractPressed, bHackActive, 
				bF5Pressed, bMenuActive, bF6Pressed, bKillTargetsActive, bNumpad9Pressed, bPoliceIgnorePlayer, 
				bF10Pressed, bHackHidden, bFlowerPowerActive, bMoneyFountainActive, bSpectateMode, bKillSpeakers,
				bPoliceIgnoreSwitchSet = false;
	static bool featureRestrictedZones = true;
	static int iFreeze = -1;
	//static int modulesActive = 0;
	static int mchbuildnr = version;
	static int mchDebugActive = false;
	

	float menuLeft = 1030.0;
	float menuWidth = 250.0;
	float menuTop = 65.0;

	//main hack switch
	if (isKeyPressedOnce(bF5Pressed, VK_F5))
		{
			if (bHackActive) 
			{	//housekeeping of vars
				drawNotification("Deactivating hack");
				bMoneyDropActive, bGodmodeActive, bGodmodeSwitchset, bMenuActive, 
					bKillTargetsActive, bPoliceIgnorePlayer, bPoliceIgnoreSwitchSet, 
					bFlowerPowerActive, bSpectateMode, bKillSpeakers = false;
			}
			else if (!bHackActive) {
				drawNotification("Activating hack");
				bHackHidden = false;
			}
			bHackActive = !bHackActive;
		}

	if (!bHackActive)
		{	
			draw_rect_sc(menuTop, menuLeft, 110.0, 13.0f);
			draw_menu_line("F5 - Hack inactive", 100.0f, 4.0f, menuTop, menuLeft, 5.0f, false, false, false, false);
		}
	else 
		{
			if (ENTITY::DOES_ENTITY_EXIST(playerPed) == TRUE)
			{
				Vehicle playerVeh = NULL;

				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
					playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

				//draw the UI for when hack is active
				draw_menu_line("s0bietftf - build " + std::to_string(mchbuildnr), 15.0f, 4.0f, 0.0f, 550.0f, 5.0f, false, false, false);

				if (mchDebugActive){
					Ped debugPed;
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE)){
						debugPed = PED::GET_VEHICLE_PED_IS_USING(playerPed);
					}
					else {
						debugPed = playerPed;
					}
					Vector3 playerCoordinate = ENTITY::GET_ENTITY_COORDS(debugPed, FALSE); //Dereck B? On your bike!
					float playerHeading = ENTITY::GET_ENTITY_HEADING(debugPed);
					draw_menu_line(" x: " + std::to_string(playerCoordinate.x) + " y: " + std::to_string(playerCoordinate.y) + " z: " + std::to_string(playerCoordinate.z) + " heading: " + std::to_string(playerHeading), 15.0f, 4.0f, 13.0f, 550.0f, 5.0f, false, false, false);
					static bool bF11Pressed;
					if (isKeyPressedOnce(bF11Pressed, VK_F11))
					{
						Log::Msg((" x: " + std::to_string(playerCoordinate.x) + " y: " + std::to_string(playerCoordinate.y) + " z: " + std::to_string(playerCoordinate.z) + " heading: " + std::to_string(playerHeading)).c_str());
					}
				}

				draw_menu_line("F5			- Hack active", menuWidth, 4.0f, menuTop, menuLeft, 5.0f, bHackActive, false, bHackActive, false);
				if (!bHackHidden) {
					draw_menu_line("F6			- Player menu", menuWidth, 4.0f, menuTop + 13.0f * 1, menuLeft, 5.0f, bMenuActive, false, bMenuActive, false);
					draw_menu_line("F7			- Godmode active", menuWidth, 4.0f, menuTop + 13.0f * 2, menuLeft, 5.0f, bGodmodeActive, false, bGodmodeActive, false);
				}
				else if (bHackHidden) {
					draw_rect_sc(menuTop, menuLeft, menuWidth, 13.0f * 2);
					draw_menu_line("F10			- Hack Hidden", menuWidth, 4.0f, menuTop + 13.0f * 1, menuLeft, 5.0f, bHackHidden, false, bHackHidden, false);
				}

				//menu switch
				if (isKeyPressedOnce(bF6Pressed, VK_F6))
				{
					if (bMenuActive){
						//leaving the menu, so we should stop dropping
						bMoneyDropActive = false;
					}
					else if (!bMenuActive){
						//switch of function that cant be accessed from the menu
						bKillTargetsActive = false;
					}
					iFreeze = -1;
					bMenuActive = !bMenuActive;
				}

				//switch to hide the hack
				if (isKeyPressedOnce(bF10Pressed, VK_F10))
				{
					bHackHidden = !bHackHidden;
				}

				//menu subsystem
				bool bReset = false;
				if (bMenuActive)
				{
					if (!bHackHidden)
					{
						//Hack modes for Inside menu
						draw_rect_sc(menuTop, menuLeft, menuWidth, 13.0f * 19);
						draw_menu_line("F10			- Hack Hidden", menuWidth, 4.0f, menuTop + 13.0f * 3, menuLeft, 5.0f, bHackHidden, false, bHackHidden, false);
						draw_menu_line("Pageup		- Prev player in list", menuWidth, 4.0f, menuTop + 13.0f * 4, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Pagedown	- Next player in list", menuWidth, 4.0f, menuTop + 13.0f * 5, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad/		- Give player all weapons", menuWidth, 4.0f, menuTop + 13.0f * 6, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad.		- Teleport to player vehicle", menuWidth, 4.0f, menuTop + 13.0f * 7, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad-		- Spawn money for player", menuWidth, 4.0f, menuTop + 13.0f * 8, menuLeft, 5.0f, bMoneyDropActive, false, bMoneyDropActive, false);
						draw_menu_line("Numpad1		- Explode player", menuWidth, 4.0f, menuTop + 13.0f * 9, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("N1+Rcont		- Frame player", menuWidth, 4.0f, menuTop + 13.0f * 10, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad2	- Clone player vehicle", menuWidth, 4.0f, menuTop + 13.0f * 11, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad3	- Remove all weapons", menuWidth, 4.0f, menuTop + 13.0f * 12, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad4	- Pay and sprayclone", menuWidth, 4.0f, menuTop + 13.0f * 13, menuLeft, 5.0f, false, false, false, false);
						//draw_menu_line("Numpad5	- (alpha) flowerpower", menuWidth, 4.0f, menuTop + 13.0f * 14, menuLeft, 5.0f, bFlowerPowerActive, false, bFlowerPowerActive, false);
						draw_menu_line("Numpad6	- attach basketball", menuWidth, 4.0f, menuTop + 13.0f * 15, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad7	- (alpha) destroy tires", menuWidth, 4.0f, menuTop + 13.0f * 16, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad8	- remove player from vehicle", menuWidth, 4.0f, menuTop + 13.0f * 17, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad9	- remove garbage bin", menuWidth, 4.0f, menuTop + 13.0f * 18, menuLeft, 5.0f, false, false, false, false);
					}

					static int iSelectedPlayer = 0;
					static bool bPgUpPressed, bPgDwnPressed = false;
					if (isKeyPressedOnce(bPgUpPressed, VK_PRIOR))
					{
						iSelectedPlayer--;
						CheckPlayer(iSelectedPlayer, false);
					}
					if (isKeyPressedOnce(bPgDwnPressed, VK_NEXT))
					{
						iSelectedPlayer++;
						CheckPlayer(iSelectedPlayer, true);
					}
					CheckPlayer(iSelectedPlayer, !bPgUpPressed);
					int iLineNum = 0;
					Ped selectedPed = NULL;
					Player selectedPlayer = NULL;
					for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
					{
						bool bSelectedPed = (playerIterator == iSelectedPlayer);
						if (bSelectedPed) {
							selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
							selectedPlayer = playerIterator;
						}
						Ped pedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
						if (ENTITY::DOES_ENTITY_EXIST(pedIterator))
						{
							if (!bHackHidden)
							{
								char chStringToDraw[50];
								strcpy_s(chStringToDraw, PLAYER::GET_PLAYER_NAME(playerIterator));
								if (bSelectedPed)
									sprintf_s(chStringToDraw, "%s F:%i", chStringToDraw, iFreeze == selectedPed);
								draw_menu_line(chStringToDraw, 145.0f, 4.0f, menuTop + 13.0f + iLineNum * 13.0f, menuLeft - 145.0f, 0.0f, false, false, bSelectedPed, false);
								iLineNum++;
							}
						}
					}
					//draw player menu
					draw_rect_sc(menuTop + 13.0f, menuLeft - 145, 145.0, iLineNum * 13.0f);

					//Give all weapons to selected player
					static bool bDividePressed = false;
					if (isKeyPressedOnce(bDividePressed, VK_DIVIDE))
					{
						GiveAllWeaponsToPed(selectedPed, WEAPONTINT_LSPD, selectedPed == playerPed);
						//notify user of action
						drawNotification("Gave all weapons to " + GetPlayerName(selectedPlayer));
					}

					//Teleport to player vehicle
					static bool bDecimalPressed = false;
					if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL) && selectedPed != playerPed)
					{
						TeleporttoSelectedPlayerVehicle(playerPed, selectedPed);
						drawNotification("Teleported to " + GetPlayerName(selectedPlayer) + "'s vehicle");
					}

					//Teleport to selected player on the menu.
					static bool bNumpad0Pressed = false;
					if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0) && selectedPed != playerPed)
					{
						TeleporttoSelectedPlayer(playerPed, selectedPed);
						drawNotification("Teleported to " + GetPlayerName(selectedPlayer));
					}

					//switch for moneydrop
					if (isKeyPressedOnce(bSubtractPressed, VK_SUBTRACT))
					{
						if (bMoneyDropActive){
							drawNotification("Stopping moneydrop");
						}
						else if (bMoneyDropActive) {
							drawNotification("And the rain of the moneyzbagz started!" + GetPlayerName(selectedPlayer) + " be rich and happy");
						}
						bMoneyDropActive = !bMoneyDropActive;
					}
					if (bMoneyDropActive)
					{
						DropMoneyonSelectedPlayer(selectedPed);
					}

					//clone vehicle
					static bool bNumpad2Pressed = false;
					if (isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2))
					{
						Vehicle clonedVeh = ClonePedVehicle(selectedPed);
						BoostBaseVehicleStats(clonedVeh); //Gotta go fast
						WAIT(0); //We need to wait for the game to assign a random radio station to the car first before changing it.
						AUDIO::SET_VEH_RADIO_STATION(playerVeh, radioNames[RADIO_SELFRADIO]);
						drawNotification("Vehicle cloned");
					}

					//park and clone
					static bool bNumpad4Pressed = false;
					if (isKeyPressedOnce(bNumpad4Pressed, VK_NUMPAD4))
					{
						if (LSCCarParkClone(selectedPed))
							drawNotification("Cloned and parked that shit");
						else
							drawNotification("Clone and park Failed");
					}

					//get some plants in LS
					/*
					static bool bNumpad5Pressed = false;
					if (isKeyPressedOnce(bNumpad5Pressed, VK_NUMPAD5))
					{
						bFlowerPowerActive = !bFlowerPowerActive;
					}
					if (bFlowerPowerActive)
					{
						FlowerPower(selectedPed);
					}
					*/
					//Attach junk to player
					static bool bNumpad6Pressed = false;
					if (isKeyPressedOnce(bNumpad6Pressed, VK_NUMPAD6))
					{
						if (AttachJunktoSelectedPlayer(selectedPed))
							drawNotification("Attached junk to " + GetPlayerName(selectedPlayer));
					}

					//Burst all the tires of another players car

					static bool bNumpad7Pressed = false;
					if (isKeyPressedOnce(bNumpad7Pressed, VK_NUMPAD7))
					{
						BurstSelectedPlayerTires(selectedPed);
						drawNotification("Bursted tires");
					}

					//Remove player from vehicle
					static bool bNumpad8Pressed = false;
					if (isKeyPressedOnce(bNumpad8Pressed, VK_NUMPAD8))
					{
						DumpPlayerFromVehicle(selectedPed, true);
						drawNotification(GetPlayerName(selectedPlayer) + " dumped from vehicle");
					}

					//kill selected player by explosion
					if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
					{
						//if controll is pressed, selected player will kill people around him.
						if (GetAsyncKeyState(VK_RCONTROL) & 0x8000)
						{
							FrameSelectedPlayer(selectedPed);
							drawNotification(GetPlayerName(selectedPlayer) + " framed!");
						}
						else
						{
							ExplodeSelectedPlayer(selectedPed);
							drawNotification(GetPlayerName(selectedPlayer) + " killed");
						}
					}

					//remove all weapons
					static bool bNumpad3Pressed = false;
					if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
					{
						WEAPON::REMOVE_ALL_PED_WEAPONS(selectedPed, TRUE);
						drawNotification("Took away all " + GetPlayerName(selectedPlayer) + " guns");
					}


			}
			else //every function without selecting a player
			{
				if (!bHackHidden){
					//Hack modes for outside menu
					draw_rect_sc(menuTop, menuLeft, menuWidth, 13.0f * 18);
					draw_menu_line("F8			- Max ammo", menuWidth, 4.0f, menuTop + 13.0f * 3, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("F9			- Remove Junk", menuWidth, 4.0f, menuTop + 13.0f * 4, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("F10			- Hack Hidden", menuWidth, 4.0f, menuTop + 13.0f * 5, menuLeft, 5.0f, bHackHidden, false, bHackHidden, false);
					draw_menu_line("Numpad.		- Repair Vehicle", menuWidth, 4.0f, menuTop + 13.0f * 6, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad0	- Teleport to waypoint", menuWidth, 4.0f, menuTop + 13.0f * 7, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad2	- Spawn Kuruma2", menuWidth, 4.0f, menuTop + 13.0f * 8, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad3	- Spawn Vestra", menuWidth, 4.0f, menuTop + 13.0f * 9, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad4	- Police disabled", menuWidth, 4.0f, menuTop + 13.0f * 10, menuLeft, 5.0f, bPoliceIgnorePlayer, false, bPoliceIgnorePlayer, false);
					draw_menu_line("Numpad5	- Kill speaking peasants", menuWidth, 4.0f, menuTop + 13.0f * 11, menuLeft, 5.0f, bKillSpeakers, false, bKillSpeakers, false);
					draw_menu_line("Numpad6	- Enforce No-Flyzone", menuWidth, 4.0f, menuTop + 13.0f * 12, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad7	- Teleport to objective", menuWidth, 4.0f, menuTop + 13.0f * 13, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad8	- Fountain of gold", menuWidth, 4.0f, menuTop + 13.0f * 14, menuLeft, 5.0f, bMoneyFountainActive, false, bMoneyFountainActive, false);
					draw_menu_line("Numpad9	- Kill all targets on map", menuWidth, 4.0f, menuTop + 13.0f * 15, menuLeft, 5.0f, bKillTargetsActive, false, bKillTargetsActive, false);
					draw_menu_line("Numpad+	- Increase wanted level", menuWidth, 4.0f, menuTop + 13.0f * 16, menuLeft, 5.0f, false, false, false, false);
					draw_menu_line("Numpad*		- Remove wanted level", menuWidth, 4.0f, menuTop + 13.0f * 17, menuLeft, 5.0f, false, false, false, false);
				}
				
				//kill all the speaking players
				static bool bNumpad1Pressed = false;
				if (isKeyPressedOnce(bNumpad1Pressed, VK_NUMPAD1))
				{
					if (bSpectateMode){
						drawNotification("Stopping Spectate");
						SpectateMode(false);
					}
					else if (!bSpectateMode) {
						drawNotification("Spectating");
						SpectateMode(true);
					}
					bSpectateMode = !bSpectateMode;
				}

				//Spawn a test car.
				static bool bNumpad2Pressed, bWaitingForModelCar = false;
				if ((isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2) || bWaitingForModelCar == true) && playerVeh == NULL)
				{
					bWaitingForModelCar = SpawnPlayerCar(playerPed, playerVeh, bWaitingForModelCar);
				}

				//Spawn a test aircraft.
				static bool bNumpad3Pressed, bWaitingForModelAircraft = false;
				if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
				{
					bWaitingForModelAircraft = SpawnPlayerAircraft(playerPed, playerVeh, bWaitingForModelAircraft);
				}

				//Police wont notice me
				static bool bNumpad4Pressed = false;
				if (isKeyPressedOnce(bNumpad4Pressed, VK_NUMPAD4))
				{
					bPoliceIgnorePlayer = !bPoliceIgnorePlayer;
				}
				
				//kill all the speaking players
				static bool bNumpad5Pressed = false;
				if (isKeyPressedOnce(bNumpad5Pressed, VK_NUMPAD5))
				{
					if (bKillSpeakers){
						drawNotification("Keep'n the talking peasants alive...");
					}
					else if (!bKillSpeakers) {
						drawNotification("Killing those peasants");
					}
					bKillSpeakers = !bKillSpeakers;
				}
				if (bKillSpeakers) {
					Player speakingPlayer = KillalltheSpeakingPlayers();
					if (speakingPlayer != -1)
						drawNotification(GetPlayerName(speakingPlayer) + " killed for speaking out loud");
				}

				// no fly zone
				static bool bNumpad6Pressed = false;
				if (isKeyPressedOnce(bNumpad6Pressed, VK_NUMPAD6))
				{
					drawNotification("Cleared Airspace of off " + std::to_string(ClearingTheSkiesofPlayers()) + " pilots");
				}

				//TP to mission objective.
				static bool bNumpad7Pressed = false;
				if (isKeyPressedOnce(bNumpad7Pressed, VK_NUMPAD7))
				{
					TeleporttoMissionObjective(playerPed, g_blipList);
					drawNotification("Teleported to Mission objective");
				}

				//Teleport to waypoint.
				static bool bNumpad0Pressed = false;
				static int teleportIteratrions = -1;
				if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0) || teleportIteratrions > -1)
				{
					teleportIteratrions = TeleporttoWaypoint(playerPed, teleportIteratrions);
					drawNotification("Teleported to waypoint");
				}

				//Fix player.
				static bool bDecimalPressed = false;
				if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL))
				{
					FixPlayer(playerPed);
					drawNotification("Player fixed");
				}

				static bool bNumpad8Pressed;
				if (isKeyPressedOnce(bNumpad8Pressed, VK_NUMPAD8))
				{
					if (bMoneyFountainActive){
						drawNotification("Stopping moneydrop");
					}
					else if (bMoneyFountainActive) {
						drawNotification("And the foutain of money started!!");
					}
					bMoneyFountainActive = !bMoneyFountainActive;
				}
				

				//Shoot all spaghettios (Fuck Deliver EMP)
				static bool bNumpad9Pressed = false;
				if (isKeyPressedOnce(bNumpad9Pressed, VK_NUMPAD9))
				{
					if (bKillTargetsActive){
						drawNotification("Stopping masacre");
					}
					else if (!bKillTargetsActive) {
						drawNotification("Starting killing spree");
					}
					bKillTargetsActive = !bKillTargetsActive;
				}

			}// end of menu

			//Force full reload animation on weapon. If you want a quicker reload, just quickly tap R. The 0x1 state seems to be time sensitive.
				if (GetAsyncKeyState(0x52) & 0x1)
				{
					FastReload(playerPed);
				}

			//Increase wanted level.
			static bool bAddPressed = false;
			if (isKeyPressedOnce(bAddPressed, VK_ADD))
			{
				IncreaseWantedLevel(player);
			}

			//Clear Wanted Level
			if (GetAsyncKeyState(VK_MULTIPLY) & 0x8000)
			{
				ClearWantedLevel(player);
			}

			//switch for godmode
			static bool bF7Pressed = false;
			if (isKeyPressedOnce(bF7Pressed, VK_F7))
			{
				bGodmodeActive = !bGodmodeActive;
			}

			static bool F8Pressed = false;
			if (isKeyPressedOnce(F8Pressed, VK_F8))
			{
				ReplenishAmmo(playerPed);				
				drawNotification("Got maximum ammo");
			}

			static bool F9Pressed = false;
			if (isKeyPressedOnce(F9Pressed, VK_F9))
			{
				RemoveAllPropsFromPlayer(playerPed);
				drawNotification("Removed attached junk");
			}
		}
	}

	/*
	a couple of functions that need to run each tick
	*/
	//moneyfountain action
	MoneyFountain(bMoneyFountainActive);

	//kill all targets active
	KillAllTargets(playerPed, g_blipList, bKillTargetsActive);

	//police ignore player
	bPoliceIgnoreSwitchSet = PoliceIgnorePlayer(player, bPoliceIgnorePlayer, bPoliceIgnoreSwitchSet);
	EnableRestrictedZones(!bPoliceIgnoreSwitchSet);

	//Godmode
	bGodmodeSwitchset = GodMode(player, playerPed, bGodmodeActive, bGodmodeSwitchset);

	return;
}

bool AttemptScriptHook() {
	rage::pgPtrCollection<GtaThread>* threadCollection = GetGtaThreadCollection();

	if (!threadCollection) {
		return false;
	}

	for (UINT16 i = 0; i < threadCollection->count(); i++) {
		GtaThread* pThread = threadCollection->at(i);

		if (!pThread)
			continue;

		//s0biet originally had some junk thread that was called for like 2 seconds then died. This thread is better.
		if (pThread->GetContext()->ScriptHash != 0x5700179C) {
			continue;
		}

		// Now what? We need to find a target thread and hook it's "Tick" function
		if (gGtaThreadOriginal.Deconstructor == NULL) {
			memcpy(&gGtaThreadOriginal, (DWORD64*)((DWORD64*)pThread)[0], sizeof(gGtaThreadOriginal)); //Create a backup of the original table so we can call the original functions from our hook.
			memcpy(&gGtaThreadNew, &gGtaThreadOriginal, sizeof(GtaThread_VTable)); //Construct our VMT replacement table.

			gGtaThreadNew.Run = Trampoline; //Replace the .Run method in the new table with our method.
		}

		if (((DWORD64*)pThread)[0] != (DWORD64)&gGtaThreadNew) { //If the table is not VMT Hooked.
			DEBUGOUT("Hooking thread [%i] (0x%X)", pThread->GetContext()->ThreadId, pThread->GetContext()->ScriptHash);
			((DWORD64*)pThread)[0] = (DWORD64)&gGtaThreadNew; //Replace the VMT pointer with a pointer to our new VMT.
			DEBUGOUT("Hooked thread [%i] (0x%X)", pThread->GetContext()->ThreadId, pThread->GetContext()->ScriptHash);
			return true;
		}
	}
	return false;
}

DWORD WINAPI lpHookScript(LPVOID lpParam) {
	while (!AttemptScriptHook()) {
		Sleep(100);
	}

	return 0; //We no longer need the lpHookScript thread because our new_Run function will now be the hip and or hop hang out spot for the KewlKidzKlub®.
}

void SpawnScriptHook() {
	CreateThread(0, 0, lpHookScript, 0, 0, 0);
}

void BypassOnlineModelRequestBlock() {
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