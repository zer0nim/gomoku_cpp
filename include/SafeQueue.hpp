#ifndef SAFEQUEUE_HPP
# define SAFEQUEUE_HPP

# include <mutex>
# include <queue>

// Thread safe implementation of a Queue using a std::queue
// https://github.com/mtrebi/thread-pool
template <typename T>
class SafeQueue {
	public:
		SafeQueue() {
		}

		~SafeQueue() {
		}

		bool empty() {
			std::unique_lock<std::mutex> lock(_mutex);
			return _queue.empty();
		}

		int size() {
			std::unique_lock<std::mutex> lock(_mutex);
			return _queue.size();
		}

		void enqueue(T &t) {
			std::unique_lock<std::mutex> lock(_mutex);
			_queue.push(t);
		}

		bool dequeue(T &t) {
			std::unique_lock<std::mutex> lock(_mutex);

			if (_queue.empty())
				return false;
			t = std::move(_queue.front());

			_queue.pop();
			return true;
		}
	private:
		std::queue<T>	_queue;
		std::mutex		_mutex;
};

#endif
