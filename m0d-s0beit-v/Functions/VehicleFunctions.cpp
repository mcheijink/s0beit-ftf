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

bool GetVehicleInfoForClanLogo(Hash vehicleModel, vector3_t& x, vector3_t& y, vector3_t& z, float& scale)
{
	switch (vehicleModel)
	{
	case VEHICLE_DOMINATOR:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FELTZER2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ADDER:
		x = { 0.0f, 1.54f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_AKUMA:
		x = { 0.0f, 0.06f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_ASEA:
		x = { 0.0f, 1.5f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ASTEROPE:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BAGGER:
		x = { 0.0f, 0.053f, 1.23f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BALLER:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BALLER2:
		x = { 0.0f, 1.55f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BANSHEE:
		x = { 0.0f, 0.94f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_BATI:
		x = { 0.0f, 0.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BATI2:
		x = { 0.0f, 0.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_BFINJECTION:
		x = { -1.0f, 0.08f, 0.19f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BISON:
		x = { 0.0f, 1.99f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BJXL:
		x = { 0.0f, 1.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_BLISTA:
		x = { 0.0f, 1.49f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.29f;
		return true;
	case VEHICLE_BOBCATXL:
		x = { 0.0f, 1.68f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.65f;
		return true;
	case VEHICLE_BODHI2:
		x = { 0.0f, 1.95f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BUCCANEER:
		x = { 0.0f, 2.01f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_BUFFALO:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_BUFFALO2:
		x = { 0.0f, 2.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_BULLET:
		x = { -1.57f, 0.07f, 0.16f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_CARBONRS:
		x = { 0.0f, 0.09f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_CARBONIZZARE:
		x = { 0.0f, 1.45f, 1.0f };
		y = { 0.0f, 0.11f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_CAVALCADE:
		x = { 0.0f, 1.51f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.55f;
		return true;
	case VEHICLE_CAVALCADE2:
		x = { 0.0f, 1.59f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_CHEETAH:
		x = { -1.61f, 0.26f, 0.17f };
		y = { 0.9f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_COGCABRIO:
		x = { 0.0f, 1.42f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COMET2:
		x = { 0.0f, 1.35f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE:
		x = { 0.0f, 0.96f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.22f;
		return true;
	case VEHICLE_DAEMON:
		x = { 0.0f, 0.06f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_DILETTANTE:
		x = { 0.0f, 1.59f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DLOADER:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DOUBLE:
		x = { 0.0f, 0.08f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_DUBSTA:
		x = { -1.71f, 0.31f, 0.27f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.75f;
		return true;
	case VEHICLE_ELEGY2:
		x = { 0.0f, 1.14f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_EMPEROR:
		x = { 0.0f, 1.31f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_EMPEROR2:
		x = { 0.0f, 1.31f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ENTITYXF:
		x = { 1.52f, 0.41f, 0.15f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_EXEMPLAR:
		x = { 0.0f, 1.32f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_F620:
		x = { 0.0f, 1.28f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_FAGGIO2:
		x = { -1.0f, 0.48f, 0.11f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_FELON:
		x = { 0.0f, 1.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_FELON2:
		x = { 0.0f, 1.24f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_FQ2:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FUGITIVE:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_FUSILADE:
		x = { 0.0f, 0.98f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.2f;
		return true;
	case VEHICLE_FUTO:
		x = { 0.0f, 1.28f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_GAUNTLET:
		x = { 0.0f, 1.735f, 1.05f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_GRANGER:
		x = { 0.0f, 2.07f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_GRESLEY:
		x = { 0.0f, 1.75f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HABANERO:
		x = { 0.0f, 1.69f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HEXER:
		x = { 0.0f, -0.46f, 1.0f };
		y = { 0.0f, 1.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.14f;
		return true;
	case VEHICLE_HOTKNIFE:
		x = { 1.43f, -0.14f, 0.18f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_INFERNUS:
		x = { -1.0f, 0.33f, 0.08f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.06f };
		scale = 0.25f;
		return true;
	case VEHICLE_INGOT:
		x = { 0.0f, 1.58f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_INTRUDER:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ISSI2:
		x = { 0.0f, 1.21f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_JACKAL:
		x = { 0.0f, 1.36f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_JB700:
		x = { 0.0f, 1.2f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_KHAMELION:
		x = { 0.0f, 1.46f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.475f;
		return true;
	case VEHICLE_LANDSTALKER:
		x = { 0.0f, 1.83f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MANANA:
		x = { 0.0f, 0.86f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.37f;
		return true;
	case VEHICLE_MESA:
		x = { 0.0f, 1.47f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MESA3:
		x = { 0.0f, 1.47f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MINIVAN:
		x = { 0.0f, 1.95f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_MONROE:
		x = { 0.0f, 1.23f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.43f;
		return true;
	case VEHICLE_NEMESIS:
		x = { 0.0f, 0.14f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.1f;
		return true;
	case VEHICLE_NINEF:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_NINEF2:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ORACLE2:
		x = { 0.0f, 1.7f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PATRIOT:
		x = { 0.0f, 1.75f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PCJ:
		x = { 0.0f, 0.02f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_PENUMBRA:
		x = { 0.0f, 1.46f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PEYOTE:
		x = { -1.0f, -0.36f, 0.2125f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PHOENIX:
		x = { 0.0f, 1.833f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.44f;
		return true;
	case VEHICLE_PICADOR:
		x = { 0.0f, 1.43f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.515f;
		return true;
	case VEHICLE_PRAIRIE:
		x = { 0.0f, 1.41f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.31f;
		return true;
	case VEHICLE_PREMIER:
		x = { 0.0f, 1.6f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PRIMO:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RADI:
		x = { 0.0f, 1.74f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RANCHERXL:
		x = { 0.0f, 1.54f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT:
		x = { 0.0f, 1.263f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RAPIDGT2:
		x = { 0.0f, 1.263f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RATLOADER:
		x = { 1.78f, 0.52f, 0.52f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_REBEL:
		x = { -1.22f, 0.6f, 0.44f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_REBEL2:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_REGINA:
		x = { 0.0f, 1.473f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ROCOTO:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ROMERO:
		x = { 0.0f, 1.83f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_RUFFIAN:
		x = { 0.0f, 0.02f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.19f;
		return true;
	case VEHICLE_RUINER:
		x = { 0.0f, 1.34f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SABREGT:
		x = { -1.0f, 0.0f, 0.14f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.015f };
		scale = 0.35f;
		return true;
	case VEHICLE_SADLER:
		x = { 0.0f, 2.26f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING:
		x = { 0.0f, 2.496f, 1.55f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SANDKING2:
		x = { 0.0f, 2.286f, 1.55f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SCHAFTER2:
		x = { 0.0f, 1.56f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.28f;
		return true;
	case VEHICLE_SCHWARZER:
		x = { 0.0f, 1.43f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.28f;
		return true;
	case VEHICLE_SEMINOLE:
		x = { 0.0f, 1.45f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SENTINEL2:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SERRANO:
		x = { 0.0f, 1.68f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.49f;
		return true;
	case VEHICLE_STANIER:
		x = { 0.0f, 1.55f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_STINGER:
		x = { 0.0f, 1.3f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_STINGERGT:
		x = { -1.0f, -0.17f, 0.12f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_STRATUM:
		x = { 0.0f, 1.52f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SULTAN:
		x = { 0.0f, 1.77f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_SUPERD:
		x = { 0.0f, 1.62f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SURANO:
		x = { 0.0f, 1.38f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_SURFER:
		x = { 0.0f, 2.48f, 0.26f };
		y = { 0.0f, -1.0f, 0.212f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.32f;
		return true;
	case VEHICLE_SURFER2:
		x = { 0.0f, 2.48f, 0.26f };
		y = { 0.0f, -1.0f, 0.212f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.32f;
		return true;
	case VEHICLE_SURGE:
		x = { 0.0f, 1.69f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_TAILGATER:
		x = { 0.0f, 1.783f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO:
		x = { -1.23f, 0.11f, 0.21f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_TORNADO2:
		x = { 0.0f, 1.44f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_TORNADO3:
		x = { 0.0f, 1.44f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_VACCA:
		x = { 0.0f, 1.76f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_VADER:
		x = { 0.0f, 0.08f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_VIGERO:
		x = { -1.0f, 0.11f, -0.15f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_VOLTIC:
		x = { 0.0f, 1.763f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.29f;
		return true;
	case VEHICLE_VOODOO2:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_WASHINGTON:
		x = { 0.0f, 1.61f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_YOUGA:
		x = { 0.0f, 2.02f, 1.0f };
		y = { 0.0f, -0.108f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_ZION:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_ZION2:
		x = { 0.0f, 1.48f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_ZTYPE:
		x = { 0.96f, 0.69f, 0.35f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_KALAHARI:
		x = { -1.0f, 0.18f, 0.1f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PARADISE:
		x = { 0.0f, 2.23f, 1.0f };
		y = { 0.0f, 0.22f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_ALPHA:
		x = { -1.0f, 0.18f, -0.05f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_HUNTLEY:
		x = { 0.0f, 1.52f, 0.99f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_ZENTORNO:
		x = { -1.24f, 0.42f, -0.14f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.035f };
		scale = 0.3f;
		return true;
	case VEHICLE_JESTER:
		x = { -1.0f, 0.17f, 0.22f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.05f };
		scale = 0.33f;
		return true;
	case VEHICLE_MASSACRO:
		x = { 0.0f, 1.37f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.33f;
		return true;
	case VEHICLE_TURISMOR:
		x = { -1.0f, 0.3f, 0.27f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_THRUST:
		x = { -1.0f, 0.405f, 0.4625f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.1625f;
		return true;
	case VEHICLE_BTYPE:
		x = { 0.0f, 1.143f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.7125f;
		return true;
	case VEHICLE_RHAPSODY:
		x = { -1.0f, 0.47f, -0.25f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2625f;
		return true;
	case VEHICLE_GLENDALE:
		x = { 0.0f, 1.683f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.775f;
		return true;
	case VEHICLE_WARRENER:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.775f;
		return true;
	case VEHICLE_BLADE:
		x = { -1.0f, 0.445f, 0.2075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.325f;
		return true;
	case VEHICLE_PANTO:
		x = { -1.0f, 0.0f, 0.335f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUBSTA3:
		x = { -1.0f, 0.34f, 0.2975f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_PIGALLE:
		x = { 0.0f, 1.623f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_COQUETTE2:
		x = { -1.0f, 0.1775f, 0.195f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_INNOVATION:
		x = { 0.0f, 0.15f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.18f;
		return true;
	case VEHICLE_HAKUCHOU:
		x = { 0.0f, 0.27f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.16f;
		return true;
	case VEHICLE_FUROREGT:
		x = { -1.0f, 0.0f, 0.2075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_RATLOADER2:
		x = { 1.78f, 0.52f, 0.52f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_SLAMVAN:
		x = { -1.0f, 0.275f, 0.195f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_DUKES2:
		x = { -1.0f, 0.0f, 0.0f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.375f;
		return true;
	case VEHICLE_DUKES:
		x = { -1.0f, 0.0f, 0.0375f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3875f;
		return true;
	case VEHICLE_STALION:
		x = { -1.0f, 0.0f, 0.0925f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.4375f;
		return true;
	case VEHICLE_BLISTA2:
		x = { -1.0f, 0.5325f, 0.245f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.2875f;
		return true;
	case VEHICLE_CASCO:
		x = { 0.0f, 0.94f, 1.03f };
		y = { 0.0f, 0.03f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_ENDURO:
		x = { 0.0f, -0.17f, 1.0f };
		y = { 0.0f, 0.34f, -0.786f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.15f;
		return true;
	case VEHICLE_GBURRITO2:
		x = { 0.0f, 2.32f, 0.94f };
		y = { 0.0f, 0.182f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.4f;
		return true;
	case VEHICLE_GUARDIAN:
		x = { -1.94f, 1.07f, 0.38f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.35f;
		return true;
	case VEHICLE_KURUMA:
	case VEHICLE_KURUMA2:
		x = { -1.0f, 0.2475f, 0.175f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.435f;
		return true;
	case VEHICLE_LECTRO:
		x = { 0.0f, 0.3f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.09f;
		return true;
	case VEHICLE_FELTZER3:
		x = { 0.0f, 1.4f, 1.0f };
		y = { 0.0f, 0.0f, -1.0f };
		z = { -1.0f, 0.0f, 0.0f };
		scale = 0.5f;
		return true;
	case VEHICLE_OSIRIS:
		x = { -1.0f, 0.27f, 0.03f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.3f;
		return true;
	case VEHICLE_VIRGO:
		x = { 1.05f, 0.0f, 0.075f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.45f;
		return true;
	case VEHICLE_WINDSOR:
		x = { -1.2f, 0.39f, 0.12f };
		y = { 1.0f, 0.0f, 0.0f };
		z = { 0.0f, -1.0f, 0.0f };
		scale = 0.55f;
		return true;
	default:
		return false;
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
				vector3_t x, y, z;
				float scale;
				if (GetVehicleInfoForClanLogo(vehicleModelHash, x, y, z, scale))
				{
					int alpha = 200;
					if (vehicleModelHash == VEHICLE_WINDSOR)
						alpha = 255;
					GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(playerVeh, ped, ENTITY::_GET_ENTITY_BONE_INDEX(playerVeh, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, alpha);
				}
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
			Log::Msg("vector3_t x, y, z");
			Log::Msg("float scale");
			Log::Msg("GetVehicleInfoForClanLogo(VEHICLE_%s, x, y, z, scale);", VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(ENTITY::GET_ENTITY_MODEL(vehicle)));
			Log::Msg("GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(playerVeh, playerPed, ENTITY::_GET_ENTITY_BONE_INDEX(playerVeh, \"chassis_dummy\"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, %i);", (ENTITY::GET_ENTITY_MODEL(vehicle) == VEHICLE_WINDSOR) ? 255 : 200);
		}
	}
}

void SetOffAlarmofPlayerVehicle(Ped selectedPed)
{
	if (PED::IS_PED_IN_ANY_VEHICLE(selectedPed, FALSE))
	{
		Vehicle selectedVehicle = PED::GET_VEHICLE_PED_IS_USING(selectedPed);
		if (GetControllofEntity(selectedVehicle)) {
			VEHICLE::SET_VEHICLE_ALARM(selectedVehicle, true);
			VEHICLE::START_VEHICLE_ALARM(selectedVehicle);
			drawNotification("Set off alarm of vehicle");
		}
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
		if (GetControllofEntity(selectedVehicle)) {
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(selectedVehicle, TRUE);
			static int tireID = 0;
			for (tireID = 0; tireID < 8; tireID++) {
				VEHICLE::SET_VEHICLE_TYRE_BURST(selectedVehicle, tireID, true, 1000.0);
			}
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
		GetControllofEntity(playerVeh);
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
			GetControllofEntity(playerVeh);
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
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_WHITE);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_WHITE);
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
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_MATTE_BLACK, COLOR_MATTE_WHITE);
				VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, MOD_TIRESMOKE, TRUE);
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, TIRESMOKE_COLOR_BLACK);
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, 0, COLOR_MATTE_WHITE);
				/*for (int i = 0; i < NEON_BACK; i++) //This will turn on all the neon emitters except the back one. That shit's annoying when I'm trying to drive.
				{
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, TRUE);
				}
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
				*/
				vector3_t x, y, z;
				float scale;
				if (GetVehicleInfoForClanLogo(VEHICLE_ZENTORNO, x, y, z, scale))
				{
					GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(playerVeh, playerPed, ENTITY::_GET_ENTITY_BONE_INDEX(playerVeh, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, 200);
				}
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
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, COLOR_METALLIC_ULTRA_BLUE, COLOR_MATTE_WHITE);
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
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, COLOR_METALLIC_ULTRA_BLUE, COLOR_METALLIC_ULTRA_BLUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, NEON_COLOR_ELECTRICBLUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 0, TRUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 1, TRUE);
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, 2, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 2, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 3, FALSE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 7, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 10, TRUE);
				VEHICLE::SET_VEHICLE_EXTRA(playerVeh, 11, TRUE);
				vector3_t x, y, z;
				float scale;
				if (GetVehicleInfoForClanLogo(VEHICLE_RUINER, x, y, z, scale))
				{
					GRAPHICS::_ADD_CLAN_DECAL_TO_VEHICLE(playerVeh, playerPed, ENTITY::_GET_ENTITY_BONE_INDEX(playerVeh, "chassis_dummy"), x.x, x.y, x.z, y.x, y.y, y.z, z.x, z.y, z.z, scale, 0, 200);
				}
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
		GetControllofEntity(playerVeh);
		VEHICLE::SET_VEHICLE_FORWARD_SPEED(playerVeh, VEHICLE::_GET_VEHICLE_MAX_SPEED(ENTITY::GET_ENTITY_MODEL(playerVeh)));
	}
	return bWaitingForModelCar;
}
