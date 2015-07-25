#include "../stdafx.h"
#include "../natives.h"
#include "../script.h"
#include "UIFunctions.h"
#include "VehicleFunctions.h"

void RemoveAllPropsFromPlayer(Ped ped)
{
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(ped, FALSE);
	Hash modelHashes[] = { 0x2E28CA22 /*p_tram_crash_s*/, 0xA50DDDD0/*prop_bball_arcade_01*/,
		0xEFC4165A/*prop_food_van_01*/, 0x8E8C7A5B/*prop_crashed_heli*/,
		0x456AA864/*prop_dj_deck_01*/, 0xBE862050/*prop_portacabin01*/,
		0xB20E5785/*prop_sculpt_fix*/, 0x58D3B4EA/*prop_micro_01*/,
		0xC42C019A/*prop_ld_ferris_wheel*/, 0x8AF58425/*prop_lev_des_barge_01*/,
		0x3DC31836/*prop_tv_flat_01*/, 0xA9BD0D16 /*prop_coke_block_01*/,
		0x1AFA6A0A /*Prop_weed_01*/, 0x4B3D240F /*prop_wheelchair_01*/,
		0x40F52369 /*p_v_43_safe_s*/, 0xF830B63E /*prop_swiss_ball_01*/,
		0xD541462D /*p_ld_soc_ball_01*/, 0x532B1DD1 /*prop_rub_trolley01a*/,
		0x0E3BA450 /*prop_xmas_tree_int*/, 0xFB631122 /*prop_bumper_car_01*/,
		0x5571173D /*prop_beer_neon_01*/, 0x6AD326C2 /*prop_space_rifle*/,
		0x7FFBC1E2 /*prop_dummy_01*/, 0x678FC2DB /*prop_wheelchair_01_s*/,
		0x5869A8F8 /*prop_large_gold*/, 0xE6CB661E /*PROP_CS_DILDO_01*/,
		0x2AE13DFA /*prop_armchair_01*/, 0x29CB0F3C /*prop_armour_pickup*/,
		0x922C2A43 /*prop_big_shit_01*/, 0xFA686C0E /*prop_bin_04a*/,
		0x1F550C17 /*prop_chair_01a*/, 0x5B5C4263 /*prop_chip_fryer*/,
		0x39885BB5 /*prop_chickencoop_a*/, 0x16A39A90 /*prop_dog_cage_01*/,
		0xE3CE09E2 /*prop_dummy_plane*/, 0x927A5723 /*prop_fan_01*/,
		0x34D5D3FD /*prop_golf_bag_01*/, 0xB467C540 /*p_spinning_anus_s*/,
		0x745F3383 /*prop_windmill_01*/, 0x392D62AA /*prop_gold_cont_01*/,
		0x07121AC4 /*prop_xmas_ext*/, 0x0E8032E4 /*prop_weed_pallet*/,
		0xD44295DD /*p_cablecar_s*/, 0x6F9939C7 /*prop_ld_toilet_01*/,
		0x9C762726 /*prop_lev_des_barge_02*/, 0x8973A868 /*prop_air_bigradar*/,
		0xC2BC19CD /*p_cs_mp_jet_01_s*/, 651101403 /*garbage bin*/,
		1840863642 /*baskedball */ };
	for each (Hash modelHash in modelHashes)
	{
		Object obj = OBJECT::GET_CLOSEST_OBJECT_OF_TYPE(playerPosition.x, playerPosition.y, playerPosition.z, 3.0f, modelHash, TRUE, 0, 0);
		if (ENTITY::DOES_ENTITY_EXIST(obj))
			ENTITY::DELETE_ENTITY(&obj);
	}
}

void RequestControl(Entity e)
{
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(e);
	if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e))
		WAIT(0);
	NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(e);
}

