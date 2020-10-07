//https://leetcode.com/problems/building-h2o/discuss/721793/CORRECT-and-efficient-C%2B%2B-solution-with-mutex-and-condition-variables.-99
//https://github.com/keineahnung2345/cpp-code-snippets/blob/master/thread/conditional_variable_notify_one.cpp
//Runtime: 172 ms, faster than 77.24% of C++ online submissions for Building H2O.
//Memory Usage: 9.2 MB, less than 18.16% of C++ online submissions for Building H2O.
class H2O {
private:
    int waitH, waitO;
    int needH, needO;
    condition_variable cvH, cvO;
    
    mutex mtx;
    bool building;
    
    void reset(){
        needH = 2;
        needO = 1;
        building = false;
    }
public:
    H2O() {
        waitH = waitO = 0;
        needH = 2;
        needO = 1;
        building = false;
    }

    void hydrogen(function<void()> releaseHydrogen) {
        unique_lock<mutex> ul(mtx);
        ++waitH;
        //condition 1: not building and the needed resource is collected
        //condition 2: still building and need H
        cvH.wait(ul, [&](){return 
            (!building && waitH >= 2 && waitO >= 1) || (building && needH > 0);});
        
        building = true;
        --waitH; //this H thread stop waiting
        --needH; //this H thread is used, so need one less H
        
        //wake up a H thread to continue building
        if(needH > 0) cvH.notify_one();
        
        //wake up a O thread to continue building
        if(needO > 0) cvO.notify_one();
        
        //complete building
        if(needH == 0 && needO == 0) reset();
        
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen) {
        unique_lock<mutex> ul(mtx);
        ++waitO;
        //condition 2: still building and need O
        cvO.wait(ul, [&](){return
            (!building && waitH >= 2 && waitO >= 1) || (building && needO > 0);});
        
        building = true;
        --waitO;
        --needO;
        
        /*
        need one or more H, we can notify all because after a thread is waken up,
        it will decrease needH, and so the condition 2 in cvH will be updated
        */
        if(needH > 0) cvH.notify_all();
        
        if(needH == 0 && needO == 0) reset();
        
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
    }
};
