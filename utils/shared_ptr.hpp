#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#include <cstddef>
#include <exception>
#include <stdexcept>

namespace ft {
    template <class T>
    class shared_ptr {
    public:

        typedef T element_type;

        shared_ptr<T>() : _data(0), _ref_counter(0) { }

        explicit shared_ptr<T>(T * target) : _data(0), _ref_counter(0) {
            if (!target)
                return;
            init_from_ptr(target);
        }

        shared_ptr<T>(const ft::shared_ptr<T> & other) : _data(other._data), _ref_counter(other._ref_counter) {
            if (!_data || !_ref_counter)
                return;
            (*_ref_counter)++;
        }

        T* operator->() {
            return &(operator*());
        }

        const T* operator->() const {
            return &(operator*());
        }

        T& operator*() {
            if (!_data)
                throw std::runtime_error("Try dereference null smart pointer");
            return *_data;
        }

        const T& operator*() const {
            if (!_data)
                throw std::runtime_error("Try dereference null smart pointer");
            return *_data;
        }

        shared_ptr<T>& operator=( const shared_ptr<T>& r ) {
            if (&r == this)
                return *this;
            _data = r._data;
            _ref_counter = r._ref_counter;
            *(_ref_counter) += 1;
            return *this;
        }

        shared_ptr<T>& operator=( T * ptr) {
            decrement_counter();
            init_from_ptr(ptr);
            return *this;
        }

        ~shared_ptr() {
            if (!_data || !_ref_counter)
                return;
            decrement_counter();
        }

        T* get() {
            return _data;
        }

        operator bool() const {
            return _data != 0;
        }

        void swap(shared_ptr<T> & other) {
            std::swap(_data, other._data);
            std::swap(_ref_counter, other._ref_counter);
        }

        void reset() {
            decrement_counter();
            _data = 0;
            _ref_counter = 0;
        }

        template<class U> bool operator==(const shared_ptr<U> & other) {
            return _data == other._data;
        }

        template<class U> bool operator==(const shared_ptr<U> & other) const {
            return _data == other._data;
        }

        template<class U> bool operator!=(shared_ptr<U> & other) {
            return _data != other._data;
        }

        template<class U> bool operator!=(shared_ptr<U> & other) const {
            return _data != other._data;
        }

        template<class U> bool operator>(const shared_ptr<U> & other) {
            return _data > other._data;
        }

        template<class U> bool operator>(const shared_ptr<U> & other) const {
            return _data > other._data;
        }

        template<class U> bool operator<(const shared_ptr<U> & other) {
            return _data < other._data;
        }

        template<class U> bool operator<(const shared_ptr<U> & other) const {
            return _data < other._data;
        }

        template<class U> bool operator<=(const shared_ptr<U> & other) {
            return _data <= other._data;
        }

        template<class U> bool operator<=(const shared_ptr<U> & other) const {
            return _data <= other._data;
        }

        template<class U> bool operator>=(const shared_ptr<U> & other) {
            return _data >= other._data;
        }

        template<class U> bool operator>=(const shared_ptr<U> & other) const {
            return _data >= other._data;
        }

    private:
        T * _data;
        size_t * _ref_counter;

        void decrement_counter() {
            if (!_ref_counter || !_data)
                return;
            (*_ref_counter)--;
            if (*_ref_counter == 0) {
                delete _data;
                delete _ref_counter;
            }
        }

        void init_from_ptr(T* data) {
            _data = data;
            _ref_counter = new size_t;
            *_ref_counter = 1;
        }
    };
}

#endif