//Function to determine if a Player object is on your Rockstar Social Club friends list.
bool IsPlayerFriend(Player player)
{
	BOOL BplayerFriend = false;
	bool bplayerFriend = false;
	int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		BplayerFriend = NETWORK::NETWORK_IS_FRIEND(&handle[0]);
	}
	if (BplayerFriend = 1)
		bplayerFriend = true;
	else
		bplayerFriend = false;

	return bplayerFriend;
}

void TeleporttoSelectedPlayerVehicle(Ped playerPed, Ped selectedPed)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
	{
		Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
		for (int i = SEAT_BACKPASSENGER; i >= SEAT_DRIVER; i--)
		{
			PED::SET_PED_INTO_VEHICLE(playerPed, selectedVehicle, i);
		}
	}
}

void TeleporttoSelectedPlayer(Ped playerPed, Ped selectedPed) 
{
	Entity e = playerPed;
	Vehicle playerVeh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (playerVeh != NULL)
		e = playerVeh;

	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, playerPosition.x, playerPosition.y, playerPosition.z + 1, FALSE, FALSE, TRUE);
}

void DropMoneyonSelectedPlayer(Ped selectedPed)
{
	try
	{
		static int iMoney = 0;
		iMoney++;
		if (ENTITY::DOES_ENTITY_EXIST(selectedPed) && !ENTITY::IS_ENTITY_DEAD(selectedPed))
		{
			if (!STREAMING::HAS_MODEL_LOADED(0x113FD533))
				STREAMING::REQUEST_MODEL(0x113FD533); //Manchester United: Nil Loadsamoney United: LOADS
			if (iMoney >= 2)
			{
				if (STREAMING::HAS_MODEL_LOADED(0x113FD533)) //Good evening and welcome to: Loads of Money.
				{
					Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE); //Dereck B? On your bike!
					static Hash PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"); //Right. Let's do up the house.
					int MONEY_DROP_AMOUNT = rand() % 25000 + 10000; // lets make it more random so r* wont recognize a pattern mch
					OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, playerPosition.x, playerPosition.y, playerPosition.z + 0.5f, 0, MONEY_DROP_AMOUNT, 0x113FD533, FALSE, TRUE); //WHOP YOUR WAD ON THE COUNTA
					STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533); //SHUT YOUR MOUTH!
				}
				iMoney = 0;
			}
		}
	}
	catch (...){ Log::Error("Got too much money."); }
}

void TeleportSelectedPlayertoAlamosSea(Ped selectedPed)
{
	//funcion is not working
	AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
	RequestControl(selectedPed);
	AI::TASK_FOLLOW_NAV_MESH_TO_COORD(selectedPed, 254.74130f, 4042.002930f, -3.102535f, 1.0f, 1000, 1048576000.0f, 0, 1193033728.0f);
}

