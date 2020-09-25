//WA
//221 / 222 test cases passed.
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<pair<int, int>> strs;
        
        int max_ele = *max_element(nums.begin(), nums.end());
        if(max_ele == 0) return "0";
        
        int max_digit = (log10((double)(max_ele)))+1;
        
        // cout << "max_digit: " << max_digit << endl;
        
        for(const int& num : nums){
            int extended_num = num;
            
            if(num != 0){
                int digit = (log10((double)(num)))+1;
                int first = num/pow(10,digit-1);
                // cout << "digit: " << digit << ", last: " << last << endl;

                while(digit++ < max_digit){
                    extended_num = extended_num*10 + first;
                }
            }
            
            // cout << num << " -> " << extended_num << endl;
            strs.push_back({num, extended_num});
        }
        
        sort(strs.rbegin(), strs.rend(), 
             [](const pair<int, int>& p1, const pair<int, int>& p2){
                 return (p1.second == p2.second) ? p1.first > p2.first: p1.second < p2.second;});
        
        string ans;
        
        for(const pair<int, int>& p : strs){
            cout << p.first << " ";
            ans += to_string(p.first);
        }
        cout << endl;
        
        return ans;
    }
};

//sort by concatenated numbers
//Runtime: 20 ms, faster than 50.98% of C++ online submissions for Largest Number.
//Memory Usage: 11.2 MB, less than 65.28% of C++ online submissions for Largest Number.
//time: O(NlogN), space: O(N)
//proof of the transitivity of our comparator: https://leetcode.com/problems/largest-number/discuss/291988/A-Proof-of-the-Concatenation-Comparator's-Transtivity
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        int max_ele = *max_element(nums.begin(), nums.end());
        if(max_ele == 0) return "0";
        
        sort(nums.rbegin(), nums.rend(), 
             [](int& a, int& b){
                 return to_string(a)+to_string(b) < to_string(b)+to_string(a);});
        
        string ans;
        for(int& num : nums){
            ans += to_string(num);
		}
        return ans;
    }
};
