//Runtime: 40 ms
//Memory Usage: 19.4 MB
class CustomStack {
    int maxSize;
    vector<int> stk;
public:
    CustomStack(int maxSize) {
        this->maxSize = maxSize;
    }
    
    void push(int x) {
        if(stk.size() < maxSize){
            stk.push_back(x);
        }
    }
    
    int pop() {
        if(stk.size() > 0){
            int top = stk[stk.size()-1];
            stk.pop_back();
            return top;
        }
        return -1;
    }
    
    void increment(int k, int val) {
        for(int i = 0; i < min((int)k, (int)stk.size()); i++){
            stk[i] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */
 
