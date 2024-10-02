#include <cstdint>
#include <cstring>
#include <iostream>
template<typename T>
class ArrayHandler {
private:
    int8_t* _array;
    int8_t _max;
    int8_t _min;
    long long _size;
    long long _count;
public:
    ArrayHandler(size_t size = 10) {
        _size = size;
        _array = new int8_t[_size];
        _max = INT8_MIN;
        _min = INT8_MAX;
        _count = 0;
    }

    void AppendElem(int8_t new_element){
        if (_count == _size) {
            _size = _size * 4;
            int8_t* new_arr = new int8_t[_size];
            std::memcpy(new_arr, _array, _count*sizeof(int8_t));//.
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

    int8_t GetMax(){
        return _max;
    }
    int8_t GetMin(){
        return _min;
    }
    long long GetIndexElem(int8_t elem){
        // 1. Доп. память для хранения первого встречного индекса
        // 2. Бин. поиск
        for (int8_t i = 0; i < _count; i++) 
            if (elem == _array[i]) 
                return i;

        return -1;
    }
    ~ArrayHandler() {
        delete [] _array;
    }

};