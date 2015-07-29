// -*- mode: c++; tab-width: 4; indent-tabs-mode: t; eval: (progn (c-set-style "stroustrup") (c-set-offset 'innamespace 0)); -*-
// vi:set ts=4 sts=4 sw=4 noet :
//
// Copyright 2011, The TPIE development team
// 
// This file is part of TPIE.
// 
// TPIE is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation, either version 3 of the License, or (at your
// option) any later version.
// 
// TPIE is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with TPIE.  If not, see <http://www.gnu.org/licenses/>

///////////////////////////////////////////////////////////////////////////
/// \file tpie/memory.h Memory management subsystem.
///////////////////////////////////////////////////////////////////////////

#ifndef __TPIE_MEMORY_H__
#define __TPIE_MEMORY_H__

#include <tpie/config.h>
#include <tpie/util.h>
#include <mutex>
#include <unordered_map>
#include <type_traits>
#include <utility>
#include <memory>
#include <atomic>

namespace tpie {

///////////////////////////////////////////////////////////////////////////////
/// \brief Thrown when trying to allocate too much memory.
///
/// When the memory limit is exceeded and the memory limit enforcement policy
/// is set to THROW, this error is thrown by the memory subsystem.
///////////////////////////////////////////////////////////////////////////////
struct out_of_memory_error : public std::bad_alloc {
	const char * msg;
	out_of_memory_error(const char * s) : msg(s) { }
	virtual const char* what() const throw() {return msg;}
};


///////////////////////////////////////////////////////////////////////////////
/// \brief Memory management object used to track memory usage.
///////////////////////////////////////////////////////////////////////////////
class memory_manager {
public:
	///////////////////////////////////////////////////////////////////////////
	/// Memory limit enforcement policies.
	///////////////////////////////////////////////////////////////////////////
	enum enforce_t {
		/** Ignore when running out of memory. */
		ENFORCE_IGNORE,
		/** \brief Log to debug log when the memory limit is exceeded.
		 * Note that not all violations will be logged. */
		ENFORCE_DEBUG,
		/** \brief Log a warning when the memory limit is exceeded. Note that
		 * not all violations will be logged. */
		ENFORCE_WARN,
		/** Throw an out_of_memory_error when the memory limit is exceeded. */
		ENFORCE_THROW
	};

	///////////////////////////////////////////////////////////////////////////
	/// Return the current amount of memory used.
	///////////////////////////////////////////////////////////////////////////
	size_t used() const throw();
   
	///////////////////////////////////////////////////////////////////////////
	/// Return the amount of memory still available to allocation.
	///////////////////////////////////////////////////////////////////////////
	size_t available() const throw();

	///////////////////////////////////////////////////////////////////////////
	/// Return the memory limit.
	///////////////////////////////////////////////////////////////////////////
	size_t limit() const throw() {return m_limit;}
	
	///////////////////////////////////////////////////////////////////////////
	/// \brief Update the memory limit.
	/// If the memory limit is exceeded by decreasing the limit,
	/// no exception will be thrown.
	/// \param new_limit The new memory limit in bytes.
	///////////////////////////////////////////////////////////////////////////
	void set_limit(size_t new_limit);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Set the memory limit enforcement policy.
	/// \param e The new enforcement policy.
	///////////////////////////////////////////////////////////////////////////
	void set_enforcement(enforce_t e);

	///////////////////////////////////////////////////////////////////////////
	/// \brief Return the current memory limit enforcement policy.
	///////////////////////////////////////////////////////////////////////////
	enforce_t enforcement() {return m_enforce;}

	///////////////////////////////////////////////////////////////////////////
	/// \internal
	/// Register that more memory has been used.
	/// Possibly throws a warning or an exception if the memory limit is
	/// exceeded, depending on the enforcement.
	///////////////////////////////////////////////////////////////////////////
	void register_allocation(size_t bytes);

	///////////////////////////////////////////////////////////////////////////
	/// \internal
	/// Register that some memory has been freed.
	///////////////////////////////////////////////////////////////////////////
	void register_deallocation(size_t bytes);

	///////////////////////////////////////////////////////////////////////////
	/// \internal
	/// Construct the memory manager object.
	///////////////////////////////////////////////////////////////////////////
	memory_manager();	

	///////////////////////////////////////////////////////////////////////////
	/// \internal
	/// Allocate the largest consecutive memory possible.
	///////////////////////////////////////////////////////////////////////////
	std::pair<uint8_t *, size_t> __allocate_consecutive(size_t upper_bound, size_t granularity);

#ifndef TPIE_NDEBUG
	// The following methods take the mutex before calling the private doubly
	// underscored equivalent.
	void register_pointer(void * p, size_t size, const std::type_info & t);
	void unregister_pointer(void * p, size_t size, const std::type_info & t);
	void assert_tpie_ptr(void * p);
	void complain_about_unfreed_memory();
#endif


private:
	std::atomic<size_t> m_used;
	size_t m_limit;
	size_t m_maxExceeded;
	size_t m_nextWarning;
	enforce_t m_enforce;

#ifndef TPIE_NDEBUG
	std::mutex m_mutex;

