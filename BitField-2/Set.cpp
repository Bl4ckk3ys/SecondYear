#include "Set.h"
#include <math.h>

Set::Set(size_t mp) : _bitField(mp){
    _maxPower = mp;
};

Set::Set(const Set& set) : _bitField(set._bitField){
    _maxPower = set._maxPower;
};

Set::Set(const BitField& bf) : _bitField(BitField(bf)){
    _maxPower = bf.GetSize();
};

void Set::InsertElem(uint64_t elem){
    _bitField.SetBit(elem); 
};

void Set::DeleteElem(uint64_t elem){
    _bitField.ClrBit(elem);
};

bool Set::IsMember(uint64_t elem){
    return _bitField.GetBit(elem);
};

size_t Set::GetMaxPower(){
    return _maxPower;
};

std::vector<uint64_t> Set::GetPrimary(){
    Set setCopy = Set(*this);
    for(size_t i; i<floor(sqrt(_maxPower));i++){
        if(setCopy.IsMember(i)){
            for(size_t j = 2*i; j<_maxPower; j+=i)
                setCopy.DeleteElem(j);
        }
    }
    std::vector<uint64_t> v;
    for(size_t i = 0;i<_maxPower;i++){
        if(setCopy.IsMember(i)) v.push_back(i);
    }
    return v;
}