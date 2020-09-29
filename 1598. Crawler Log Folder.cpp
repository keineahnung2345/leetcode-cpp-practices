//stack
//Runtime: 8 ms, faster than 91.48% of C++ online submissions for Crawler Log Folder.
//Memory Usage: 11.2 MB, less than 5.03% of C++ online submissions for Crawler Log Folder.
class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string> stk;
        
        for(const string& log : logs){
            if(log == "./"){
                
            }else if(log == "../"){
                if(!stk.empty()) stk.pop();
            }else{
                stk.push(log);
            }
        }
        
        return stk.size();
    }
};