	// Before calling these methods, you must have the mutex.
	void __register_pointer(void * p, size_t size, const std::type_info & t);
	void __unregister_pointer(void * p, size_t size, const std::type_info & t);
	void __assert_tpie_ptr(void * p);
	void __complain_about_unfreed_memory();

	std::unordered_map<void *, std::pair<size_t, const std::type_info *> > m_pointers;
#endif
};

///////////////////////////////////////////////////////////////////////////////
/// \internal \brief Used by tpie_init to initialize the memory manager.
///////////////////////////////////////////////////////////////////////////////
void init_memory_manager();

///////////////////////////////////////////////////////////////////////////////
/// \internal \brief Used by tpie_finish to deinitialize the memory manager.
///////////////////////////////////////////////////////////////////////////////
void finish_memory_manager();

///////////////////////////////////////////////////////////////////////////////
/// \brief Return a reference to the memory manager.
/// May only be called when init_memory_manager has been called.
/// See \ref tpie_init().
///////////////////////////////////////////////////////////////////////////////
memory_manager & get_memory_manager();

///////////////////////////////////////////////////////////////////////////////
/// \internal
/// Register a pointer, for debugging memory leaks and such.
///////////////////////////////////////////////////////////////////////////////
inline void __register_pointer(void * p, size_t size, const std::type_info & t) {
#ifndef TPIE_NDEBUG
	get_memory_manager().register_pointer(p, size, t);
#else
	unused(p);
	unused(size);
	unused(t);
#endif
}

///////////////////////////////////////////////////////////////////////////////
/// \internal
/// Unregister a registered pointer.
///////////////////////////////////////////////////////////////////////////////
inline void __unregister_pointer(void * p, size_t size, const std::type_info & t) {
#ifndef TPIE_NDEBUG
	get_memory_manager().unregister_pointer(p, size, t);
#else
	unused(p);
	unused(size);
	unused(t);
#endif
}

///////////////////////////////////////////////////////////////////////////////
/// In a debug build, assert that a given pointer has been allocated with
/// tpie_new.
///////////////////////////////////////////////////////////////////////////////
inline void assert_tpie_ptr(void * p) {
#ifndef TPIE_NDEBUG
	if (p)
		get_memory_manager().assert_tpie_ptr(p);
#else
	unused(p);
#endif
}

#ifndef DOXYGEN
///////////////////////////////////////////////////////////////////////////////
/// \internal
///////////////////////////////////////////////////////////////////////////////
template <typename T, 
	bool x=std::is_polymorphic<T>::value
>
struct __object_addr {
	void * operator()(T * o) {return static_cast<void *>(o);}
};

///////////////////////////////////////////////////////////////////////////////
/// \internal
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct __object_addr<T, true> {
	void * operator()(T * o) {return dynamic_cast<void *>(o);}
};
#endif

///////////////////////////////////////////////////////////////////////////////
/// Cast between pointer types. If the input pointer is polymorphic, its base
/// address is found, and that is then casted to the output type.
///
/// \tparam D A non-polymorphic pointer type.
/// \tparam T Any type.
///////////////////////////////////////////////////////////////////////////////
template <typename D, typename T>
inline D ptr_cast(T * t) { return reinterpret_cast<D>(__object_addr<T>()(t)); }


template <typename T>
inline T * __allocate() {
	if(!std::is_polymorphic<T>::value) return reinterpret_cast<T *>(new uint8_t[sizeof(T)]);	
	uint8_t * x = new uint8_t[sizeof(T)+sizeof(size_t)];
	*reinterpret_cast<size_t*>(x) = sizeof(T);
	return reinterpret_cast<T*>(x + sizeof(size_t));
}

template <typename T>
inline size_t tpie_size(T * p) {
	if(!std::is_polymorphic<T>::value) return sizeof(T);
	uint8_t * x = ptr_cast<uint8_t *>(p);
	return * reinterpret_cast<size_t *>(x - sizeof(size_t));
}


///////////////////////////////////////////////////////////////////////////////
/// \internal
/// Used to perform allocations in a safe manner.
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct array_allocation_scope_magic {
	size_t size;
	T * data;
	array_allocation_scope_magic(size_t s): size(0), data(0) {
		get_memory_manager().register_allocation(s * sizeof(T) );
		size=s;
	}

	T * allocate() {
		data = new T[size];
		__register_pointer(data, size*sizeof(T), typeid(T));
		return data;
	}

	T * finalize() {
		T * d = data;
		size = 0;
		data = 0;
		return d;
	}

	~array_allocation_scope_magic() {
		if(size) get_memory_manager().register_deallocation(size*sizeof(T));
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \internal
/// Used in tpie_new to perform allocations in a safe manner.
///////////////////////////////////////////////////////////////////////////////
template <typename T>
struct allocation_scope_magic {
	size_t deregister;
	T * data;
	allocation_scope_magic(): deregister(0), data(0) {}
	
	T * allocate() {
		get_memory_manager().register_allocation(sizeof(T));
		deregister = sizeof(T);
		data = __allocate<T>();
		__register_pointer(data, sizeof(T), typeid(T));
		return data;
	}

	T * finalize() {
		T * d = data;
		deregister = 0;
		data = 0;
		return d;
	}
	
	~allocation_scope_magic() {
		if (data) __unregister_pointer(data, sizeof(T), typeid(T));
		delete[] reinterpret_cast<uint8_t*>(data);
		if (deregister) get_memory_manager().register_deallocation(deregister);
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Allocate a new array and register its memory usage.
/// \param size The number of elements in the new array.
/// \return The new array.
///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline T * tpie_new_array(size_t size) {
	array_allocation_scope_magic<T> m(size);
	m.allocate();
	return m.finalize();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Allocate an element of the type given as template parameter, and
/// register its memory usage with TPIE.
///
/// The implementation of tpie_new either uses variadic templates (if supported
/// by the compiler) or a bunch of tpie_new overloads to support a variable
/// number of constructor parameters.
///
/// \tparam T The type of element to allocate
/// \tparam Args The variadic number of types of constructor parameters.
/// \param args The variadic number of arguments to pass to the constructor of
/// T.
///////////////////////////////////////////////////////////////////////////////
template <typename T, typename ... Args>
inline T * tpie_new(Args &&... args) {
	allocation_scope_magic<T> m; 
	new(m.allocate()) T(std::forward<Args>(args)...);
	return m.finalize();
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Delete an object allocated with tpie_new.
/// \param p the object to delete
///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void tpie_delete(T * p) throw() {
	if (p == 0) return;
	get_memory_manager().register_deallocation(tpie_size(p));
	uint8_t * pp = ptr_cast<uint8_t *>(p);
	__unregister_pointer(pp, tpie_size(p), typeid(*p));
	p->~T();
	if(!std::is_polymorphic<T>::value) 
		delete[] pp;
	else
		delete[] (pp - sizeof(size_t));
}

///////////////////////////////////////////////////////////////////////////////
/// \brief Delete an array allocated with tpie_new_array.
/// \param a The array to delete.
/// \param size The size of the array in elements as passed to tpie_new_array.
///////////////////////////////////////////////////////////////////////////////
template <typename T>
inline void tpie_delete_array(T * a, size_t size) throw() {
	if (a == 0) return;
	get_memory_manager().register_deallocation(sizeof(T) * size);
	__unregister_pointer(a, sizeof(T) * size, typeid(T) );
	delete[] a;
}

struct tpie_deleter {
	template <typename T>
	void operator()(T * t) {
		tpie_delete(t);
	}
};

///////////////////////////////////////////////////////////////////////////////
/// \brief like std::unique_ptr, but delete the object with tpie_delete.
/// \tparam T the type of the object.
///////////////////////////////////////////////////////////////////////////////
template <typename T>
using unique_ptr=std::unique_ptr<T, tpie_deleter>;


///////////////////////////////////////////////////////////////////////////////
/// \brief A allocator object usable in STL containers, using the TPIE
/// memory manager.
/// \tparam T The type of the elements that can be allocated.
///////////////////////////////////////////////////////////////////////////////
template <class T>
class allocator {
private:
    typedef std::allocator<T> a_t;
    a_t a;
public:
    typedef typename a_t::size_type size_type;
    typedef typename a_t::difference_type difference_type;
	typedef typename a_t::pointer pointer;
	typedef typename a_t::const_pointer const_pointer;
	typedef typename a_t::reference reference;
	typedef typename a_t::const_reference const_reference;
    typedef typename a_t::value_type value_type;

	allocator() throw() {}
	allocator(const allocator & a) throw() {unused(a);}
	template <typename T2>
	allocator(const allocator<T2> & a) throw() {unused(a);}

    template <class U> struct rebind {typedef allocator<U> other;};

    T * allocate(size_t size, const void * hint=0) {
		get_memory_manager().register_allocation(size * sizeof(T));
		T * res = a.allocate(size, hint);
		__register_pointer(res, size, typeid(T));
		return res;
    }

    void deallocate(T * p, size_t n) {
		if (p == 0) return;
		__unregister_pointer(p, n, typeid(T));
		get_memory_manager().register_deallocation(n * sizeof(T));
		return a.deallocate(p, n);
    }
    size_t max_size() const {return a.max_size();}

	template <typename U, typename ...TT>
	void construct(U * p, TT &&...x) {a.construct(p, std::forward<TT>(x)...);}

	void construct(T * p) {
		new(p) T();
	}
    void construct(T * p, const T& val) {a.construct(p, val);}
    void destroy(T * p) {a.destroy(p);}    
	pointer address(reference x) const {return &x;}
	const_pointer address(const_reference x) const {return &x;}


	friend bool operator==(const allocator &, const allocator &) {return true;}
	friend bool operator!=(const allocator &, const allocator &) {return false;}
};

///////////////////////////////////////////////////////////////////////////////
/// \brief Find the largest amount of memory that can be allocated as a single
/// chunk.
///////////////////////////////////////////////////////////////////////////////
size_t consecutive_memory_available(size_t granularity=5*1024*1024);

} //namespace tpie

#endif //__TPIE_MEMORY_H__
