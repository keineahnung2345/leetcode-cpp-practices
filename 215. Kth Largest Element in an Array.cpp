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

//Divide and conquer
//https://leetcode.com/problems/kth-largest-element-in-an-array/discuss/60495/Sharing-my-12ms-divide-and-conquer-solution-in-c%2B%2B
// /Runtime: 8 ms, faster than 97.62% of C++ online submissions for Kth Largest Element in an Array.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Kth Largest Element in an Array.
class Solution {
public:
    int randomizedPartition(vector<int>& nums, int start, int end){
        srand(time(NULL));
        int choose = rand()%(end-start+1) + start;
        //move random selected element to the end
        swap(nums[choose], nums[end]);
        //set it as pivot
        int pivot = nums[end];
        int l = start-1; //the end of left partition
        for(int r = start; r < end; r++){
            if(nums[r] <= pivot){
                //elements < pivot will be partitioned into left part
                swap(nums[r], nums[++l]);
            }
        }
        l++; //now l becomes the start of right partition
        swap(nums[l], nums[end]);
        return l;
    };
    
    int randomizedSelect(vector<int>& nums, int start, int end, int k){
        //find kth smallest
        if(start == end) return nums[start];
        int mid = randomizedPartition(nums, start, end);
        //here mid is the index to nums
        //now we need to convert it to the index to nums[start:end] (1-based)
        int i = mid-start+1; //+1 for 1-based
        if(i == k){
            return nums[mid];
        }else if(i < k){
            //find (k-i)th smallest in the right partition
            return randomizedSelect(nums, mid+1, end, k-i);
        }else{
            //find kth element in the lest partition
            return randomizedSelect(nums, start, mid-1, k);
        }
    }
    
    int findKthLargest(vector<int>& nums, int k) {
        //find kth largest -> find (nums.size()-k+1)th smallest
        return randomizedSelect(nums, 0, nums.size()-1, nums.size()-k+1);
    }
};
