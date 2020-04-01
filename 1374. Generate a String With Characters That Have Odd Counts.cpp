//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Generate a String With Characters That Have Odd Counts.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for Generate a String With Characters That Have Odd Counts.
class Solution {
public:
    string generateTheString(int n) {
        if(n % 2 == 1) return string(n, 'a');
        string ans = string(n-1, 'a');
        ans += 'b';
        return ans;
    }
};
