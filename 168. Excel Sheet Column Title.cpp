//https://leetcode.com/problems/excel-sheet-column-title/discuss/441430/Detailed-Explanation-Here's-why-we-need-n-at-first-of-every-loop-(JavaPythonC%2B%2B)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Excel Sheet Column Title.
//Memory Usage: 6 MB, less than 100.00% of C++ online submissions for Excel Sheet Column Title.
class Solution {
public:
    string convertToTitle(int n) {
        string ans;
        
        /*
        For string ABZ,
        it is n = (0+1)*26^2 + (1+1)*26^2 + (25+1)*26^0,
        to get 'Z'(which is 25),
        we operate on the equation above:
        n-1 = (0+1)*26^2 + (1+1)*26^2 + 25,
        so we do (n-1)%26 to get the last char, which is 'Z' (1)
        
        then to go to the next iteration,
        we need to make n = (0+1)*26^2 + (1+1)*26^2,
        we do this by n = (n-1)/26 (2)
        */
        while(n){
            // cout << n%26 << " ";
            ans.insert(ans.begin(), 'A' + (n-1)%26);
            n = (n-1)/26;
        }
        // cout << endl;
        
        return ans;
    }
};
