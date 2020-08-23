//Greedy
//Runtime: 256 ms, faster than 40.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
//Memory Usage: 25.7 MB, less than 20.00% of C++ online submissions for Minimum Numbers of Function Calls to Make Target Array.
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int ans = 0;
        
        while(any_of(nums.begin(), nums.end(), [](const int& e){return e >= 2;})){
            for(int& num : nums){
                if(num&1){
                    ++ans;
                    --num;
                }
            }
            
            transform(nums.begin(), nums.end(), nums.begin(), [](int& x){return x>>1;});
            ++ans;
        }
        
        ans += accumulate(nums.begin(), nums.end(), 0);
        
        return ans;
    }
};
