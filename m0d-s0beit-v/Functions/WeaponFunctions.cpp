#include "../stdafx.h"
//weaponfunctions

void BruteForceWeaponAddons(Ped ped, Hash weaponHash, bool bSilencer)
{
	//Since only I get these anyway, might as well craft it for me.
	static Hash weaponAddons[] = { COMPONENT_AT_SCOPE_MACRO, COMPONENT_AT_SCOPE_MACRO_02, COMPONENT_AT_SCOPE_SMALL, COMPONENT_AT_SCOPE_SMALL_02, COMPONENT_AT_SCOPE_MEDIUM, COMPONENT_AT_SCOPE_LARGE, COMPONENT_AT_SCOPE_MAX, COMPONENT_AT_RAILCOVER_01, COMPONENT_AT_AR_AFGRIP, COMPONENT_AT_PI_FLSH, COMPONENT_AT_AR_FLSH, COMPONENT_PISTOL_CLIP_02, COMPONENT_COMBATPISTOL_CLIP_02, COMPONENT_APPISTOL_CLIP_02, COMPONENT_MICROSMG_CLIP_02, COMPONENT_SMG_CLIP_02, COMPONENT_ASSAULTRIFLE_CLIP_02, COMPONENT_CARBINERIFLE_CLIP_02, COMPONENT_ADVANCEDRIFLE_CLIP_02, COMPONENT_MG_CLIP_02, COMPONENT_COMBATMG_CLIP_02, COMPONENT_ASSAULTSHOTGUN_CLIP_02, COMPONENT_PISTOL50_CLIP_02, COMPONENT_ASSAULTSMG_CLIP_02, COMPONENT_SNSPISTOL_CLIP_02, COMPONENT_COMBATPDW_CLIP_02, COMPONENT_HEAVYPISTOL_CLIP_02, COMPONENT_SPECIALCARBINE_CLIP_02, COMPONENT_BULLPUPRIFLE_CLIP_02, COMPONENT_VINTAGEPISTOL_CLIP_02, COMPONENT_MARKSMANRIFLE_CLIP_02, COMPONENT_HEAVYSHOTGUN_CLIP_02, COMPONENT_GUSENBERG_CLIP_02 };
	for each (Hash addonHash in weaponAddons)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(weaponHash, addonHash))
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, addonHash);
	}
	if (bSilencer)
	{
		//static Hash silencers[] = { COMPONENT_AT_PI_SUPP, COMPONENT_AT_PI_SUPP_02, COMPONENT_AT_AR_SUPP, COMPONENT_AT_SR_SUPP, COMPONENT_AT_AR_SUPP_02 };
		static Hash silencers[] = { COMPONENT_AT_PI_SUPP_02, COMPONENT_AT_AR_SUPP };
		for each (Hash silencerHash in silencers)
		{
			if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(weaponHash, silencerHash)) {
				if (weaponHash != WEAPON_ADVANCEDRIFLE && WEAPON::GET_WEAPONTYPE_GROUP(weaponHash) != WEAPON_TYPE_GROUP_SHOTGUN)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, silencerHash);
			}
		}
		if (weaponHash == WEAPON_SNIPERRIFLE || weaponHash == WEAPON_MICROSMG)
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, COMPONENT_AT_AR_SUPP_02);
	}
}

