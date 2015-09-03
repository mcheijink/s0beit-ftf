#pragma once

#include "../stdafx.h"

void BoostBaseVehicleStats(Vehicle vehicle);
Vehicle ClonePedVehicle(Ped ped);
void DumpPlayerFromVehicle(Ped PlayerID, bool Notification);
void DumpVehicleStats(Vehicle vehicle);
void SetOffAlarmofPlayerVehicle(Ped selectedPed);
bool LSCCarParkClone(Ped selectedPed);
void BurstSelectedPlayerTires(Ped selectedPed);
bool SpawnPlayerAircraft(Ped playerPed, bool bWaitingForModelAircraft);
bool SpawnPlayerCar(Ped playerPed, bool bWaitingForModelCar);
bool GetVehicleInfoForClanLogo(Hash vehicleModel, vector3_t& x, vector3_t& y, vector3_t& z, float& scale);
Vehicle ClonePedVehicle(Ped ped);
void AIWanderCar(Ped playerPed);
void AIParkCar(Ped playerPed);
void AIJackVehicle(Ped selectedPlayer);
void VehicleGodmode(Entity playerPed, bool GodmodeOn);
void AIDrivetoWaypoint(Ped driverPed);