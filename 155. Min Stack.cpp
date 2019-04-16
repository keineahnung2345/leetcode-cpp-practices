//Runtime: 240 ms, faster than 5.05% of C++ online submissions for Min Stack.
//Memory Usage: 16.7 MB, less than 97.85% of C++ online submissions for Min Stack.

class MinStack {
public:
    /** initialize your data structure here. */
    vector<int> v;
    MinStack() {
        vector<int> v;
    }
    
    void push(int x) {
        v.push_back(x);
    }
    
    void pop() {
        v.erase(v.begin()+v.size()-1);
    }
    
    int top() {
        //return v[v.size()-1];
        return v.back();
    }
    
    int getMin() {
        return *min_element(v.begin(), v.end());
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
 
