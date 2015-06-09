#include "stdafx.h"
#include "natives.h"

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

void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
{
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
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

void BruteForceWeaponAddons(Ped ped, Hash weaponHash, bool bSilencer )
{
	//Since only I get these anyway, might as well craft it for me.
	static Hash weaponAddons[] = { COMPONENT_AT_SCOPE_MACRO, COMPONENT_AT_SCOPE_MACRO_02, COMPONENT_AT_SCOPE_SMALL, COMPONENT_AT_SCOPE_SMALL_02, COMPONENT_AT_SCOPE_MEDIUM, COMPONENT_AT_SCOPE_LARGE, COMPONENT_AT_SCOPE_MAX, COMPONENT_AT_RAILCOVER_01, COMPONENT_AT_AR_AFGRIP, COMPONENT_AT_PI_FLSH, COMPONENT_AT_AR_FLSH, COMPONENT_PISTOL_CLIP_02, COMPONENT_COMBATPISTOL_CLIP_02, COMPONENT_APPISTOL_CLIP_02, COMPONENT_MICROSMG_CLIP_02, COMPONENT_SMG_CLIP_02, COMPONENT_ASSAULTRIFLE_CLIP_02, COMPONENT_CARBINERIFLE_CLIP_02, COMPONENT_ADVANCEDRIFLE_CLIP_02, COMPONENT_MG_CLIP_02, COMPONENT_COMBATMG_CLIP_02, COMPONENT_ASSAULTSHOTGUN_CLIP_02, COMPONENT_PISTOL50_CLIP_02, COMPONENT_ASSAULTSMG_CLIP_02, COMPONENT_SNSPISTOL_CLIP_02, COMPONENT_HEAVYPISTOL_CLIP_02, COMPONENT_SPECIALCARBINE_CLIP_02, COMPONENT_BULLPUPRIFLE_CLIP_02, COMPONENT_VINTAGEPISTOL_CLIP_02, COMPONENT_MARKSMANRIFLE_CLIP_02, COMPONENT_HEAVYSHOTGUN_CLIP_02, COMPONENT_GUSENBERG_CLIP_02 };
	for each (Hash addonHash in weaponAddons)
	{
		if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(weaponHash, addonHash))
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, addonHash);
	}
	if (bSilencer)
	{
		//static Hash silencers[] = { COMPONENT_AT_PI_SUPP, COMPONENT_AT_PI_SUPP_02, COMPONENT_AT_AR_SUPP, COMPONENT_AT_SR_SUPP, COMPONENT_AT_AR_SUPP_02 };
		static Hash silencers[] = { COMPONENT_AT_PI_SUPP_02, COMPONENT_AT_AR_SUPP, COMPONENT_AT_SR_SUPP };
		for each (Hash silencerHash in silencers)
		{
			if (WEAPON::_CAN_WEAPON_HAVE_COMPONENT(weaponHash, silencerHash)) {
				if (weaponHash != WEAPON_ADVANCEDRIFLE)
					WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, silencerHash);
			}
		}
		if (weaponHash == WEAPON_SNIPERRIFLE )
			WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weaponHash, COMPONENT_AT_AR_SUPP_02);
	}
}

