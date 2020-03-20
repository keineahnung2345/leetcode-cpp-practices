//TLE
//30 / 37 test cases passed.
class FreqStack {
public:
    map<int, int> counter;
    vector<int> vec;
    
    FreqStack() {
        
    }
    
    void push(int x) {
        vec.push_back(x);
        counter[x]++;
    }
    
    int pop() {
        map<int, int>::iterator p = max_element(counter.begin(), counter.end(), 
            [] (const pair<int, int> & p1, const pair<int, int> & p2) {
                return p1.second < p2.second;
            }
        );
        int mode = p->second;
        int key;
        for(int i = vec.size()-1; i >= 0; i--){
            key = vec[i];
            if(counter[key] == mode){
                vec[i] = -1;
                counter[key]--;
                if(counter[key] == 0){
                    counter.erase(key);
                }
                break;
            }
        }
        return key;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
 
 //Runtime error
 class FreqStack {
public:
    map<int, int> counter;
    vector<int> vec;
    
    FreqStack() {
        
    }
    
    void push(int x) {
        vec.push_back(x);
        counter[x]++;
    }
    
    int pop() {
        map<int, int>::iterator p = max_element(counter.begin(), counter.end(), 
            [] (const pair<int, int> & p1, const pair<int, int> & p2) {
                return p1.second < p2.second;
            }
        );
        int mode = p->second;
        int key;
        auto rit = find_if(vec.rbegin(), vec.rend(), 
               [this, &mode](const int& key){
                   return this->counter[key] == mode;
               });
        int idx = vec.rend() - rit - 1;
        vec[idx] = -1;
        counter[key]--;
        
        return key;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */

//Approach 1: Stack of Stacks
//Runtime: 408 ms, faster than 10.44% of C++ online submissions for Maximum Frequency Stack.
//Memory Usage: 73.1 MB, less than 91.67% of C++ online submissions for Maximum Frequency Stack.
//time: push and pop, O(1), space: O(n)
class FreqStack {
public:
    map<int, int> freq;
    map<int, stack<int>> group;
    int maxfreq;
    
    FreqStack() {
        maxfreq = 0;
    }
    
    void push(int x) {
        int f = freq[x] + 1;
        freq[x] = f;
        maxfreq = max(maxfreq, f);
        
        // don't need to check whether group[f] is initialized?
        group[f].push(x);
        
        /*
        if x is pushed multiple times, 
        then group[1], group[2], group[3], ... will all have x 
        */
    }
    
    int pop() {
        int x = group[maxfreq].top(); group[maxfreq].pop();
        freq[x]--;
        if(group[maxfreq].size() == 0){
            /*
            In this circumstance, maxfreq is consecutive
            */
            maxfreq--;
        }
        return x;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 */
