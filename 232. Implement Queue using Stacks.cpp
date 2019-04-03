//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Implement Queue using Stacks.
//Memory Usage: 8.8 MB, less than 97.79% of C++ online submissions for Implement Queue using Stacks.

/**
push:  O(n), O(n)
pop:   O(1), O(1)
peek:  O(1), O(1)
empty: O(1), O(1)
**/

class MyQueue {
public:
    stack<int> stk;
    
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        stack<int> tmp;
        while(!stk.empty()){
            tmp.push(stk.top());
            stk.pop();
        }
        stk.push(x);
        while(!tmp.empty()){
            stk.push(tmp.top());
            tmp.pop();
        }
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        int tmp = stk.top();
        stk.pop();
        return tmp;
    }
    
    /** Get the front element. */
    int peek() {
        return stk.top();
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return stk.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
 
 /**
 Approach #2 (Two Stacks) Push - O(1)O(1) per operation, Pop - Amortized O(1)O(1) per operation.
 **/
 
 /**
push:  O(1), O(n)
pop:   amortized O(1), worst O(n), O(1)
peek:  O(1), O(1)
empty: O(1), O(1)
**/

/**
class MyQueue {
public:
    stack<int> s1, s2;
    int front;
    
    /** Initialize your data structure here. */
    MyQueue() {
    }
    
    /** Push element x to the back of queue. */
    void push(int x) {
        if(s1.empty()) front = x;
        s1.push(x);
    }
    
    /** Removes the element from in front of queue and returns that element. */
    int pop() {
        if(s2.empty()){
            while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
        }
        int tmp = s2.top();
        s2.pop();
        return tmp;
    }
    
    /** Get the front element. */
    int peek() {
        if(!s2.empty()){
            return s2.top();
        }
        return front;
    }
    
    /** Returns whether the queue is empty. */
    bool empty() {
        return s1.empty() && s2.empty();
    }
};
**/
