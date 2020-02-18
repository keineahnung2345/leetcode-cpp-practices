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
