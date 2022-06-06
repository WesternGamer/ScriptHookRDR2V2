#pragma once


using rage__scrThread__Update = uint32_t(*)(rage::scrThread* thread, uint32_t opsCount);

class Core
{
public:
	static bool EnsureSelfReference(HMODULE hModule);
	static bool DeleteSelfReference();

	bool Init();
	bool Uninit();

	rage__scrThread__Update m_RageScrThreadUpdate{};
};