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
 
//unordered_map + vector
//https://leetcode.com/problems/insert-delete-getrandom-o1/discuss/85422/AC-C%2B%2B-Solution.-Unordered_map-%2B-Vector
//Runtime: 80 ms, faster than 75.07% of C++ online submissions for Insert Delete GetRandom O(1).
//Memory Usage: 22.8 MB, less than 61.84% of C++ online submissions for Insert Delete GetRandom O(1).
class RandomizedSet {
public:
    vector<int> vals;
    unordered_map<int, int> val2pos;
    
    /** Initialize your data structure here. */
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(val2pos.find(val) != val2pos.end()){
            return false;
        }
        
        vals.emplace_back(val);
        val2pos[val] = vals.size()-1;
        
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(val2pos.find(val) == val2pos.end()){
            return false;
        }
        
        if(vals.back() == val){
            vals.pop_back();
            val2pos.erase(val);
        }else{
            int last = vals.back(), newpos = val2pos[val];
            swap(vals.back(), vals[val2pos[val]]);
            vals.pop_back();
            val2pos[last] = newpos;
            val2pos.erase(val);
        }
        
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return vals[rand()%vals.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