bool AttachJunktoSelectedPlayer(Ped selectedPed)
{
	//load junk model
	/* Sample objects:
	prop_bskball_01=1840863642  		0xF77CB21C
	prop_cs_bin_02=651101403			0x0F3F3CB0
	prop_defilied_ragdoll_01=-332567508	0x7A2A3826
	prop_bball_arcade_01				0xA50DDDD0
	Garbage can							651101403
	Basketball							1840863642
	*/
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		Hash objectModel = 651101403;
		if (!STREAMING::HAS_MODEL_LOADED(objectModel))
		{
			STREAMING::REQUEST_MODEL(objectModel);
		}
		if (STREAMING::HAS_MODEL_LOADED(objectModel) == TRUE)
		{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
			Object junkObject = OBJECT::CREATE_OBJECT(objectModel, playerPosition.x, playerPosition.y, playerPosition.z, 1, 1, 0);
			OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(junkObject);
			if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
			}
			RequestControl(junkObject);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(junkObject, selectedPed, PED::GET_PED_BONE_INDEX(selectedPed, SKEL_ROOT),
				0.00f,	//floatx
				0.00f,	//floaty
				1.0f,	//floatz
				0.0f,	//xrot
				180.0f,	//yrot 
				0.0f,	//zrot
				false, false, false, false, 2, true);
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(objectModel);
			return true;
		}
		else 
			return false;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		//airdancer
		Hash objectModel = 0x8F2D17AA;
		char* animAirDancer = "anim@p_airdancer_01_s";
		if (!STREAMING::HAS_MODEL_LOADED(objectModel))
		{
			STREAMING::REQUEST_MODEL(objectModel);
		}
		if (!STREAMING::HAS_ANIM_DICT_LOADED(animAirDancer))
		{
			STREAMING::REQUEST_ANIM_DICT(animAirDancer);
		}
		if (STREAMING::HAS_MODEL_LOADED(objectModel) == TRUE && STREAMING::HAS_ANIM_DICT_LOADED(animAirDancer) == TRUE)
		{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
			Object junkObject = OBJECT::CREATE_OBJECT(objectModel, playerPosition.x, playerPosition.y, playerPosition.z, 1, 1, 0);
			OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(junkObject);
			if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
			}
			RequestControl(junkObject);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(junkObject, selectedPed, PED::GET_PED_BONE_INDEX(selectedPed, SKEL_ROOT),
				0.00f,	//floatx
				0.00f,	//floaty
				0.0f,	//floatz
				0.0f,	//xrot
				0.0f,	//yrot 
				0.0f,	//zrot
				false, false, false, false, 2, true);
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(objectModel);
			//Any animAirDanceScene = NETWORK::NETWORK_CREATE_SYNCHRONISED_SCENE(, 0.0, 0.0, 0.0, 2, 0, 0, 0x3f800000, 0, 0x3f800000)

			ENTITY::PLAY_ENTITY_ANIM(junkObject, animAirDancer, "p_airdancer_01_s", 1000.0, 0, 0, 0, 0, 0);
			//ENTITY::PLAY_SYNCHRONIZED_ENTITY_ANIM(v_433, v_45F, "darts_ig_intro_alt1_dart", "mini@dartsintro_alt1", 1000.0, 0x41000000, 0, 0x447a0000);
			return true;
		}
		else
			return false;
	}
	else 
	{
		Hash objectModel = 1840863642;
		if (!STREAMING::HAS_MODEL_LOADED(objectModel))
		{
			STREAMING::REQUEST_MODEL(objectModel);
		}
		if (STREAMING::HAS_MODEL_LOADED(objectModel) == TRUE)
		{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
			Object junkObject = OBJECT::CREATE_OBJECT(objectModel, playerPosition.x, playerPosition.y, playerPosition.z, 1, 1, 0);
			OBJECT::PLACE_OBJECT_ON_GROUND_PROPERLY(junkObject);
			if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
			{
				AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
			}
			RequestControl(junkObject);
			ENTITY::ATTACH_ENTITY_TO_ENTITY(junkObject, selectedPed, PED::GET_PED_BONE_INDEX(selectedPed, SKEL_Head),
				0.05f,	//floatx
				0.01f,	//floaty
				0.00f,	//floatz
				0.0f,	//xrot
				180.0f,	//yrot 
				0.0f,	//zrot
				false, false, false, false, 2, true);
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(objectModel);
			return true;
		}
		else 
			return false;
	}
}

void AttackPlayerWithRandomPeds(Ped selectedPed)
{
	//function not working
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
	{
		Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(selectedVehicle); //requesting permission to fuck up another player

		//Remove PED from vehicle and lock it up
		AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
		VEHICLE::SET_VEHICLE_DOORS_LOCKED_FOR_ALL_PLAYERS(selectedVehicle, true);
	}
	//select a random ped arround player
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
	Vector3 createdPos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(selectedPed, 0.0f, 35.0f, 0.0f);
	//transvest hash: 0x5715E410
	//stungun hash: 0x1E4A619F

	Ped createdPed = PED::CREATE_PED(130, 0x5715E410, createdPos.x, createdPos.y, createdPos.z, 1.0, false, true);

	PED::SET_PED_CAN_SWITCH_WEAPON(createdPed, true);
	WEAPON::GIVE_DELAYED_WEAPON_TO_PED(createdPed, 0x1E4A619F, 1000, true);

	PED::REGISTER_TARGET(createdPed, selectedPed);
	AI::TASK_COMBAT_PED(createdPed, selectedPed, 0, 1);

	STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x5715E410);
}