void GiveAllWeaponsToPed(Ped ped, WeaponTints weaponTint, bool removeWeaponsFirst)
{
	if (removeWeaponsFirst)
		WEAPON::REMOVE_ALL_PED_WEAPONS(ped, TRUE);
	static Hash weaponList[] = { WEAPON_ADVANCEDRIFLE, WEAPON_APPISTOL, WEAPON_ASSAULTRIFLE, WEAPON_ASSAULTSHOTGUN, WEAPON_ASSAULTSMG, WEAPON_BALL, WEAPON_BAT, WEAPON_BOTTLE, WEAPON_BULLPUPSHOTGUN, WEAPON_CARBINERIFLE, WEAPON_COMBATMG, WEAPON_COMBATPDW, WEAPON_COMBATPISTOL, WEAPON_CROWBAR, WEAPON_DAGGER, WEAPON_FIREEXTINGUISHER, WEAPON_FIREWORK, WEAPON_FLAREGUN, WEAPON_GOLFCLUB, WEAPON_GRENADE, WEAPON_GRENADELAUNCHER, WEAPON_GUSENBERG, WEAPON_HAMMER, WEAPON_HEAVYPISTOL, WEAPON_HEAVYSHOTGUN, WEAPON_HEAVYSNIPER, WEAPON_HOMINGLAUNCHER, WEAPON_KNIFE, WEAPON_MARKSMANRIFLE, WEAPON_MG, WEAPON_MICROSMG, WEAPON_MOLOTOV, WEAPON_MUSKET, WEAPON_NIGHTSTICK, WEAPON_PETROLCAN, WEAPON_PISTOL, WEAPON_PISTOL50, WEAPON_PROXMINE, WEAPON_PUMPSHOTGUN, WEAPON_RPG, WEAPON_SAWNOFFSHOTGUN, WEAPON_SMG, WEAPON_SMOKEGRENADE, WEAPON_SNIPERRIFLE, WEAPON_SNOWBALL, WEAPON_SNSPISTOL, WEAPON_SPECIALCARBINE, WEAPON_STICKYBOMB, WEAPON_STUNGUN, WEAPON_VINTAGEPISTOL, WEAPON_MINIGUN };
	for each (Hash weapon in weaponList)
	{
		int maxAmmo;
		if (WEAPON::HAS_PED_GOT_WEAPON(ped, weapon, FALSE) == FALSE)
		{
			WEAPON::GIVE_WEAPON_TO_PED(ped, weapon, (WEAPON::GET_MAX_AMMO(ped, weapon, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, TRUE);
			BruteForceWeaponAddons(ped, weapon, true); //This doesn't work for people who are not the player running the commands. You can take their weapons, but if you try to add attachments? FUCK YOU! I AIIIIIIIINNN'T HAVIN' THAT SHIT!
			WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, weapon, ((weapon == WEAPON_MINIGUN) || (weapon == WEAPON_SPECIALCARBINE)) ? WEAPONTINT_PLATINUM : WEAPONTINT_LSPD);
		}
		if (WEAPON::GET_WEAPONTYPE_GROUP(weapon) == WEAPON_TYPE_GROUP_THROWABLE)
		{
			WEAPON::REMOVE_WEAPON_FROM_PED(ped, weapon);
			WEAPON::GIVE_WEAPON_TO_PED(ped, weapon, (WEAPON::GET_MAX_AMMO(ped, weapon, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, TRUE);
		}
	}
}

void CheckAndSelectWeapon(Ped ped, Hash weaponHash)
{
	if (WEAPON::HAS_PED_GOT_WEAPON(ped, weaponHash, 0) == FALSE) //If some fucking cunt took our weapons, give them back.
	{
		int maxAmmo;
		WEAPON::GIVE_WEAPON_TO_PED(ped, weaponHash, (WEAPON::GET_MAX_AMMO(ped, weaponHash, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, TRUE);
		WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, weaponHash, (weaponHash == WEAPON_MINIGUN) ? WEAPONTINT_PLATINUM : WEAPONTINT_LSPD);
		BruteForceWeaponAddons(ped, weaponHash, true);
	}
	WEAPON::SET_CURRENT_PED_WEAPON(ped, weaponHash, TRUE);
}

void FlowerPower(Ped selectedPed) 
{
	//function not working
	Hash modelHashes[] = {
		-901521477,//prop_pot_plant_02a
		-1878463678,//prop_pot_plant_02b	
		1558349046,//prop_pot_plant_02c 
		-1299468213,//prop_pot_plant_02d	
		-1860309428,//prop_pot_plant_03a	
		2139768797,//prop_pot_plant_04a 
		-1304172382,//prop_pot_plant_05d_l1 
		-1491050248//prop_pot_plant_bh1 
	};
	for each (Hash modelHash in modelHashes)
	{
		//load all the models
		if (!STREAMING::HAS_MODEL_LOADED(modelHash))
		{
			STREAMING::REQUEST_MODEL(modelHash);
			drawNotification(std::to_string(modelHash) + " loaded");
		}
	}
	//debugstart
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	Ped debugPed;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE)){
		debugPed = PED::GET_VEHICLE_PED_IS_USING(playerPed);
	}
	else {
		debugPed = playerPed;
	}

	//debugend
	Vector3 lastHitCoordinate;
		if (PED::IS_PED_SHOOTING(selectedPed))
		{
			if (WEAPON::GET_PED_LAST_WEAPON_IMPACT_COORD(selectedPed, &lastHitCoordinate))
			{
				//debugstart
				Vector3 playerCoordinate = ENTITY::GET_ENTITY_COORDS(debugPed, FALSE); //Dereck B? On your bike!
				float playerHeading = ENTITY::GET_ENTITY_HEADING(debugPed);

				Log::Msg("Hit found!");
				//player coordinates
				Log::Msg("pedcoordinates:");
				Log::Msg((" x: " + std::to_string(playerCoordinate.x) + " y: " + std::to_string(playerCoordinate.y) + " z: " + std::to_string(playerCoordinate.z) + " heading: " + std::to_string(playerHeading)).c_str());
				//hitpoint coordinates
				Log::Msg("hitcoordinates:");
				Log::Msg((" x: " + std::to_string(lastHitCoordinate.x) + " y: " + std::to_string(lastHitCoordinate.y) + " z: " + std::to_string(lastHitCoordinate.z)).c_str());
				//other vars
				Log::Msg("dwordcoordinates:");
				Log::Msg((" x: " + std::to_string(lastHitCoordinate._paddingx) + " y: " + std::to_string(lastHitCoordinate._paddingy) + " z: " + std::to_string(lastHitCoordinate._paddingz)).c_str());
				//debugend

				//lastHitCoordinate.x = Loc[0], lastHitCoordinate.y = Loc[1], lastHitCoordinate.z = Loc[2];

				drawNotification("shots found");
				//lastHitCoordinate.x, lastHitCoordinate.y, lastHitCoordinate.z = 0.0f;

				drawNotification("hit at x: " + std::to_string(lastHitCoordinate.x) + "y: " + std::to_string(lastHitCoordinate.y) + "z: " + std::to_string(lastHitCoordinate.z));
				Object junkObject = OBJECT::CREATE_OBJECT(modelHashes[rand() % 7], lastHitCoordinate.x, lastHitCoordinate.y, lastHitCoordinate.z, 1, 1, 0);
			}
		}
		
}

void FastReload(Ped playerPed)
{
	Hash currentWeapon;
	WEAPON::GET_CURRENT_PED_WEAPON(playerPed, &currentWeapon, 1);

	Vehicle playerVeh;
	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
		playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

	if (WEAPON::IS_WEAPON_VALID(currentWeapon) && WEAPON::GET_WEAPONTYPE_GROUP(currentWeapon) == WEAPON_TYPE_GROUP_PISTOL && playerVeh == NULL) //Only pistols need this. #ONLY90SKIDSREMBERTHINGSFROMTHE90S
	{
		int clipazine, maxAmmo;
		WEAPON::GET_AMMO_IN_CLIP(playerPed, currentWeapon, &clipazine); //m8 do you even 30 caliber assault magazine clips?
		maxAmmo = WEAPON::GET_MAX_AMMO_IN_CLIP(playerPed, currentWeapon, TRUE);
		if (clipazine != maxAmmo)
		{
			keybd_event(0x52, 0, KEYEVENTF_KEYUP, 0); //We need to jitter the game's listener for the R key for one frame.
			WEAPON::SET_AMMO_IN_CLIP(playerPed, currentWeapon, 0);
		}
	}
}

