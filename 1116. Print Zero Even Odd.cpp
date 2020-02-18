//Runtime: 24 ms, faster than 91.61% of C++ online submissions for Print Zero Even Odd.
//Memory Usage: 9.2 MB, less than 100.00% of C++ online submissions for Print Zero Even Odd.
//https://leetcode.com/problems/print-zero-even-odd/discuss/358630/C%2B%2B-Solution

class ZeroEvenOdd {
private:
    int n;
    mutex mtx;
    condition_variable cv;
    //used to choose next thread
    int next; //-1 for zero, 1 for odd, 0 for even
    //the next integer to print
    int i;
public:
    ZeroEvenOdd(int n) {
        this->n = n;
        this->next = -1;
        this->i = 1;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        //need a while loop
        while(this->i <= this->n){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [this](){return this->next == -1;});
            //need to check whether i is valid before printing
            if(this-> i <= this->n){
                printNumber(0);
            }
            //this line should be put outside "if" block!
            //, so other threads can exit
            this->next = i%2;
            //need "unlock" here!
            lck.unlock();
            cv.notify_all();
        }

        return;
    }

    void even(function<void(int)> printNumber) {
        while(this->i <= this->n){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [this](){return this->next == 0;});
            if(this-> i <= this->n){
                printNumber(i);
            }
            this->i += 1;
            this->next = -1;
            lck.unlock();
            cv.notify_all();
        }
        return;
    }

    void odd(function<void(int)> printNumber) {
        while(this->i <= this->n){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [this](){return this->next == 1;});
            if(this-> i <= this->n){
                printNumber(i);
            }
            this->i += 1;
            this->next = -1;
            lck.unlock();
            cv.notify_all();
        }
        return;
    }
};
