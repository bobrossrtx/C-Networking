#pragma once
#include "net_common.h"

namespace net
{
	namespace ts
	{
		template<typename T>
		class tsqueue
		{
		public:
			tsqueue() = default;
			tsqueue(const tsqueue<T>&) = delete;
			virtual ~tsqueue() { clear(); }

		public:
			// Returns and maintainns item at front of Queue
			const T& front()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.front();
			}

			// Returns and maintainns item at back of Queue
			const T& back()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.back();
			}

			// Adds an item to back of Queue
			void push_back(const T& item)
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.emplace_back(std::move(item));
			}

			// Adds an item to front of Queue
			void push_front(const T& item)
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.emplace_front(std::move(item));
			}

			// Returns true if Queue has no items
			bool empty()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.empty();
			}

			// Returns number of items in Queue
			size_t count()
			{
				std::scoped_lock lock(muxQueue);
				return deqQueue.empty();
			}

			// Clears Queue
			void clear()
			{
				std::scoped_lock lock(muxQueue);
				deqQueue.clear();
			}

			// Removes and returns item from front of Queue
			T pop_front()
			{
				std::scoped_lock lock(muxQueue);
				auto t = std::move(deqQueue.front());
				deqQueue.pop_front();
				return t;
			}

			// Removes and returns item from back of Queue
			T pop_back()
			{
				std::scoped_lock lock(muxQueue);
				auto t = std::move(deqQueue.back());
				deqQueue.pop_back();
				return t;
			}

		protected:
			std::mutex muxQueue;
			std::deque<T> deqQueue;
		};
	}
}