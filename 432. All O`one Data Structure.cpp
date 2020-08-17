//https://leetcode.com/problems/all-oone-data-structure/discuss/91416/Java-AC-all-strict-O(1)-not-average-O(1)-easy-to-read
//Runtime: 96 ms, faster than 63.80% of C++ online submissions for All O`one Data Structure.
//Memory Usage: 25.6 MB, less than 37.00% of C++ online submissions for All O`one Data Structure.
class Bucket{
public:
    int count;
    unordered_set<string> keys;
    Bucket *prev, *next;
    
    Bucket(int c){
        count = c;
        prev = next = nullptr;
    };
};

class AllOne {
public:
    unordered_map<string, int> key2count;
    unordered_map<int, Bucket*> count2bucket;
    
    //a doubly-linked list
    Bucket *head, *tail;
    
    /** Initialize your data structure here. */
    AllOne() {
        head = new Bucket(INT_MIN);
        tail = new Bucket(INT_MAX);
        head->next = tail;
        tail->prev = head;
    }
    
    /** Inserts a new key <Key> with value 1. Or increments an existing key by 1. */
    void inc(string key) {
        if(key2count.find(key) == key2count.end()){
            key2count[key] = 1;
            if(count2bucket.find(1) == count2bucket.end()){
                count2bucket[1] = new Bucket(1);
                // if(head->next->count != 1){
                    insertBucketAfter(count2bucket[1], head);
                // }
            }
            count2bucket[1]->keys.insert(key);
        }else{
            changeKey(key, 1);
        }
        // cout << key << " -> " << key2count[key] << endl;
    }
    
    /** Decrements an existing key by 1. If Key's value is 1, remove it from the data structure. */
    void dec(string key) {
        if(key2count.find(key) != key2count.end()){
            int count = key2count[key];
            if(count == 1){
                key2count.erase(key);
                removeKeyFromBucket(count2bucket[count], key);
            }else{
                changeKey(key, -1);
            }
        }
        // cout << key << " -> " << key2count[key] << endl;
    }
    
    /** Returns one of the keys with maximal value. */
    string getMaxKey() {
        return tail->prev == head ? "" : *(tail->prev->keys.begin());
    }
    
    /** Returns one of the keys with Minimal value. */
    string getMinKey() {
        return head->next == tail ? "" : *(head->next->keys.begin());
    }
    
    void changeKey(string& key, int offset){
        //offset is 1 or -1
        int oldcount = key2count[key];
        int newcount = oldcount+offset;
        key2count[key] = newcount;
        
        Bucket* oldbucket = count2bucket[oldcount];
        
        if(count2bucket.find(newcount) == count2bucket.end()){
            count2bucket[newcount] = new Bucket(newcount);
            insertBucketAfter(count2bucket[newcount], (offset == 1) ? oldbucket : oldbucket->prev);
        }
        
        count2bucket[newcount]->keys.insert(key);
        removeKeyFromBucket(oldbucket, key);
    }
    
    void removeKeyFromBucket(Bucket* bucket, string& key){
        bucket->keys.erase(key);
        if(bucket->keys.empty()){
            removeBucketFromList(bucket);
            count2bucket.erase(bucket->count);
        }
    };
    
    void removeBucketFromList(Bucket* bucket){
        bucket->prev->next = bucket->next;
        bucket->next->prev = bucket->prev;
        // delete bucket; //why not?
        bucket->next = nullptr; 
        bucket->prev = nullptr;
    }
    
    void insertBucketAfter(Bucket* newbucket, Bucket* prebucket){
        newbucket->prev = prebucket;
        newbucket->next = prebucket->next;
        prebucket->next->prev = newbucket;
        prebucket->next = newbucket;    
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
 
