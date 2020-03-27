//Runtime: 516 ms, faster than 5.03% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.5 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
class NumArray {
public:
    vector<int> nums;
    vector<int> sum;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        this->sum = vector<int>(nums.size(), 0);
        for(int i = 0; i < nums.size(); i++){
            sum[i] = ((i-1>=0)?sum[i-1]:0) + nums[i];
        }
    }
    
    void update(int i, int val) {
        for(int cur = i; cur < sum.size(); cur++){
            sum[cur] += (val - nums[i]);
        }
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        return sum[j] - ((i-1>=0)?sum[i-1]:0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
 