void FrameSelectedPlayer(Ped selectedPed)
{
	static int playerIterator = 0;
	for (int i = 0; i < 5; i++)
	{
		Ped playerPedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
		if (ENTITY::DOES_ENTITY_EXIST(playerPedIterator) && playerPedIterator) //If the iteration exists, and they're alive, and they're not me.
		{
				try
				{
					AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPedIterator); //If they're in a jet, or something. Toss them out.
					Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPedIterator, FALSE);
					FIRE::ADD_OWNED_EXPLOSION(selectedPed, playerPosition.x, playerPosition.y, playerPosition.z, EXPLOSION_TANKER, 1000.0f, FALSE, TRUE, 0.0f); //We can blame anyone for the explosion. Whoever is selected in the menu will be blamed.
				}
				catch (...) { Log::Error("Crashed"); break; } //IDK why, but if you call these functions too many times per tick, it causes a crash. We can just toss the exception. Hopefully this fixes the crash...
		}
		playerIterator++;
		if (playerIterator > 29)
			playerIterator = 0;
	}
}

void ExplodeSelectedPlayer(Ped selectedPed)
{
	//and else, only himself
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
		FIRE::ADD_OWNED_EXPLOSION(selectedPed, playerPosition.x, playerPosition.y, playerPosition.z, EXPLOSION_TANKER, 1000.0f, FALSE, TRUE, 0.0f);
}

bool PoliceIgnorePlayer(Player player, bool bPoliceIgnorePlayer, bool bPoliceIgnoreSwitchSet)
{
	if (bPoliceIgnorePlayer)
	{
		if (!bPoliceIgnoreSwitchSet)
		{
			//police wont catch me
			int frozenWantedLevel = 0;
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
			PLAYER::SET_MAX_WANTED_LEVEL(frozenWantedLevel);

			//people will ignore me
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);

			//disable army base:
			drawNotification("Police disabled");
			bPoliceIgnoreSwitchSet = true;
		}
	}
	else if (!bPoliceIgnorePlayer)
	{
		if (bPoliceIgnoreSwitchSet){
			//regain wantedlevel
			PLAYER::SET_MAX_WANTED_LEVEL(5);

			//stop ignoring me
			PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
			PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
			PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
			PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false);
			//enable army base:
			bPoliceIgnoreSwitchSet = false;
			drawNotification("Police started looking again");
		}
	}
	else
		bPoliceIgnoreSwitchSet = false;
	return bPoliceIgnoreSwitchSet;
}

//kill al the speakers
Player KillalltheSpeakingPlayers()
{
	for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
	{
		Ped pedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
		if (ENTITY::DOES_ENTITY_EXIST(pedIterator))
		{
			if (NETWORK::NETWORK_IS_PLAYER_TALKING(playerIterator))
			{
				ExplodeSelectedPlayer(pedIterator);
				return playerIterator;
			}
		}
	}
	return -1;
}

//enforce no-fly zone
int ClearingTheSkiesofPlayers()
{
	int iFlyingcount = 0;
	for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
	{
		Ped pedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
		if (ENTITY::DOES_ENTITY_EXIST(pedIterator))
		{
			if (PED::IS_PED_IN_FLYING_VEHICLE(pedIterator))
			{
				DumpPlayerFromVehicle(pedIterator, false);
				iFlyingcount++;
			}
		}
	}
	return iFlyingcount;
}

