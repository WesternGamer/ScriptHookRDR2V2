#include "../pch.h"

#define DLL_EXPORT __declspec(dllexport)

// TODO: implement
DLL_EXPORT void keyboardHandlerRegister(globalvars::KeyboardHandler handler)
{
}

// TODO: implement
DLL_EXPORT void keyboardHandlerUnregister(globalvars::KeyboardHandler handler)
{
}

// TODO: implement
DLL_EXPORT void scriptWait(DWORD time)
{
}

// TODO: implement
DLL_EXPORT void scriptRegister(HMODULE module, void (*LP_SCRIPT_MAIN)())
{
}

DLL_EXPORT void scriptRegisterAdditionalThread(HMODULE module, void (*LP_SCRIPT_MAIN)())
{
	scriptRegister(module, LP_SCRIPT_MAIN);
}

// TODO: implement
DLL_EXPORT void scriptUnregister(HMODULE module)
{
}

// TODO: implement
DLL_EXPORT void nativeInit(uint64_t hash)
{
}

// TODO: implement
DLL_EXPORT void nativePush64(uint64_t value)
{
}

// TODO: implement
DLL_EXPORT uint64_t* nativeCall()
{
	return nullptr;
}

// TODO: implement
DLL_EXPORT uint64_t* getGlobalPtr(int globalIndex)
{
	return nullptr;
}

// TODO: implement
DLL_EXPORT uint64_t* getStaticPtr(const char* scriptName, int staticIndex)
{
	return nullptr;
}

DLL_EXPORT int worldGetAllPeds(int* array, int arraySize)
{
	int count = 0;
	const auto pool = rage::fwBasePool::GetPedPool();

	if (!pool)
		return 0;

	for (int i = 0; count < arraySize && i < static_cast<int>(pool->m_size); i++)
	{
		if (pool->IsValid(i))
		{
			if (auto obj = pool->GetAt<uint64_t>(i))
				array[count++] = globalvars::g_CoreInstance->m_FwScriptGuidCreateGuid(obj);
		}
	}

	return count;
}

DLL_EXPORT int worldGetAllObjects(int* array, int arraySize)
{
	int count = 0;
	const auto pool = rage::fwBasePool::GetObjectPool();

	if (!pool)
		return 0;

	for (int i = 0; count < arraySize && i < static_cast<int>(pool->m_size); i++)
	{
		if (pool->IsValid(i))
		{
			if (auto obj = pool->GetAt<uint64_t>(i))
				array[count++] = globalvars::g_CoreInstance->m_FwScriptGuidCreateGuid(obj);
		}
	}

	return count;
}

DLL_EXPORT int worldGetAllVehicles(int* array, int arraySize)
{
	int count = 0;
	const auto pool = rage::fwBasePool::GetVehiclePool();

	if (!pool)
		return 0;

	for (int i = 0; count < arraySize && i < static_cast<int>(pool->m_size); i++)
	{
		if (pool->IsValid(i))
		{
			if (auto obj = pool->GetAt<uint64_t>(i))
				array[count++] = globalvars::g_CoreInstance->m_FwScriptGuidCreateGuid(obj);
		}
	}

	return count;
}

DLL_EXPORT int worldGetAllPickups(int* array, int arraySize)
{
	int count = 0;
	const auto pool = rage::fwBasePool::GetPickupPool();

	if (!pool)
		return 0;

	for (int i = 0; count < arraySize && i < static_cast<int>(pool->m_size); i++)
	{
		if (pool->IsValid(i))
		{
			if (auto obj = pool->GetAt<uint64_t>(i))
				array[count++] = globalvars::g_CoreInstance->m_FwScriptGuidCreateGuid(obj);
		}
	}

	return count;
}

// TODO: implement
DLL_EXPORT BYTE* getScriptHandleBaseAddress(int handle)
{
	return nullptr;
}

DLL_EXPORT eGameVersion getGameVersion()
{
	return (GetModuleHandleA("steam_api64.dll")) == nullptr ? eGameVersion::VER_NO_STEAM_1355 : eGameVersion::VER_STEAM_1355;
}