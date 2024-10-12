#include <iostream>
#include <cstdint>
#include <cstring>

template<typename T>
class ArrayHandler {
private:
    T* _array;
    T _max;
    T _min;
    size_t _size;
    size_t _count;
public:
    ArrayHandler(size_t size = 10) {
        _size = size;
        _array = new T[_size];
        _max = 0;
        _min = INT8_MAX;
        _count = 0;
    }
    void AppendElem(T new_element){
        if (_count == _size) {
            _size = _size * 2;
            T* new_arr = new T[_size];
            std::memcpy(new_arr, _array, (_size/2)*sizeof(T));
            delete [] _array;
            _array = new_arr;
        }
        _array[_count] = new_element;
        _count++;
        if (_max < new_element) _max = new_element;
        if (_min > new_element) _min = new_element;
    }

    bool IsContains(T elem) {
        return false;
    }

    T GetMax(){
        return _max;
    }
    T GetMin(){
        return _min;
    }

    ~ArrayHandler() {
        delete [] _array;
    }

};