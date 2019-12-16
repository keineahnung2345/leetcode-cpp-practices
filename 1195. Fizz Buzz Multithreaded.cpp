//Runtime: 1428 ms, faster than 12.41% of C++ online submissions for Fizz Buzz Multithreaded.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Fizz Buzz Multithreaded.

class FizzBuzz {
private:
    int n;
    int cur;
    mutex mtx;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->cur = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(this->cur <= this->n){
            if(this->cur % 15 != 0 && this->cur % 3 == 0){
                mtx.lock();
                printFizz();
                this->cur++;
                mtx.unlock();
            }
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(this->cur <= this->n){
            if(this->cur % 15 != 0 && this->cur % 5 == 0){
                mtx.lock();
                printBuzz();
                this->cur++;
                mtx.unlock();
            }
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(this->cur <= this->n){
            if(this->cur % 15 == 0){
                mtx.lock();
                printFizzBuzz();
                this->cur++;
                mtx.unlock();
            }
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(this->cur <= this->n){
            if(this->cur % 3 != 0 && this->cur % 5 != 0){
                mtx.lock();
                printNumber(this->cur);
                this->cur++;
                mtx.unlock();
            }
        }
    }
};
