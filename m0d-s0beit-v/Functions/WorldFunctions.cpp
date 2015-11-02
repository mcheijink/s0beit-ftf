#include "../stdafx.h"

float Height(Vector3 Coordinate)
{
	float waterheight, groundheight;

	WATER::GET_WATER_HEIGHT(Coordinate.x, Coordinate.y, Coordinate.z, &waterheight);
	GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(Coordinate.x, Coordinate.y, Coordinate.z, &groundheight);

	if (waterheight > groundheight)
	{
		return waterheight;
	}
	else
	{
		return groundheight;
	}
}

void AntiCrash()
{
	Ped *peds = new Ped[202];
	peds[0] = 100;
	int nearbyPeds = PED::GET_PED_NEARBY_PEDS(PLAYER::PLAYER_PED_ID(), peds, -1);
	for (int i = 0; i < nearbyPeds; i++)
	{
		int pedToDeleteID = i * 2 + 2;

		if (!ENTITY::DOES_ENTITY_EXIST(peds[pedToDeleteID]) || PED::IS_PED_A_PLAYER(peds[pedToDeleteID]))
		{
			continue;
		}

		Ped pedToDelete = peds[pedToDeleteID];
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(pedToDelete, TRUE, TRUE);
		PED::DELETE_PED(&pedToDelete);
	}
	delete peds;
}