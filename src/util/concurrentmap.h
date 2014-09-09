// Copyright (c) 2014, Sam Crow samcrow@uw.edu
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies,
// either expressed or implied, of the FreeBSD Project.

#ifndef CONCURRENTHASHMAP_H
#define CONCURRENTHASHMAP_H
#include <unordered_map>
#include <functional>
#include <mutex>

/**
 * Maps keys to values using an underlying map and provides synchronization
 * on operations. This class is thread-safe. Each method appears to execute atomically.
 * 
 * @param K the key type
 * @param V the value type
 * @param Map The type of underlying map to use
 */
template < typename K, typename V, class Map = std::unordered_map<K, V> >
class ConcurrentMap
{
public:
    typedef K key_type;
    typedef V mapped_type;
    typedef std::pair<K, V> value_type;
    
    /**
     * @brief Creates a mapping from the provided
     * key to the provided value. If a mapping
     * corresponding to the key already exists,
     * it is discarded.
     * @param key
     * @param value
     */
    void set(const K& key, const V& value) {
        std::unique_lock<std::mutex> lock(mutex);
        map[key] = value;
    }
    
    /**
     * @brief Creates a mapping from the provided
     * key to the provided value. If a mapping
     * corresponding to the key already exists,
     * it is discarded.
     * @param key
     * @param value
     */
    void set(K&& key, V&& value) {
        std::unique_lock<std::mutex> lock(mutex);
        map[key] = value;
    }
    
    /**
     * @brief Returns the value corresponding to the requested key
     * @param value
     * @return 
     * @throws std::out_of_range if the provided key does not map
     * to anything
     */
    V at(const K& key) {
        std::unique_lock<std::mutex> lock(mutex);
        return map.at(key);
    }
    
    /**
     * @brief Removes and returns the value corresponding to the requested key
     * @param key
     * @return 
     * @throws std::out_of_range if the provided key does not map
     * to any value
     */
    V remove(const K& key) {
        std::unique_lock<std::mutex> lock(mutex);
        auto iter = map.find(key);
        if(iter == map.end()) {
            throw std::out_of_range("No value found in map");
        }
        V value = iter->second;
        map.erase(iter);
        return value;
    }
    
    /**
     * @brief Returns true if this map contains the requested key.
     * Otherwise returns false.
     * @param key
     * @return 
     */
    bool contains(const K& key) {
        std::unique_lock<std::mutex> lock(mutex);
        return map.find(key) != map.end();
    }
    
    /**
     * Deletes eache value stored in this map, and then
     * clears the map.
     * 
     * Enabled only if the value type is a pointer.
     */
    template < typename V2 = V >
    typename std::enable_if<std::is_pointer<V2>::value>::type
    deleteAll() {
        std::unique_lock<std::mutex> lock(mutex);
        for(auto iter = map.begin(); iter != map.end(); iter++) {
            V pointer = iter->second;
            delete pointer;
        }
        map.clear();
    }
    
    typedef std::function< void (value_type) > operation;
    
    /**
     * @brief Applys the provided operation to each element
     * in the map, in the order returned by the map's iterator.
     * 
     * @param op
     */
    void applyToAll(operation op) {
        std::unique_lock<std::mutex> lock(mutex);
        for(value_type pair : map) {
            op(pair);
        }
    }
    
    void clear() {
        std::unique_lock<std::mutex> lock(mutex);
        map.clear();
    }
    
private:
    
    Map map;
    
    std::mutex mutex;
    
};

#endif // CONCURRENTHASHMAP_H
