#include "../../pch.h"

// https://uspto.report/patent/grant/11273380 Method and apparatus for preventing cheating in a video game environment by providing obfuscated game variables
// Not ideal but it does the job

rage::fwBasePool* rage::fwBasePool::GetPedPool()
{
	const auto ptr = globalvars::g_CoreInstance->m_PedPoolEncryptionInstance;

	if (!ptr->isSet)
		return nullptr;

	const auto encr = _rotr64(_rotl64(ptr->second, 0x20), 2);
	const auto actual = _rotl64(_rotl64(encr ^ ptr->first, ((encr & 0xFF) & 0x1Fu) + 3), 0x20);

	return reinterpret_cast<fwBasePool*>(~actual);
}

rage::fwBasePool* rage::fwBasePool::GetObjectPool()
{
	const auto ptr = globalvars::g_CoreInstance->m_ObjectPoolEncryptionInstance;

	if (!ptr->isSet)
		return nullptr;

	const auto encr = _rotl64(_rotr64(ptr->second, 2), 32);
	const auto actual = _rotl64(_rotl64(encr ^ ptr->first, 32), ((encr & 0xFF) & 0x1Fu) + 2);
	return reinterpret_cast<fwBasePool*>(~actual);
}

rage::fwBasePool* rage::fwBasePool::GetVehiclePool()
{
	const auto ptr = globalvars::g_CoreInstance->m_VehiclePoolEncryptionInstance;

	if (!ptr->isSet)
		return nullptr;

	const auto encr = _rotl64(_rotr64(ptr->second, 1), 32);
	const auto actual = _rotl64(_rotl64(encr ^ ptr->first, 32), ((encr & 0xFF) & 0x1Fu) + 4);
	return reinterpret_cast<fwBasePool*>(~actual);
}

rage::fwBasePool* rage::fwBasePool::GetPickupPool()
{
	const auto ptr = globalvars::g_CoreInstance->m_PickupPoolEncryptionInstance;

	if (!ptr->isSet)
		return nullptr;

	const auto encr = _rotl64(_rotr64(ptr->second, 2), 32);
	const auto actual = _rotl64(_rotl64(ptr->first ^ encr, 32), ((encr & 0xFF) & 0x1Fu) + 2);
	return reinterpret_cast<fwBasePool*>(~actual);
}