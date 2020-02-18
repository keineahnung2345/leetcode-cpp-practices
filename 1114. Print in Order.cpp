//Runtime: 1624 ms, faster than 10.44% of C++ online submissions for Print in Order.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Print in Order.

class Foo {
public:
    int count;
    
    Foo() {
        count = 0;
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        count += 1;
    }

    void second(function<void()> printSecond) {
        while(count < 1){
        }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        count += 1;
    }

    void third(function<void()> printThird) {
        while(count < 2){
            
        }
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        count += 1;
    }
};

//https://leetcode.com/problems/print-in-order/discuss/343384/C%2B%2BWhy-most-of-the-solutions-using-mutex-are-wrong%2Bsolution
//Runtime: 152 ms, faster than 63.21% of C++ online submissions for Print in Order.
//Memory Usage: 9.3 MB, less than 100.00% of C++ online submissions for Print in Order.
class Foo {
public:
    int count;
    mutex mtx;
    condition_variable cv;
    
    Foo() {
        count = 1;
    }

    void first(function<void()> printFirst) {
        unique_lock<mutex> lck(mtx);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        count += 1;
        cv.notify_all();
    }

    void second(function<void()> printSecond) {
        unique_lock<mutex> lck(mtx);
        // printSecond() outputs "second". Do not change or remove this line.
        cv.wait(lck, [this](){return count == 2;});
        printSecond();
        count += 1;
        cv.notify_all();
    }

    void third(function<void()> printThird) {
        unique_lock<mutex> lck(mtx);
        // printThird() outputs "third". Do not change or remove this line.
        cv.wait(lck, [this](){return count == 3;});
        printThird();
        count += 1;
        cv.notify_all();
    }
};
