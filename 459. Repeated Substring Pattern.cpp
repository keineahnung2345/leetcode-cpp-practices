//Runtime: 720 ms, faster than 7.41% of C++ online submissions for Repeated Substring Pattern.
//Memory Usage: 490.2 MB, less than 10.45% of C++ online submissions for Repeated Substring Pattern.

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        //l stands for the length of substring
        //max length of substring cannot exceed s.size()/2
        for(int l = 1; l <= s.size()/2; l++){
            int j = 0;
            // cout << s.substr(0, l) << endl;
            while(j + l <= s.size() && s.substr(j, l) == s.substr(0, l)){
                // cout << s.substr(j, l) << endl;
                j += l;
            }
            if(j == s.size()) return true;
        }
        return false;
    }
};

//https://leetcode.com/problems/repeated-substring-pattern/discuss/94334/Easy-python-solution-with-explaination
//Runtime: 36 ms, faster than 79.40% of C++ online submissions for Repeated Substring Pattern.
//Memory Usage: 15.5 MB, less than 62.69% of C++ online submissions for Repeated Substring Pattern.

class Solution {
public:
    bool repeatedSubstringPattern(string s) {
        if(s.size() == 0) return false;
        string ss = s + s;
        return ss.substr(1, ss.size()-2).find(s)!=string::npos;
    }
};
