#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <utility>

// memory management

namespace {
template <typename T>
class vecBuff {
public:
  vecBuff() noexcept = default;
  explicit vecBuff(size_t capacity) : buffer_(Allocate(capacity)), capacity_(capacity) {}

  vecBuff(const vecBuff&) = delete;
  vecBuff(vecBuff && rhs) noexcept;

  ~vecBuff();

  vecBuff& operator=(const vecBuff &rhs) = delete;
  vecBuff& operator=(vecBuff &&rhs) noexcept;

  T* operator+(size_t compensate) noexcept;
  const T* operator+(size_t compensate) const noexcept;

  T& operator[](size_t index) noexcept;
  const T& operator[](size_t index) const noexcept;

  void swap_(vecBuff& other) noexcept;
  const T* getAddress() const noexcept;
  T* getAddress() noexcept;
  size_t calc_capacity() const noexcept;

private:
  void init(vecBuff &&other) noexcept;
  // выделяет сырую память под n элементов и возвращает указатель на неё
  static T* Allocate(size_t n);
  // освобождает сырую память, выделенную ранее по адресу buf при помощи Allocate
  static void Deallocate(T* buff) noexcept;


  T* buffer_ = nullptr;
  size_t capacity_ = 0;
};

template <typename T>
vecBuff<T>::vecBuff(vecBuff &&other) noexcept {
  init(std::move(other));
}

template <typename T>
vecBuff<T>& vecBuff<T>::operator=(vecBuff &&rhs) noexcept {
  init(std::move(rhs));
  return *this;
}

template <typename T>
vecBuff<T>::~vecBuff() {
  Deallocate(buffer_);
}

template <typename T>
T* vecBuff<T>::operator+(size_t compensate) noexcept {
  // разрешается получать адрес ячейки памяти, следующей за последним элементом массива
  assert(compensate <= capacity_);
  return buffer_ + compensate;
}

template <typename T>
const T* vecBuff<T>::operator+(size_t compensate) const noexcept {
  return const_cast<vecBuff&>(*this) + compensate;
}

template <typename T>
const T& vecBuff<T>::operator[](size_t index) const noexcept{
  return const_cast<vecBuff&>(*this)[index];
}

template <typename T>
T& vecBuff<T>::operator[](size_t index) noexcept {
  assert(index < capacity_);
  return buffer_[index];
}
template <typename T>
void vecBuff<T>::swap_(vecBuff &other) noexcept {
  std::swap(buffer_, other.buffer_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
const T* vecBuff<T>::getAddress() const noexcept {
  return buffer_;
}

template <typename T>
T* vecBuff<T>::getAddress() noexcept {
  return buffer_;
}

template <typename T>
size_t vecBuff<T>::calc_capacity() const noexcept {
  return capacity_;
}

template <typename T>
void vecBuff<T>::init(vecBuff &&other) noexcept {
  Deallocate(buffer_);
  buffer_ = std::exchange(other.buffer_, nullptr);
  capacity_ = std::exchange(other.capacity_, 0);
}

template <typename T>
T* vecBuff<T>::Allocate(size_t n) {
  return n != 0 ? static_cast<T*>(operator new(n* sizeof(T))) : nullptr;
}

template <typename T>
void vecBuff<T>::Deallocate(T* buf) noexcept {
  if(buf != nullptr) {
    operator delete(buf);
  }
}

}

// class vector
template <typename T>
class vector {
public:
  using iterator = T*;
  using const_iterator = const T*;


  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;
  
  vector() noexcept = default;
  explicit vector(size_t size_);
  vector(const vector &other);
  vector(vector &&other) noexcept;

  vector& operator =(const vector &rhs);
  vector& operator=(vector &&rhs) noexcept;
  ~vector();

  void swap_(vector &other) noexcept;

  size_t Size() const noexcept;
  size_t capacity_() const noexcept;
  void reserve_(size_t new_capacity);
  void resize_(size_t new_size);

  template<typename... Args>
  T& emplaceBack(Args&&... args);
  T& pushBack(const T &value);
  T& pushBack(T &&value);
  void popBack() noexcept;

  template <typename... Args>
  iterator emplace_(const_iterator pos, Args&&... args);
  iterator erase_(const_iterator pos) noexcept(std::is_nothrow_move_assignable_v<T>);
  iterator insert_(const_iterator pos, const T &value);
  iterator insert_(const_iterator pos, T &&value);

  const T& operator[](size_t index) const noexcept;
  T& operator[](size_t index) noexcept;
private:
  vecBuff<T> data_;
  size_t size_ = 0;

  // если move-конструктор не выбрасывает исключений или нет copy-конструктора, 
  // то делаем перемещение, иначе копируем элементы из старой области памяти в новую
  static void safeMove(T *from, size_t size, T* to);

  template <typename... Args>
  iterator emplaceWithReallocate(const_iterator pos, Args&&... args);

  template <typename ...Args>
  iterator emplaceWithoutReallocate(const_iterator pos, Args&&... args);
}; // class vector

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return data_.getAddress();
} 

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return data_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return data_.getAddress();
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return data_ + size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
  return data_.getAddress();
}

