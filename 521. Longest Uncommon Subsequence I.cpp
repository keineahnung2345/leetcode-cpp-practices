//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Longest Uncommon Subsequence I .
//Memory Usage: 8.5 MB, less than 40.00% of C++ online submissions for Longest Uncommon Subsequence I .
class Solution {
public:
    int findLUSlength(string a, string b) {
        if(a != b){
            return max(a.size(), b.size());
        }
        return -1;
    }
};
