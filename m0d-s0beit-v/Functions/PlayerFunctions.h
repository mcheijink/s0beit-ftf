#pragma once

#include "../stdafx.h"

void RemoveAllPropsFromPlayer(Ped ped);
bool IsPlayerFriend(Player player);
void TeleporttoSelectedPlayerVehicle(Ped playerPed, Ped selectedPed);
void TeleporttoSelectedPlayer(Ped playerPed, Ped selectedPed);
void DropMoneyonSelectedPlayer(Ped selectedPed);
void TeleportSelectedPlayertoAlamosSea(Ped selectedPed);
bool AttachJunktoSelectedPlayer(Ped selectedPed);
void AttackPlayerWithRandomPeds(Ped selectedPed);
void FrameSelectedPlayer(Ped selectedPed);
void ExplodeSelectedPlayer(Ped selectedPed);
bool PoliceIgnorePlayer(Player player, bool bPoliceIgnorePlayer, bool bPoliceIgnoreSwitchSet);
Player KillalltheSpeakingPlayers();
int ClearingTheSkiesofPlayers();
void TeleporttoMissionObjective(Ped playerPed, BlipList* g_blipList);
int TeleporttoWaypoint(Ped playerPed, int teleportIteratrions);
void FixPlayer(Ped playerPed);
void KillAllTargets(Ped playerPed, BlipList* g_blipList, bool bKillTargetsActive);
bool GodMode(Player player, Ped playerPed, bool bGodmodeActive, bool bGodmodeSwitchset);
void IncreaseWantedLevel(Player player);
void ClearWantedLevel(Player player);
void ReplenishAmmo(Ped playerPed);
void EnableRestrictedZones(bool featureRestrictedZones);
void RequestControl(Entity e);
void SpectatePlayer(Ped playerped);
void SpectateMode(bool Active, Ped selectedPed);
void PlayerGodmode(Player player, Entity playerPed, bool GodModeOn);
bool GodMode(Player player, Ped playerPed, bool bGodmodeActive, bool bGodmodeSwitchset);
void PlayerInvisible(bool Invisible);
void CrashPlayer(Ped selectedPed);