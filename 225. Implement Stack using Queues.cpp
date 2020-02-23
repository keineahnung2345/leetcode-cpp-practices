//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Implement Stack using Queues.
//Memory Usage: 8.9 MB, less than 66.67% of C++ online submissions for Implement Stack using Queues.
class MyStack {
public:
    queue<int> q1, q2;
    
    /** Initialize your data structure here. */
    MyStack() {
        
    }
    
    /** Push element x onto stack. */
    void push(int x) {
        q1.push(x);
    }
    
    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        while(q1.size() > 1){
            q2.push(q1.front());
            q1.pop();
        }
        //last element in q1
        int x = q1.front(); q1.pop();
        q1.swap(q2);
        return x;
    }
    
    /** Get the top element. */
    int top() {
        return q1.back();
    }
    
    /** Returns whether the stack is empty. */
    bool empty() {
        return q1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
 
