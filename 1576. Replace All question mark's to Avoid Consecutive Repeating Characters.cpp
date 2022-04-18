//Runtime: 4 ms, faster than 25.81% of C++ online submissions for Replace All ?'s to Avoid Consecutive Repeating Characters.
//Memory Usage: 6.1 MB, less than 60.58% of C++ online submissions for Replace All ?'s to Avoid Consecutive Repeating Characters.
class Solution {
public:
    string modifyString(string s) {
        int n = s.size();
        
        for(int i = 0; i < n; ++i){
            if(s[i] == '?'){
                vector<bool> chosen(26, false);
                
                if(i-1 >= 0){
                    chosen[s[i-1]-'a'] = true;
                }
                
                if(i+1 < n && s[i+1] != '?'){
                    chosen[s[i+1]-'a'] = true;
                }
                
                for(int j = 0; j < 26; ++j){
                    if(!chosen[j]){
                        s[i] = 'a'+j;
                        break;
                    }
                }
            }
        }
        
        return s;
    }
};
