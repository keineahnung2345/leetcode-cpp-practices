//TLE
//131 / 151 test cases passed.
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int MOD = 1e9+7;
        int n = arr.size();
        
        if(all_of(arr.begin(), arr.end(), [](int& e){return !(e&1);})){
            return 0;
        }
        
        if(all_of(arr.begin(), arr.end(), [&n](int& e){return e&1;})){
            int ans = 0;
            
            while(n > 0){
                ans += n;
                n -= 2;
            }
            
            return ans;
        }
        
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            int subsum = 0;
            for(int j = i; j < n; ++j){
                subsum += arr[j];
                if(subsum&1){
                    ++ans;
                    if(ans > MOD) ans -= MOD;
                }
            }
        }
        
        return ans;
    }
};
