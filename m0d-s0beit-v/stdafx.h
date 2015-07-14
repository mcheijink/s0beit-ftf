// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN
//#define __DEBUG

// Windows Header Files:
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
#include <string>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <iostream>
#include <fstream>
#include <timeapi.h>

#pragma comment(lib, "winmm.lib")

extern MODULEINFO g_MainModuleInfo;

// Mine
#include "Log.h"
#include "Pattern.h"

// Rockstar
#include "Types.h"
#include "pgCollection.h"
#include "scrThread.h"
#include "Hashes.h"
#include "VehicleValues.h"
#include "natives.h"

// Main
#include "script.h"

#include "Functions\PlayerFunctions.h"
#include "Functions\UIFunctions.h"
#include "Functions\VehicleFunctions.h"
#include "Functions\WeaponFunctions.h"
#include "Functions\WorldFunctions.h"

#define version 1203

void Tick();
void Run();
void RunUnreliable();