void GiveAllWeaponsToPed(Ped ped, WeaponTints weaponTint, bool removeWeaponsFirst )
{
	if (removeWeaponsFirst)
		WEAPON::REMOVE_ALL_PED_WEAPONS(ped, TRUE);
	static Hash weaponList[] = { WEAPON_ADVANCEDRIFLE, WEAPON_APPISTOL, WEAPON_ASSAULTRIFLE, WEAPON_ASSAULTSHOTGUN, WEAPON_ASSAULTSMG, WEAPON_BALL, WEAPON_BAT, WEAPON_BOTTLE, WEAPON_BULLPUPSHOTGUN, WEAPON_CARBINERIFLE, WEAPON_COMBATMG, WEAPON_COMBATPISTOL, WEAPON_CROWBAR, WEAPON_DAGGER, WEAPON_FIREEXTINGUISHER, WEAPON_FIREWORK, WEAPON_FLAREGUN, WEAPON_GOLFCLUB, WEAPON_GRENADE, WEAPON_GRENADELAUNCHER, WEAPON_GUSENBERG, WEAPON_HAMMER, WEAPON_HEAVYPISTOL, WEAPON_HEAVYSHOTGUN, WEAPON_HEAVYSNIPER, WEAPON_HOMINGLAUNCHER, WEAPON_KNIFE, WEAPON_MARKSMANRIFLE, WEAPON_MG, WEAPON_MICROSMG, WEAPON_MOLOTOV, WEAPON_MUSKET, WEAPON_NIGHTSTICK, WEAPON_PETROLCAN, WEAPON_PISTOL, WEAPON_PISTOL50, WEAPON_PROXMINE, WEAPON_PUMPSHOTGUN, WEAPON_RAILGUN, WEAPON_RPG, WEAPON_SAWNOFFSHOTGUN, WEAPON_SMG, WEAPON_SMOKEGRENADE, WEAPON_SNIPERRIFLE, WEAPON_SNOWBALL, WEAPON_SNSPISTOL, WEAPON_SPECIALCARBINE, WEAPON_STICKYBOMB, WEAPON_STUNGUN, WEAPON_VINTAGEPISTOL, WEAPON_MINIGUN };
	for each (Hash var in weaponList)
	{
		int maxAmmo;
		if (WEAPON::HAS_PED_GOT_WEAPON(ped, var, FALSE) == FALSE)
		{
			WEAPON::GIVE_WEAPON_TO_PED(ped, var, (WEAPON::GET_MAX_AMMO(ped, var, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, TRUE);
			BruteForceWeaponAddons(ped, var, true); //This doesn't work for people who are not the player running the commands. You can take their weapons, but if you try to add attachments? FUCK YOU! I AIIIIIIIINNN'T HAVIN' THAT SHIT!
			WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, var, ((var == WEAPON_MINIGUN) || (var == WEAPON_SPECIALCARBINE)) ? WEAPONTINT_PLATINUM : WEAPONTINT_LSPD);
		}
		else if (WEAPON::GET_WEAPONTYPE_GROUP(var) == WEAPON_TYPE_GROUP_THROWABLE)
		{
			WEAPON::REMOVE_WEAPON_FROM_PED(ped, var);
			WEAPON::GIVE_WEAPON_TO_PED(ped, var, (WEAPON::GET_MAX_AMMO(ped, var, &maxAmmo) == TRUE) ? maxAmmo : 9999, FALSE, TRUE);
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
		BruteForceWeaponAddons(ped, weaponHash, false);
	}
	WEAPON::SET_CURRENT_PED_WEAPON(ped, weaponHash, TRUE);
}

void BoostBaseCarStats(Vehicle vehicle)
{
	VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0); //IDK what this does, but I guess it allows individual mods to be added? It's what the game does before calling SET_VEHICLE_MOD.
	VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
	BOOL IsRCtrlUp = !(GetAsyncKeyState(VK_RCONTROL) & 0x8000);
	//ENTITY::SET_ENTITY_INVINCIBLE(vehicle, IsRCtrlUp); //That should do the trick.
	ENTITY::SET_ENTITY_PROOFS(vehicle, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp, IsRCtrlUp);
	//VEHICLE::SET_VEHICLE_STRONG(vehicle, TRUE); //2stronk
	//VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(vehicle, TRUE); //6stronk9meme
	VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, FALSE); //What seems to be the officer, problem? *le9gagmemeface*
	VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, FALSE); //Bulletproof Tires.
	//VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(vehicle, FALSE); //I don't think this really works, but fuck it. Call it anyway.
	//VEHICLE::SET_VEHICLE_CAN_BREAK(vehicle, FALSE); //Hopefully this fixes the car blowing up after getting hit by a train...
	//VEHICLE::SET_VEHICLE_ENGINE_CAN_DEGRADE(vehicle, FALSE);
	VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ENGINE, MOD_INDEX_FOUR, FALSE); //6fast9furious
	VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_BRAKES, MOD_INDEX_THREE, FALSE); //GOTTA STOP FAST
	VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_TRANSMISSION, MOD_INDEX_THREE, FALSE); //Not when I shift in to MAXIMUM OVERMEME!
	VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_SUSPENSION, MOD_INDEX_FOUR, FALSE); //How low can you go?
	VEHICLE::SET_VEHICLE_MOD(vehicle, MOD_ARMOR, MOD_INDEX_FIVE, FALSE); //100% armor.
	//VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, "GUT_HAKT"); // Custom plate
	VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, MOD_TURBO, TRUE); //Forced induction huehuehue
	VEHICLE::_SET_VEHICLE_HEALTH(vehicle, 1000.0f); //This is what the game does
}

Vehicle ClonePedCar(Ped ped, Ped playerPed)
{
	Vehicle pedVeh = NULL;
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
		VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
		int primaryColor, secondaryColor;
		VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
		VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
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
		int neonColor[3];
		VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
		VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
		VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
	}
	return pedVeh;
}

void SetIntStatWithBothVarients(const char* chStatName, int value, int characterIndex)
{
	char chBuffer[50];
	sprintf_s(chBuffer, "MP%i_%s", characterIndex, chStatName);
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(chBuffer), value, TRUE);
	chBuffer[0] = 'm';
	chBuffer[1] = 'p';
	STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY(chBuffer), value, TRUE);
}

