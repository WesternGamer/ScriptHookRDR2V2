#include "../pch.h"

Detour::Detour()
{
	MH_Initialize();
	globalvars::g_LogInstance->Write("Initializing Detour");
}


Detour::~Detour()
{
	MH_Uninitialize();
	globalvars::g_LogInstance->Write("Initialization of Detour");
}


void Detour::Queue(const char* name, LPVOID target, LPVOID ownFunc, LPVOID* original)
{
	m_hooks.push(hooks(name, target, ownFunc, original));
	globalvars::g_LogInstance->Write("Queued {} for hooking", name);
}

void Detour::Hook()
{
	MH_Initialize();
	while (!m_hooks.empty())
	{
		auto& [name, target, ownFunc, original] = m_hooks.top();
		MH_CreateHook(target, ownFunc, original);
		globalvars::g_LogInstance->Write("Hooked {}", name);
		m_doneHooks.push(target);
		m_hooks.pop();
	}
}

void Detour::Destroy()
{
	while (!m_doneHooks.empty())
	{
		MH_RemoveHook(m_doneHooks.top());
		m_doneHooks.pop();
	}
	globalvars::g_LogInstance->Write("Removed all Hooks");
}

void Detour::EnableAll()
{
	MH_EnableHook(MH_ALL_HOOKS);
}

void Detour::DisableAll()
{
	MH_DisableHook(MH_ALL_HOOKS);
}
