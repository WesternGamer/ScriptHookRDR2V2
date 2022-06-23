#pragma once


using rage__scrThread__Update = uint32_t(*)(rage::scrThread* thread, uint32_t opsCount);

using rage__fwScriptGuid__CreateGuid = uint32_t(*)(uint64_t* base);

struct GameVariableEncryption // Memory representation of game variable obfuscation in .data section
{
	bool isSet;				// 0x0000
	char pad[7];			// 0x0001 compiler...
	uint64_t first;			// 0x0008
	uint64_t second;		// 0x0010
};

class Core
{
public:
	static bool EnsureSelfReference(HMODULE hModule);
	static bool DeleteSelfReference();

	bool Init();
	bool Uninit();

	rage__scrThread__Update m_RageScrThreadUpdate{};

	rage__fwScriptGuid__CreateGuid m_FwScriptGuidCreateGuid{};

	// Ped pool
	GameVariableEncryption* m_PedPoolEncryptionInstance{};
	rage::fwBasePool* m_PedPoolInstance{};

	// Vehicle Pool
	GameVariableEncryption* m_VehiclePoolEncryptionInstance{};
	rage::fwBasePool* m_VehiclePoolInstance{};

	// Object Pool
	GameVariableEncryption* m_ObjectPoolEncryptionInstance{};
	rage::fwBasePool* m_ObjectPoolInstance{};

	// Pickup Pool
	GameVariableEncryption* m_PickupPoolEncryptionInstance{};
	rage::fwBasePool* m_PickupPoolInstance{};
};