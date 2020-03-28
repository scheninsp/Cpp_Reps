//implement a custom shared_ptr

//required:
//operators : ->, *, &
//functions : 
//copy constructor
//copy assign 
//get(), reset()
//hold(), release()
//swap()
//make_shared()

//feature:
//using template
//using pimpl

#include<functional>
#include<atomic>
#include<iostream>  //debug

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
			std::atomic<unsigned int> m_counter;

		public:
			template<typename D=DefaultDeleter>
			SharedPtrImpl(T* ptr = nullptr, D deleter = D()) :m_ptr(ptr), m_deleter(deleter), m_counter(1) {};

			template<typename D = DestructorDeleter, typename... Args> 
			SharedPtrImpl(T* ptr = nullptr, D deleter = D(), Args&&... args) :m_ptr(ptr), m_deleter(deleter), m_counter(1) {
				new (m_ptr) T(std::forward<Args>(args)...);
			};

			~SharedPtrImpl() {
				m_deleter(m_ptr);
			};

			T* operator->() const {
				return m_ptr;
			};

			T& operator*() const {
				return *m_ptr;
			};

			T* get() const {
				return m_ptr;
			};

			void hold() {
				++m_counter;
			};

			bool release(){
				--m_counter;
				return m_counter == 0;
			};

		}; // class SharedPtrImpl

	}//namespace impl

	template<typename T>
	class SharedPtr {

	private:
		impl::SharedPtrImpl<T> *m_impl;

	public:

		explicit SharedPtr(impl::SharedPtrImpl<T> *impl) :m_impl(impl){};

		template<typename D = impl::DefaultDeleter>
		SharedPtr(T* ptr = nullptr, D deleter = D()):m_impl(new impl::SharedPtrImpl<T>(ptr, deleter)) {};

		//class type in template will be automatic casted in member function (exp.45, effective cpp)
		template<typename U, typename D = impl::DefaultDeleter>
		SharedPtr(U* ptr = nullptr, D deleter = D()) :m_impl(new impl::SharedPtrImpl<T>(ptr, deleter)) {};

		~SharedPtr() {
			// -1, if m_counter == 0, delete impl
			if (m_impl->release()) {
				delete m_impl;
			}
		}

		//copy constructor
		SharedPtr(const SharedPtr<T> &other) {
			m_impl = other.m_impl;
			m_impl->hold();
		}
		
		template<typename U>
		SharedPtr(const SharedPtr<U> &other) {
			m_impl = other.m_impl;
			m_impl->hold();
		}

		//swap self 
		void swap(SharedPtr &other) {
			std::swap(m_impl, other.m_impl);
		}

		//copy assign
		SharedPtr<T> & operator=(const SharedPtr<T> &other) {
			SharedPtr<T> tmp(other);
			swap(tmp);
			return *this;
		}

		template<typename U>
		SharedPtr<U> & operator=(const SharedPtr<U> &other) {
			SharedPtr<U> tmp(other);
			swap(tmp);
			return *this;
		}

		//operators : ->, &
		T* operator->() const {
			return m_impl->operator->();
		}

		T& operator*() const {
			return **m_impl;
		}

		T* get()const{
			return m_impl->get();
		}

		//reset only avaliable when shared_ptr has no reference
		template<typename D= impl::DefaultDeleter>
		void reset(T* ptr=nullptr, D deleter=D()) {
			if (release(m_impl)) { delete m_impl; }

			m_impl = new impl::SharedPtrImpl(ptr, deleter);
		}

	}; //class SharedPtr

	template<typename T>
	void swap(SharedPtr<T> &lhs, SharedPtr<T> &rhs) {
		lhs.swap(rhs);
	};
	
	//(1) allocate memory for a ptr to T
	//(2) cast ptr type to T* 
	//(3) construct impl::SharedPtrImpl<T>
	//(4) construct SharedPtr<T>
	template<typename T, typename... Args>
	SharedPtr<T> make_shared(Args&&... args) {
		
		//debug
		std::cout << "sizeof(T): " <<sizeof(T) << std::endl;
		std::cout << "sizeof(impl::SharedPtrImpl<T>): " <<sizeof(impl::SharedPtrImpl<T>) << std::endl;

		void* ptr1 = operator new(sizeof(T) + sizeof(impl::SharedPtrImpl<T>));
		if (ptr1 == nullptr) {
			throw std::bad_alloc();
		}
		char* ptr = static_cast<char*>(ptr1);
		char* ptr3 = ptr + sizeof(impl::SharedPtrImpl<T>);
		auto t_ptr = reinterpret_cast<T *>(ptr3);    
		//memory : 
		//ptr --- SharedPtrImpl<T>
		//t_ptr --- T

		try {
			auto impl = new(ptr) impl::SharedPtrImpl<T>(t_ptr, impl::DestructorDeleter(), std::forward<T>(args)...);
			return SharedPtr<T>(impl);
		}
		catch (...) {
			operator delete(ptr);
			throw;
		}
		
	};
	

}//namespace scutil