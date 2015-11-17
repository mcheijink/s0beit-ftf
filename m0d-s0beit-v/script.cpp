#include "stdafx.h"

//https://s-media-cache-ak0.pinimg.com/236x/a5/32/43/a5324394baa368ef5273ef2e95a2976c.jpg
Player moneyPlayer = -1;

BlipList* pBlipList;
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

int cint(float number)
{
	int result = (number + 0.5);
	return result;
}
void RunUnreliable() //Put functions that don't really need to be run every frame that can cause heavy wait times for the function here.
{

}

void Run() //Put functions that don't really need to be run every frame that can cause heavy wait times for the function here.
 //Only call WAIT(0) here. The Tick() function will ignore wakeAt and call this again regardless of the specified wakeAt time.
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
				bPoliceIgnoreSwitchSet, bLeftAltPressed, bNumpad3Pressed, bInvisible = false;
	static bool featureRestrictedZones = true;
	static int iFreeze = -1;
	//static int modulesActive = 0;
	static int mchbuildnr = version;
	static int mchDebugActive = true;

	static Ped driverPed = NULL;
	

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
					bFlowerPowerActive, bSpectateMode, bKillSpeakers, bInvisible = false;
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
					float playerSpeed = ENTITY::GET_ENTITY_SPEED(debugPed) * 3.6;
					draw_menu_line(" x: " + std::to_string(cint(playerCoordinate.x)) + " y: " + std::to_string(cint(playerCoordinate.y)) + " z: " + std::to_string(cint(playerCoordinate.z)) + " heading: " + std::to_string(cint(playerHeading)) + " speed: " + std::to_string(cint(playerSpeed)), 15.0f, 4.0f, 13.0f, 550.0f, 5.0f, false, false, false);
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
						draw_rect_sc(menuTop, menuLeft, menuWidth, 13.0f * 18);
						draw_menu_line("F10			- Hack Hidden", menuWidth, 4.0f, menuTop + 13.0f * 3, menuLeft, 5.0f, bHackHidden, false, bHackHidden, false);
						draw_menu_line("Pageup		- Prev player in list", menuWidth, 4.0f, menuTop + 13.0f * 4, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Pagedown	- Next player in list", menuWidth, 4.0f, menuTop + 13.0f * 5, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad/		- Give player all weapons", menuWidth, 4.0f, menuTop + 13.0f * 6, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad.		- Teleport to player vehicle", menuWidth, 4.0f, menuTop + 13.0f * 7, menuLeft, 5.0f, false, false, false, false);
						//draw_menu_line("Numpad-		- Spawn money for player", menuWidth, 4.0f, menuTop + 13.0f * 8, menuLeft, 5.0f, bMoneyDropActive, false, bMoneyDropActive, false);
						draw_menu_line("Numpad1		- Explode player", menuWidth, 4.0f, menuTop + 13.0f * 8, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("N1+Rcont		- Frame player", menuWidth, 4.0f, menuTop + 13.0f * 9, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad2	- Clone player vehicle", menuWidth, 4.0f, menuTop + 13.0f * 10, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad3	- Remove all weapons", menuWidth, 4.0f, menuTop + 13.0f * 11, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad4	- Pay and sprayclone", menuWidth, 4.0f, menuTop + 13.0f * 12, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad5	- spectate player", menuWidth, 4.0f, menuTop + 13.0f * 13, menuLeft, 5.0f, bSpectateMode, false, bSpectateMode, false);
						draw_menu_line("Numpad6	- attach basketball", menuWidth, 4.0f, menuTop + 13.0f * 14, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad7	- jack ride", menuWidth, 4.0f, menuTop + 13.0f * 15, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad8	- remove player from vehicle", menuWidth, 4.0f, menuTop + 13.0f * 16, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad9	- spawn moneyped", menuWidth, 4.0f, menuTop + 13.0f * 17, menuLeft, 5.0f, false, false, false, false);
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
					for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
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

					//Teleport to selected player on the menu.
					static bool bNumpad0Pressed = false;
					if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0) && selectedPed != playerPed)
					{
						TeleporttoSelectedPlayer(playerPed, selectedPed);
						drawNotification("Teleported to " + GetPlayerName(selectedPlayer));
					}

					//kill selected player by explosion
					if (IsKeyPressed(VK_NUMPAD1))
					{
						//if controll is pressed, selected player will kill people around him.
						if (IsKeyPressed(VK_RCONTROL))
						{
							FrameSelectedPlayer(selectedPed);
							drawNotification(GetPlayerName(selectedPlayer) + " framed!");
						}
						else if (IsKeyPressed(VK_LMENU))
						{
							for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
							{
								selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
								ExplodeSelectedPlayer(selectedPed);
							}
							drawNotification("Everybody exploded themselve :P");
						}
						else
						{
							ExplodeSelectedPlayer(selectedPed);
							drawNotification(GetPlayerName(selectedPlayer) + " killed");
						}
					}

					//clone vehicle
					static bool bNumpad2Pressed = false;
					if (isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2))
					{
						Vehicle clonedVeh = ClonePedVehicle(selectedPed);
						BoostBaseVehicleStats(clonedVeh); //Gotta go fast
						WAIT(0); //We need to wait for the game to assign a random radio station to the car first before changing it.
						AUDIO::SET_VEH_RADIO_STATION(playerVeh, AUDIO::GET_RADIO_STATION_NAME(RADIO_SELFRADIO));
						drawNotification("Vehicle cloned");
					}

					//remove all weapons
					if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
					{
						if (IsKeyPressed(VK_LMENU))
						{
							for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
							{
								selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
								WEAPON::REMOVE_ALL_PED_WEAPONS(selectedPed, TRUE);
							}
							drawNotification("Everybody lost their guns");
						}
						else
						{
							WEAPON::REMOVE_ALL_PED_WEAPONS(selectedPed, TRUE);
							drawNotification("Took away all " + GetPlayerName(selectedPlayer) + " guns");
						}
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

					static bool bNumpad5Pressed = false;
					if (isKeyPressedOnce(bNumpad5Pressed, VK_NUMPAD5))
					{
						if (bSpectateMode){
							drawNotification("Stopping Spectate");
							AI::CLEAR_PED_TASKS(playerPed);
							SpectateMode(false, selectedPed);
						}
						else if (!bSpectateMode) {
							drawNotification("Spectating");
							AIWanderCar(playerPed);
							SpectateMode(true, selectedPed);
						}
						bSpectateMode = !bSpectateMode;
					}

					//get some plants in LS
					/*
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
						//all players or just 1?
						if (IsKeyPressed(VK_LMENU))
						{
							for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
							{
								selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
								AttachJunktoSelectedPlayer(selectedPed);
							}
							drawNotification("Junk to the masses!");
						}
						else {
							if (AttachJunktoSelectedPlayer(selectedPed))
								drawNotification("Attached junk to " + GetPlayerName(selectedPlayer));
						}
					}

					//Jack players ride
					static bool bNumpad7Pressed = false;
					if (isKeyPressedOnce(bNumpad7Pressed, VK_NUMPAD7))
					{
						AIJackVehicle(selectedPed);
						drawNotification(GetPlayerName(selectedPlayer) + " got jacked");
					}

					//Remove player from vehicle
					static bool bNumpad8Pressed = false;
					if (isKeyPressedOnce(bNumpad8Pressed, VK_NUMPAD8))
					{
						//all players or just 1?
						if (IsKeyPressed(VK_LMENU))
						{
							for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
							{
								selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
								DumpPlayerFromVehicle(selectedPed, true);
							}
							drawNotification("Everybody out of their car");
						}
						else {
							DumpPlayerFromVehicle(selectedPed, true);
							drawNotification(GetPlayerName(selectedPlayer) + " dumped from vehicle");
						}
					}

					static bool bNumpad9Pressed = false;
					if (isKeyPressedOnce(bNumpad9Pressed, VK_NUMPAD9))
					{
						SpawnPedMoney(selectedPed);
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
					

					//Give all weapons to selected player
					static bool bDividePressed = false;
					if (isKeyPressedOnce(bDividePressed, VK_DIVIDE))
					{
						//all players or just 1?
						if (IsKeyPressed(VK_LMENU))
						{
							for (Player playerIterator = 0; playerIterator < 31; playerIterator++)
							{
								selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
								GiveAllWeaponsToPed(selectedPed, WEAPONTINT_LSPD, selectedPed == playerPed);
							}
							drawNotification("Gave all weapons to all players");
						}
						else {
							GiveAllWeaponsToPed(selectedPed, WEAPONTINT_LSPD, selectedPed == playerPed);
							//notify user of action
							drawNotification("Gave all weapons to " + GetPlayerName(selectedPlayer));
						}
					}

					//Teleport to player vehicle
					static bool bDecimalPressed = false;
					if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL) && selectedPed != playerPed)
					{
						TeleporttoSelectedPlayerVehicle(playerPed, selectedPed);
						drawNotification("Teleported to " + GetPlayerName(selectedPlayer) + "'s vehicle");
					}

				}
				else //every function without selecting a player
				{
					if (!bHackHidden){
						//Hack modes for outside menu
						draw_rect_sc(menuTop, menuLeft, menuWidth, 13.0f * 19);
						draw_menu_line("F8			- Max ammo", menuWidth, 4.0f, menuTop + 13.0f * 3, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("F9			- Remove Junk", menuWidth, 4.0f, menuTop + 13.0f * 4, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("F10			- Hack Hidden", menuWidth, 4.0f, menuTop + 13.0f * 5, menuLeft, 5.0f, bHackHidden, false, bHackHidden, false);
						draw_menu_line("Numpad.		- Repair Vehicle", menuWidth, 4.0f, menuTop + 13.0f * 6, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad0	- Teleport to waypoint", menuWidth, 4.0f, menuTop + 13.0f * 7, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad1		- Drive to waypoint", menuWidth, 4.0f, menuTop + 13.0f * 8, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad2	- Spawn Kuruma2", menuWidth, 4.0f, menuTop + 13.0f * 9, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad3	- Spawn Vestra", menuWidth, 4.0f, menuTop + 13.0f * 10, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad4	- Police disabled", menuWidth, 4.0f, menuTop + 13.0f * 11, menuLeft, 5.0f, bPoliceIgnorePlayer, false, bPoliceIgnorePlayer, false);
						draw_menu_line("Numpad5	- Kill speaking peasants", menuWidth, 4.0f, menuTop + 13.0f * 12, menuLeft, 5.0f, bKillSpeakers, false, bKillSpeakers, false);
						draw_menu_line("Numpad6	- Enforce No-Flyzone", menuWidth, 4.0f, menuTop + 13.0f * 13, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad7	- Teleport to objective", menuWidth, 4.0f, menuTop + 13.0f * 14, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad8	- Get a driver", menuWidth, 4.0f, menuTop + 13.0f * 15, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad9	- Kill all targets on map", menuWidth, 4.0f, menuTop + 13.0f * 16, menuLeft, 5.0f, bKillTargetsActive, false, bKillTargetsActive, false);
						draw_menu_line("Numpad+	- Increase wanted level", menuWidth, 4.0f, menuTop + 13.0f * 17, menuLeft, 5.0f, false, false, false, false);
						draw_menu_line("Numpad*		- Remove wanted level", menuWidth, 4.0f, menuTop + 13.0f * 18, menuLeft, 5.0f, false, false, false, false);
					}

					static bool bNumpad1Pressed;
					if (isKeyPressedOnce(bNumpad1Pressed, VK_NUMPAD1))
					{
						if ((driverPed != NULL) && (PED::IS_PED_ON_SPECIFIC_VEHICLE(driverPed, playerVeh)))
							AIDrivetoWaypoint(driverPed);
						else
							AIDrivetoWaypoint(playerPed);
						drawNotification("Driving to Waypoint");
					}

					//Spawn a test car.
					static bool bNumpad2Pressed, bWaitingForModelCar = false;
					if ((isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2) || bWaitingForModelCar == true) && playerVeh == NULL)
					{
						bWaitingForModelCar = SpawnPlayerCar(playerPed, bWaitingForModelCar);
					}

					//Spawn a test aircraft.
					static bool bNumpad3Pressed, bWaitingForModelAircraft = false;
					if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
					{
						bWaitingForModelAircraft = SpawnPlayerAircraft(playerPed, bWaitingForModelAircraft);
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
						TeleporttoMissionObjective(playerPed, pBlipList);
						drawNotification("Teleported to Mission objective");
					}

					static bool bNumpad8Pressed;
					if (isKeyPressedOnce(bNumpad8Pressed, VK_NUMPAD8))
					{
						driverPed = getRandomPedToDrive();
						if (driverPed != NULL)
							drawNotification("Getting a new driver");
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

					//Teleport to waypoint.
					static bool bNumpad0Pressed = false;
					static int teleportIteratrions = -1;
					if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0))
					{
						TeleporttoWaypoint(playerPed);
						drawNotification("Teleported to waypoint");
					}

					//Fix player.
					static bool bDecimalPressed = false;
					if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL))
					{
						FixPlayer(playerPed);
						drawNotification("Player fixed");
					}

				}// end of menu

				//Force full reload animation on weapon. If you want a quicker reload, just quickly tap R. The 0x1 state seems to be time sensitive.
				if (IsKeyPressed(0x52))
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
				if (IsKeyPressed(VK_MULTIPLY))
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
	//kill all targets active
	KillAllTargets(playerPed, pBlipList, bKillTargetsActive);

	//police ignore player
	PoliceIgnorePlayer(player, bPoliceIgnorePlayer);
	EnableRestrictedZones(!bPoliceIgnoreSwitchSet);

	//Godmode
	GodMode(player, playerPed, bGodmodeActive);

	//SetRadio();
	//AntiCrash();

	if (!(driverPed == NULL) && PED::IS_PED_DEAD_OR_DYING(driverPed, true))
		driverPed = NULL;

	return;
}
bool AttemptScriptHook()
{
	rage::pgPtrCollection<GtaThread>* threadCollection = GetGtaThreadCollection(pBlipList);

	if (!threadCollection) {
		return false;
	}

	for (UINT16 i = 0; i < threadCollection->count(); i++) {
		GtaThread* pThread = threadCollection->at(i);

		if (!pThread)
			continue;

		//s0biet originally had some junk thread that was called for like 2 seconds then died. This thread is better.
		if (pThread->GetContext()->ScriptHash != 0x5700179C) { //MAIN_PERSISTANT?
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

	return 0; //We no longer need the lpHookScript thread because our Trampoline function will now be the hip and or hop hang out spot for the KewlKidzKlub®.
}

void SpawnScriptHook() {
	CreateThread(0, 0, lpHookScript, 0, 0, 0);
}