#ifndef __JSLIB_LRUCACHE_H__
#define __JSLIB_LRUCACHE_H__

#include <unordered_map>
#include <list>
#include <cassert>

namespace JSLib{

/**
 * LRUCache
 * LRUCache manages key/value pair in least recently used cahce manner.
 * You can specify max entry size on construct.
 * When you get a value from a key, the entry is moved to the top 
 * of list as the most recently used entry.
 * If you insert a key/value pair that of key already exists in the cache
 * the existing entry is removed and new key/value pair is inserted
 * as the most recently used entry.
 * 
 * Usage:
 *
 *     LRUCache<int, std::string> myCache(10);
 *     myCache.insert(1, "My First String");
 *     myCache.insert(2, "My Second String");
 *     myCache.insert(3, "My Third String");
 *     const std::string* str = myCache.get(2);
 *     if( NULL == str ){
 *        // The entry is not in cache
 *        str = getValueViaSlowMedia(2);
 *     }
 *     std::cout << "The value corresponds to 2 is " << *str;
 *
 **/

template<class KEY, class VALUE>
class LRUCache{
    struct ListEntry;
    typedef std::list<ListEntry> ValueList;
    typedef std::unordered_map<KEY, typename ValueList::iterator> KeyHashTable;

    struct ListEntry{
        ListEntry(VALUE v, typename KeyHashTable::iterator i):value(v),it(i){};
        ~ListEntry(){};
        VALUE value;
        typename KeyHashTable::iterator it;
    };

public:
    /**
     * Constructor
     * Specify the max entry size.
     * If the size is 0 the max entry size is unlimited.
     **/
    LRUCache(size_t max_size):maxSize_(max_size){};
    
    void insert( const KEY& key, const VALUE& value ){
        assert(values_.size() == keyMap_.size());
        typename KeyHashTable::const_iterator existingValue = keyMap_.find(key);
        if( existingValue != keyMap_.end()){
            // Move the value to the front.
            values_.splice(values_.begin(), values_, existingValue->second);
            values_.begin()->value = value;
            // No need to update the iterator in keyMap_ since the iterator is still valid.
        }else{
            if( 0 != maxSize_ && maxSize_ <= values_.size() ){
                // Erase the least recently used entry
                keyMap_.erase(values_.rbegin()->it);
                values_.pop_back();
            }
            values_.push_front(ListEntry(value, keyMap_.begin())); // The iterator is temporary.
            std::pair<typename KeyHashTable::iterator, bool> result = keyMap_.insert(std::make_pair(key,values_.begin()));
            values_.begin()->it = result.first;
        }
    };

    const VALUE* get(const KEY& key) {
        assert(values_.size() == keyMap_.size());
        typename KeyHashTable::const_iterator i = keyMap_.find(key);
        if( i != keyMap_.end() ){
            values_.splice(values_.begin(), values_, i->second);
            return &(i->second->value);
        }else{
            return reinterpret_cast<VALUE*>(NULL);
        }
    };

    void clear(){
        assert(values_.size() == keyMap_.size());
        values_.clear();
        keyMap_.clear();
    };

    size_t size(){
        assert(values_.size() == keyMap_.size());
        return values_.size(); 
    }
private:
    size_t maxSize_;
    KeyHashTable keyMap_;
    ValueList values_;
};

} // JSLib
#endif
