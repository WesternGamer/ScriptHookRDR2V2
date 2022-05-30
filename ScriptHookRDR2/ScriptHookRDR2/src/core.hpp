#pragma once

class Core
{
public:
	static bool EnsureSelfReference(HMODULE hModule);
	static bool DeleteSelfReference();
};