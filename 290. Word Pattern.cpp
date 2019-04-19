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

//https://leetcode.com/problems/word-pattern/discuss/73409/Short-C%2B%2B-read-words-on-the-fly

class Solution {
public:
    bool wordPattern(string pattern, string str) {  
        map<char, int> p2i;
        map<string, int> s2i;
        int i = 0, n = pattern.size();
        
        istringstream is(str);
        
        //init -> (condition -> block -> increment)*n -> condition -> break
        //so in the 1st iteration, word will be str's first token
        for(string word; is >> word; i++){
            //i == n: it only happens when str's token count larger than pattern length
            if(i == n || p2i[pattern[i]] != s2i[word]){
                return false;
            }
            //can't set the value to 0, because 0 is the default value
            p2i[pattern[i]] = s2i[word] = i+1;
        }
        
        //i means token count now
        return i == n;
    }
};
