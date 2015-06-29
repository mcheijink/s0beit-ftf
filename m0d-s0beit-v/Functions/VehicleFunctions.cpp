#include "../stdafx.h"
#include "../natives.h"
#include "UIFunctions.h"
#include "PlayerFunctions.h"

void BoostBaseVehicleStats(Vehicle vehicle)
{
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
	BOOL IsRCtrlUp = (GetAsyncKeyState(VK_RCONTROL) & 0x8000);
	ENTITY::SET_ENTITY_INVINCIBLE(vehicle, IsRCtrlUp); //That should do the trick.
	ENTITY::SET_ENTITY_PROOFS(vehicle, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp);
	VEHICLE::SET_VEHICLE_STRONG(vehicle, IsRCtrlUp); //2stronk
	VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, !IsRCtrlUp); //I don't think this really works, but fuck it. Call it anyway.
	VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, !IsRCtrlUp); //Hopefully this fixes the car blowing up after getting hit by a train...
	VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, !IsRCtrlUp);
	VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE); //What seems to be the officer, problem? *le9gagmemeface*
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, FALSE); //Bulletproof Tires.
	Hash vehicleModel = ENTITY::GET_ENTITY_MODEL(vehicle);
	if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModel) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModel))
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0); //IDK what this does, but I guess it allows individual mods to be added? It's what the game does before calling SET_VEHICLE_MOD.
		VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(vehicle, IsRCtrlUp); //6stronk9meme
		VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ENGINE, MOD_INDEX_FOUR, FALSE); //6fast9furious
		VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_BRAKES, MOD_INDEX_THREE, FALSE); //GOTTA STOP FAST
		VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_TRANSMISSION, MOD_INDEX_THREE, FALSE); //Not when I shift in to MAXIMUM OVERMEME!
		VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SUSPENSION, MOD_INDEX_FOUR, FALSE); //How low can you go?
		VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, MOD_INDEX_FIVE, FALSE); //100% armor.
		VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE); //Forced induction huehuehue
	}
	VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.0f); //This is what the game does
}

void AddClanLogoToVehicle(Vehicle vehicle, Ped ped)
{
	vector3_t x, y, z;
	float scale;
	Hash modelHash = ENTITY::GET_ENTITY_MODEL(vehicle);
	if (GetVehicleInfoForClanLogo(modelHash, x, y, z, scale))
	{
		int alpha = 200;
		if (modelHash == VEHICLE_WINDSOR)
			alpha = 255;
		GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(vehicle, ped, ENTITY::_GET_ENTITY_BONE_INDEX(vehicle, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
	}
}

Vehicle ClonePedVehicle(Ped ped)
{
	Vehicle pedVeh = NULL;
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
		pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
	else //If they're not in a vehicle, try to get their last vehicle.
		pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, TRUE);
	if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
	{
		Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
		STREAMING::REQUEST_MODEL(vehicleModelHash); //This should already be loaded since we're stealing it from someone in memory.
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
		Vehicle playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
		PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, SEAT_DRIVER);
		int primaryColor, secondaryColor;
		VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
		VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) || VEHICLE::IS_THIS_MODEL_A_BIKE(vehicleModelHash))
		{
			VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
			for (int i = 0; i <= MOD_BACKWHEELS; i++)
			{
				if (i > MOD_ARMOR && i < MOD_FRONTWHEELS)
					VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
				else
					VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
			}
			int tireSmokeColor[3], pearlescentColor, wheelColor;
			VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
			VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
			VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
			if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
			{
				int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
				if (convertableState == 0 || convertableState == 3 || convertableState == 5)
					VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
				else
					VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
			}
			for (int i = 0; i <= NEON_BACK; i++)
			{
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
			}
			for (int i = 0; i <= 11; i++)
			{
				if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
					VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
			}
			if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
			{
				VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
			}
			int neonColor[3];
			VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
			VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
			if (GRAPHICS::_HAS_VEHICLE_GOT_DECAL(pedVeh, 0) == TRUE)
			{
				AddClanLogoToVehicle(playerVeh, ped);
			}
		}
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
	}
	return pedVeh;
}

