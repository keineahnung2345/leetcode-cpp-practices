//Runtime: 156 ms, faster than 13.19% of C++ online submissions for Insert Delete GetRandom O(1).
//Memory Usage: 22.8 MB, less than 61.19% of C++ online submissions for Insert Delete GetRandom O(1).
class RandomizedSet {
public:
    set<int> myset;
    
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        std::pair<std::set<int>::iterator, bool> result = myset.insert(val);
        return result.second;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(myset.find(val) == myset.end()){
            return false;
        }
        myset.erase(val);
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int n = myset.size();
        set<int>::iterator it = myset.begin();
        advance(it, rand()%n);
        return *it;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
 
