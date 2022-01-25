#ifndef FT_OPTIONAL_HPP
#define FT_OPTIONAL_HPP

#include <stdexcept>

namespace ft {

    template<class T>
    class optional {
    public:
        optional(const T & value) : _has_value(true), _value(value) {}
        optional(const optional<T> & other) : _has_value(other._has_value), _value(other._value) {}
        optional() : _has_value(false) {}

        T&  operator*() {
            if (!_has_value)
                throw std::runtime_error("Try to return non-existing value");
            return _value;
        }

        operator bool() {
            return _has_value;
        }

        optional<T>& operator=(const T& other)
        {
            _value = other;
            return *this;
        }

        T& value() {
            if (!_has_value)
                throw std::runtime_error("Try to return non-existing value");
            return _value;
        }

        bool has_value() {
            return _has_value;
        }

        void reset() {
            _has_value = false;
            _value.T::~T();
        }

    private:
        bool _has_value;
        T _value;
    };
}
#endif