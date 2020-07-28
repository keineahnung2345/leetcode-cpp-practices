//Runtime: 16 ms, faster than 86.23% of C++ online submissions for Shuffle String.
//Memory Usage: 15.5 MB, less than 100.00% of C++ online submissions for Shuffle String.
class Solution {
public:
    string restoreString(string s, vector<int>& indices) {
        int n = s.size();
        string ans(n, '#');
        
        for(int i = 0; i < n; ++i){
            ans[indices[i]] = s[i];
        }
        
        return ans;
    }
};
