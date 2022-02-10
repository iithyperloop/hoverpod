#include <thread>
#include <atomic>
#include <functional>

namespace Hyperloop {

	template <class T>
	class Thread {
		std::atomic<T> val;
		std::thread thread;
	public:
		Thread(void (*F)(std::atomic<T> &val), T initial_val) {
			val.store(initial_val);
			thread = std::thread(F, std::ref(val));
		}

		T get() {
			return val.load();
		}

		void run_synchronously() {
			thread.detach();
		}

		void run_asynchronously() {
			thread.attach();
		}
	};

}
