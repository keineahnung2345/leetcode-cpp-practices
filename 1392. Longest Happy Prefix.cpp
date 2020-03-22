//either Time Limit Exceeded or Memory Limit Exceeded
//69 / 72 test cases passed.
class Solution {
public:
    string longestPrefix(string s) {
        int N = s.size();
        int SEGMENT = 10000;
        
        //l starts from N-1(substring cannot be itself)
        for(int l = N-1; l >= 1; l--){
            // cout << l << endl;
            // string prefix = s.substr(0, l);
            // string suffix = s.substr(N-l);

            // bool same = true;
            // for(int i = 0; i < prefix.size(); i++){
            //     if(prefix[i] != suffix[i]){
            //         same = false;
            //         break;
            //     }
            // }
            // if(same){
            //     return prefix;
            // }
            // if(prefix == suffix){
            //     return prefix;
            // }
            
            
            bool same = true;
            for(int i = 0; i <= l/SEGMENT; i++){
                //partPrefix could exceed the boundary
                string partPrefix = s.substr(0+i*SEGMENT, SEGMENT);
                string partSuffix = s.substr(N-l+i*SEGMENT, SEGMENT);
                //partPrefix could exceed the boundary
                if(partPrefix.size() != partSuffix.size()){
                    partPrefix = partPrefix.substr(0, partSuffix.size());
                }
                
                for(int i = 0; i < partPrefix.size(); i++){
                    if(partPrefix[i] != partSuffix[i]){
                        same = false;
                        break;
                    }
                }
                
                if(same == false){
                    break;
                }
                
                // if(partPrefix != partSuffix){
                //     same = false;
                //     break;
                // }
            }

            if(same){
                return s.substr(0, l);
            }
        }
        
        return "";
    }
};

//KMP
//Runtime: 48 ms, faster than 28.57% of C++ online submissions for Longest Happy Prefix.
//Memory Usage: 19 MB, less than 100.00% of C++ online submissions for Longest Happy Prefix.
class Solution {
public:
    vector<int> preprocess(string& pattern){
        int n = pattern.size();
        vector<int> lps(n, 0);
        
        for(int i = 1, len = 0; i < n; ){
            if(pattern[i] == pattern[len]){
                len++;
                lps[i] = len;
                i++;
            }else if(len > 0){
                len = lps[len-1];
            }else{
                i++;
            }
        }
        
        return lps;
    };
    
    string longestPrefix(string s) {
        vector<int> lps = preprocess(s);
        // for(int e : lps){
        //     cout << e;
        // }
        // cout << endl;
        
        // int length = *max_element(lps.begin(), lps.end());
        int length = lps[lps.size()-1];
        return s.substr(0, length);
    }
};

//Rolling hash
//https://leetcode.com/problems/longest-happy-prefix/discuss/547448/Python-rolling-hash
//Runtime: 296 ms, faster than 14.29% of C++ online submissions for Longest Happy Prefix.
//Memory Usage: 14.3 MB, less than 100.00% of C++ online submissions for Longest Happy Prefix.
class Solution {
public:
    //https://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/
    long long int power(long long int x, long long int y, long long int p){  
        long long int res = 1;

        // Update x if it is more than or equal to p
        x = x % p; 

        while(y > 0){
            // If y is odd, multiply x with result
            if(y & 1){
                res = (res*x) % p;
            }

            // y must be even now
            y >>= 1;
            x = (x*x) % p;
        }
        
        return res;  
    };
    
    string longestPrefix(string s) {
        int N = s.size();
        if(N == 1) return "";
        long long int mod = pow(10, 9) + 7;
        
        long long int prefixHash = 0, suffixHash = 0;
        
        int res = -1;
        
        //i cannot be N-1 because we only want the proper substrings
        for(int i = 0; i < N-1; i++){
            // prefixHash += (s[i]-'a') * ((long long int)pow(26, i) % mod);
            prefixHash += (s[i]-'a') * power(26, i, mod);
            prefixHash %= mod;
            
            //Note it's s[N-1-i] here!
            suffixHash = suffixHash * 26 + (s[N-1-i] - 'a');
            suffixHash %= mod;
            
            // cout << i << " " << prefixHash << " " << suffixHash << endl;
            
            if(prefixHash == suffixHash){
                res = i;
            }
        }
        
        return (res == -1) ? "" : s.substr(0, res+1);
    }
};
