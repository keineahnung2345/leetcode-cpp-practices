//TLE
//36 / 39 test cases passed.
class Solution {
public:
    bool isPossibleDivide(vector<int>& nums, int k) {
        int N = nums.size();
        if(N % k != 0) return false;
        int times = N/k;
        
        sort(nums.begin(), nums.end());
        
        while(times-- > 0){
            int smallest = nums[0];
            for(int i = smallest; i < smallest + k; i++){
                auto it = find(nums.begin(), nums.end(), i);
                if(it != nums.end()){
                    nums.erase(it);
                }else{
                    return false;
                }
            }
        }
        
        return true;
    }
};
