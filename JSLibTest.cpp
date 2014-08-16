#include "include/algorithm"
#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

#define TEST_ASSERT(cond) \
        do{ \
            if( !(cond) ){ \
               std::cout << "\x1b[31m" << "ASSERT FAILED: " \
                         << "\x1b[0m"  << "[" << __FUNCTION__  << "] " << #cond << std::endl; \
            } \
        }while(0) \

bool isOdd(int v){
    return (v%2) != 0;
}

int makeTriple(int v){
    return v*3;
}

void Test_transform_if(){
    std::vector<int> arr1;
    for( int i = 0 ; i < 10; i++ ){
        arr1.push_back(i);
    }
    std::vector<int> arr2;
    JSLib::transform_if(arr1.begin(), arr1.end(), std::back_inserter(arr2), makeTriple, isOdd);
    TEST_ASSERT(arr2.size() == 5);
    TEST_ASSERT(arr2[2] == 15);
}

int main(int argc, const char** argv){
    Test_transform_if();
    return 0;
}