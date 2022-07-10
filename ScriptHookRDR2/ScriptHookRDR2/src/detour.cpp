#include "../pch.h"

void Detour::queue(const char* name, LPVOID target, LPVOID ownFunc, LPVOID* original)
{
	m_hooks.push(hooks(name, target, ownFunc, original));
	globalvars::g_LogInstance->Write("Queued {} for hooking", name);
}

void Detour::hook()
{
	MH_Initialize();
	while (!m_hooks.empty())
	{
		auto hook = m_hooks.top();
		// Do Minhook stuff
		// if mh_ok print:
		globalvars::g_LogInstance->Write("Hooked {}", hook.name);
		m_hooks.pop();
	}
}