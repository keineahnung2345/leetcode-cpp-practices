//Runtime: 48 ms, faster than 25.07% of C++ online submissions for Design Circular Deque.
//Memory Usage: 13.9 MB, less than 100.00% of C++ online submissions for Design Circular Deque.
class MyCircularDeque {
public:
    vector<int> q;
    int head, curSize;
    bool isStart;
    
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        q = vector<int>(k, -1);
        head = 0;
        curSize = 0;
        isStart = true;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(isFull()) return false;
        if(isEmpty()){
            head = 0;
        }else{
            head = (head-1+q.size()) % q.size();
        }
        q[head] = value;
        curSize++;
        // for(int i = 0; i < q.size(); i++){
        //     cout << q[i] << " ";
        // }
        // cout << endl;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(isFull()) return false;
        q[(head+curSize) % q.size()] = value;
        curSize++;
        // for(int i = 0; i < q.size(); i++){
        //     cout << q[i] << " ";
        // }
        // cout << endl;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(isEmpty()) return false;
        q[head] = -1;
        head = (head+1) % q.size();
        curSize--;
        // for(int i = 0; i < q.size(); i++){
        //     cout << q[i] << " ";
        // }
        // cout << endl;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(isEmpty()) return false;
        q[(head+curSize-1) % q.size()] = -1;
        curSize--;
        // for(int i = 0; i < q.size(); i++){
        //     cout << q[i] << " ";
        // }
        // cout << endl;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return q[head];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return q[(head+curSize-1) % q.size()];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return curSize == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return curSize == q.size();
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */

//no edge case
//https://leetcode.com/problems/design-circular-deque/discuss/155209/c%2B%2B-99-ring-buffer-no-edge-cases.-fb-interviewer-really-loves-it.-easy-to-impl-in-4mins.-cheers!
//Runtime: 48 ms, faster than 25.07% of C++ online submissions for Design Circular Deque.
//Memory Usage: 14.1 MB, less than 100.00% of C++ online submissions for Design Circular Deque.
class MyCircularDeque {
public:
    vector<int> q;
    int head, tail, curSize;
    
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) {
        q = vector<int>(k, -1);
        head = k-1; //exclusive
        tail = 0; //exclusive
        curSize = 0;
    }
    
    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value) {
        if(isFull()) return false;
        q[head] = value;
        head = (head-1+q.size()) % q.size();
        curSize++;
        return true;
    }
    
    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value) {
        if(isFull()) return false;
        q[tail] = value;
        tail = (tail+1) % q.size();
        curSize++;
        return true;
    }
    
    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront() {
        if(isEmpty()) return false;
        head = (head+1) % q.size();
        q[head] = -1;
        curSize--;
        return true;
    }
    
    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast() {
        if(isEmpty()) return false;
        tail = (tail-1+q.size()) % q.size();
        q[tail] = -1;
        curSize--;
        return true;
    }
    
    /** Get the front item from the deque. */
    int getFront() {
        return q[(head+1) % q.size()];
    }
    
    /** Get the last item from the deque. */
    int getRear() {
        return q[(tail-1+q.size()) % q.size()];
    }
    
    /** Checks whether the circular deque is empty or not. */
    bool isEmpty() {
        return curSize == 0;
    }
    
    /** Checks whether the circular deque is full or not. */
    bool isFull() {
        return curSize == q.size();
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
