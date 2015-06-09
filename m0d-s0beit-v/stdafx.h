// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS

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

#pragma comment(lib, "Psapi")

//
extern MODULEINFO g_MainModuleInfo;

// Mine
#include "Log.h"
#include "Pattern.h"

// Rockstar
#include "Types.h"
#include "pgCollection.h"
#include "scrThread.h"
#include "Hashes.h"
#include "vehicleValues.h"

// Main
#include "script.h"