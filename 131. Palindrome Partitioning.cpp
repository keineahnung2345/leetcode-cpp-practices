//TLE
class Solution {
public:
    bool isPalindrome(string s){
        int N = s.size();
        
        //get the last half of s
        string s_rvs = s.substr(N - N/2);
        reverse(s_rvs.begin(), s_rvs.end());
        
        return s.substr(0, N/2) == s_rvs;
    };
    
    void backtrack(vector<vector<string>>& parts, vector<string>& part, string s, int start){
        if(start >= s.size()){
            bool flag = true;
            for(string token : part){
                if(!isPalindrome(token)){
                    flag = false;
                    break;
                }
            }
            if(flag) parts.push_back(part);
        }else{
            for(int i = 1; start + i <= s.size(); i++){
                // cout << start << " : " << start+i << endl;
                string token = s.substr(start, i);
                part.push_back(token);
                backtrack(parts, part, s, start+i);
                part.pop_back();
            }
        }
    };
    
    vector<vector<string>> partition(string s) {
        int N = s.size();
        vector<vector<string>> parts;
        vector<string> part;
        
        backtrack(parts, part, s, 0);
        
        return parts;
    }
};