void DumpPlayerFromVehicle(Ped PlayerID, bool Notification)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(PlayerID, FALSE))
	{
		//Remove PED from vehicle
		AI::CLEAR_PED_TASKS_IMMEDIATELY(PlayerID);
		//need to remove the parachute: 0xFBAB5776
		WEAPON::REMOVE_WEAPON_FROM_PED(PlayerID, 0xFBAB5776);

		if (Notification){
			std::string selectedPedName = PLAYER::GET_PLAYER_NAME(PlayerID);
			drawNotification(selectedPedName + "Removed from vehicle");
		}
	}
}

void DumpVehicleStats(Vehicle vehicle)
{
	if (ENTITY::DOES_ENTITY_EXIST(vehicle) == FALSE || ENTITY::IS_ENTITY_A_VEHICLE(vehicle) == FALSE)
		Log::Error("DumpVehicleStats was passed an incorrect entity");
	char* modNames[] = { "MOD_SPOILER", "MOD_FRONTBUMPER", "MOD_REARBUMPER", "MOD_SIDESKIRT", "MOD_EXHAUST", "MOD_CHASSIS", "MOD_GRILLE", "MOD_HOOD", "MOD_FENDER", "MOD_RIGHTFENDER", "MOD_ROOF", "MOD_ENGINE", "MOD_BRAKES", "MOD_TRANSMISSION", "MOD_HORNS", "MOD_SUSPENSION", "MOD_ARMOR", "", "MOD_TURBO", "", "MOD_TIRESMOKE", "", "MOD_XENONLIGHTS", "MOD_FRONTWHEELS", "MOD_BACKWHEELS" };
	int primaryColor, secondaryColor;
	VEHICLE::GET_VEHICLE_COLOURS(vehicle, &primaryColor, &secondaryColor);
	Log::Msg("vehicleModelHash = VEHICLE_%s; //0x%X", VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(vehicle)), ENTITY::GET_ENTITY_MODEL(vehicle));
	Log::Msg("VEHICLE::SET_VEHICLE_COLOURS(playerVeh, %u, %u);", primaryColor, secondaryColor);
	Log::Msg("VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, %i);", VEHICLE::GET_VEHICLE_WINDOW_TINT(vehicle));
	if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(vehicle)) == TRUE || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(vehicle)))
	{
		Log::Msg("VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVeh, %s);", VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(vehicle) ? "TRUE" : "FALSE");
		Log::Msg("VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, %i);", VEHICLE::GET_VEHICLE_WHEEL_TYPE(vehicle));
		for (int i = 0; i <= MOD_BACKWHEELS; i++)
		{
			if (i > MOD_ARMOR && i < MOD_FRONTWHEELS)
			{
				BOOL bModOn = VEHICLE::IS_TOGGLE_MOD_ON(vehicle, i);
				if (i == MOD_TIRESMOKE && bModOn == TRUE)
				{
					int tireSmokeColor[3];
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					Log::Msg("VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);", VEHICLE::IS_TOGGLE_MOD_ON(vehicle, i));
					Log::Msg("VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, %u, %u, %u);", tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
				}
				else if (bModOn == TRUE)
				{
					Log::Msg("VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, %s, TRUE);", modNames[i]);
				}
			}
			else if (VEHICLE::GET_VEHICLE_MOD(vehicle, i) != -1)
				Log::Msg("VEHICLE::SET_VEHICLE_MOD(playerVeh, %s, %i, %s);", modNames[i], VEHICLE::GET_VEHICLE_MOD(vehicle, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(vehicle, i) ? "TRUE" : "FALSE");
		}
		int pearlescentColor, wheelColor;
		Log::Msg("VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, \"%s\");", VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(vehicle));
		Log::Msg("VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, %i);", VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(vehicle));
		VEHICLE::GET_VEHICLE_EXTRA_COLOURS(vehicle, &pearlescentColor, &wheelColor);
		Log::Msg("VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, %u, %u);", pearlescentColor, wheelColor);
		bool bDumpLightColor = false;
		for (int i = 0; i <= NEON_BACK; i++)
		{
			BOOL bIsLightOn = VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(vehicle, i);
			if (bIsLightOn == TRUE)
			{
				if (bDumpLightColor == false)
				{
					int neonColor[3];
					VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, &neonColor[0], &neonColor[1], &neonColor[2]);
					Log::Msg("VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, %u, %u, %u);", neonColor[0], neonColor[1], neonColor[2]);
					bDumpLightColor = true;
				}
				Log::Msg("VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, %i, TRUE);", i);
			}
		}
		if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(vehicle, 0))
		{
			int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(vehicle);
			if (convertableState == 0 || convertableState == 3 || convertableState == 5)
				Log::Msg("VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, TRUE);");
			else
				Log::Msg("VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, TRUE);");
		}
		for (int i = 0; i <= 11; i++)
		{
			if (VEHICLE::DOES_EXTRA_EXIST(vehicle, i) == TRUE)
				Log::Msg("VEHICLE::SET_VEHICLE_EXTRA(playerVeh, %i, %s);", i, VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(vehicle, i) ? "FALSE" : "TRUE");
		}
		if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(vehicle) > 1) && VEHICLE::GET_VEHICLE_LIVERY(vehicle) >= 0)
		{
			Log::Msg("VEHICLE::SET_VEHICLE_LIVERY(playerVeh, %i);", VEHICLE::GET_VEHICLE_LIVERY(vehicle));
		}
		if (GRAPHICS::_HAS_VEHICLE_GOT_DECAL(vehicle, 0) == TRUE)
		{
			Log::Msg("AddClanLogoToVehicle(playerVeh, playerPed);");
		}
	}
}

