//Runtime: 60 ms, faster than 93.26% of C++ online submissions for Sort an Array.
//Memory Usage: 12.2 MB, less than 100.00% of C++ online submissions for Sort an Array.
class Solution {
public:
    void swap(vector<int>& nums, int i, int j){
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
    };
    
    int partition(vector<int>& nums, int left, int right){
        int pivot = nums[right];
        int i = left - 1; //the end of the subarray < pivot
        for(int j = left; j < right; j++){
            if(nums[j] < pivot){
                //left part's size + 1
                i++;
                //now i points to the first element of right part
                //swap right part's element and nums[j]
                swap(nums, i, j);
                //now i points to the last element of left part
            }
        }
        i++;
        //now i pionts to right part's first element
        swap(nums, i, right);
        return i;
    };
    
    void quickSort(vector<int>& nums, int left, int right){
        if(left < right){
            int pivot = partition(nums, left, right);
            quickSort(nums, left, pivot-1);
            quickSort(nums, pivot+1, right);
        }
    };
    
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
};
