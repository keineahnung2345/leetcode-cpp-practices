//Runtime: 244 ms, faster than 16.67% of C++ online submissions for Find Kth Bit in Nth Binary String.
//Memory Usage: 58.1 MB, less than 66.67% of C++ online submissions for Find Kth Bit in Nth Binary String.
class Solution {
public:
    string reverse(string s){
        return string(s.rbegin(), s.rend());
    }
    
    string invert(string& s){
        string ret;
        ret.resize(s.size());
        transform(s.begin(), s.end(), ret.begin(), 
            [](char c){return (c == '1') ? '0' : '1';});
        return ret;
    }
    
    char findKthBit(int n, int k) {
        string s = "0";
        
        for(int i = 2; i <= n && s.size() < k; ++i){
            s = s + "1" + reverse(invert(s));
            // cout << s << endl;
        }
        
        // cout << s << endl;
        
        return s[k-1];
    }
};
