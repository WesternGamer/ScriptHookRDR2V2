#pragma once

namespace rage
{
	class scrThread
	{
		using scrProgramId = uint32_t;

		enum eState
		{
			THREAD_STATE_IDLE,
			THREAD_STATE_RUNNING,
			THREAD_STATE_KILLED,
			THREAD_STATE_UNK3,
			THREAD_STATE_UNK4
		};

		class Serialized
		{
		public:
			uint32_t m_threadId;					// 0x0000
			scrProgramId m_ProgramId;				// 0x0004
			eState m_threadState;					// 0x0008
			uint32_t m_unk;							// 0x000C
			uint32_t m_StaticVarCountLow;			// 0x0010
			uint32_t m_StaticVarCount;				// 0x0014
			uint32_t m_timerA;						// 0x0018
			uint32_t m_timerB;						// 0x001C
			uint32_t m_timerC;						// 0x0020
			uint32_t m_unk1;						// 0x0024
			uint32_t m_unk2;						// 0x0028
			char pad_002C[0x24];					// 0x002C
			uint32_t m_stackSize;					// 0x0050
			char pad_0054[0xC];						// 0x0054
			uint32_t m_unk3;						// 0x0060
			char pad_0064[0x64C];					// 0x0054
		};

		class Info
		{
			using Command = void(*)(Info* info);

			uint64_t* retn = retnStack;			// 0x0000
			uint32_t argCount = 0;				// 0x0008
			char pad_000C[0x4];					// 0x000C
			uint64_t* args = argStack;			// 0x0010 
			uint32_t dataCount = 0;				// 0x0018
			char pad_001C[0x4];					// 0x001C
			uint8_t vectorSpace[192]{};			// 0x0020

			uint64_t argStack[32]{};
			uint64_t retnStack[16]{};

			void Reset()
			{
				argCount = 0;
				dataCount = 0;
				std::memset(retnStack, 0, sizeof(retnStack));
			}

			template<typename T>
			T GetArgument(int idx)
			{
				intptr_t* arguments = (intptr_t*)args;
				return *(T*)&arguments[idx];
			}

			uint64_t* GetResultPointer()
			{
				return retn;
			}

			template<typename T>
			void SetResult(int idx, T value)
			{
				intptr_t* returnValues = (intptr_t*)retn;
				*(T*)&returnValues[idx] = value;
			}

			template<typename T>
			void Push(T value)
			{
				static_assert(sizeof(T) <= 8);
				args[argCount++] = *reinterpret_cast<uint64_t*>(&value);
			}
		};

		virtual ~scrThread() = default;
		virtual eState Reset(scrProgramId programId, void const* staticArgs, int staticArgsCount) = 0;
		virtual eState Run(uint32_t opsCount) = 0;
		virtual eState Update(uint32_t opsCount) = 0;
		virtual void Kill() = 0;

		Serialized& GetSerialized()
		{
			return m_Serialized;
		}

		Serialized m_Serialized;		// 0x0008
		uintptr_t m_Stack;				// 0x06B8
		char pad_06C0[0x4];				// 0x06C0
		uint32_t m_OpsCount;			// 0x06C4
		uint32_t m_ArgCountBits;		// 0x06C8
		uint32_t m_StaticArgSize;		// 0x06CC
		const char* m_ExitMessage;		// 0x06D0
		scrProgramId m_ScriptNameHash;	// 0x06D8
		char pad_06DC[0x4];				// 0x06DC

	};	static_assert(sizeof(scrThread) == 0x6E0, "rage::scrThread is not properly sized!");
}