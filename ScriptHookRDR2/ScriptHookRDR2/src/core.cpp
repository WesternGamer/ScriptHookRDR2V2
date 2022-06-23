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

rage::fwBasePool* GetPtrFromEncryption(GameVariableEncryption* encryptionPtr)
{
	// https://uspto.report/patent/grant/11273380 Method and apparatus for preventing cheating in a video game environment by providing obfuscated game variables

	const auto ptr = encryptionPtr;
	const auto firstShift = _rotl64(_rotr64(ptr->second, 2), 32);
	const auto secondShift = _rotl64(_rotl64(firstShift ^ ptr->first, 32), ((firstShift & 0xFF) & 0x1Fu) + 2);
	return reinterpret_cast<rage::fwBasePool*>(~secondShift);
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

	m_FwScriptGuidCreateGuid = scanner.scan("rage::fwScriptGuid::CreateGuid", "E8 ? ? ? ? B3 01 8B 15").Sub(0x8D).As<rage__fwScriptGuid__CreateGuid>();

	m_PedPoolEncryptionInstance = scanner.scan("Ped pool Encryption", "0F 28 F0 48 85 DB 74 56 8A 05 ? ? ? ? 84 C0 75 05").Add(0xA).Rip().As<GameVariableEncryption*>();
	m_PedPoolInstance = GetPtrFromEncryption(m_PedPoolEncryptionInstance);

	m_VehiclePoolEncryptionInstance = scanner.scan("Vehicle Pool Encryption", "48 83 EC 20 8A 05 ? ? ? ? 45 33 E4").Add(0x6).Rip().As<GameVariableEncryption*>();
	m_VehiclePoolInstance = GetPtrFromEncryption(m_VehiclePoolEncryptionInstance);

	m_ObjectPoolEncryptionInstance = scanner.scan("Object Pool Encryption", "3C 05 75 67").Add(0x14).Rip().As<GameVariableEncryption*>();
	m_ObjectPoolInstance = GetPtrFromEncryption(m_ObjectPoolEncryptionInstance);

	m_PickupPoolEncryptionInstance = scanner.scan("Pickup Pool Encryption", "0F 84 ? ? ? ? 8A 05 ? ? ? ? 48 85").Add(0x8).Rip().As<GameVariableEncryption*>();
	m_PickupPoolInstance = GetPtrFromEncryption(m_PickupPoolEncryptionInstance);

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