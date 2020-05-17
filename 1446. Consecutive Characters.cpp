//Runtime: 12 ms, faster than 66.67% of C++ online submissions for Consecutive Characters.
//Memory Usage: 6.8 MB, less than 100.00% of C++ online submissions for Consecutive Characters.
class Solution {
public:
    int maxPower(string s) {
        if(s.size() == 0) return 0;
        
        int ans = 1; //need to initialize as 1, not 0!(imagine the case "j")
        int cur = 1; //need to initialize as 1, not 0!
        
        char last = s[0];
        for(int i = 1; i < s.size(); i++){
            if(s[i] == last){
                cur++;
            }
            
            if(s[i] != last || i == s.size()-1){
                ans = max(ans, cur);
                cur = 1;
            }
            
            last = s[i];
        }
        
        return ans;
    }
};
