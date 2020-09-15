//Runtime: 4 ms, faster than 92.11% of C++ online submissions for Length of Last Word.
//Memory Usage: 6.4 MB, less than 92.88% of C++ online submissions for Length of Last Word.
class Solution {
public:
    int lengthOfLastWord(string s) {
        int ans = 0;
        int n = s.size();
        
        int i = n-1;
        
        while(i >= 0 && s[i] == ' ') --i;
        
        for(; (i >= 0) && (s[i] != ' '); --i){
            ++ans;
        }
        
        return ans;
    }
};