void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool bDrawRect = true, bool rescaleText = true)
{
	// default values
	int text_col[4] = { 255, 255, 255, 255 },
		rect_col[4] = { 70, 95, 95, 255 };
	float text_scale = 0.30f;
	int font = 0; //Maybe make this a parameter in the future.

	// correcting values for active line
	if (active)
	{
		text_col[0] = 0;
		text_col[1] = 0;
		text_col[2] = 0;

		rect_col[0] = 218;
		rect_col[1] = 242;
		rect_col[2] = 216;

		if (rescaleText) text_scale = 0.40f;
	}

	if (title)
	{
		rect_col[0] = 0;
		rect_col[1] = 0;
		rect_col[2] = 0;

		if (rescaleText) text_scale = 0.50;
		font = 1;
	}

	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

	textLeft += lineLeft;

	float lineWidthScaled = lineWidth / (float)screen_w; // line width
	float lineTopScaled = lineTop / (float)screen_h; // line top offset
	float textLeftScaled = textLeft / (float)screen_w; // text left offset
	float lineHeightScaled = lineHeight / (float)screen_h; // line height

	float lineLeftScaled = lineLeft / (float)screen_w;

	// text upper part
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING((LPSTR)caption.c_str());
	UI::_DRAW_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

	int num25 = UI::_0x9040DFB09BE75706(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	float num26 = UI::_0xDB88A37483346780(text_scale, 0);

	if (bDrawRect)
		draw_rect(lineLeftScaled, lineTopScaled + (0.007f), lineWidthScaled, ((((float)(num25)*num26) + (lineHeightScaled * 2.0f)) + 0.005f), rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}

void draw_text(float x, float y, char* chSampleText, color_t color)
{
	UI::SET_TEXT_FONT(0);
	UI::SET_TEXT_SCALE(0.0, 0.25f);
	UI::SET_TEXT_COLOUR(color.red, color.green, color.blue, color.alpha); //White
	UI::SET_TEXT_CENTRE(0);
	UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(chSampleText);
	UI::_DRAW_TEXT(x, y);
}
//Function to determine if a Player object is on your Rockstar Social Club friends list.
BOOL IsPlayerFriend(Player player)
{
	int handle[76]; //var num3 = sub_34009(A_0, (A_1) + 264, (A_1) + 272);
	NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle[0], 13);
	if (NETWORK::NETWORK_IS_HANDLE_VALID(&handle[0], 13))
	{
		return NETWORK::NETWORK_IS_FRIEND(&handle[0]);
	}
	Log::Error("Bad handle on %i", player);
	return FALSE;
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
		if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(vehicle, 0)) {
			int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(vehicle);
			if (convertableState == 0 || convertableState == 3 || convertableState == 5)
				Log::Msg("VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, TRUE);");
			else
				Log::Msg("VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, TRUE);");
		}
	}
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

