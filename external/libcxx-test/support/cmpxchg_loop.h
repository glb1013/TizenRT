/****************************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <atomic>

template <class A, class T>
bool cmpxchg_weak_loop(A& atomic, T& expected, T desired) {
  for (int i = 0; i < 10; i++) {
    if (atomic.compare_exchange_weak(expected, desired) == true) {
      return true;
    }
  }

  return false;
}

template <class A, class T>
bool cmpxchg_weak_loop(A& atomic, T& expected, T desired,
                       std::memory_order success,
                       std::memory_order failure) {
  for (int i = 0; i < 10; i++) {
    if (atomic.compare_exchange_weak(expected, desired, success,
                                     failure) == true) {
      return true;
    }
  }

  return false;
}

template <class A, class T>
bool c_cmpxchg_weak_loop(A* atomic, T* expected, T desired) {
  for (int i = 0; i < 10; i++) {
    if (std::atomic_compare_exchange_weak(atomic, expected, desired) == true) {
      return true;
    }
  }

  return false;
}

template <class A, class T>
bool c_cmpxchg_weak_loop(A* atomic, T* expected, T desired,
                         std::memory_order success,
                         std::memory_order failure) {
  for (int i = 0; i < 10; i++) {
    if (std::atomic_compare_exchange_weak_explicit(atomic, expected, desired,
                                                   success, failure) == true) {
      return true;
    }
  }

  return false;
}
