//implement a custom shared_ptr

//required:
//operators : ->, *, &
//functions : 
//copy constructor
//copy assign 
//get(), reset()
//hold(), release()
//swap()

//feature:
//using template
//using pimpl

#include<functional>
#include<atomic>

namespace scutil {

	namespace impl {

		class DefaultDeleter {
		public:
			template<typename T>
			void operator()(T* ptr) { delete ptr; }
		};

		class DestructorDeleter {
		public:
			template<typename T>
			void operator()(T* ptr) { ptr->~T(); }
		};

		template<typename T>
		class SharedPtrImpl {

		private:
			T* m_ptr;
			std::function<void(T*)> m_deleter;
			std::atomic<unsigned int> m_couter;

		public:
			template<typename D=DefaultDeleter>
			SharedPtrImpl(T* ptr = nullptr, D deleter = D()) :m_ptr(ptr), m_deleter(deleter), m_counter(1) {};

			template<typename D = DestructorDeleter, typename... Args> 
			SharedPtrImpl(T* ptr = nullptr, D deleter = D(), Args&&... args) :m_ptr(ptr), m_deleter(deleter), m_counter(1) {
				new (m_ptr) T(std::forward<Args>(args)...);
			};

			~SharedPtrImpl() {
				m_deleter(m_ptr);
			}

			T* operator->() const {
				return m_ptr;
			}

			T& operator&() const {
				return *m_ptr;
			}

			T* get() const {
				return m_ptr;
			}

			void hold() {
				++m_counter;
			}

			bool release{
				--m_counter;
				return m_counter == 0;
			}

		}; // class SharedPtrImpl

	}//namespace impl




}