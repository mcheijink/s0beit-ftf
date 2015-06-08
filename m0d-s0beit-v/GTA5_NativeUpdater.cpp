#include "stdafx.h"
#include "GTA5_NativeUpdater.h"

#define ECHO_DEF(x) #x

// Find ScriptSetup
// 40 53 48 83 EC 20 83 F9 01 0F 85 A3 00 00 00

//

// Find All Native References
// 48 B9 ? ? ? ? ? ? ? ? E8

char* gNamespaceNames[] = {
	"INDEX_APP",
	"INDEX_AUDIO",
	"INDEX_CAM",
	"_NULLSTUB1",
	"INDEX_UI",
	"INDEX_GAMEPLAY",
	"INDEX_CONTROLS",
	"INDEX_PED",
	"INDEX_PLAYER",
	"INDEX_AI",
	"INDEX_VEHICLE",
	"_NULLSTUB2",
	"INDEX_OBJECT",
	"INDEX_SCRIPT",
	"INDEX_STATS",
	"INDEX_STREAMING",
	"INDEX_PATHFIND",
	"INDEX_WEAPON",
	"INDEX_FIRE",
	"INDEX_ZONE",
	"INDEX_GRAPHICS",
	"_NULLSTUB3",
	"INDEX_CUTSCENE",
	"INDEX_TIME",
	"INDEX_NETWORK",
	"INDEX_BRAIN",
	"_NULLSTUB4",
	"INDEX_WATER",
	"_NULLSTUB5",
	"INDEX_UNK",
	"INDEX_DECISIONEVENT",
	"INDEX_INTERIOR",
	"INDEX_ROPE",
	"INDEX_MOBILE",
	"INDEX_ENTITY",
	"INDEX_ITEMSET",
	"_NULLSTUB6",
	"INDEX_WORLDPROBE",
	"INDEX_DECORATOR",
	"INDEX_DATAFILE",
	"INDEX_UNK_SC",
	"INDEX_DLC1",
	"INDEX_DLC2",
	"INDEX_NETWORKCASH",
	"INDEX_UNK1",
	"INDEX_UNK2",
	"INDEX_UNDOC001",
	"INDEX_UNDOC002",
	"MAX"
};

UINT64 NATIVE_CACHE[MAX][723];

// This will keep going until it hits a JMP or RET
// It's super basic, but fits our needs
Opcodes GetFunctionOpcodes(DWORD64 dwFunctionAddress) {
	Opcodes ret;

	for (UCHAR* pStart = (UCHAR*)dwFunctionAddress;;) {
		if (pStart[0] == 0xCC)
			break; // Something else may have happened, lmao

		size_t opcodeSize = LDE(pStart, 64);

		//printf("SIZE: %d\n", opcodeSize);

		// This needs serious bug fixing
		if (opcodeSize == -1 || opcodeSize == 0) {
			//printf("Opcode Error: 0x%X\n", pStart[0]);
			break;
		}

		Opcode op;

		op.addr = (DWORD64)pStart;

		for (size_t i = 0; i < opcodeSize; i++) {
			op.bytes.push_back(pStart[i]);
		}

		ret.op.push_back(op);

		// Add stuff here if it gets funky
		if (pStart[0] == 0xC3 || pStart[0] == 0xC2 || pStart[0] == 0xE9)
			break;

		pStart += opcodeSize;
	}

	return ret;
}

// This is a function which can sort of vaguely tell us if a native has changed or not.
// It's completely insane, truly, but hey I'm in a damn hurry.
// Uncomment at your peril
DWORD64 Native::GetFunctionRoughHash() {
	DWORD64 pseudoHash = 0;

	/*
	Opcodes ops = GetFunctionOpcodes(this->func);

	for (auto op : ops.op) {
	if (op.bytes.size() <= 0)
	continue; // how

	pseudoHash += op.bytes[0];

	if (op.bytes.size() > 1 && op.bytes[0] == 0x48) {
	pseudoHash += op.bytes[1];
	}
	else if (op.bytes[0] == 0xE8) { // We don't handle JMPs unfortunately, mostly because it can cause serious issues with functions with random JMPs in it
	DWORD64 dwFunctionCallAddress = (*(int*)(op.addr + 1) + op.addr + 5);

	Opcodes funcOps = GetFunctionOpcodes(dwFunctionCallAddress);

	for (auto fop : funcOps.op) {
	if (fop.bytes.size() <= 0)
	continue; // how

	pseudoHash += fop.bytes[0];
	}
	}
	}
	*/

	return pseudoHash;
}

bool isNullStub(eScriptNativeCollectionIndex idx) {
	return (
		idx == _NULLSTUB1 ||
		idx == _NULLSTUB2 ||
		idx == _NULLSTUB3 ||
		idx == _NULLSTUB4 ||
		idx == _NULLSTUB5 ||
		idx == _NULLSTUB6);
}

std::vector<DWORD64> GetHashesInFunction(DWORD64 dwFunctionStart) {
	std::vector<DWORD64> hashes;

	Opcodes ops = GetFunctionOpcodes(dwFunctionStart);

	for (auto op : ops.op) {
		// mov rcx, [hash]
		if (op.bytes.size() > 2 && op.bytes.at(0) == 0x48 && op.bytes.at(1) == 0xB9) {
			hashes.push_back(*(DWORD64*)(op.addr + 2));
		}
	}

	return hashes;
}

void GetNativesInFunction(DWORD64 dwFunctionStart, int scriptNamespaceIndex) {
	Opcodes ops = GetFunctionOpcodes(dwFunctionStart);

	int i = 0;
	for (auto op : ops.op) {
		// mov rcx, [hash]
		if (op.bytes.size() > 2 && op.bytes.at(0) == 0x48 && op.bytes.at(1) == 0xB9) {
			NATIVE_CACHE[scriptNamespaceIndex][i] = *(DWORD64*)(op.addr + 2);
			DEBUGOUT("%s[%i] = 0x%016llX", gNamespaceNames[scriptNamespaceIndex], i, NATIVE_CACHE[scriptNamespaceIndex][i]);
			i++;
		}
	}
}

void GetNativeHashes() {
	DEBUGOUT("Getting hash table signature");
	DWORD64 dwAddressOfAddNatives = Pattern::Scan(g_MainModuleInfo, "E8 ? ? ? ? 8D 4B 04 33 D2");

	if (dwAddressOfAddNatives != 0) {
		dwAddressOfAddNatives = (*(int*)(dwAddressOfAddNatives + 1) + dwAddressOfAddNatives + 5);

		int scriptNamespaceIndex = -1;

		Opcodes ops = GetFunctionOpcodes(dwAddressOfAddNatives);

		for (auto op : ops.op) {
			if (op.bytes.data()[0] == 0xE8 || op.bytes.data()[0] == 0xE9) { // CALL || JMP
				scriptNamespaceIndex++; // We're in the namespace

				if (isNullStub((eScriptNativeCollectionIndex)scriptNamespaceIndex))
					continue;

				DWORD64 dwFunctionCallAddress = (*(int*)(op.addr + 1) + op.addr + 5);
				DEBUGOUT("Getting the %s table's hashes", gNamespaceNames[scriptNamespaceIndex] + 6);
				GetNativesInFunction(dwFunctionCallAddress, scriptNamespaceIndex);
			}
		}
		DEBUGOUT("Finished gathering native hashes.");
	}
	else {
		Log::Fatal("Unable to find Script Setup. Native functions will not work.");
	}
}