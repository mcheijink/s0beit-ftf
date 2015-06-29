#pragma once

#include "../stdafx.h"


void BruteForceWeaponAddons(Ped ped, Hash weaponHash, bool bSilencer);
void GiveAllWeaponsToPed(Ped ped, WeaponTints weaponTint, bool removeWeaponsFirst);
void CheckAndSelectWeapon(Ped ped, Hash weaponHash);
void FlowerPower(Ped selectedPed);
void FastReload(Ped playerped);