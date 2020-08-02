/**
Design a HashSet without using any built-in hash table libraries.

To be specific, your design should include these functions:

add(value): Insert a value into the HashSet. 
contains(value) : Return whether the value exists in the HashSet or not.
remove(value): Remove a value in the HashSet. If the value does not exist in the HashSet, do nothing.

Example:

MyHashSet hashSet = new MyHashSet();
hashSet.add(1);         
hashSet.add(2);         
hashSet.contains(1);    // returns true
hashSet.contains(3);    // returns false (not found)
hashSet.add(2);          
hashSet.contains(2);    // returns true
hashSet.remove(2);          
hashSet.contains(2);    // returns false (already removed)

Note:

All values will be in the range of [0, 1000000].
The number of operations will be in the range of [1, 10000].
Please do not use the built-in HashSet library.
**/

//Runtime: 280 ms, faster than 11.94% of C++ online submissions for Design HashSet.
//Memory Usage: 35.7 MB, less than 100.00% of C++ online submissions for Design HashSet.

class MyHashSet {
public:
    /** Initialize your data structure here. */
    vector<int> v;
    
    MyHashSet() {
        
    }
    
    void add(int key) {
        if(!contains(key)){
            v.push_back(key);
        }
    }
    
    void remove(int key) {
        if(contains(key)){
            v.erase(find(v.begin(), v.end(), key));
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        return find(v.begin(), v.end(), key)!=v.end();
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

//vector and hash function
//https://leetcode.com/problems/design-hashset/discuss/210494/Real-Python-Solution-no-cheating-open-addressing
//Runtime: 172 ms, faster than 81.39% of C++ online submissions for Design HashSet.
//Memory Usage: 40.9 MB, less than 77.23% of C++ online submissions for Design HashSet.
class MyHashSet {
public:
    /** Initialize your data structure here. */
    int capacity;
    int size;
    vector<int> s;
    float load_factor;
    
    MyHashSet() {
        capacity = 8;
        size = 0;
        //-1 means untouched
        //-2 means once exist but removed, tombstone
        s = vector<int>(capacity, -1);
        load_factor = 2.0f/3.0f;
    }
    
    int hash(int key){
        return key % capacity;
    }
    
    int rehash(int key){
        return (key*5+1) % capacity;
    }
    
    void add(int key) {
        //enlarge the vector
        if(float(size)/capacity >= load_factor){
            capacity <<= 1;
            vector<int> ns(capacity, -1);
            
            for(int i = 0; i < capacity >> 1; ++i){
                if(s[i] >= 0){ //not -1 or -2
                    int pos = hash(s[i]);
                    while(ns[pos] != -1){ //while the position is filled
                        //when rehash, we use the "new capacity"!!
                        pos = rehash(pos);
                    }
                    //find a empty place, fill it
                    ns[pos] = s[i];
                }
            }
            
            s = ns;
        }
        
        int pos = hash(key);
        
        while(s[pos] >= 0){ //want to find s[pos] is -1 or -2
            //key is already in the hashset
            if(s[pos] == key) return;
            pos = rehash(pos);
        }
        
        //found an empty space, fill it
        s[pos] = key;
        ++size;
    }
    
    void remove(int key) {
        int pos = hash(key);
        
        /*
        loop until we meet an untouched position,
        note that we don't stop when we meet -2(tombstone)
        */
        while(s[pos] != -1){ 
            if(s[pos] == key){
                //only remove if we meet "key"
                s[pos] = -2;
                --size;
                break;
            }
            pos = rehash(pos);
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int pos = hash(key);
        
        /*
        loop until we meet an untouched position,
        note that we don't stop when we meet -2(tombstone)
        */
        while(s[pos] != -1){
            if(s[pos] == key) return true;
            pos = rehash(pos);
        }
        
        return false;
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
