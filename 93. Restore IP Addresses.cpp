//backtracking
//Runtime: 4 ms, faster than 80.26% of C++ online submissions for Restore IP Addresses.
//Memory Usage: 7.1 MB, less than 26.58% of C++ online submissions for Restore IP Addresses.
class Solution {
public:
    vector<string> ans;
    
    string join(const string& s, vector<int>& split){
        string ret = s;
        
        for(int i = split.size()-1; i >= 0; --i){
            // cout << split[i] << " " << ret << endl;
            ret.insert(ret.begin()+split[i], '.');
        }
        // cout << ret << endl;
        
        return ret;
    }
    
    bool isValid(string s){
        //length == 0 or length > 3
        if(s.empty() || s.size() > 3) return false;
        //length == 3 and >= 256
        if(s.size() == 3 && stoi(s) >= 256) return false;
        //length > 1 and start with 0
        if(s.size() > 1 && s[0] == '0') return false;
        return true;
    }
    
    void backtrack(string& s, int start, vector<int>& split){
        if(split.size() == 3){
            if(isValid(s.substr(split.back()))){
                ans.push_back(join(s, split));
            }
        }else{
            for(int len = 1; len <= 3 && start + len < s.size(); ++len){
                if(!isValid(s.substr(start, len))) continue;
                //now s[start:start+len-1] is valid
                //'.' will be the (start+len)th char
                split.push_back(start+len);
                backtrack(s, start+len, split);
                split.pop_back();
            }
        }
    }
    
    vector<string> restoreIpAddresses(string s) {
        vector<int> split;
        backtrack(s, 0, split);
        return ans;
    }
};
