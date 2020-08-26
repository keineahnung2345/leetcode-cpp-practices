//WA
//311 / 325 test cases passed.
//[3,4,2,3] should be false
class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
        int violate_count = 0;
        for(int i = 1; i < nums.size(); i++){
            if(nums[i] < nums[i-1]){
                violate_count++;
            }
        }
        // cout << violate_count << endl;
        return violate_count <= 1;
    }
};
