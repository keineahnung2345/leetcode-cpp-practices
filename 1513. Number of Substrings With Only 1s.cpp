//Runtime: 84 ms, faster than 25.00% of C++ online submissions for Number of Substrings With Only 1s.
//Memory Usage: 8.9 MB, less than 100.00% of C++ online submissions for Number of Substrings With Only 1s.
class Solution {
public:
    int moduloMultiplication(int a, int b, int mod) {
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
    } 
    
    int numSub(string s) {
        int MOD = 1e9+7;
        
        map<int, int> counter;
        
        int n = s.size();
        
        int len = 0;
        
        for(int i = 0; i <= n; ++i){
            if(i == n || s[i] == '0'){
                if(len > 1){
                    // counter[1] is handled otherwhere
                    // cout << "len: " << len << ", count increase" << endl;
                    counter[len]++;
                }
                len = 0;
            }else{
                ++len;
                counter[1]++;
            }
            // cout << "len: " << len << endl;
        }
        
        int ans = 0;
        
        for(auto it = counter.begin(); it != counter.end(); ++it){
            if(it->first == 1){
                ans += it->second;
            }else{
                int a = it->first;
                int b = it->first-1;
                if(a % 2 == 0) a /= 2;
                if(b % 2 == 0) b /= 2;
                int t = moduloMultiplication(a, b, MOD);
                t = moduloMultiplication(t, it->second, MOD);
                ans += t;
                // ans += (it->first) * (it->first-1) / 2 * it->second;
            }
        }
        
        return ans;
    }
};
