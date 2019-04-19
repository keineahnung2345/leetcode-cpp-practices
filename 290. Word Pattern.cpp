//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Word Pattern.
//Memory Usage: 8.5 MB, less than 88.89% of C++ online submissions for Word Pattern.

class Solution {
public:
    bool wordPattern(string pattern, string str) {        
        map<char, string> m1;
        map<string, char> m2;
        
        string delimiter = " ";

        size_t pos = 0;
        string token;
        int i = 0;
        while ((pos = str.find(delimiter)) != string::npos) {
            token = str.substr(0, pos);
            // cout << token << endl;
            if(m1.find(pattern[i]) == m1.end()){
                m1[pattern[i]] = token;
            }else if(m1[pattern[i]] != token){
                return false;
            }
            
            if(m2.find(token) == m2.end()){
                m2[token] = pattern[i];
            }else if(m2[token] != pattern[i]){
                return false;
            }
            
            str.erase(0, pos + delimiter.length());
            i++;
        }
        // cout << i << endl;
        //i means the count of space in str
        if(i != pattern.size()-1) return false;
        
        if(m1.find(pattern[i]) == m1.end()){
            m1[pattern[i]] = str;
        }else if(m1[pattern[i]] != str){
            return false;
        }

        if(m2.find(str) == m2.end()){
            m2[str] = pattern[i];
        }else if(m2[str] != pattern[i]){
            return false;
        }
        
        return true;
    }
};
