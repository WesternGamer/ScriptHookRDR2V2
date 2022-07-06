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

	void queue(const char* name, LPVOID target, LPVOID ownFunc, LPVOID* original);

	void hook();

private:
	void* m_OriginalRageScrThreadUpdate{};
	std::stack<hooks> m_hooks;
};