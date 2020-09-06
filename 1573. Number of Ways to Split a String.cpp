//Runtime: 108 ms, faster than 12.50% of C++ online submissions for Number of Ways to Split a String.
//Memory Usage: 14.9 MB, less than 37.50% of C++ online submissions for Number of Ways to Split a String.
class Solution {
public:
    long long MOD = 1e9 + 7;
    
    int numWays(string s) {
        int n = s.size();
        
        vector<int> ones;
        
        for(int i = 0; i < n; ++i){
            if(s[i] == '1'){
                ones.push_back(i);
            }
        }
        
        int cnt = ones.size();
        
        if(cnt == 0){
            //(n-1)C2
            long long a = n-1, b = n-2;
            return ((a*b)>>1)%MOD;
        }
        
        if(cnt % 3 != 0){
            return 0;
        }
        
        long long ans = 0;
        
        // cout << cnt/3-1 << " : " << ones[cnt/3-1] << endl;
        // cout << cnt/3 << " : " << ones[cnt/3] << endl;
        
        long long a = ones[cnt/3] - ones[cnt/3-1];
        long long b = ones[cnt*2/3] - ones[cnt*2/3-1];
        ans = (a*b) % MOD;
        
        return ans;
    }
};
