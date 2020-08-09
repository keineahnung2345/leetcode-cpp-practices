//Brute force
//Runtime: 4 ms, faster than 83.33% of C++ online submissions for Make The String Great.
//Memory Usage: 6.2 MB, less than 83.33% of C++ online submissions for Make The String Great.
class Solution {
public:
    string makeGood(string s) {
        int i = 0;
        
        while(i+1 < s.size()){
            //'A': 65, 'a': 97
            if(abs(s[i] - s[i+1]) == 32){
                s.erase(i, 2);
                if(i > 0) --i;
            }else{
                ++i;
            }
        }
        
        return s;
    }
};

//stack
//https://leetcode.com/problems/make-the-string-great/discuss/781009/Java-Simple-Solution-using-Stack-Explained
//Runtime: 4 ms, faster than 83.33% of C++ online submissions for Make The String Great.
//Memory Usage: 6.8 MB, less than 33.33% of C++ online submissions for Make The String Great.
class Solution {
public:
    string makeGood(string s) {
        stack<char> stk;
        int n = s.size();
        
        for(int i = 0; i < n; ++i){
            if(!stk.empty() && abs(stk.top()-s[i]) == 32){
                stk.pop();
            }else{
                stk.push(s[i]);
            }
        }
        
        string ans(stk.size(), '#');
        
        for(int i = stk.size()-1; i >= 0; --i){
            ans[i] = stk.top(); stk.pop();
        }
        
        return ans;
    }
};