void TeleporttoMissionObjective(Ped playerPed, BlipList* g_blipList)
{
	Vehicle playerVeh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	for (int i = 0; i <= 1000; i++)
	{
		Blip* blip = g_blipList->m_Blips[i].m_pBlip;
		if (blip)
		{
			if ((blip->dwColor == BLIPCOLOR_MISSION && blip->iIcon == BLIP_CIRCLE) ||
				(blip->dwColor == BLIPCOLOR_YELLOWMISSION && blip->iIcon == BLIP_CIRCLE) ||
				(blip->dwColor == BLIPCOLOR_NONE && blip->iIcon == BLIP_RACEFLAG) ||
				(blip->dwColor == BLIPCOLOR_GREEN && blip->iIcon == BLIP_CIRCLE) ||
				(blip->iIcon == BLIP_SPECIALCRATE))
			{
				Entity e = playerPed;
				if (playerVeh)
					e = playerVeh;
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(e);
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, blip->x, blip->y, blip->z, FALSE, FALSE, TRUE);
				break; //During a race there's sometimes 2 yellow markers. We want the first one.
			}
		}
	}
}

int TeleporttoWaypoint(Ped playerPed, int teleportIteratrions) {
	Entity e = playerPed;
	Vehicle playerVeh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (playerVeh != NULL)
		e = playerVeh;
	static Vector3 coords, oldLocation;
	if (teleportIteratrions == -1)
	{
		int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
		for (int i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = UI::GET_BLIP_INFO_ID_COORD(i);
				teleportIteratrions = 19;
				oldLocation = ENTITY::GET_ENTITY_COORDS(e, FALSE);
				break;
			}
		}
	}
	if (teleportIteratrions > -1)
	{
		bool groundFound = false;
		static float groundCheckHeight[] = { 800.0f, 750.0f, 700.0f, 650.0f, 600.0f, 550.0f, 500.0f, 450.0f, 400.0f, 350.0f, 300.0f, 250.0f, 200.0f, 100.0f, 150.0f, 50.0f, 100.0f, 150.0f, 150.0f, 0.0f };
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[teleportIteratrions], FALSE, FALSE, TRUE);
		if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[teleportIteratrions], &coords.z) == TRUE)
		{
			groundFound = true;
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, coords.z + 3, FALSE, FALSE, TRUE);
			teleportIteratrions = -1;
		}
		if (teleportIteratrions > -1)
			teleportIteratrions--;
		if (!groundFound && teleportIteratrions < 0)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, oldLocation.x, oldLocation.y, oldLocation.z, FALSE, FALSE, TRUE);
		}
	}
	return teleportIteratrions;
}

void FixPlayer(Ped playerPed)
{
	Vehicle playerVeh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
	{
		RequestControl(playerVeh); //Can't hurt to try.
		VEHICLE::SET_VEHICLE_FIXED(playerVeh);
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(playerVeh, 1000.0f);
		VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(playerVeh);
		BoostBaseVehicleStats(playerVeh);
	}
	PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
	//We can only change stats that are not ServerAuthoritative="true" in mpstatssetup.xml.
	//STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_MENTAL_STATE"), 0.0f, TRUE);
}

