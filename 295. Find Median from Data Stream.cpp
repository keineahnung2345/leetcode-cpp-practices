//Approach 1: Simple Sorting
//TLE
//15 / 18 test cases passed.
//time: O(NlogN), space: O(N)
class MedianFinder {
public:
    vector<int> vec;
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        vec.push_back(num);
        sort(vec.begin(), vec.end());
    }
    
    double findMedian() {
        int n = vec.size();
        if(n&1) return vec[n>>1];
        return (vec[(n>>1)-1]+vec[n>>1])/2.0;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
 
//Approach 2: Insertion Sort
//Runtime: 444 ms, faster than 15.81% of C++ online submissions for Find Median from Data Stream.
//Memory Usage: 46.8 MB, less than 94.97% of C++ online submissions for Find Median from Data Stream.
//time: O(N+logN) = O(N), space: O(N)
class MedianFinder {
public:
    vector<int> vec;
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(vec.empty()){
            vec.push_back(num);
        }else{
            /*
            lower_bound: find the smallest number >= x
            if there is no such element, it returns vec.end(),
            in this case, this statement is still safe
            */
            vec.insert(lower_bound(vec.begin(), vec.end(), num), num);
        }
    }
    
    double findMedian() {
        int n = vec.size();
        if(n&1) return vec[n>>1];
        return (vec[(n>>1)-1]+vec[n>>1])/2.0;
    }
};

//Approach 3: Two Heaps
//Runtime: 424 ms, faster than 18.81% of C++ online submissions for Find Median from Data Stream.
//Memory Usage: 47 MB, less than 41.77% of C++ online submissions for Find Median from Data Stream.
//time: O(logN), space: O(N)
class MedianFinder {
public:
    //maxPQ: smaller half, may contain one more element than minPQ
    //minPQ: larger half
    priority_queue<int, vector<int>> maxPQ;
    priority_queue<int, vector<int>, greater<int>> minPQ;
    
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        maxPQ.push(num);
        int t = maxPQ.top(); maxPQ.pop();
        minPQ.push(t);
        
        //minPQ's size must be <= maxPQ's size
        if(minPQ.size() > maxPQ.size()){
            t = minPQ.top(); minPQ.pop();
            maxPQ.push(t);
        }
    }
    
    double findMedian() {
        if(maxPQ.size() > minPQ.size()){
            return maxPQ.top();
        }
        return (maxPQ.top()+minPQ.top())/2.0;
    }
};

//Approach 4: Multiset and Two Pointers
//Runtime: 220 ms, faster than 95.39% of C++ online submissions for Find Median from Data Stream.
//Memory Usage: 49.3 MB, less than 9.29% of C++ online submissions for Find Median from Data Stream.
//time: O(logN), space: O(N)
class MedianFinder {
public:
    //AVL tree
    multiset<int> mset;
    multiset<int>::iterator lo, hi;
    
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int n = mset.size();
        multiset<int>::iterator it = mset.insert(num);
        
        if(!n){
            //originally empty
            lo = hi = it;
        }else if(n&1){
            //odd number of elements, lo and hi points to same location
            if(num < *lo){
                /*
                [1,2,3]
                becomes
                [1,1,2,3]
                */
                --lo;
            }else if(num == *lo){
                /*
                In C++, if there are already elements equal to num,
                then it insert num after such elements,
                so larger half's size will increase
                
                [1,2,3]: lo and hi points to 2
                becomes
                [1,2,2,3]: lo points to 1st 2, hi points to 2nd 2
                */
                ++hi;
            }else{
                //num > *lo
                ++hi;
            }
        }else{
            //even number of elements
            if(*lo <= num && num < *hi){
                //note the <= and < here!!
                /*
                In C++, if there are already elements equal to num,
                then it insert num after such elements
                
                so when num equal to *lo,
                it will also be inserted btw the two pointers
                */
                lo = hi = it;
            }else if(num < *lo){
                /*
                only when num < *lo(not ==),
                num is inserted before lo
                
                [1,3,4,5]
                becomes
                [1,2,3,4,5]
                */
                hi = lo;
                //lo and hi both points to old lo
            }else{
                /*
                when num >= *hi,
                num is always inserted after hi
                
                [1,3,4,5]
                becomes
                [1,3,4,5,6]
                */
                lo = hi;
                //lo and hi both points to old hi
            }
        }
    }
    
    double findMedian() {
        return (*lo + *hi)/2.0;
    }
};

//Multiset and One Pointer
//Runtime: 300 ms, faster than 44.92% of C++ online submissions for Find Median from Data Stream.
//Memory Usage: 49.5 MB, less than 5.62% of C++ online submissions for Find Median from Data Stream.
class MedianFinder {
public:
    multiset<int> mset;
    //mid points to the lower median if mset have even elements
    multiset<int>::iterator mid;
    
    /** initialize your data structure here. */
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        int n = mset.size();
        mset.insert(num);
        
        if(n == 0){
            mid = mset.begin();
        }else if(num < *mid){
            /*
            [1,3,4]
            becomes
            [1,2,3,4]
            
            [1,3,4,5]
            beocmes
            [1,2,3,4,5]
            */
            mid = (n&1) ? prev(mid) : mid;
        }else{
            //num >= *mid, num is inserted after mid
            /*
            [1,3,4]
            becomes
            [1,3,4,6]
            
            [1,3,4,5]
            beocmes
            [1,3,4,5,6]
            */
            mid = (n&1) ? mid : next(mid);
        }
    }
    
    double findMedian() {
        int n = mset.size();
        return (n&1) ? *mid: (*mid + *(next(mid)))/2.0;
    }
};