template <typename T>
typename vector<T>::const_iterator vector<T>::cend() const noexcept {
  return data_ + size_;
}

template <typename T>
vector<T>::vector(size_t size) 
  : data_(size)
  , size_(size)
{
  std::uninitialized_value_construct_n(data_.getAddress(), size);
}

template <typename T>
vector<T>::vector(const vector &other)
  : data_(other.size_)
  , size_(other.size_)
{
  std::uninitialized_value_construct_n(other.data_.getAddress(), size_, data_.getAddress());
}


template <typename T>
vector<T>::vector(vector<T> &&other) noexcept {
  data_ = std::move(other.data_);
  size_ = std::exchange(other.size_, 0);
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T> &rhs) {
  if(this != &rhs) {
    if(rhs.size_ > data_.capacity_()) {
      vector rhsCopy(rhs);
      swap_(rhsCopy);
    } else {
      // если в источнике элементов меньше чем в приёмнике,
      // то копируем все элементы из источника, оставшиеся в приёмнике - удаляем
      // иначе копируем всё что поместится, остальное инициализируем
      size_t copy_el = rhs.size_ < size_ ? rhs.size_ : size_;
      auto end = std::copy_n(rhs.data_.getAddress(), copy_el, data_.getAddress());
        if(rhs.size_ < size_) {
          std::destroy_n(end, size_ - rhs.size_);
        } else {
          std::uninitialized_copy_n(rhs.data_.getAddress() + size_, rhs.size_ - size_, end);
        }
        size_ = rhs.size_;
    }
  }
  return *this;
}


template <typename T>
vector<T>& vector<T>::operator=(vector<T> &&rhs) noexcept {
  swap_(rhs);
  return *this;
}

template <typename T>
vector<T>::~vector() {
  std::destroy_n(data_.getAddress(), size_);
}

template <typename T>
void vector<T>::swap_(vector<T> &other) noexcept {
  data_.swap_(other.data_);
  std::swap(size_, other.size_);
}
template <typename T>
size_t vector<T>::Size() const noexcept {
  return size_;
}
template <typename T>
size_t vector<T>::capacity_() const noexcept {
  return data_.capacity_();
}
template <typename T>
void vector<T>::reserve_(size_t new_capacity) {
  if(new_capacity <= data_.capacity_()) {
    return;
  }
  vecBuff<T> new_data{new_capacity};
  safeMove(data_.getAddress(), size_, new_data.getAddress());
  data_.swap_(new_data);
}

template <typename T>
void vector<T>::resize_(size_t new_size) {
  if(new_size < size_) {
    std::destroy_n(data_.getAddress() + new_size, size_ - new_size);
  } else if (new_size > size_) {
    reserve_(new_size);
    std::uninitialized_value_construct_n(data_.getAddress() + size_, new_size - size_);
  }
  size_ = new_size;
}