eThreadState new_Run(GtaThread* This) {
	rage::scrThread* runningThread = GetActiveThread();
	SetActiveThread(This); //Set the active thread to our hijacked thread.

	//Anything after here is fair game for you to run whatever natives you want.
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	//static bool bQuit, F12 = false;
	//if (isKeyPressedOnce(F12, VK_F12)){ bQuit = true;}
	//if (bQuit) { return gGtaThreadOriginal.Run(This); }

	//godmode function
	static bool bGodmodeActive, bF8Pressed = false;
	if (bGodmodeActive)
	{
		draw_menu_line("Godmode active", 150.0f, 4.0f, 13.0f, 0.0f, 5.0f, false, false, false, false);
		//Godmode
		if (!PLAYER::GET_PLAYER_INVINCIBLE(player))
		{
			DEBUGOUT("Setting godmode");
			PLAYER::SET_PLAYER_INVINCIBLE(player, true);
			ENTITY::SET_ENTITY_PROOFS(playerPed, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE);
			PED::SET_PED_CAN_RAGDOLL(playerPed, FALSE);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, FALSE);
		}

		//Max armor.
		PED::ADD_ARMOUR_TO_PED(playerPed, PLAYER::GET_PLAYER_MAX_ARMOUR(player) - PED::GET_PED_ARMOUR(playerPed));
	}
	else{
		draw_menu_line("Godmode inactive", 150.0f, 4.0f, 13.0f, 0.0f, 5.0f, false, false, false, false);
		if (PLAYER::GET_PLAYER_INVINCIBLE(player))
		{
			DEBUGOUT("Deactivating godmode");
			PLAYER::SET_PLAYER_INVINCIBLE(player, false);
			ENTITY::SET_ENTITY_PROOFS(playerPed, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
			PED::SET_PED_CAN_RAGDOLL(playerPed, TRUE);
			PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, TRUE);
		}
	}
	
	static bool bHackActive, bF7Pressed = false;
	if (isKeyPressedOnce(bF7Pressed, VK_F7))
	{
		bHackActive = !bHackActive;
	}
	if (!bHackActive)
	{
		//housekeeping of vars
		bGodmodeActive = false;
		draw_menu_line("Hack inactive", 150.0f, 4.0f, 0.0f, 0.0f, 5.0f, false, false, false, false);
	}
	else {
		if (ENTITY::DOES_ENTITY_EXIST(playerPed) == TRUE)
		{
			Hash currentWeapon;
			Vehicle playerVeh = NULL;

			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
				playerVeh = PED::GET_VEHICLE_PED_IS_USING(playerPed);

			//Test that drawing works.
			draw_menu_line("Hack active", 150.0f, 4.0f, 0.0f, 0.0f, 5.0f, false, false, false, false);
			draw_menu_line("s0biet by gir489 - mch8-6-2015 ", 15.0f, 4.0f, 0.0f, 550.0f, 5.0f, false, false, false);

			static bool bMenuActive, bF3Pressed = false;
			static int iFreeze = -1;
			if (isKeyPressedOnce(bF3Pressed, VK_F3))
			{
				iFreeze = -1;
				bMenuActive = !bMenuActive;
			}
			bool bReset = false;
			if (bMenuActive)
			{
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
				for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
				{
					bool bSelectedPed = (playerIterator == iSelectedPlayer);
					if (bSelectedPed)
						selectedPed = PLAYER::GET_PLAYER_PED(playerIterator);
					Ped pedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
					if (ENTITY::DOES_ENTITY_EXIST(pedIterator))
					{
						char chStringToDraw[50];
						strcpy_s(chStringToDraw, PLAYER::GET_PLAYER_NAME(playerIterator));
						if (bSelectedPed)
							sprintf_s(chStringToDraw, "%s F:%i", chStringToDraw, iFreeze == selectedPed);
						draw_menu_line(chStringToDraw, 150.0f, 4.0f, 25.0f + iLineNum * 13.0f, 350.0f, 0.0f, false, false, bSelectedPed, false);
						iLineNum++;
					}
				}

				static bool bDividePressed = false;
				if (isKeyPressedOnce(bDividePressed, VK_DIVIDE))
				{
					GiveAllWeaponsToPed(selectedPed, WEAPONTINT_LSPD, selectedPed == playerPed);
				}

				static bool bDecimalPressed = false;
				if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL) && selectedPed != playerPed)
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{
						Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
						for (int i = SEAT_BACKPASSENGER; i >= SEAT_DRIVER; i--)
						{
							PED::SET_PED_INTO_VEHICLE(playerPed, selectedVehicle, i);
						}
					}
					Entity attachedEnt = ENTITY::GET_ENTITY_ATTACHED_TO(selectedPed);
					if (ENTITY::DOES_ENTITY_EXIST(attachedEnt))
					{
						if (ENTITY::IS_ENTITY_A_VEHICLE(attachedEnt) == FALSE)
							ENTITY::DELETE_ENTITY(&attachedEnt);
					}
				}

				//Teleport to selected player on the menu.
				static bool bNumpad0Pressed = false;
				if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0) && selectedPed != playerPed)
				{
					Entity e = playerPed;
					if (playerVeh != NULL)
						e = playerVeh;

					Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, playerPosition.x, playerPosition.y, playerPosition.z + 1, FALSE, FALSE, TRUE);
				}

				//https://www.youtube.com/watch?v=ON-7v4qnHP8
				if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
				{
					try
					{
						static bool bLoadsAMoney = false;
						bLoadsAMoney = !bLoadsAMoney;
						if (bLoadsAMoney)
						{
								//money bag has hash 0x113FD533
							STREAMING::REQUEST_MODEL(0x113FD533); //Manchester United: Nil Loadsamoney United: LOADS
							if (STREAMING::HAS_MODEL_LOADED(0x113FD533)) //Good evening and welcome to: Loads of Money.
							{
								Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE); //Dereck B? On your bike!
								static Hash PICKUP_MONEY_CASE = GAMEPLAY::GET_HASH_KEY("PICKUP_MONEY_CASE"); //Right. Let's do up the house.
								int MONEY_DROP_AMOUNT = rand() % 35000 + 25000; // lets make it more random so r* wont recognize a pattern mch
								OBJECT::CREATE_AMBIENT_PICKUP(PICKUP_MONEY_CASE, playerPosition.x, playerPosition.y, playerPosition.z + 0.5f, 0, MONEY_DROP_AMOUNT, 0x113FD533, FALSE, TRUE); //WHOP YOUR WAD ON THE COUNTA
								STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x113FD533); //SHUT YOUR MOUTH!
							}
						}
					}
					catch (...){ Log::Error("Got too much money."); }
				}

				static bool bNumpad2Pressed = false;
				if (isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2))
				{
					Vehicle clonedVeh = ClonePedCar(selectedPed, playerPed);
					BoostBaseCarStats(clonedVeh); //Gotta go fast
				}

				//set off alarm of another players car
				static bool bNumpad4Pressed = false;
				if (isKeyPressedOnce(bNumpad4Pressed, VK_NUMPAD4))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(selectedPed);
						Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
						VEHICLE::SET_VEHICLE_ALARM(selectedVehicle, true);
						VEHICLE::START_VEHICLE_ALARM(selectedVehicle);
						//notify user of action
						UI::_SET_NOTIFICATION_TEXT_ENTRY("Set off alarm of vehicle");
						UI::_DRAW_NOTIFICATION(FALSE, TRUE);
					}
				}

				//Change plate of another players car
				static bool bNumpad5Pressed = false;
				if (isKeyPressedOnce(bNumpad5Pressed, VK_NUMPAD5))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{	
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(selectedPed);
						Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
						VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(selectedVehicle, "Gut_Hakt");
						//notify user of action
						UI::_SET_NOTIFICATION_TEXT_ENTRY("Changed license plate to Gut_Hakt");
						UI::_DRAW_NOTIFICATION(FALSE, TRUE);
					}
				}

				//Kill the engine of another players car
				static bool bNumpad6Pressed = false;
				if (isKeyPressedOnce(bNumpad6Pressed, VK_NUMPAD6))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(selectedPed);
						Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
						VEHICLE::SET_VEHICLE_ENGINE_HEALTH(selectedVehicle, 0.0);
						VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(selectedVehicle, 0.0);
						//notify user of action
						UI::_SET_NOTIFICATION_TEXT_ENTRY("Ruined Engine and fuel tank");
						UI::_DRAW_NOTIFICATION(FALSE, TRUE);
					}
				}

				//Burst all the tires of another players car
				static bool bNumpad7Pressed = false;
				if (isKeyPressedOnce(bNumpad7Pressed, VK_NUMPAD7))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{
						//fuck up the tires
						Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(selectedPed); //requesting permission to fuck up another player
						static int tireID = 0;
						for (tireID = 0; tireID < 8; tireID++) {
							VEHICLE::SET_VEHICLE_TYRE_BURST(selectedVehicle, tireID, true, 1000.0);
						}
						//notify user of action
						UI::_SET_NOTIFICATION_TEXT_ENTRY("Bursted tires");
						UI::_DRAW_NOTIFICATION(FALSE, TRUE);
					}
				}

				//Remove player from vehicle
				static bool bNumpad8Pressed = false;
				if (isKeyPressedOnce(bNumpad8Pressed, VK_NUMPAD8))
				{
					if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
					{
						//Remove PED from vehicle
						AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
						//notify user of action
						UI::_SET_NOTIFICATION_TEXT_ENTRY("Player Removed from vehicle");
						UI::_DRAW_NOTIFICATION(FALSE, TRUE);
					}
				}
				

				if (IsPlayerFriend(iSelectedPlayer) == FALSE)
				{
					if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
					{
						if (GetAsyncKeyState(VK_RCONTROL) & 0x8000)
						{
							Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(selectedPed, FALSE);
							if (selectedPed != playerPed)
							{
								AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
								FIRE::ADD_OWNED_EXPLOSION(selectedPed, playerPosition.x, playerPosition.y, playerPosition.z, 4, 400.0f, FALSE, TRUE, 0.0f);
							}
							else
							{
								FIRE::ADD_EXPLOSION(playerPosition.x, playerPosition.y, playerPosition.z, 4, 400.0f, FALSE, TRUE, 0.0f);
							}
						}
						else
						{
							static int iCounter = 0;
							for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
							{
								try
								{
									Ped playerPedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
									if (ENTITY::DOES_ENTITY_EXIST(playerPedIterator) && playerPedIterator != playerPed) //If the iteration exists, and they're alive, and they're not me.
									{
										if (IsPlayerFriend(playerIterator) == FALSE && selectedPed != playerPedIterator)
										{
											if (iCounter == 5)
											{
												try
												{
													AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPedIterator); //If they're in a jet, or something. Toss them out.
													Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPedIterator, FALSE);
													static bool bExplode = false;
													bExplode = !bExplode;
													if (bExplode)
														FIRE::ADD_OWNED_EXPLOSION(selectedPed, playerPosition.x, playerPosition.y, playerPosition.z, 4, 400.0f, FALSE, TRUE, 0.0f); //We can blame anyone for the explosion. Whoever is selected in the menu will be blamed.
													else
														FIRE::START_SCRIPT_FIRE(playerPosition.x, playerPosition.y, playerPosition.z, 5, TRUE); //For LEXD Godmode kids who don't set entity proofs properly.
												}
												catch (...) { break; Log::Error("Crashed"); iCounter = -10; } //IDK why, but if you call these functions too many times per tick, it causes a crash. We can just toss the exception. Hopefully this fixes the crash...
											}
										}
									}
								}
								catch (...) { break; Log::Error("Crashed"); iCounter = -10; } //IDK why, but if you call these functions too many times per tick, it causes a crash. We can just toss the exception. Hopefully this fixes the crash...
							}
							iCounter++;
							if (iCounter > 5)
								iCounter = 0;
						}
					}

					static bool bNumpad3Pressed = false;
					if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
					{
						if (iFreeze == selectedPed)
							iFreeze = -1;
						else
							iFreeze = selectedPed;
					}
					if (iFreeze != -1 && (selectedPed != playerPed))
					{
						if (iFreeze == selectedPed)
						{
							WEAPON::REMOVE_ALL_PED_WEAPONS(selectedPed, TRUE);
							AI::CLEAR_PED_TASKS_IMMEDIATELY(selectedPed);
						}
					}
				}
			}
			else //every function without selecting a player
			{
				//Test IsPlayerFriend and give a sample player iteration
				if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
				{
					static int iCounter = 0;
					for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
					{
						Ped playerPedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
						if (ENTITY::DOES_ENTITY_EXIST(playerPedIterator) && playerPedIterator != playerPed) //If the iteration exists, and they're alive, and they're not me.
						{
							if (IsPlayerFriend(playerIterator) == FALSE)
							{
								if (iCounter == 5)
								{
									try
									{
										AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPedIterator);
										WEAPON::REMOVE_ALL_PED_WEAPONS(playerPedIterator, TRUE); //Why does this work? C'mon, Rockstar...
										Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPedIterator, FALSE);
										static bool bExplode = false;
										bExplode = !bExplode;
										if (bExplode)
											FIRE::ADD_OWNED_EXPLOSION(playerPedIterator, playerPosition.x, playerPosition.y, playerPosition.z, 4, 400.0f, FALSE, TRUE, 0.0f);
										else
											FIRE::START_SCRIPT_FIRE(playerPosition.x, playerPosition.y, playerPosition.z, 5, TRUE); //For LEXD Godmode kids who don't set entity proofs properly.
									}
									catch (...) { break; Log::Error("Crashed"); iCounter = -10; } //IDK why, but if you call these functions too many times per tick, it causes a crash. We can just toss the exception. Hopefully this fixes the crash...
								}
							}
						}
					}
					iCounter++;
					if (iCounter > 5)
						iCounter = 0;
				}

				//Spawn a test car.
				static bool bNumpad2Pressed, bWaitingForModelCar = false;
				if ((isKeyPressedOnce(bNumpad2Pressed, VK_NUMPAD2) || bWaitingForModelCar == true) && playerVeh == NULL)
				{
					Hash vehicleModelHash = VEHICLE_KURUMA2;
					if (GetAsyncKeyState(VK_RCONTROL) & 0x8000)
						vehicleModelHash = VEHICLE_BTYPE;
					if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
						vehicleModelHash = VEHICLE_ZENTORNO;
					if (GetAsyncKeyState(VK_DOWN) & 0x8000)
						vehicleModelHash = VEHICLE_INSURGENT;
					STREAMING::REQUEST_MODEL(vehicleModelHash);
					if (STREAMING::HAS_MODEL_LOADED(vehicleModelHash) == TRUE)
					{
						Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPed, FALSE);
						playerVeh = VEHICLE::CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, ENTITY::GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(playerVeh);
						PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, SEAT_DRIVER);
						BoostBaseCarStats(playerVeh);
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
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, PLATE_YELLOWONBLACK);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_BLACK);
							VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_BLACK);
							//VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
							//VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_METALLIC_ULTRA_BLUE);
							//for (int i = 0; i < NEON_BACK; i++) //This will turn on all the neon emitters except the back one. That shit's annoying when I'm trying to drive.
							//{
							//	VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, TRUE);
							//}
							//VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
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
							VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_METALLIC_ULTRA_BLUE, COLOR_MATTE_WHITE);
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_METALLIC_ULTRA_BLUE);
							for (int i = 0; i < NEON_BACK; i++) //This will turn on all the neon emitters except the back one. That shit's annoying when I'm trying to drive.
							{
								VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, TRUE);
							}
							VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
						}
						else if (vehicleModelHash == VEHICLE_INSURGENT)
						{
							VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, WHEEL_TYPE_SPORT);
							VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_FRONTWHEELS, WHEEL_SPORT_DEEPFIVE, TRUE);
							VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_FOREST_GREEN);
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
							VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
							VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_FOREST_GREEN);
							VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, WINDOWTINT_GREEN);
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, "GETFUCKD");
							VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, PLATE_YELLOWONBLACK);
							VEHICLE::SET_VEHICLE_MOD(playerVeh, MOD_HORNS, HORN_TRUCK, FALSE);
						}
						STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
						bWaitingForModelCar = false;
					}
					else
					{
						bWaitingForModelCar = true;
					}
				}

				//Spawn a test aircraft.
				static bool bNumpad3Pressed, bWaitingForModelAircraft = false;
				if (isKeyPressedOnce(bNumpad3Pressed, VK_NUMPAD3))
				{
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
							STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(vehicleModelHash);
							bWaitingForModelAircraft = false;
						}
						else
						{
							bWaitingForModelAircraft = true;
						}
					}
					if (playerVeh != NULL && (VEHICLE::IS_THIS_MODEL_A_PLANE(ENTITY::GET_ENTITY_MODEL(playerVeh)) == TRUE || VEHICLE::IS_THIS_MODEL_A_HELI(ENTITY::GET_ENTITY_MODEL(playerVeh)) ||
						ENTITY::GET_ENTITY_MODEL(playerVeh) == VEHICLE_BLIMP || ENTITY::GET_ENTITY_MODEL(playerVeh) == VEHICLE_BLIMP2) == TRUE)
					{
						NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(playerVeh);
						Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerVeh, FALSE);
						if (playerPosition.z < 350.0f)
							ENTITY::SET_ENTITY_COORDS_NO_OFFSET(playerVeh, playerPosition.x, playerPosition.y, playerPosition.z + 800, FALSE, FALSE, TRUE);
						VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, 0.0f);
						ENTITY::SET_ENTITY_PROOFS(playerVeh, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE);
						VEHICLE::SET_VEHICLE_STRONG(playerVeh, FALSE);
						VEHICLE::SET_VEHICLE_IS_STOLEN(playerVeh, FALSE);
						VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(playerVeh, FALSE);
						VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, 500);
						VEHICLE::SET_VEHICLE_CAN_BE_VISIBLY_DAMAGED(playerVeh, TRUE);
					}
				}

				//TP to mission objective.
				static bool bNumpad7Pressed = false;
				if (isKeyPressedOnce(bNumpad7Pressed, VK_NUMPAD7))
				{
					for (int i = 0; i <= 1000; i++)
					{
						Blip* blip = g_blipList->m_Blips[i].m_pBlip;
						if (blip)
						{
							//if ( blip->dwColor != 0x3 && !(blip->bIcon == 150 && blip->dwColor == 1) ) //Cut out most of the random job blips.
							DEBUGOUT("Blip%i ID: %i ID2: %i Icon: %i Color: 0x%X Message: %s", i, blip->iID, blip->iID2, blip->bIcon, blip->dwColor, blip->szMessage == NULL ? "" : blip->szMessage);
							if ((blip->dwColor == 0x42 && blip->bIcon == 1) /*Mission blip*/ ||
								(blip->dwColor == 0x5 && blip->bIcon == 1) /*Yellow blip*/ ||
								(blip->dwColor == 0x0 && blip->bIcon == 38) /*Race flag*/ ||
								(blip->dwColor == 0x2 && blip->bIcon == 1) /*Green blips*/)
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

				//Teleport to waypoint.
				static bool bNumpad0Pressed = false;
				static int teleportIteratrions = -1;
				if (isKeyPressedOnce(bNumpad0Pressed, VK_NUMPAD0) || teleportIteratrions > -1)
				{
					Entity e = playerPed;
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
				}
			}

			//Increase wanted level.
			static bool bAddPressed = false;
			if (isKeyPressedOnce(bAddPressed, VK_ADD))
			{
				if (PLAYER::GET_PLAYER_WANTED_LEVEL(player) < 5)
				{
					PLAYER::SET_PLAYER_WANTED_LEVEL(player, PLAYER::GET_PLAYER_WANTED_LEVEL(player) + 1, FALSE);
					PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
				}
			}

			//Clear Wanted Level
			if (GetAsyncKeyState(VK_MULTIPLY) & 0x8000)
			{
				PLAYER::SET_PLAYER_WANTED_LEVEL(player, 0, FALSE);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(player, FALSE);
			}

			//Fix player.
			static bool bDecimalPressed = false;
			if (isKeyPressedOnce(bDecimalPressed, VK_DECIMAL))
			{
				if (ENTITY::DOES_ENTITY_EXIST(playerVeh) && !ENTITY::IS_ENTITY_DEAD(playerVeh))
				{
					NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(playerVeh); //Can't hurt to try.
					VEHICLE::SET_VEHICLE_FIXED(playerVeh);
					VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(playerVeh);
					BoostBaseCarStats(playerVeh);
				}
				PED::CLEAR_PED_BLOOD_DAMAGE(playerPed);
				//We can only change stats that are not ServerAuthoritative="true" in mpstatssetup.xml.
				STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MP0_PLAYER_MENTAL_STATE"), 0.0f, TRUE);
				Entity attachedEnt = ENTITY::GET_ENTITY_ATTACHED_TO(playerPed);
				if (ENTITY::DOES_ENTITY_EXIST(attachedEnt))
				{
					if (ENTITY::IS_ENTITY_A_VEHICLE(attachedEnt) == FALSE)
						ENTITY::DELETE_ENTITY(&attachedEnt);
				}
				//SetIntStatWithBothVarients("CHEAT_BITSET", 0, 0);
				//SetIntStatWithBothVarients("BAD_SPORT_BITSET", 0, 0);
				//STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_IS_HIGH_EARNER"), FALSE, TRUE);
				//STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_IS_CHEATER"), FALSE, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_IS_CHEATER_TIME"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_WAS_I_BAD_SPORT"), 0, TRUE);
				//STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_BADSPORT"), 0, TRUE);
				//STATS::STAT_SET_FLOAT(GAMEPLAY::GET_HASH_KEY("MPPLY_OVERALL_CHEAT"), 0, TRUE);
				//STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_CHAR_IS_BADSPORT"), FALSE, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_NUM"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_CHEATER_NUM"), 0, TRUE);
				//Any date[12]; //Should be enough.
				//memset(&date, 0, sizeof(date));
				//STATS::STAT_SET_DATE(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_CHEATER_DT"), &date[0], 7, TRUE);
				//STATS::STAT_SET_DATE(GAMEPLAY::GET_HASH_KEY("MPPLY_BECAME_BADSPORT_DT"), &date[0], 7, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_DESTROYED_PVEHICLES"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_BADSPORT_MESSAGE"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_KILLS_PLAYERS_CHEATER"), 69, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_DEATHS_PLAYERS_CHEATER"), 420, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_REPORT_PENALTY"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_COMMEND_PENALTY"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_REPORT_RESTORE"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_LAST_COMMEND_RESTORE"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_REPORT_STRENGTH"), 32, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_COMMEND_STRENGTH"), 32, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VOTED_OUT"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VOTED_OUT_DELTA"), 0, TRUE);
				//STATS::STAT_SET_INT(GAMEPLAY::GET_HASH_KEY("MPPLY_VOTED_OUT_QUIT"), 0, TRUE);
				//STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_WAS_I_BAD_SPORT"), FALSE, TRUE);
				//STATS::STAT_SET_BOOL(GAMEPLAY::GET_HASH_KEY("MPPLY_WAS_I_CHEATER"), FALSE, TRUE);
			}

			//switch for godmode
			if (isKeyPressedOnce(bF8Pressed, VK_F8))
			{
				bGodmodeActive = !bGodmodeActive;
			}

			static bool F10Pressed = false;
			if (isKeyPressedOnce(F10Pressed, VK_F10))
			{
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

			static bool F9Pressed = false;
			if (isKeyPressedOnce(F9Pressed, VK_F9))
			{
				//Remove attached junk
				if (ENTITY::IS_ENTITY_ATTACHED(PLAYER::PLAYER_PED_ID()))
				{
					ENTITY::DETACH_ENTITY(PLAYER::PLAYER_PED_ID(), TRUE, TRUE);
				}
			}

			static bool bMouse5Pressed = false;
			if (isKeyPressedOnce(bMouse5Pressed, VK_XBUTTON1))
			{
				static BOOL bThermalVision = FALSE;
				bThermalVision = !bThermalVision;
				GRAPHICS::SET_SEETHROUGH(bThermalVision);
			}

			static bool b1pressed = false;
			if (isKeyPressedOnce(b1pressed, 0x31))
			{
				if (currentWeapon == WEAPON_UNARMED)
					CheckAndSelectWeapon(playerPed, WEAPON_KNIFE);
				else
					CheckAndSelectWeapon(playerPed, WEAPON_UNARMED);
			}
			static bool b2pressed = false;
			if (isKeyPressedOnce(b2pressed, 0x32))
			{
				if (playerVeh == NULL)
					CheckAndSelectWeapon(playerPed, WEAPON_HEAVYPISTOL);
				else if (currentWeapon == WEAPON_MICROSMG)
					CheckAndSelectWeapon(playerPed, WEAPON_FLAREGUN);
				else
					CheckAndSelectWeapon(playerPed, WEAPON_MICROSMG);
			}
			static bool b3pressed = false;
			if (isKeyPressedOnce(b3pressed, 0x33))
			{
				if (currentWeapon == WEAPON_ADVANCEDRIFLE)
					CheckAndSelectWeapon(playerPed, WEAPON_COMBATMG);
				else
					CheckAndSelectWeapon(playerPed, WEAPON_ADVANCEDRIFLE);
			}
			static bool b4pressed = false;
			if (isKeyPressedOnce(b4pressed, 0x34))
			{
				CheckAndSelectWeapon(playerPed, WEAPON_MINIGUN);
			}
			static bool b5pressed = false;
			if (isKeyPressedOnce(b5pressed, 0x35))
			{
				if (currentWeapon == WEAPON_HEAVYSNIPER)
					CheckAndSelectWeapon(playerPed, WEAPON_SNIPERRIFLE);
				else
					CheckAndSelectWeapon(playerPed, WEAPON_HEAVYSNIPER);
			}
			static bool b6pressed = false;
			if (isKeyPressedOnce(b6pressed, 0x36))
			{
				if (playerVeh)
					CheckAndSelectWeapon(playerPed, WEAPON_STICKYBOMB);
				else
					CheckAndSelectWeapon(playerPed, WEAPON_HOMINGLAUNCHER);
			}

			//How about some ESP? Commented out because it sucks.
			/*for (Player playerIterator = 0; playerIterator < 30; playerIterator++)
			{
			Ped playerPedIterator = PLAYER::GET_PLAYER_PED(playerIterator);
			if (ENTITY::DOES_ENTITY_EXIST(playerPedIterator) && !ENTITY::IS_ENTITY_DEAD(playerPedIterator) && playerPedIterator != playerPed)
			{
			//Remove this if you want to see everyone or people behind walls.
			if (ENTITY::HAS_ENTITY_CLEAR_LOS_TO_ENTITY(playerPed, playerPedIterator))
			{
			Vector3 playerPosition = ENTITY::GET_ENTITY_COORDS(playerPedIterator, FALSE);
			float screenX, screenY;
			if (GRAPHICS::_WORLD3D_TO_SCREEN2D(playerPosition.x, playerPosition.y, playerPosition.z +.5, &screenX, &screenY) == TRUE) //If we can see them.
			{
			//DEBUGOUT("Drawing on %s %f %f", PLAYER::GET_PLAYER_NAME(playerIterator), screenX, screenY);
			draw_text(screenX, screenY, PLAYER::GET_PLAYER_NAME(playerIterator), color_t{ 0xFF, 0xFF, 0xFF, 0xFF }); //This isn't perfect because Run is called once per tick not once per frame, so expect some lag on the ESP.
			}
			}
			}
			}*/
		}

		//Return control to the thread we stole it from.
		SetActiveThread(runningThread);
		return gGtaThreadOriginal.Run(This);
	}
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

			gGtaThreadNew.Run = new_Run; //Replace the .Run method in the new table with our method.
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
		Log::Error("Failed to find model table signature");
}