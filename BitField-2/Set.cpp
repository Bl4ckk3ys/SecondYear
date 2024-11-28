#include "Set.h"
#include <math.h>

Set::Set(size_t mp) : _bitField(mp), _maxPower(mp) {

}
Set::Set(const Set &s) : _bitField(s._bitField), _maxPower(s._maxPower){

} 
Set::Set(const BitField &bf) : _bitField(bf), _maxPower(bf.GetLength()){

}

size_t Set::GetMaxPower() const{
    return _maxPower;
}    
void Set::InsElem(const uint64_t Elem){
    _bitField.SetBit(Elem);
}
void Set::DelElem(const uint64_t Elem){
    _bitField.ClrBit(Elem);
}
bool Set::IsMember(const uint64_t Elem) const{
    return _bitField.GetBit(Elem);
}


bool Set::operator== (const Set &s) const{
    return _bitField==s._bitField;
}
bool Set::operator!= (const Set &s) const{
    return (_bitField==s._bitField)!=true;
}
Set& Set::operator=(const Set &s){
    _maxPower = s.GetMaxPower();
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    Set copy = Set(*this);
    copy.InsElem(Elem);
    return copy;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set copy = Set(*this);
    copy.DelElem(Elem);
    return copy;
}
                                   
Set Set::operator+ (const Set &s){
    Set tmp = Set(*this);
    if(_maxPower >= s.GetMaxPower()) 
        tmp._bitField = tmp._bitField | s._bitField; 
    else{
        tmp = Set(s); 
        tmp._bitField = tmp._bitField | _bitField;
    } 
    return tmp;
}
Set Set::operator* (const Set &s){
    Set tmp = Set(*this);
    if(_maxPower >= s.GetMaxPower()) 
        tmp._bitField = tmp._bitField & s._bitField; 
    else{
        tmp = Set(s); 
        tmp._bitField = tmp._bitField & _bitField;
    } 
    return tmp;
}
Set Set::operator~ (){
    return Set(~_bitField);
}
std::vector<uint64_t> Set::GetPrimary(){
    Set copy = *this;
    copy.DelElem(0);
    //copy.DelElem(1);
    for(uint64_t i = 2 ;i<floor(sqrt(_maxPower));i++){
        if(copy.IsMember(i)){
            for(size_t j = 2*i; j<_maxPower; j+=i)
                copy.DelElem(j);
        }
    }
    std::vector<uint64_t> v;
    for(size_t i = 0;i<_maxPower;i++){
        if(copy.IsMember(i)) v.push_back(i);
    }
    return v;
}