template <typename T>
T& vector<T>::pushBack(const T &value) {
  return emplaceBack(value);
}

template <typename T>
T& vector<T>::pushBack(T &&value) {
  return emplaceBack(std::move(value));
}

template <typename T>
void vector<T>::popBack() noexcept {
  assert(size_ > 0);
  std::destroy_n(data_+(size_- 1));
  --size_;
}
template <typename T>
template <typename... Args>
T& vector<T>::emplaceBack(Args&&... args) {
  if(size_ == capacity_()) {
    vecBuff<T> new_data{size_ == 0 ? 1 : size_ * 2};
    new (new_data + size_) T(std::forward<Args>(args)...);
    safeMove(data_.getAddress(), size_, new_data.getAddress());
    data_.swap_(new_data);    
    } else {
      new(data_ + size_) T(std::forward<Args>(args)...);
    }
    ++size_;
    return data_[size_ - 1];
  }

template <typename T> 
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace_(const_iterator pos, Args&&... args) {
  if(pos == end()) {
    return &emplace_(std::forward<Args>(args)...);
  }
  if(size_ == capacity_()) {
    return emplaceWithReallocate(pos, std::forward<Args>(args)...);
  } else {
    return emplaceWithoutReallocate(pos, std::forward<Args>(args)...);
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert_(const_iterator pos, const T &value) {
  return emplace_(pos, value); 
}

template <typename T>
typename vector<T>::iterator vector<T>::insert_(const_iterator pos, T &&value) {
  return emplace_(pos, std::move(value));
}

template<typename T>
typename vector<T>::iterator vector<T>::erase_(const_iterator pos) 
  noexcept(std::is_nothrow_move_assignable_v<T>) {
    assert(size_ > 0);
    size_t index = static_cast<size_t>(pos - begin());
    std::move(begin() + index + 1, end(), begin() + index);
    data_[size_ - 1].~T();
    --size_;
    return begin() + index;  
  
}

template <typename T>
const T& vector<T>::operator[](size_t index) const noexcept {
  return const_cast<vector&>(*this)[index];
}

template <typename T>
T& vector<T>::operator[](size_t index) noexcept {
  assert (index < size_);
  return data_[index];
}

template <typename T>
void vector<T>::safeMove(T* from, size_t size, T *to) {
  if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>) {
    std::uninitialized_move_n(from, size, to);
  } else {
    std::uninitialized_copy_n(from, size, to);
  }
  std::destroy_n(from, size);
}


template <typename T>
template <typename... Args>
typename vector<T>::iterator
vector<T>::emplaceWithReallocate(const_iterator pos, Args&&... args) {
  size_t index = static_cast<size_t>(pos - begin());
  vecBuff<T> new_data{size_ == 0 ? 1 : size_ * 2};
  new (new_data + index) T(std::forward<Args>(args)...);
  try {
    safeMove(data_.getAddress(), index, new_data.getAddress());
  } catch (...) {
    new_data[index].~T();
    throw;
  }

  try {
    safeMove(data_ + index, size_ - index, new_data + (index + 1));
  } catch (...) {
    std::destroy_n(new_data.getAddress(), index + 1);
    throw;
  }
  data_.swap_(new_data);

  ++size_;
  return begin() + index;
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator
vector<T>::emplaceWithoutReallocate(const_iterator pos, Args&&... args) {
  size_t index = static_cast<size_t>(pos - begin());
  T tmp(std::forward<Args>(args)...);
  // память после последнего элемента - не инициализирована,
  // поэтому инициализируем её размещающим new
  // остальные элементы двигаем вправо на один элемент
  new (end()) T(std::move(data_[size_ - 1]));
  std::move_backward(begin() + index, end() - 1, end());
  data_[index] = std::move(tmp);
  
  ++size_;
  return begin() + index; 
}

template <typename T>
std::ostream& operator <<(std::ostream &out, const vector<T> &vector) {
  out << "[ ";
  for(const auto &el : vector) {
    out << el << " ";
  }
  out << "]\n";
  return out;
}




















