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

	void queue(const char* name, LPVOID target, LPVOID ownFunc, LPVOID* original)
	{
		m_hooks.push(hooks(name, target, ownFunc, original));
		globalvars::g_LogInstance->Write("Queued {} for hooking", name);
	}

	void hook()
	{
		while (!m_hooks.empty())
		{
			auto hook = m_hooks.top();
			// Do Minhook stuff
			// if mh_ok print:
			globalvars::g_LogInstance->Write("Hooked {}", hook.name);
			m_hooks.pop();
		}
	}

private:
	void* m_OriginalRageScrThreadUpdate{};
	std::stack<hooks> m_hooks;
};