void SetOffAlarmofPlayerVehicle(Ped selectedPed)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
	{
		Entity selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
		RequestControl(PED::GET_VEHICLE_PED_IS_USING(selectedPed));
		VEHICLE::SET_VEHICLE_ALARM(selectedVehicle, true);
		VEHICLE::START_VEHICLE_ALARM(selectedVehicle);
		drawNotification("Set off alarm of vehicle");
	}
}

bool LSCCarParkClone(Ped selectedPed)
{
	Vector3 carpark[10];
	float carparkheading = 298.0f;
	carpark[0].x = -377.052338f; carpark[0].y = -146.578171f; carpark[0].z = 38.136883f;
	carpark[1].x = -378.185455f; carpark[1].y = -143.062912f; carpark[1].z = 38.637417f;
	carpark[2].x = -379.831360f; carpark[2].y = -139.990662f; carpark[2].z = 38.637928f;
	carpark[3].x = -381.609650f; carpark[3].y = -137.015427f; carpark[3].z = 38.638058f;
	carpark[4].x = -383.640381f; carpark[4].y = -134.032303f; carpark[4].z = 38.638317f;
	carpark[5].x = -385.417297f; carpark[5].y = -131.086594f; carpark[5].z = 38.637768f;
	carpark[6].x = -386.984100f; carpark[6].y = -127.842491f; carpark[6].z = 38.656815f;
	carpark[7].x = -388.355316f; carpark[7].y = -124.618080f; carpark[7].z = 38.638138f;
	carpark[8].x = -389.692169f; carpark[8].y = -121.593727f; carpark[8].z = 38.629921f;
	carpark[9].x = -392.876312f; carpark[9].y = -118.994896f; carpark[9].z = 38.053879f;

	Vehicle pedVeh = NULL;
	pedVeh = PED::GET_VEHICLE_PED_IS_IN(selectedPed, TRUE);
	int counter;
	if (ENTITY::DOES_ENTITY_EXIST(pedVeh))
	{
		Hash vehicleModelHash = ENTITY::GET_ENTITY_MODEL(pedVeh);
		if (VEHICLE::IS_THIS_MODEL_A_CAR(vehicleModelHash) && !VEHICLE::IS_BIG_VEHICLE(vehicleModelHash))
		{
			counter = 0;
			for each (Vector3 carparkcoordinate in carpark)
			{
				GAMEPLAY::CLEAR_AREA_OF_VEHICLES(carparkcoordinate.x, carparkcoordinate.y, carparkcoordinate.z, 2.0f, true, true, true, true, true);
			}

			STREAMING::REQUEST_MODEL(vehicleModelHash); //This should already be loaded since we're stealing it from someone in memory.
			counter = 0;
			for each (Vector3 carparkcoordinate in carpark)
			{
				Vehicle clonedVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, carparkcoordinate.x, carparkcoordinate.y, carparkcoordinate.z, carparkheading, TRUE, TRUE);
				VEHICLE::SET_VEHICLE_MOD_KIT(clonedVeh, 0);
				int primaryColor, secondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(clonedVeh, primaryColor, secondaryColor);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(clonedVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
				for (int i = 0; i <= MOD_BACKWHEELS; i++)
				{
					if (i > MOD_ARMOR && i < MOD_FRONTWHEELS)
						VEHICLE::TOGGLE_VEHICLE_MOD(clonedVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
					else
						VEHICLE::SET_VEHICLE_MOD(clonedVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
				}
				int tireSmokeColor[3], pearlescentColor, wheelColor;
				VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(clonedVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(clonedVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(clonedVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
				VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(clonedVeh, pearlescentColor, wheelColor);
				if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0))
				{
					int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
					if (convertableState == 0 || convertableState == 3 || convertableState == 5)
						VEHICLE::RAISE_CONVERTIBLE_ROOF(clonedVeh, 1);
					else
						VEHICLE::LOWER_CONVERTIBLE_ROOF(clonedVeh, 1);
				}
				for (int i = 0; i <= NEON_BACK; i++)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(clonedVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
				}
				for (int i = 0; i <= 11; i++)
				{
					if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
						VEHICLE::SET_VEHICLE_EXTRA(clonedVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
				}
				if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0)
				{
					VEHICLE::SET_VEHICLE_LIVERY(clonedVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
				}
				int neonColor[3];
				VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(clonedVeh, neonColor[0], neonColor[1], neonColor[2]);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(clonedVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
				VEHICLE::SET_VEHICLE_LIGHTS(clonedVeh, true);
				VEHICLE::SET_VEHICLE_ALARM(clonedVeh, true);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
				BoostBaseVehicleStats(clonedVeh);
			}
			return true;
		}
	}
	return false;
}

void BurstSelectedPlayerTires(Ped selectedPed)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
	{
		//fuck up the tires
		Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
		RequestControl(selectedVehicle);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(selectedVehicle, TRUE);
			static int tireID = 0;
			for (tireID = 0; tireID < 8; tireID++) 
			{
				VEHICLE::SET_VEHICLE_TYRE_BURST(selectedVehicle, tireID, true, 1000.0);
			}
	}
}

bool SpawnPlayerAircraft(Ped playerPed, Vehicle playerVeh, bool bWaitingForModelAircraft)
{
	bool bWaiting = true;
	if (bWaitingForModelAircraft || playerVeh == NULL)
	{
		Hash vehicleModelHash = (GetAsyncKeyState(VK_RCONTROL) & 0x8000) ? VEHICLE_BUZZARD : VEHICLE_VESTRA; //This was Vincentor's idea. See: https://www.youtube.com/watch?v=jAsgKuXaGb4
		STREAMING::REQUEST_MODEL(vehicleModelHash);
		if (STREAMING::HAS_MODEL_LOADED(vehicleModelHash) == TRUE)
		{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
			playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z + 800, ENTITY::GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
			PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, SEAT_DRIVER);
			if (vehicleModelHash == VEHICLE_VESTRA)
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
			else
			{
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::SET_HELI_BLADES_FULL_SPEED(playerVeh);
			}
			BoostBaseVehicleStats(playerVeh);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
			bWaiting = false;
		}
		else
		{
			bWaiting = true;
		}
	}
	if (playerVeh != NULL && (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(playerVeh)) == TRUE || VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(playerVeh)) == TRUE ||
		ENTITY::GET_ENTITY_MODEL(playerVeh) == VEHICLE_BLIMP || ENTITY::GET_ENTITY_MODEL(playerVeh) == VEHICLE_BLIMP2 || ENTITY::GET_ENTITY_MODEL(playerVeh) == VEHICLE_TITAN))
	{
		RequestControl(playerVeh);
		Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerVeh, FALSE);
		if (playerPosition.z < 350.0f)
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerVeh, playerPosition.x, playerPosition.y, playerPosition.z + 800, FALSE, FALSE, TRUE);
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, 500.0f);
		BoostBaseVehicleStats(playerVeh);
	}
	return bWaiting;
}

