//Runtime: 336 ms, faster than 62.59% of C++ online submissions for Print FooBar Alternately.
//Memory Usage: 10.5 MB, less than 100.00% of C++ online submissions for Print FooBar Alternately.
class FooBar {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    bool isFoo;

public:
    FooBar(int n) {
        this->n = n;
        this->isFoo = true;
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [this](){return isFoo;});
        	// printFoo() outputs "foo". Do not change or remove this line.
        	printFoo();
            isFoo = false;
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; i++) {
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [this](){return !isFoo;});
        	// printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            isFoo = true;
            cv.notify_all();
        }
    }
};