void KillAllTargets(Ped playerPed, BlipList* g_blipList, bool bKillTargetsActive)
{
	if (bKillTargetsActive)
	{
		for (int i = 0; i <= 1000; i++)
		{
			Blip* blip = g_blipList->m_Blips[i].m_pBlip;
			if (blip)
			{
				if (blip->dwColor != BLIPCOLOR_BLUE) //Don't hit friendlies.
				{
					if (blip->iIcon == BLIP_COP /*cop*/ || blip->iIcon == BLIP_SPAGHETTIO || (blip->iIcon == BLIP_CIRCLE && blip->dwColor == BLIPCOLOR_RED))
					{
						static bool bShoot = false;
						bShoot = !bShoot;
						if (bShoot)
						{
							static Hash weaponList[] = { WEAPON_ADVANCEDRIFLE, WEAPON_APPISTOL, WEAPON_ASSAULTRIFLE, WEAPON_ASSAULTSMG, WEAPON_CARBINERIFLE, WEAPON_COMBATMG, WEAPON_COMBATPDW, WEAPON_COMBATPISTOL, WEAPON_HEAVYPISTOL, WEAPON_HEAVYSNIPER, WEAPON_MARKSMANRIFLE, WEAPON_MG, WEAPON_MICROSMG, WEAPON_PISTOL, WEAPON_PISTOL50, WEAPON_SMG, WEAPON_SNIPERRIFLE, WEAPON_SNSPISTOL, WEAPON_SPECIALCARBINE, WEAPON_MINIGUN };
							if (blip->fScale == 1.0f)
								FIRE::ADD_OWNED_EXPLOSION(playerPed, blip->x, blip->y, blip->z, EXPLOSION_TANKER, 1000.0f, FALSE, TRUE, 0.0f);
							else
								GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(blip->x + 0.1f, blip->y, blip->z - 0.15f, blip->x - 0.1f, blip->y, blip->z + 1, 1000, TRUE, weaponList[rand() % (sizeof(weaponList) / 4)], playerPed, TRUE, TRUE, 1.0f); //FWARRRRRRAING! ~benji Alaska 2277
						}
					}
					if ((blip->dwColor == BLIPCOLOR_NONE && (blip->iIcon == BLIP_HELIBLADESENEMY || blip->iIcon == BLIP_COPHELICOPTER)) ||
						(blip->dwColor == BLIPCOLOR_RED && (blip->iIcon == BLIP_PLANE || blip->iIcon == BLIP_MOTORCYCLE || blip->iIcon == BLIP_CAR || blip->iIcon == BLIP_HELICOPTER || blip->iIcon == BLIP_JET2 || blip->iIcon == BLIP_HELICOPTERBLADES || blip->iIcon == BLIP_PLANEVEHICLE)))
					{
						FIRE::ADD_OWNED_EXPLOSION(playerPed, blip->x, blip->y, blip->z, EXPLOSION_TANKER, 1000.0f, FALSE, TRUE, 0.0f);
					}
				}
			}
		}
	}	
}

void PlayerGodmode(Player player, Entity playerPed, bool GodModeOn)
{
	PLAYER::SET_PLAYER_INVINCIBLE(player, GodModeOn);
	ENTITY::SET_ENTITY_PROOFS(playerPed, GodModeOn, GodModeOn, GodModeOn, GodModeOn, GodModeOn, GodModeOn, GodModeOn, GodModeOn);
	PED::SET_PED_CAN_RAGDOLL(playerPed, !GodModeOn);
	PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, !GodModeOn);
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
	{
		VehicleGodmode(playerPed, GodModeOn);
	}
}

bool GodMode(Player player, Ped playerPed, bool bGodmodeActive, bool bGodmodeSwitchset)
{
	if (bGodmodeActive)
	{
		if (!bGodmodeSwitchset)
		{
			DEBUGOUT("Setting godmode");
			drawNotification("Activating godmode");
			PlayerGodmode(player, playerPed, true);
			PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));

			bGodmodeSwitchset = true;
		}
		else if (!PLAYER::GET_PLAYER_INVINCIBLE(player)) 
		{
			PlayerGodmode(player, playerPed, true);
			PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
		}
		
	}
	else if (!bGodmodeActive)
	{
		if (bGodmodeSwitchset)
		{
			DEBUGOUT("Deactivating godmode");
			drawNotification("Deactivating godmode");
			PlayerGodmode(player, playerPed, false);
			bGodmodeSwitchset = false;
		}
		else if (PLAYER::GET_PLAYER_INVINCIBLE(player))
		{	// bugfix for random godmode active
			PlayerGodmode(player, playerPed, false);
		}
	}
	return bGodmodeSwitchset;
}


