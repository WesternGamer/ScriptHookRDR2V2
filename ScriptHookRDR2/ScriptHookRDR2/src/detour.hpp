#pragma once

struct hooks
{
	const char* name;
	LPVOID target;
	LPVOID ownFunc;
	LPVOID* original;
};

class Detour
{
public:

	Detour();
	~Detour();

	void Queue(const char* name, LPVOID target, LPVOID ownFunc, LPVOID* original);

	void Hook();
	void Destroy();

	static void EnableAll();
	static void DisableAll();

private:
	void* m_OriginalRageScrThreadUpdate{};
	std::stack<hooks> m_hooks;
	std::stack<LPVOID> m_doneHooks;
};