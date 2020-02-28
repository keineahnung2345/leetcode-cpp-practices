//Brute Force
//query time: O(n), space: O(1)
//Runtime: 176 ms, faster than 15.17% of C++ online submissions for Range Sum Query - Immutable.
//Memory Usage: 17.3 MB, less than 72.41% of C++ online submissions for Range Sum Query - Immutable.
class NumArray {
public:
    vector<int> nums;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
    }
    
    int sumRange(int i, int j) {
        int ans = 0;
        for(int pos = i; pos <= j; pos++){
            ans += nums[pos];
        }
        return ans;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
 
//Cache
//Runtime: 28 ms, faster than 94.08% of C++ online submissions for Range Sum Query - Immutable.
//Memory Usage: 17.2 MB, less than 79.31% of C++ online submissions for Range Sum Query - Immutable.
//acc_sum[0] is 0
//acc_sum[k] is the cumulative sum for nums[0 ... k-1](inclusive)
//pre-computation time: O(n), query time: O(1)
//space: O(n)
class NumArray {
public:
    vector<int> acc_sum;
    
    NumArray(vector<int>& nums) {
        int N = nums.size();
        this->acc_sum = vector<int>(N+1);
        this->acc_sum[0] = 0;
        for(int i = 1; i < N+1; i++){
            this->acc_sum[i] = this->acc_sum[i-1] + nums[i-1];
        }
    }
    
    int sumRange(int i, int j) {
        return this->acc_sum[j+1] - this->acc_sum[i];
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
 
