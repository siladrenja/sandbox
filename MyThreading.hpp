#pragma once
#include <thread>
#include <atomic>



namespace CustomThreading {
		namespace {
			//template<class _Fn, class... _Args>
			//struct ThreadFuncArgs {
			//	bool& Thr;
			//	_Fn&& _Fx;
			//	_Args&& _Ax;
			//};
		
		}

		template <class _Fn, class... _Args>
		void ThreadFunction(std::atomic<bool>& Thr, _Fn&& _Fx, _Args&& ..._Ax) {
			Thr = true; 
			_Fx(_Ax...);	
			Thr = false;
		}

		class m_Thread {
		public:
			std::atomic<bool> isActive = { false };

			m_Thread() {
				isActive = false;
			}

			
			template<typename F, typename... Args>
			m_Thread(F&& f, Args&&... args) : _thread{
				[this](auto&& f, auto&&... args) {
				
				f(args...);
				
				isActive = false;
			},
			std::forward<F>(f),
			std::forward<Args>(args)... } {
				isActive = true;
			}

			int Join() {
				if (_thread.joinable()) {
					_thread.join();
					return TRUE;
				}

				return FALSE;
			}


		private:
			std::thread _thread;

		};
	
		
		
}

	
