#pragma once

namespace rage
{
	class fwBasePool
	{
	public:
		void* vtable;                // 0x0000
		uintptr_t m_entries;         // 0x0008
		uint8_t* m_flags;            // 0x0010
		uint32_t m_size;             // 0x0018
		uint32_t m_itemSize;         // 0x001C
		uint32_t m_0020;             // 0x0020
		uint32_t m_0024;             // 0x0024
		uint32_t m_freeSlotIndex;    // 0x0028

		bool full() const
		{
			return m_size - (m_freeSlotIndex & 0x3FFFFFFF) <= 256;
		}

		int64_t GetNumFreeSlots() const
		{
			return m_size - (static_cast<signed int>(4 * m_freeSlotIndex) >> 2);
		}

		int32_t GetScriptGuid(int32_t index) const
		{
			return (index << 8) + m_flags[index];
		}

		int32_t GetIndex(int32_t scriptGuid) const
		{
			return scriptGuid >> 8;
		}

		bool IsValid(int32_t index) const
		{
			return !(m_flags[index] & 0x80);
		}

		template<typename T>
		T* GetAt(uint32_t index)
		{
			if (m_flags[index])
				return reinterpret_cast<T*>(m_entries + (index * m_itemSize));

			return nullptr;
		}

		static fwBasePool* GetPedPool();
		static fwBasePool* GetObjectPool();
		static fwBasePool* GetVehiclePool();
		static fwBasePool* GetPickupPool();
	};
}