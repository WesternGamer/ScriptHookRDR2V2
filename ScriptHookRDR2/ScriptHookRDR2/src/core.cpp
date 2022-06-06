#include "../pch.h"

/*
* Core::EnsureSelfReference -> Bool (hModule: HMODULE) DOC:
*	This function is necessary for the lifetime of our own module.
*	ScriptHook is a loaded as a dependency from the .asi scripts hence when we free the scripts it will decrement our own ref count as well
*	so if we don't increment it by ourself we will crash eventually.
*/
bool Core::EnsureSelfReference(HMODULE hModule)
{
	char fileName[MAX_PATH];
	GetModuleFileNameA(hModule, fileName, MAX_PATH);
	globalvars::g_Module = LoadLibraryA(fileName);
	return globalvars::g_Module != nullptr;
}

/*
* Core::DeleteSelfReference -> Bool () DOC:
*	This function is responsible for decrementing our ref count so we can freely unload from the process.
*/
bool Core::DeleteSelfReference()
{
	return FreeLibrary(globalvars::g_Module);
}

/*
* Core::Init() -> Bool () DOC:
*	This function is responsible for the startup of our hook.
*	It initializes the core standards needed for this hook to function properly.
*/
bool Core::Init()
{
	Scan scanner(nullptr); // Init our pattern scanner to access the game memory.

	m_RageScrThreadUpdate = scanner.scan("rage::scrThread::Update", "E8 ? ? ? ? 8B F8 E8 ? ? ? ? 80 3D").Add(1).Rip().As<rage__scrThread__Update>();

	return true;
}

/*
* Core::Uninit() -> Bool () DOC:
*	This function will cleanup our hook and remove it from memory.
*/
bool Core::Uninit()
{
	// TODO: implement cleanup logic
	return true;
}