#include "BitField.h"


BitField::BitField(size_t len){
    _sizeBit = len;
    _sizeMem = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t))!= 0);
    _mem = new uint16_t[_sizeMem];
    for (size_t i = 0; i< _sizeMem; ++i)
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp){
    _sizeBit = tmp._sizeBit;
    _sizeMem = tmp._sizeMem;
    _mem = new uint16_t[_sizeMem];
    for(size_t i = 0; i < _sizeMem;++i)
        _mem[i] = tmp._mem[i];
}

uint16_t BitField::GetMask(size_t n) const{//получение маски конкретного бита
    return 1 << (n % 16);
}

void BitField::SetBit(size_t n){ //ставит в бит значение 1
    if(n>_sizeBit)
        throw "Bit out of range";
    _mem[GetMemIndex(n)] |= GetMask(n);//или равно
}
 
BitField& BitField::operator=(const BitField& tmp){
    if(_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _sizeMem = tmp._sizeMem;
        _mem = new uint16_t[_sizeMem];
    }
    for(size_t i = 0; i < _sizeMem; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}

size_t BitField::GetMemIndex(size_t n)const{//позволяет вернуть в каком эл-те лежит бит
    size_t index = n/(8*sizeof(uint16_t));
    if(n>=_sizeBit)
        throw "Bit out of range";
    return index;
}

uint8_t BitField::GetBit(size_t n) const{
    uint16_t mask1 = GetMask(n);
    uint16_t mask2 = _mem[GetMemIndex(n)];
    if((mask2 & mask1)==0) return 0;
    return 1;
}


void BitField::ClrBit(size_t n){
    uint8_t mask = GetMask(n);
    mask = ~mask;
    _mem[GetMemIndex(n)] &= mask;
}

BitField BitField::operator|(const BitField& tmp){
    BitField B(*this);
    for(size_t i = 0; i<_sizeMem;i++){
        B._mem[i] |= tmp._mem[i];
    }
    return *this;
}

BitField BitField::operator^(const BitField& tmp){
    BitField B(*this);
    for(size_t i = 0; i<_sizeMem;i++){
        B._mem[i] ^= tmp._mem[i];
    }
    return *this;
}

bool BitField::operator==(const BitField& tmp){
    if(_sizeBit != tmp._sizeBit) return false;
    for(size_t i = 0; i < _sizeMem;++i){
        if(_mem[i]!=tmp._mem[i]) return false;
    }
    return true;
}

BitField BitField::operator~(){
    BitField cpy = BitField(*this);
    for(size_t i = 0;i < _sizeMem; ++i){
        cpy._mem[i] = ~cpy._mem[i];
    }
}