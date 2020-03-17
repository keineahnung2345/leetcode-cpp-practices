//Runtime: 260 ms, faster than 7.78% of C++ online submissions for LRU Cache.
//Memory Usage: 36.6 MB, less than 100.00% of C++ online submissions for LRU Cache.
class LRUCache {
public:
    map<int, int> cache;
    int capacity;
    vector<int> keyTimes;
    
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    void updateKeyTimes(int key){
        if(find(keyTimes.begin(), keyTimes.end(), key) != keyTimes.end()){
            keyTimes.erase(find(keyTimes.begin(), keyTimes.end(), key));
        }
        keyTimes.push_back(key);
    }
    
    int get(int key) {
        if(cache.find(key) != cache.end()){
            updateKeyTimes(key);
            return cache[key];
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(cache.find(key) == cache.end() && cache.size() == capacity){
            //it's a new key, we need to pop oldest pair
            int oldest = keyTimes[0];
            //remove first element
            keyTimes.erase(keyTimes.begin());
            cache.erase(cache.find(oldest));
        }
        cache[key] = value;
        updateKeyTimes(key);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 
