// Copyright (C) 2001 Octavian Procopiuc
//
// File:    ami_cache.h
// Author:  Octavian Procopiuc <tavi@cs.duke.edu>
//
// $Id: ami_cache.h,v 1.3 2002-01-03 20:36:12 tavi Exp $
//
// Declaration and definition of AMI_CACHE_MANAGER
// implementation(s).
//

#ifndef _AMI_CACHE_H
#define _AMI_CACHE_H

// The b_vector class.
#include <b_vector.h>

// The only implementation is AMI_cache_manager_lru.
#define AMI_CACHE_MANAGER AMI_cache_manager_lru

// Base class for all implementations.
class AMI_cache_manager_base {
protected:

  // Max size.
  size_t capacity_;

  // Associativity.
  size_t assoc_;

  // Constructor. Protected to prevent instantiation of this class.
  AMI_cache_manager_base(size_t capacity, size_t assoc):
    capacity_(capacity), assoc_(assoc) {}

public:

};

// Implementation using an LRU replacement policy.
template<class T, class W>
class AMI_cache_manager_lru: public AMI_cache_manager_base {
protected:

  // The type of the item stored. Pair of key and T.
  typedef pair<size_t,T> item_type_;

  // The array of items.
  item_type_ * pdata_;

  // The number of sets (equals capacity / associativity).
  size_t sets_;

  // The writeout function object.
  W writeout_;

public:

  AMI_cache_manager_lru(size_t capacity, size_t assoc = 0);

  // Read an item from the cache based on the key k. The item is
  // passed to the user and *removed* from the cache (but not written
  // out).
  bool read(size_t k, T& item);

  // Write an item to the cache based on the key k. If the set where
  // the item should go is full, the last item (ie, the l.r.u. item)
  // is written out.
  bool write(size_t k, const T& item);

  // Erase an item from the cache based on the key k. The item is
  // written out first.
  bool erase(size_t k);

  // Write out all items in the cache.
  void flush();

  ~AMI_cache_manager_lru();
};

template<class T, class W>
AMI_cache_manager_lru<T,W>::AMI_cache_manager_lru(size_t capacity, size_t assoc):
  AMI_cache_manager_base(capacity, assoc == 0 ? capacity: assoc), writeout_() {

  size_t i;

  if (capacity_ != 0) {
    if (assoc_ > capacity_) {
      LOG_WARNING_ID("Associativity too big. Reduced to capacity.");
      assoc_ = capacity_;
    }
    assert(capacity_ % assoc_ == 0);
    
    // The number of cache lines.
    sets_ = capacity_ / assoc_;
    
    // Initialize the array (mark all positions empty).
    pdata_ = new item_type_[capacity_];
    for (i = 0; i < capacity_; i++)
      pdata_[i].first = 0;

  } else {

    pdata_ = NULL;
    sets_ = 0;
  }
}

template<class T, class W>
bool AMI_cache_manager_lru<T,W>::read(size_t k, T& item) {
  
  size_t i;
  if (capacity_ == 0)
    return false;

  assert(k != 0);

  // The cache line, based on the key k.
  b_vector<item_type_> set(&pdata_[(k % sets_) * assoc_], assoc_);

  // Find the item using the key.
  for (i = 0; i < set.capacity(); i++)
    if (set[i].first == k)
      break;
  if (i == set.capacity())
    return false;

  //  memcpy(&item, &set[i].second, sizeof(T));
  item = set[i].second;

  // Erase the item from the cache.
  // NB: We don't write it out because we pass it up to the user.
  if (set.capacity() > 1)
    set.erase(i);

  // Mark the last item empty.
  set[set.capacity() - 1].first = 0;

  return true;
}

template<class T, class W>
bool AMI_cache_manager_lru<T,W>::write(size_t k, const T& item) {

  assert(k != 0);

  if (capacity_ == 0) {

    writeout_(item);

  } else {

    // The cache line, based on the key k.
    b_vector<item_type_> set(&pdata_[(k % sets_) * assoc_], assoc_);
    
    // Write out the item in the last position.
    if (set[assoc_ - 1].first != 0)
      writeout_(set[assoc_ - 1].second);
    
    // Insert in the first position.
    if (set.capacity() > 1)
      set.insert(item_type_(k, item), 0);
    else
      set[0] = item_type_(k, item);
  }

  return true;
}

template<class T, class W>
bool AMI_cache_manager_lru<T,W>::erase(size_t k) {

  size_t i;
  assert(k != 0);

  // The cache line, based on the key k.
  b_vector<item_type_> set(&pdata_[(k % sets_) * assoc_], assoc_);

  // Find the item using the key.
  for (i = 0; i < set.capacity(); i++)
    if (set[i].first == k)
      break;

  // If not found, return false.
  if (i == set.capacity())
    return false;

  // Write out the item in position i;
  writeout_(set[i].second);

  // Erase the item from the cache.
  set.erase(i);

  // Mark last item in the set as empty.
  set[set.capacity() - 1].first = 0;
  return true;
}

template<class T, class W>
void AMI_cache_manager_lru<T,W>::flush() {
  size_t i;
  for (i = 0; i < capacity_; i++) {
    if (pdata_[i].first != 0) {
      writeout_(pdata_[i].second);
      pdata_[i].first = 0;
    }
  }
}

template<class T, class W>
AMI_cache_manager_lru<T,W>::~AMI_cache_manager_lru() {
  flush();
}

#endif // _AMI_CACHE_H
