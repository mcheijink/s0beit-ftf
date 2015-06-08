#include "stdafx.h"

#pragma once
#pragma comment(lib, "LDE64-x64/LDE64x64.lib")

extern "C" size_t __fastcall LDE(const LPVOID lpData, unsigned int size);

struct Opcode {
	DWORD64				addr;
	std::vector<UINT8>	bytes;
};

struct Opcodes {
	std::vector<Opcode> op;
};

struct Native {
	DWORD64 hash;
	DWORD64 func;

	DWORD64 GetFunctionRoughHash();
};

struct Namespace {
	std::vector<Native> natives;
	std::string name;
};

enum eScriptNativeCollectionIndex
{
	INDEX_APP = 0,
	INDEX_AUDIO = 1,
	INDEX_CAM = 2,
	_NULLSTUB1 = 3,
	INDEX_UI = 4,
	INDEX_GAMEPLAY = 5,
	INDEX_CONTROLS = 6,
	INDEX_PED = 7,
	INDEX_PLAYER = 8,
	INDEX_AI = 9,
	INDEX_VEHICLE = 10,
	_NULLSTUB2 = 11,
	INDEX_OBJECT = 12,
	INDEX_SCRIPT = 13,
	INDEX_STATS = 14,
	INDEX_STREAMING = 15,
	INDEX_PATHFIND = 16,
	INDEX_WEAPON = 17,
	INDEX_FIRE = 18,
	INDEX_ZONE = 19,
	INDEX_GRAPHICS = 20,
	_NULLSTUB3 = 21,
	INDEX_CUTSCENE = 22,
	INDEX_TIME = 23,
	INDEX_NETWORK = 24,
	INDEX_BRAIN = 25,
	_NULLSTUB4 = 26,
	INDEX_WATER = 27,
	_NULLSTUB5 = 28,
	INDEX_UNK = 29,
	INDEX_DECISIONEVENT = 30,
	INDEX_INTERIOR = 31,
	INDEX_ROPE = 32,
	INDEX_MOBILE = 33,
	INDEX_ENTITY = 34,
	INDEX_ITEMSET = 35,
	_NULLSTUB6 = 36,
	INDEX_WORLDPROBE = 37,
	INDEX_DECORATOR = 38,
	INDEX_DATAFILE = 39,
	INDEX_UNK_SC = 40,
	INDEX_DLC1 = 41,
	INDEX_DLC2 = 42,
	INDEX_NETWORKCASH = 43,
	INDEX_UNK1 = 44,
	INDEX_UNK2 = 45,
	INDEX_UNDOC001 = 46,
	INDEX_UNDOC002 = 47,
	MAX
};

extern UINT64 NATIVE_CACHE[MAX][723];

void GetNativeHashes();