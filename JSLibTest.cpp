#include <iostream>

#include "include/algorithm"
#include "include/LRUCache.h"
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

void Test_LRUCache(){
    // insert
    JSLib::LRUCache<std::string, int> myCache(3);
    myCache.insert("1",1);
    TEST_ASSERT(myCache.size() == 1);
    myCache.insert("2",2);
    TEST_ASSERT(myCache.size() == 2);
    myCache.insert("3",3);
    TEST_ASSERT(myCache.size() == 3);
    myCache.insert("4",4); // 1st pair must be dropped out here
    TEST_ASSERT(myCache.size() == 3);
    TEST_ASSERT(myCache.get("1") == NULL);
    TEST_ASSERT(*myCache.get("2") == 2);
    TEST_ASSERT(*myCache.get("3") == 3);
    TEST_ASSERT(*myCache.get("4") == 4);

    // Must override the value
    myCache.insert("2",5);
    TEST_ASSERT(*myCache.get("2") == 5);

    // LRU
    JSLib::LRUCache<std::string, int> myCache2(3);
    myCache2.insert("1",1);
    myCache2.insert("2",2);
    myCache2.insert("3",3);
    myCache2.get("1"); // now 1 is the most recenly used entry
    myCache2.insert("4",4); // "2"/2 pair must be dropped out here
    TEST_ASSERT(myCache2.size() == 3);
    TEST_ASSERT(*myCache2.get("1") == 1);
    TEST_ASSERT(myCache2.get("2") == NULL);
    TEST_ASSERT(*myCache2.get("3") == 3);
    TEST_ASSERT(*myCache2.get("4") == 4);
}

int main(int argc, const char** argv){
    Test_transform_if();
    Test_LRUCache();
    return 0;
}