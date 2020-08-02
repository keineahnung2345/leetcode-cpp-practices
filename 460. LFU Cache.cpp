//heap + map
//TLE
//20 / 23 test cases passed.
struct FTV{
    int freq;
    int time;
    int value;
    
    FTV(int f, int t, int v){
        freq = f;
        time = t;
        value = v;
    }
};

class FTVCompare{
public:
    bool operator() (pair<int, FTV*>& a, pair<int, FTV*>& b) {
        //the smaller freq, the smaller time will be evicted
        return (a.second->freq == b.second->freq) ? a.second->time > b.second->time : a.second->freq > b.second->freq;
    }
};

class LFUCache {
public:
    int capacity;
    int time;
    
    // std::function<bool (FTV*, FTV*)> comp = [](FTV* a, FTV* b){
    //     return (a->freq == b->freq) ? a->time < b->time : a->freq < b->freq;
    // };
    //(key, (freq, time, value))
    priority_queue<pair<int, FTV*>, vector<pair<int, FTV*>>, FTVCompare> pq;

    unordered_map<int, int> kvs;
    
    LFUCache(int capacity) {
        this->capacity = capacity;
        time = 0;
    }
    
    int get(int key) {
        if(kvs.find(key) == kvs.end()) return -1;
        ++time;
        // cout << "get (" << key << ")" << endl;
        // cout << "there are " << kvs.size() << "(" << pq.size() << ") elements." << endl;
        //don't need to update value, just update freq and time
        update(key, -1);
        return kvs[key];
    }
    
    void put(int key, int value) {
        ++time;
        if(capacity == 0) return;
        //evict one
        // cout << "put (" << key << ", " << value << ")" << endl;
        // cout << "there are " << kvs.size() << "(" << pq.size() << ") elements." << endl;
        
        if(kvs.find(key) != kvs.end()){
            //update
            update(key, value);
        }else{
            if(kvs.size() == capacity){
                pair<int, FTV*> p = pq.top(); pq.pop();
                kvs.erase(p.first);
                // cout << "put " << key << ", evict " << p.first << endl;
            }
            //insert
            kvs[key] = value;
            pq.push({key, new FTV(1, time, value)});
        }    
    }
    
    void update(int key, int value){
        if(value == -1) value = kvs[key];
        kvs[key] = value;
        priority_queue<pair<int, FTV*>, vector<pair<int, FTV*>>, FTVCompare> pq_tmp;
        while(pq.top().first != key){
            pair<int, FTV*> p = pq.top(); pq.pop();
            pq_tmp.push(p);
        }
        pair<int, FTV*> p = pq.top(); pq.pop();
        pq.push({p.first, new FTV(p.second->freq+1, time, value)});

        while(!pq_tmp.empty()){
            pair<int, FTV*> p = pq_tmp.top(); pq_tmp.pop();
            pq.push(p);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 
//double linked list + map
//https://leetcode.com/problems/lfu-cache/discuss/207673/Python-concise-solution-**detailed**-explanation%3A-Two-dict-%2B-Doubly-linked-list
//Runtime: 176 ms, faster than 97.79% of C++ online submissions for LFU Cache.
//Memory Usage: 40.5 MB, less than 93.48% of C++ online submissions for LFU Cache.
class DListNode{
public:
    int key;
    int value;
    int freq;
    DListNode *prev, *next;
    
    DListNode(int k, int v){
        key = k;
        value = v;
        freq = 1;
        prev = next = nullptr;
    }
};

class DList{
public:
    DListNode* sentinel;
    /*
    sentinel->next points to the head of list,
    sentinel->prev points to the tail of list
    */
    int size;
    
    DList(){
        size = 0;
        //sentinel is a dummy node
        sentinel = new DListNode(-1, -1);
        sentinel->prev = sentinel->next = sentinel;
    }
    
    void prepend(DListNode* node){
        //append to head
        //update node itself
        node->next = sentinel->next;
        node->prev = sentinel;
        //update node->next's prev
        sentinel->next->prev = node;
        //update node->prev's next
        //node becomes head of list
        sentinel->next = node;
        ++size;
    }
    
    DListNode* pop(DListNode* node = nullptr){
        if(size == 0) return nullptr;
        //the last in the list
        if(node == nullptr) node = sentinel->prev;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        --size;
        return node;
    }
};

class LFUCache {
public:
    //(key, node)
    unordered_map<int, DListNode*> nodes;
    //(freq, DList)
    unordered_map<int, DList*> freqs;
    int capacity;
    int min_freq;
    
    LFUCache(int capacity) {
        this->capacity = capacity;
        min_freq = 0;
    }
    
    void _update(DListNode* node){
        //update the node's freq, freq list and min_freq
        if(freqs.find(node->freq) == freqs.end()){
            freqs[node->freq] = new DList();
        }
        if(freqs.find(node->freq+1) == freqs.end()){
            freqs[node->freq+1] = new DList();
        }
        // cout << "pop from freqs[" << node->freq << "]" << endl;
        freqs[node->freq]->pop(node);
        if(min_freq == node->freq && freqs[node->freq]->size == 0){
            ++min_freq;
        }
        
        ++node->freq;
        // cout << "prepend to freqs[" << node->freq << "]" << endl;
        freqs[node->freq]->prepend(node);
    }
    
    int get(int key) {
        // cout << "get " << key << endl;
        if(nodes.find(key) == nodes.end()){
            return -1;
        }
        
        DListNode* node = nodes[key];
        
        //update the node's freq, freq list and min_freq
        _update(node);
        
        return node->value;
    }
    
    void put(int key, int value) {
        if(capacity == 0) return;
        // cout << "put (" << key << ", " << value << ")" << endl;
        if(nodes.find(key) != nodes.end()){
            DListNode* node = nodes[key];
            //update the node's freq, freq list and min_freq
            _update(node);
            //the node's value is also needed to be updated!
            node->value = value;
        }else{
            if(nodes.size() == capacity){
                if(freqs.find(min_freq) == freqs.end()){
                    freqs[min_freq] = new DList();
                }
                
                // cout << "freqs[" << min_freq << "]: ";
                // DListNode* cur = freqs[min_freq]->sentinel->next;
                // while(cur != freqs[min_freq]->sentinel){
                //     cout << "(" << cur->key << ", " << cur->value << ") ";
                //     cur = cur->next;
                // }
                // cout << endl;
                
                //delete the node from freq list and the map
                DListNode* node = freqs[min_freq]->pop();
                if(node){
                    // cout << "evict (" << node->key << ", " << node->value << ")" << endl;
                    nodes.erase(node->key);
                }
            }
            
            DListNode* node = new DListNode(key, value);
            nodes[key] = node;
            if(freqs.find(1) == freqs.end()) freqs[1] = new DList();
            freqs[1]->prepend(node);
            min_freq = 1;
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 