void IncreaseWantedLevel(Player player)
{
	if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
	{
		PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, FALSE);
		PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
		drawNotification("Wanted-level up");
	}
}

void ClearWantedLevel(Player player)
{
	PLAYER::SET_PLAYER_WANTED_LEVEL(player, 0, FALSE);
	PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
	drawNotification("Wanted cleared");
}

void ReplenishAmmo(Ped playerPed)
{
	Hash currentWeapon;
	//Infinite Ammo - Get max ammo
	if (WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &currentWeapon, 1))
	{
		if (WEAPON::IS_WEAPON_VALID(currentWeapon))
		{
			int maxAmmo;
			if (WEAPON::GET_MAX_AMMO(playerPed, currentWeapon, &maxAmmo))
			{
				WEAPON::SET_PED_AMMO(playerPed, currentWeapon, maxAmmo);
			}
		}
	}
}

void EnableRestrictedZones(bool featureRestrictedZones)
{
	if (!featureRestrictedZones)
	{
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("am_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("restrictedareas");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_armybase");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_lossantosintl");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prison");
		GAMEPLAY::TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("re_prisonvanbreak");
	}
}


void SpectatePlayer(Ped playerped)
{
	Any SpectateCam;

	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerped, FALSE);
	SpectateCam = CAM::CREATE_CAM_WITH_PARAMS("DEFAULT_SCRIPTED_FLY_CAMERA", playerPosition.x, playerPosition.y, playerPosition.z, 0.0, 0.0, 0.0, 50.0, 0, 2);
	CAM::ATTACH_CAM_TO_ENTITY(SpectateCam, playerped, 0, -5, 1, 1);
	//CAM::ATTACH_CAM_TO_PED_BONE(hi, selectedPed, 0, 0, -5, 1, 1);
	//CAM::POINT_CAM_AT_PED_BONE(hi, selectedPed, 0, 0, 0.7, 0, 1);
	//CAM::SET_CAM_FOV(hi, 50.0);
	CAM::SET_CAM_ACTIVE(playerped, 1);
}
void SpectateMode(bool Active, Ped selectedPed)
{
	NETWORK::NETWORK_SET_IN_SPECTATOR_MODE(Active, selectedPed);
}


void BreatheFire(Ped selectedPed)
{
	Vector3 Mouth = PED::GET_PED_BONE_COORDS(selectedPed, SKEL_ROOT, 0.1f , 0.0f, 0.0f);
	FIRE::_ADD_SPECFX_EXPLOSION(Mouth.x, Mouth.y, Mouth.z, EXPLOSION_DIR_FLAME, EXPLOSION_DIR_FLAME, 1.0f, true, true, 0.0f);
}


void CrashPlayer(Ped selectedPed)
{
	const int maxPeds = 40;
	Ped ClonedPed[maxPeds];
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Vector3 selectedPedPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
	Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);


	// check distance so i dont crash myself
	if (GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(playerPosition.x, playerPosition.y, playerPosition.z, selectedPedPosition.x, selectedPedPosition.y, selectedPedPosition.z, false) > 250.0f)
	{
		if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
		}

		//spawn peds
		for (int i = 0; i < maxPeds; i++)
		{
			ClonedPed[i] = PED::CLONE_PED(selectedPed, 0.0f, false, false);
		}
		//I may need a wait function?

		//and delete the evidence
		for (int i = 0; i < maxPeds; i++)
		{
			PED::DELETE_PED(&ClonedPed[i]);
		}
	}
}

void PlayerInvisible(bool Invisible)
{
	if (Invisible)
	{
		NETWORK::SET_LOCAL_PLAYER_INVISIBLE_LOCALLY(false);
	}
	else
	{
		NETWORK::SET_LOCAL_PLAYER_VISIBLE_LOCALLY(false);
	}	
}