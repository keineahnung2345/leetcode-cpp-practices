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
 
//map + double linked list
//https://leetcode.com/problems/lru-cache/discuss/45911/Java-Hashtable-%2B-Double-linked-list-(with-a-touch-of-pseudo-nodes)
//Runtime: 116 ms, faster than 55.33% of C++ online submissions for LRU Cache.
//Memory Usage: 37.3 MB, less than 96.34% of C++ online submissions for LRU Cache.
class DLinkedNode{
public:
    int key;
    int value;
    DLinkedNode *prev, *post;
    DLinkedNode() : key(0), value(0), prev(NULL), post(NULL) {};
    DLinkedNode(int k, int v){
        this->key = k;
        this->value = v;
        this->prev = NULL;
        this->post = NULL;
    };
};

class LRUCache {
public:
    map<int, DLinkedNode*> cache; //from key to node
    int count, capacity;
    DLinkedNode *head, *tail;

    void addNode(DLinkedNode* node){
        //add to head
        node->prev = head;
        node->post = head->post;

        head->post->prev = node;
        head->post = node;
    };

    void removeNode(DLinkedNode* node){
        DLinkedNode *prev = node->prev, *post = node->post;

        // node->prev = NULL; //this will set prev to NULL?
        // node->post = NULL;

        prev->post = post;
        post->prev = prev;

    };

    void moveToHead(DLinkedNode* node){
        removeNode(node);
        addNode(node);
    };

    DLinkedNode* popTail(){
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    };
    
    LRUCache(int capacity) {
        this->count = 0;
        this->capacity = capacity;
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->post = tail;
        tail->prev = head;
    }
    
    int get(int key) {
        DLinkedNode* node = cache[key];
        if(node == NULL){
            return -1;
        }
        moveToHead(node);
        return node->value;
    }
    
    void put(int key, int value) {
        DLinkedNode* node = cache[key];
        if(node == NULL){
            node = new DLinkedNode(key, value);
            cache[key] = node;
            addNode(node);
            ++count;
            if(count > capacity){
                DLinkedNode* last = popTail();
                cache.erase(cache.find(last->key));
                --count;
            }
        }else{
            node->value = value;
            moveToHead(node);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
