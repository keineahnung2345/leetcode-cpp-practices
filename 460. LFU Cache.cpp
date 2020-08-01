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
 
