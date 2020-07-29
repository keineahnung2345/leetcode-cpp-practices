//DP
//https://leetcode.com/problems/string-compression-ii/discuss/755970/Python-dynamic-programming
//TLE
//63 / 132 test cases passed.
class Solution {
public:
    int counter(string& s, int cur, char last_char, int last_count, int k){
        if(cur == s.size()) return 0;
        
        if(s[cur] == last_char){
            /*
            we only discard char when we first meet it,
            so here we always keep the char
            */
            int incr = 0;
            if(last_count == 1 || log10(last_count+1) == int(log10(last_count+1))){
                /*
                we need one more digit when the count changes from:
                1->2, 9->10, 99->100
                */
                incr = 1;
            }
            int ret = incr + counter(s, cur+1, s[cur], last_count+1, k);
            // cout << "(" << cur << ", " << last_char << ", " << last_count << ", " << k << ") : " << ret << endl;
            return ret;
        }else{
            /*
            when we meet first such char, 
            we can choose whether to keep it or discard it
            */
            //add 1: current char is the first char of its kind, and it takes one position in the encoded string
            int keep_count = 1 + counter(s, cur+1, s[cur], 1, k);
            //current char deleted, so last_char and last_count remain unchanged
            //k < 0 is impossible, early stopping
            int discard_count = (k >= 1) ? counter(s, cur+1, last_char, last_count, k-1) : numeric_limits<int>::max();
            
            int ret = min(keep_count, discard_count);
            // cout << "(" << cur << ", " << last_char << ", " << last_count << ", " << k << ") : " <<  ret << endl;
            return ret;
        }
    };
    
    int getLengthOfOptimalCompression(string s, int k) {
        int n = s.size();
        
        return counter(s, 0, '#', 0, k);
    }
};
