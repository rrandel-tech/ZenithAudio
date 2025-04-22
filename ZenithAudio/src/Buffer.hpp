#pragma once

#include <cstdint>
#include <cstring>

namespace Zenith {

	class Buffer
	{
	public:
		Buffer() = default;

		Buffer(uint32_t size)
			: m_Size(size)
		{
			m_Data = new uint8_t[size];
		}

		~Buffer()
		{
			delete[] m_Data;
		}

		void Resize(uint32_t newSize)
		{
			if (newSize <= m_Size)
				return;

			uint8_t* newData = new uint8_t[newSize];
			if (m_Data)
			{
				std::memcpy(newData, m_Data, m_Size);
				delete[] m_Data;
			}
			m_Data = newData;
			m_Size = newSize;
		}

		uint8_t* Data() { return m_Data; }
		const uint8_t* Data() const { return m_Data; }
		uint32_t Size() const { return m_Size; }

	private:
		uint8_t* m_Data = nullptr;
		uint32_t m_Size = 0;
	};

}
