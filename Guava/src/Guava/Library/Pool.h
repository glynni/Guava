#pragma once

namespace Guava
{
	template<typename T>
	class Pool
	{
	public:

		Pool() {}

		void Reset()
		{
			m_UsedSize = 0;
		}

		void ReserveAdditional(const size_t size)
		{
			Resize(m_UsedSize + size);
		}

		void Push(const T& element)
		{
			Resize(++m_UsedSize);
			m_Memory[m_UsedSize-1] = element;
		}

		const size_t Size() const
		{
			return m_UsedSize;
		}

		const size_t MemorySize() const
		{
			return sizeof(T) * m_UsedSize;
		}

		const T* Data() const
		{
			return m_Memory.data();
		}

	private:

		std::vector<T> m_Memory;
		size_t m_MemorySize = 0;
		size_t m_UsedSize = 0;

		void Resize(const size_t size)
		{
			if (m_MemorySize < size)
			{
				m_Memory.resize(size);
				m_MemorySize = m_Memory.size();
			}
		}
	};
}