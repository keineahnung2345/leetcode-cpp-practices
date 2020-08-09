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

//Recursion
//https://leetcode.com/problems/find-kth-bit-in-nth-binary-string/discuss/780984/Java-Recursive-Solution
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Find Kth Bit in Nth Binary String.
//Memory Usage: 6.2 MB, less than 66.67% of C++ online submissions for Find Kth Bit in Nth Binary String.
class Solution {
public:
    char findKthBit(int n, int k) {
        if(n == 1){
            //stop condition
            return '0';
        }
        /*
        n = 1, len = 1
        n = 2, len = 1*2+1 = 3
        n = 3, len = 3*2+1 = 7
        n = 4, len = 7*2+1 = 15
        */
        int len = (1<<n) - 1;
        
        //note that k is 1-based!
        if(k == (len>>1)+1){
            return '1';
        }else if(k < (len>>1)+1){
            //left part
            return findKthBit(n-1, k);
        }else{
            //right part
            /*
            kth bit in the original string
            becomes (l-k+1)th bit in the reverted string
            */
            //and we also need to invert it
            return findKthBit(n-1, len-k+1) == '0' ? '1' : '0';
        }
    }
};
