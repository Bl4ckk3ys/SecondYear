#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Set.h"
#include "BitField.h"

int main(int argc, char **argv) {
    // ::testing::InitGoogleTest(&argc, argv);

    // return RUN_ALL_TESTS();


    BitField s1(10);
    
    s1.SetBit(3);
    s1.SetBit(2);
    s1.SetBit(5);
    s1.SetBit(9);
    s1.SetBit(7);
    s1.Print();
    
    BitField s2 = s1<<2;
    s2.Print();
    return 0;
}