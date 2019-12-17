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

//using condition_variable and mutex
//https://leetcode.com/problems/fizz-buzz-multithreaded/discuss/387994/C%2B%2B-mutex-condition_variable-please-suggest-improvements
//Runtime: 48 ms, faster than 57.33% of C++ online submissions for Fizz Buzz Multithreaded.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Fizz Buzz Multithreaded.
class FizzBuzz {
private:
    int n;
    int count;
    mutex m;
    condition_variable cv;

public:
    FizzBuzz(int n) {
        this->n = n;
        this->count = 1;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(true){
            unique_lock<mutex> lock(m);
            //wait for lock
            while(count <= n && !(count % 3 == 0 && count % 5 != 0)){
                cv.wait(lock);
            }
            //lock acquired
            if(count > n) break;
            printFizz();
            ++count;
            //release lock
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(true){
            unique_lock<mutex> lock(m);
            while(count <= n && !(count % 3 != 0 && count % 5 == 0)){
                cv.wait(lock);
            }
            if(count > n) break;
            printBuzz();
            ++count;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(true){
            unique_lock<mutex> lock(m);
            while(count <= n && !(count % 15 == 0)){
                cv.wait(lock);
            }
            if(count > n) break;
            printFizzBuzz();
            ++count;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(true){
            unique_lock<mutex> lock(m);
            while(count <= n && (count % 3 == 0 || count % 5 == 0)){
                cv.wait(lock);
            }
            if(count > n) break;
            printNumber(count);
            count++;
            cv.notify_all();
        }
    }
};

/*
The error of unique_lock<mutex> lock;(it should be unique_lock<mutex> lock(m);):
AddressSanitizer:DEADLYSIGNAL
=================================================================
==29==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000010 (pc 0x7f95fb0ff193 bp 0x7f95ea79cd40 sp 0x7f95ea79cbd8 T4)
==29==The signal is caused by a READ memory access.
==29==Hint: address points to the zero page.
    #0 0x7f95fb0ff192 in __pthread_mutex_unlock_usercnt (/lib/x86_64-linux-gnu/libpthread.so.0+0xb192)
    #1 0x7f95fb1010d6 in __pthread_cond_wait (/lib/x86_64-linux-gnu/libpthread.so.0+0xd0d6)
    #2 0x7f95fcdac3ab in std::condition_variable::wait(std::unique_lock<std::mutex>&) (/usr/local/lib64/libstdc++.so.6+0xb53ab)
    #5 0x7f95fcdb1a6e  (/usr/local/lib64/libstdc++.so.6+0xbaa6e)
    #6 0x7f95fb0fb493 in start_thread (/lib/x86_64-linux-gnu/libpthread.so.0+0x7493)
    #7 0x7f95fb805ace in __clone (/lib/x86_64-linux-gnu/libc.so.6+0xe8ace)
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/lib/x86_64-linux-gnu/libpthread.so.0+0xb192) in __pthread_mutex_unlock_usercnt
Thread T4 created by T0 here:
    #0 0x7f95fd0c22d0 in pthread_create (/usr/local/lib64/libasan.so.5+0x492d0)
    #1 0x7f95fcdb1cf4 in std::thread::_M_start_thread(std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >, void (*)()) (/usr/local/lib64/libstdc++.so.6+0xbacf4)
    #2 0x7f95fb73d2e0 in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x202e0)
==29==ABORTING
*/
