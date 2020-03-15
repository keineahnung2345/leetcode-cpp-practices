//Reference to 47. Permutations II.cpp
//https://github.com/keineahnung2345/leetcode-cpp-practices/blob/master/47.%20Permutations%20II.cpp
//Runtime: 288 ms, faster than 8.14% of C++ online submissions for Reordered Power of 2.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Reordered Power of 2.
class Solution {
public:
    bool isPowerOf2(vector<int>& perm){
        if(perm[0] == 0) return false;
        
        int N = 0;
        for(int i = 0; i < perm.size(); i++){
            N = N * 10 + perm[i];
        }
        
        // if((int)log2(N) == log2(N)){
        //     for(int i = 0; i < perm.size(); i++){
        //         cout << perm[i];
        //     }
        //     cout << endl;
        //     cout << N << endl;
        // }
        
        return (int)log2(N) == log2(N);
    };
    
    bool backtrack(vector<int>& perm, vector<int>& nums, vector<bool>& used){
        if(perm.size() == nums.size()){
            // for(int i = 0; i < perm.size(); i++){
            //     cout << perm[i];
            // }
            // cout << endl;
            return isPowerOf2(perm);
        }else{
            for(int i = 0; i < nums.size(); i++){
                if(used[i]) continue;
                if(i > 0 && nums[i] == nums[i-1] && !used[i-1]) continue;
                perm.push_back(nums[i]);
                used[i] = true;
                if(backtrack(perm, nums, used)) return true;
                perm.pop_back();
                used[i] = false;
            }
        }
        
        return false;
    };
    
    bool reorderedPowerOf2(int N) {
        vector<int> nums;
        while(N){
            nums.insert(nums.begin(), N%10);
            N /= 10;
        }
        
        sort(nums.begin(), nums.end());
        
        vector<bool> used(nums.size(), false);
        vector<int> perm;
        
        return backtrack(perm, nums, used);
    }
};
