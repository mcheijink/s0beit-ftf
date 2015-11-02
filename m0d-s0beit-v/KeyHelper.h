#pragma once

#include "stdafx.h"

#define IsKeyPressed(key) GetAsyncKeyState(key) & 0x8000

bool isKeyPressedOnce(bool& bIsPressed, DWORD vk);
void ReleaseKeys();