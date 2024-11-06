#include <iostream>

class BitField{
private:
    size_t _sizeMem;
    uint16_t* _mem;
    size_t _sizeBit;//кол-во занятых эл-в
    size_t GetMemIndex(size_t n)const{//позволяет вернуть в каком эл-те лежит бит
        size_t index = n/(8*sizeof(uint16_t));
        if(n>=_sizeBit)
            throw "Bit out of range";
        return index;
    };
    uint16_t GetMask(size_t n) const;//получение маски конкретного бита

public:
    BitField(size_t sizeBit);
    BitField(const BitField& tmp);
    size_t GetSize() const;
    uint8_t GetBit(size_t n) const; //возвращает значение бита, не меняет состояние объекта, поэтому конст
    void SetBit(size_t n); //ставит в бит значение 1
    void ClrBit(size_t n); //ставит в бит значение 0

    BitField& operator=(const BitField& tmp);
    BitField operator|(const BitField& tmp);
    BitField operator^(const BitField& tmp);
    bool operator==(const BitField& tmp);
    BitField operator~();
    ~BitField(){
        //очистить и присвоить null_ptr
    };

    //сделать перегрузку оператора вывода всех битов битового поля в консоль 
};