/**
Design a HashMap without using any built-in hash table libraries.

To be specific, your design should include these functions:

put(key, value) : Insert a (key, value) pair into the HashMap. If the value already exists in the HashMap, update the value.
get(key): Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
remove(key) : Remove the mapping for the value key if this map contains the mapping for the key.

Example:

MyHashMap hashMap = new MyHashMap();
hashMap.put(1, 1);          
hashMap.put(2, 2);         
hashMap.get(1);            // returns 1
hashMap.get(3);            // returns -1 (not found)
hashMap.put(2, 1);          // update the existing value
hashMap.get(2);            // returns 1 
hashMap.remove(2);          // remove the mapping for 2
hashMap.get(2);            // returns -1 (not found) 

Note:

All keys and values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashMap library.
**/

//Runtime: 216 ms, faster than 23.40% of C++ online submissions for Design HashMap.
//Memory Usage: 41.2 MB, less than 96.95% of C++ online submissions for Design HashMap.

class MyHashMap {
public:
    vector<int> keys;
    vector<int> values;
    
    /** Initialize your data structure here. */
    MyHashMap() {
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        vector<int>::iterator it = find(keys.begin(), keys.end(), key);
        if(it!=keys.end()){
            values[(it - keys.begin())] = value;
        }else{
            keys.push_back(key);
            values.push_back(value);
        }
        
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        vector<int>::iterator it = find(keys.begin(), keys.end(), key);
        if(it==keys.end()){
            return -1;
        }else{
            return values[it-keys.begin()];
        }
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        vector<int>::iterator it = find(keys.begin(), keys.end(), key);
        if(it!=keys.end()){
            keys.erase(it);
            values.erase(values.begin() + (it - keys.begin()));
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap obj = new MyHashMap();
 * obj.put(key,value);
 * int param_2 = obj.get(key);
 * obj.remove(key);
 */
 
