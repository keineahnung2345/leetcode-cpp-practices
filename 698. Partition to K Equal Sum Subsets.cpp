//TLE
//64 / 149 test cases passed.
class Solution {
public:
    int partitionSum;
    vector<int> subsets;
    bool ans;
    
    void backtrack(vector<int>& nums, int k, int start){
        if(start == nums.size()){
            for(int val : subsets){
                cout << val << " ";
            }
            cout << endl;
            ans = all_of(subsets.begin(), subsets.end(), 
                          [this](const int& val){return val == partitionSum;});
        }else if(!ans){ //early stop
            for(int i = 0; i < k; i++){
                //early stop
                if(subsets[i] + nums[start] > partitionSum)
                    continue;
                subsets[i] += nums[start];
                backtrack(nums, k, start+1);
                subsets[i] -= nums[start];
            }
        }
    };
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        subsets = vector<int>(k, 0);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) return false;
        partitionSum = sum/k;
        ans = false;
        backtrack(nums, k, 0);
        return ans;
    }
};
