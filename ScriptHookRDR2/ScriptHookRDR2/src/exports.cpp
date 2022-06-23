#include "../pch.h"

#define DLL_EXPORT __declspec(dllexport)

DLL_EXPORT int worldGetAllPeds(int* array, int arraySize)
{
	int count = 0;
	const auto pool = globalvars::g_CoreInstance->m_PedPoolInstance;

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
	const auto pool = globalvars::g_CoreInstance->m_ObjectPoolInstance;

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
	const auto pool = globalvars::g_CoreInstance->m_VehiclePoolInstance;

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
	const auto pool = globalvars::g_CoreInstance->m_PickupPoolInstance;

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