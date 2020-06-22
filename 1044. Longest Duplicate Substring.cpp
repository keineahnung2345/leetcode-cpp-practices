//WA(something to do with overflow?)
//14 / 16 test cases passed.
class Solution {
public:
    int modPower(int x, unsigned int y, unsigned int m){ 
        if (y == 0) 
            return 1; 
        long long p = modPower(x, y/2, m) % m; 
        p = (p * p) % m; 

        return (y%2 == 0)? p : (x * p) % m; 
    };

    // Function to return gcd of a and b 
    int gcd(int a, int b){ 
        if (a == 0) 
            return b; 
        return gcd(b%a, a); 
    };

    // Function to find modular inverse of a under modulo m 
    // Assumption: m is prime 
    int modInverse(int a, int m){ 
        int g = gcd(a, m); 
        if (g != 1){
            return -1;
        }else{ 
            // If a and m are relatively prime, then modulo inverse 
            // is a^(m-2) mode m 
            return modPower(a, m-2, m);
        } 
    };
    
    int modMultiply(int a, int b, int mod) {
        int res = 0; // Initialize result 

        // Update a if it is more than 
        // or equal to mod 
        a %= mod;

        while (b){ 
            /*
            If b is even then 
            a * b = 2 * a * (b / 2), 
            otherwise 
            a * b = a + a * (b - 1)
            */
            // If b is odd, add 'a' to result 
            if(b & 1){
                res = (res + a) % mod;
            }

            // Here we assume that doing 2*a 
            // doesn't cause overflow 
            a = (2 * a) % mod; 

            b >>= 1; // b = b / 2 
        } 

        return res; 
    };
    
    string longestDupSubstring(string S) {
        int n = S.size();
        int p = 26;
        // int MOD = 1e9 + 7; //slower
        int MOD = 19260817;
        int pInv = modInverse(p, MOD);
        
        //binary search to find right boundary
        int left = 0, right = n-1;
        int len;
        
        string ans;
        
        vector<int> powers(n);
        powers[0] = 1;
        for(int i = 1; i < n; ++i){
            powers[i] = modMultiply(powers[i-1], p, MOD);
        }
        
        while(left <= right){
            //mid
            len = left + (right-left)/2;
            if(len == 0) break;
            // cout << left << ", " << len << ", " << right << endl;
            
            //hash value -> start indices
            unordered_map<long long, vector<int>> hashs;
            
            long long hash = 0, power = 1;
            
            for(int i = 0; i < len; ++i){
                // hash += (S[i]-'a')* power;
                // power = (power * p) % MOD;
                hash = (hash + modMultiply(S[i]-'a', powers[i], MOD)) % MOD;
            }
            //p^(n-1)
            // power = (power * pInv) % MOD;
            
            hashs[hash].push_back(0);
            
            bool valid = false;
            for(int start = 1; start+len-1 < n; ++start){
                hash = (hash - (S[start-1]-'a')) % MOD;
                hash = modMultiply(hash, pInv, MOD);
                hash = (hash + modMultiply(S[start+len-1]-'a', powers[len-1], MOD) % MOD);
                
                if(hashs.find(hash) != hashs.end()){
                    for(int& matched_start : hashs[hash]){
                        if(strcmp((S.substr(matched_start, len)).data(), S.substr(start, len).data()) == 0){
                        //slower
                        // if(S.substr(matched_start, len) == S.substr(start, len)){
                            valid = true;
                            if(len > ans.size())
                            ans = S.substr(start, len);
                            break;
                        }
                    }
                }
                if(valid) break;
                hashs[hash].push_back(start);
                // for(auto it = hashs.begin(); it != hashs.end(); ++it){
                //     cout << it->first << " ";
                // }
                // cout << endl;
            }
            
            if(valid){
                left = len+1;
            }else{
                right = len-1;
            }
        }
        
        if(right < 0) return "";
        
        return ans;
    }
};
