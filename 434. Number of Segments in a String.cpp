//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Number of Segments in a String.
//Memory Usage: 7.8 MB, less than 100.00% of C++ online submissions for Number of Segments in a String.

class Solution {
public:
    int countSegments(string s) {
        if(s.empty()) return 0;
        
        bool lastIsSpace = true;
        int ans = 0;
        
        for(int i = 0; i < s.size(); i++){
            if(s[i] == ' '){
                lastIsSpace = true;
            }else if(lastIsSpace){
                //only update lastIsSpace when it's true and s[i] is not space
                //update ans when we meet first char of a block
                lastIsSpace = false;
                ans++;
            }
        }
        return ans;
    }
};
