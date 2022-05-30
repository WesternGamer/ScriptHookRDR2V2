#include "../pch.h"

/*
* Core::EnsureSelfReference -> Bool (hModule: HMODULE) DOC:
*	This function is necessary for the lifetime of our own module.
*	ScriptHook is a loaded as a dependency from the .asi scripts hence when we free the scripts it will decrement our own ref count aswell
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