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
 
//https://leetcode.com/problems/min-stack/discuss/49014/Java-accepted-solution-using-one-stack
//Runtime: 36 ms, faster than 84.44% of C++ online submissions for Min Stack.
//Memory Usage: 16.7 MB, less than 99.73% of C++ online submissions for Min Stack.

class MinStack {
public:
    /** initialize your data structure here. */
    stack<int> stk;
    int m = INT_MAX;
    MinStack() {
    }
    
    void push(int x) {
        if(x <= m){ //note it's <=, not <!
            //2nd smallest value is under 1st smallest value
            stk.push(m);
            m = x;
        }
        stk.push(x);
    }
    
    void pop() {
        int tmp = stk.top();
        stk.pop();
        //pop 2nd smallest value along 1st smallest value
        if(tmp == m){
            //when pop 1st smallest value
            //update m to 2nd smallest value
            m = stk.top();
            stk.pop();
        }
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        return m;
    }
};
