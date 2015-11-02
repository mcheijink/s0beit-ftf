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
void AIWanderCar(Ped playerPed);
void AIParkCar(Ped playerPed);
void AIJackVehicle(Ped selectedPlayer);
void VehicleGodmode(Entity playerPed, bool GodmodeOn);
void AIDrivetoWaypoint(Ped driverPed);
void SetRadio();