#include "BitField.h"


size_t BitField::GetMemIndex(size_t n) const{
    if(n>=_memSize) throw "Bit out of range. ";
    return n/(8*sizeof(uint16_t));
}
uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % 16);
}

BitField::BitField(size_t len) {
    _sizeBit = len;//кол-во битов задействованных в хранении чисел (кол-во чисел)
    _memSize = (len / (8*sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t))!=0);//кол-во ячеек  
    _mem = new uint16_t[_memSize];
    for(size_t i = 0; i<_memSize; ++i) 
        _mem[i] = 0;
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    for(size_t i = 0; i<_memSize; ++i)
        _mem[i] = tmp._mem[i];
}

BitField& BitField::operator=(const BitField& tmp) {
    if(_sizeBit!=tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    for(size_t i = 0; i < _sizeBit; ++i)
        _mem[i] = tmp._mem[i];
    return *this;
}
    
size_t BitField::GetLength() const {
    return _sizeBit;
}
void BitField::SetBit(size_t n) {
    if(n>_memSize) throw "Bit out of range. ";
    _mem[GetMemIndex(n)] |= GetMask(n);
}
void BitField::ClrBit(size_t n) {
    _mem[GetMemIndex(n)] &= ~GetMask(n);
}
uint8_t BitField::GetBit(size_t n) const {
    uint16_t mask_1 = GetMask(n);
    uint16_t mask_2 = _mem[GetMemIndex(n)];
    if(mask_1 & mask_2 == 1) return 1;
    return 0;
}
BitField BitField::operator|(const BitField& tmp) {
    BitField copy = BitField(*this);
    for(size_t i = 0; i < _sizeBit; ++i)
        copy._mem[i] |= tmp._mem[i];
    return copy;
}

BitField BitField::operator&(const BitField& tmp) {
    BitField copy = BitField(*this);
    for(size_t i = 0; i < _sizeBit; ++i)
        copy._mem[i] &= tmp._mem[i];
    return copy;
}
BitField BitField::operator^(const BitField& tmp) { //XOR
    BitField copy = BitField(*this);
    for(size_t i = 0; i < _sizeBit; ++i)
        copy._mem[i] ^= tmp._mem[i];
    return copy;
}
bool BitField::operator==(const BitField& tmp) const{
    if(_sizeBit != tmp._sizeBit) return false;
    for(size_t i = 0; i < _sizeBit; ++i){
        if(_mem[i]!=tmp._mem[i]) return false;
    }
    return true;
}
BitField BitField::operator~(){
    BitField copy = BitField(*this);
    for(size_t i = 0; i < _sizeBit; ++i) 
        copy._mem[i] = ~copy._mem[i];
    return copy;
}