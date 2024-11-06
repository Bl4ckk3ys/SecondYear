#include "BitField.h"
#include <vector>
class Set{
private:
    BitField _bitField;
    size_t _maxPower;//max razmer nashego mn-va
public:
    Set(size_t mp);
    Set(const Set& set);
    Set(const BitField& bf);
    operator BitField();
    
    std::vector<uint64_t> GetPrimary();
    
    size_t GetMaxPower();
    void InsertElem(uint64_t elem);
    void DeleteElem(uint64_t elem);
    bool IsMember(uint64_t elem);

    bool operator==(const Set& tmp);
    Set& operator=(const Set& tmp);
    Set operator+(const Set& tmp);
    Set operator+(uint64_t elem);
    Set operator-(uint64_t elem);
    Set operator*(const Set& tmp);
    Set operator~();

    friend std::istream& operator>>(std::istream& istr, Set& set);
    friend std::ostream& operator<<(std::ostream& istr, const Set& set);

};