bool SpawnPlayerCar(Ped playerPed, Vehicle playerVeh, bool bWaitingForModelCar)
{
	if (playerVeh == NULL || bWaitingForModelCar == true)
	{
		Hash vehicleModelHash = VEHICLE_KURUMA2;
		if (GetAsyncKeyState(VK_UP) & 0x8000)
			vehicleModelHash = VEHICLE_BTYPE;
		else if (GetAsyncKeyState(VK_RMENU) & 0x8000)
			vehicleModelHash = VEHICLE_RUINER;
		else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			vehicleModelHash = VEHICLE_ZENTORNO;
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			vehicleModelHash = VEHICLE_INSURGENT;
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			vehicleModelHash = VEHICLE_RHINO;
		STREAMING::REQUEST_MODEL(vehicleModelHash);
		if (STREAMING::HAS_MODEL_LOADED(vehicleModelHash) == TRUE)
		{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
			playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
			RequestControl(playerVeh);
			PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, SEAT_DRIVER);
			BoostBaseVehicleStats(playerVeh);
			if (vehicleModelHash == VEHICLE_KURUMA2) //Test that I can make a perfect 1:1 clone of my Kuruma with only calling natives.
			{
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_SPOILER, MOD_INDEX_ONE, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTBUMPER, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_SIDESKIRT, MOD_INDEX_FIVE, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_EXHAUST, MOD_INDEX_ONE, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HORNS, HORN_SADTROMBONE, FALSE);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, WHEEL_TYPE_HIGHEND);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTWHEELS, WHEEL_HIGHEND_SUPAGEE, TRUE); //TRUE because we want the Custom Tires.
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_XENONLIGHTS, TRUE);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_BLACK);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_BLACK);
				/*for (int i = 0; i < NEON_BACK; i++) //This will turn on all the neon emitters except the back one. That shit's annoying when I'm trying to drive.
				{
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, TRUE);
				}
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
				*/
				drawNotification("Spawned Kuruma");
			}
			else if (vehicleModelHash == VEHICLE_ZENTORNO)
			{
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_CHASSIS, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_SPOILER, MOD_INDEX_SEVEN, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTBUMPER, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_SIDESKIRT, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_EXHAUST, MOD_INDEX_FOUR, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HORNS, HORN_SADTROMBONE, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HOOD, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, WHEEL_TYPE_HIGHEND);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTWHEELS, WHEEL_HIGHEND_SUPAGEE, TRUE);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_XENONLIGHTS, TRUE);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_BLACK);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, PLATE_YELLOWONBLUE);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_BLACK);
				/*for (int i = 0; i < NEON_BACK; i++) //This will turn on all the neon emitters except the back one. That shit's annoying when I'm trying to drive.
				{
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, TRUE);
				}
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
				*/
				AddClanLogoToVehicle(playerVeh, playerPed);
				drawNotification("Spawned Zentorno");

			}
			else if (vehicleModelHash == VEHICLE_INSURGENT)
			{
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, WHEEL_TYPE_SPORT);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTWHEELS, WHEEL_SPORT_DEEPFIVE, TRUE);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_BLACK);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_GREEN);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HORNS, HORN_TRUCK, FALSE);
				drawNotification("Spawned Insurgent");
			}
			else if (vehicleModelHash == VEHICLE_RUINER)
			{
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_BLACK);
				VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVeh, FALSE);
				VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, WHEEL_TYPE_MUSCLE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_SPOILER, MOD_INDEX_TWO, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_EXHAUST, MOD_INDEX_ONE, FALSE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HORNS, HORN_SADTROMBONE, FALSE);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_XENONLIGHTS, TRUE);
				VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTWHEELS, WHEEL_MUSCLE_CLASSICFIVE, TRUE);
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, PLATE_YELLOWONBLUE);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 0, TRUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 1, TRUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 2, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 2, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 3, FALSE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 7, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 10, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 11, TRUE);
				AddClanLogoToVehicle(playerVeh, playerPed);
				drawNotification("Spawned Ruiner");
			}
			else
			{
				//all other vehicles
				drawNotification("Spawned Vehicle");
			}
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
			bWaitingForModelCar = false;
		}
		else
		{
			bWaitingForModelCar = true;
		}
	}
	else if (playerVeh != NULL)
	{
		RequestControl(playerVeh);
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, VEHICLE::_GET_VEHICLE_MAX_SPEED(ENTITY::GET_ENTITY_MODEL(playerVeh)));
	}
	return bWaitingForModelCar;
}
