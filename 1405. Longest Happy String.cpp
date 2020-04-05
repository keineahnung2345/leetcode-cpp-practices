//https://leetcode.com/problems/longest-happy-string/discuss/564277/C%2B%2BJava-a-greater-b-greater-c
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Longest Happy String.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Longest Happy String.
class Solution {
public:
    string longestDiverseString(int a, int b, int c, char aa = 'a', char bb = 'b', char cc = 'c') {
        //make sure a >= b >= c
        if(a < b)
            return longestDiverseString(b,a,c,bb,aa,cc);
        if(a < c)
            return longestDiverseString(c,b,a,cc,bb,aa);
        if(b < c)
            return longestDiverseString(a,c,b,aa,cc,bb);
        //we only have aa now
        if(b == 0){
            // cout << a << " " << b << " " << c << endl;
            string tmp = string(min(2, a), aa);
            // cout << tmp << endl;
            return tmp;
        }
        /*
        whether to append bb after two aa,
        if we have most b in the next time, 
        then we don't have to append b here,
        otherwise, a is possible to be appended in next time,
        so we need to insert b here
        */
        int use_b = (a - min(2, a)) >= b ? 1 : 0;
        string tmp = string(min(2, a), aa) + string(use_b, bb) + longestDiverseString(a-min(2, a),b-use_b,c,aa,bb,cc);
        // cout << a << " " << b << " " << c << endl;
        // cout << tmp << endl;
        return tmp;
    }
};
