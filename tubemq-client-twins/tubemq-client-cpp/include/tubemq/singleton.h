/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef _TUBEMQ_SINGLETON_H
#define _TUBEMQ_SINGLETON_H

#include <assert.h>
#include <stdlib.h>

#include <mutex>
#include <thread>

#include "tubemq/noncopyable.h"

namespace tubemq {

template <typename T>
class Singleton : noncopyable {
 public:
  Singleton() = delete;
  ~Singleton() = delete;

  static T& instance() {
    std::call_once(once_, Singleton::init);
    assert(value_ != nullptr);
    return *value_;
  }

 private:
  static void init() { value_ = new T(); }

 private:
  static std::once_flag once_;
  static T* value_;
};

template <typename T>
T* Singleton<T>::value_ = nullptr;

}  // namespace tubemq

#endif  // _TUBEMQ_SINGLETON_H
