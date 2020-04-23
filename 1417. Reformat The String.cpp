//Runtime: 12 ms, faster than 95.94% of C++ online submissions for Reformat The String.
//Memory Usage: 7.7 MB, less than 100.00% of C++ online submissions for Reformat The String.
class Solution {
public:
    string reformat(string s) {
        string num = "", alpha = "";
        
        for(char c : s){
            if(c >= '0' && c <= '9'){
                num += c;
            }else{
                alpha += c;
            }
        }
        
        if(abs((int)num.size() - (int)alpha.size()) >= 2) return "";
        
        string ans = "";
        
        if(num.size() >= alpha.size()){
            //num first
            for(int i = 0; i < num.size(); i++){
                ans += num[i];
                if(i < alpha.size()) ans += alpha[i];
            }
        }else{
            //alpha first
            for(int i = 0; i < alpha.size(); i++){
                ans += alpha[i];
                if(i < num.size()) ans += num[i];
            }
        }
         
           
        return ans;
    }
};
