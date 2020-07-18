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

