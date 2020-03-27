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
 
//Approach 2: Sqrt Decomposition
//Runtime: 52 ms, faster than 38.63% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.6 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//time: preprocessing - O(n), range sum query - O(sqrt(n)), update query - O(1)
//space: O(sqrt(n))
class NumArray {
public:
    vector<int> blocks;
    vector<int> nums;
    int len;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        /*
        9 -> 3
        10 -> 4
        */
        if(nums.size() == 0){
            this->len = 0;
        }else{
            this->len = ceil(nums.size()/sqrt(nums.size()));
        }
        this->blocks = vector<int>(len, 0);
        for(int i = 0; i < nums.size(); i++){
            blocks[i/len] += nums[i];
        }
    }
    
    void update(int i, int val) {
        int blockId = i/len;
        blocks[blockId] += (val - nums[i]);
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        
        int startBlock = i/len, endBlock = j/len;
        
        if(startBlock == endBlock){
            for(int k = i; k <= j; k++){
                sum += nums[k];
            }
        }else{
            /*
            startBlock+1: the next block's id
            (startBlock+1)*len: the next block's start position
            (startBlock+1)*len-1: the current block's end position
            */
            for(int k = i; k <= (startBlock+1)*len -1; k++){
                sum += nums[k];
            }
            for(int k = startBlock+1; k <= endBlock-1; k++){
                sum += blocks[k];
            }
            for(int k = endBlock*len; k <= j; k++){
                sum += nums[k];
            }
        }
        
        return sum;
    }
};
