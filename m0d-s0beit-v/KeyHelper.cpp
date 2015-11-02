#include "stdafx.h"

bool isKeyPressedOnce(bool& bIsPressed, DWORD vk)
{
	if (IsKeyPressed(vk))
	{
		if (bIsPressed == false)
		{
			bIsPressed = true;
			return true;
		}
	}
	else if (bIsPressed == true)
	{
		bIsPressed = false;
	}
	return false;
}

void ReleaseKeys()
{
	keybd_event(VK_NUMPAD1, 0, KEYEVENTF_KEYUP, 0);
}