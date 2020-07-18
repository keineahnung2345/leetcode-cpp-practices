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
 
