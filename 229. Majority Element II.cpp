//hashmap, counter
//Runtime: 32 ms, faster than 54.63% of C++ online submissions for Majority Element II.
//Memory Usage: 15.8 MB, less than 17.16% of C++ online submissions for Majority Element II.
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int> counter;
        
        for(int& num : nums){
            ++counter[num];
        }
        
        vector<int> ans;
        int n = nums.size();
        
        for(auto it = counter.begin(); it != counter.end(); ++it){
            if(it->second > n/3){
                ans.push_back(it->first);
            }
        }
        
        return ans;
    }
};

//Approach 1: Boyer-Moore Voting Algorithm
//Runtime: 32 ms, faster than 54.63% of C++ online submissions for Majority Element II.
//Memory Usage: 15.6 MB, less than 54.60% of C++ online submissions for Majority Element II.
//time: O(N), space: O(1)
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        /*
        the initial value of a and b should be different,
        consider [-2147483648],
        in the second pass, a will be -2147483648 and b also be -2147483648,
        so acounter and bcounter will be 1 after 2nd pass,
        but bcounter should not be updated
        */
        int a = INT_MIN, b = INT_MIN+1;
        int acounter = 0, bcounter = 0;
        
        int n = nums.size();
        
        for(int& num : nums){
            /*
            we should check if num == a or num == b before
            acounter == 0 or bcounter == 0:
            consider the case [1,1],
            in 1st iteration, a will be 1 by acounter == 0,
            in 2nd iteration, b will be 1 by bcounter == 0,
            this is not what we want
            */
            if(num == a){
                ++acounter;
            }else if(num == b){
                ++bcounter;
            }else if(acounter == 0){
                a = num;
                ++acounter;
            }else if(bcounter == 0){
                b = num;
                ++bcounter;
            }else if(num != a && num != b){
                --acounter;
                --bcounter;
            }
        }
        
        acounter = bcounter = 0;
        for(int i = 0; i < n; ++i){
            if(nums[i] == a) ++acounter;
            if(nums[i] == b) ++bcounter;
        }
        
        vector<int> ans;
        
        if(acounter > n/3) ans.push_back(a);
        if(bcounter > n/3) ans.push_back(b);
        
        return ans;
    }
};
