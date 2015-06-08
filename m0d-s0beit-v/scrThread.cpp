#include "stdafx.h"

void NativeInvoke::Invoke(NativeContext *cxt, UINT64 hash)
{
	auto fn = GetNativeHandler(hash);

	if (fn != 0)
	{
		fn(cxt);
	}
}