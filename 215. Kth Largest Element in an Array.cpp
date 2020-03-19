//Runtime: 12 ms, faster than 77.42% of C++ online submissions for Kth Largest Element in an Array.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Kth Largest Element in an Array.

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        //the smaller the earlier to be popped
        priority_queue<int, vector<int>, greater<int>> pq;
        
        for(int num : nums){
            pq.push(num);
            if(pq.size() > k){
                pq.pop();
            }
        }
        
        //the smallest in top k elements
        return pq.top();
    }
};
