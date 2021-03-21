/**
 * @file memory.hpp
 * @author Han Luo (han.luo@han.luo@gmail.com)
 * @brief Utilities to create continuous memory for c type data
 * @version 0.1
 * @date 2020-03-20
 *
 * @copyright Copyright (c) 2020
 * @license   MIT
 *
 */

#pragma once
#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdlib>
#include <type_traits>

namespace Memory {

template <typename DT> inline DT *createC(int m) { return new DT[m]; }

template <typename DT> inline void freeC(DT *array) {
  if (array)
    delete[] array;
}

template <typename DT> inline DT **createC(int m, int n) {
  DT **array = new DT *[m];
  *array = new DT[m * n];
  for (int i = 1; i < m; ++i) {
    array[i] = array[i - 1] + n;
  }
  return array;
}

template <typename DT> inline void freeC(DT **array) {
  if (array) {
    if (array[0])
      delete[] array[0];
    delete[] array;
  }
}

template <typename DT> inline DT ***createC(int m, int n, int k) {
  DT ***array = new DT **[m];
  *array = new DT *[m * n];
  **array = new DT[m * n * k];

  for (int i = 1; i < m; ++i) {
    array[i] = array[i - 1] + n;
    array[i][0] = array[i - 1][0] + n * k;
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 1; j < n; j++) {
      array[i][j] = array[i][j - 1] + k;
    }
  }
  return array;
}

template <typename DT> inline void freeC(DT ***array) {
  if (array) {
    if (array[0]) {
      if (array[0][0]) {
        delete[] array[0][0];
      }
      delete[] array[0];
    }
    delete[] array;
  }
}

template <int dim, typename T> struct pointer_n {
  static_assert(dim < 4, "dimension must be smaller than 4");
  static_assert(dim > 0, "dimension must be greater than 0");

  typedef T type;
};

template <typename T> struct pointer_n<1, T> { typedef T *type; };

template <typename T> struct pointer_n<2, T> { typedef T **type; };

template <typename T> struct pointer_n<3, T> { typedef T ***type; };

template <std::size_t dim, typename T>
using pointer_n_t = typename pointer_n<dim, T>::type;

template <int dim, typename T, typename U = int> class SmartArray {
public:
  typedef pointer_n_t<dim, T> pointer_type;
  typedef pointer_n_t<dim - 1, T> value_type;
  pointer_type data = nullptr;

public:
  SmartArray() : data(nullptr) {}

  template <typename... Tail>
  explicit SmartArray(
      typename std::enable_if<sizeof...(Tail) + 1 == dim, T>::type head,
      Tail... tail) {
    data = createC<T>(head, U(tail)...);
  }

  // Constructor/Assignment that allows move semantics
  SmartArray(SmartArray &&other) noexcept { other.swap(*this); }
  SmartArray &operator=(SmartArray &&other) noexcept {
    other.swap(*this);
    return *this;
  }

  // Constructor/Assignment that binds to nullptr
  // This makes usage with nullptr cleaner
  SmartArray(std::nullptr_t) : data(nullptr) {}
  SmartArray &operator=(std::nullptr_t) {
    reset();
    return *this;
  }

  // Remove compiler generated copy semantics.
  SmartArray(SmartArray const &) = delete;
  SmartArray &operator=(SmartArray const &) = delete;

  // Const correct access owned object
  value_type &operator*() const { return *data; }

  // Access to smart pointer state
  pointer_type get() const { return data; }
  explicit operator bool() const { return data; }

  // Modify object state
  pointer_type release() noexcept {
    pointer_type result = nullptr;
    std::swap(result, data);
    return result;
  }

  void swap(SmartArray &other) noexcept { std::swap(data, other.data); }

  void reset() {
    freeC(data);
    data = nullptr;
  }

  ~SmartArray() { freeC(data); }

  value_type &operator[](std::size_t index) { return data[index]; }
};

template <int dim, typename T, typename U = int>
void swap(SmartArray<dim, T> &lhs, SmartArray<dim, T> &rhs) {
  lhs.swap(rhs);
}

} // namespace Memory

#endif