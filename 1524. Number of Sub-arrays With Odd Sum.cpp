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

//DP
//https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/discuss/754702/Some-hints-to-help-you-solve-this-problem-on-your-own
//Runtime: 392 ms, faster than 67.62% of C++ online submissions for Number of Sub-arrays With Odd Sum.
//Memory Usage: 122.9 MB, less than 100.00% of C++ online submissions for Number of Sub-arrays With Odd Sum.
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int n = arr.size();
        int MOD = 1e9+7;
        
        //padding ahead
        arr.insert(arr.begin(), 0);
        //dp[i]: dp value of arr[0...i]
        vector<int> zeroCounts(n+1);
        vector<int> oneCounts(n+1);
        vector<int> cumsums(n+1);
        
        for(int i = 1; i <= n; ++i){
            cumsums[i] = (cumsums[i-1] + arr[i])&1;
            
            if(!(arr[i]&1)) zeroCounts[i] = 1;
            else oneCounts[i] = 1;
            
            //arr[1...i] = arr[1...i-1] + arr[i]
            if(!(arr[i]&1)){
                zeroCounts[i] = (zeroCounts[i]+zeroCounts[i-1])%MOD;
                oneCounts[i] = (oneCounts[i]+oneCounts[i-1])%MOD;
            }else if(arr[i]){
                zeroCounts[i] = (zeroCounts[i]+oneCounts[i-1])%MOD;
                oneCounts[i] = (oneCounts[i]+zeroCounts[i-1])%MOD;
            }
        }
        
//         for(int i = 0; i <= n; ++i){
//             cout << cumsums[i] << " ";
//         }
//         cout << endl;
        
//         for(int i = 0; i <= n; ++i){
//             cout << zeroCounts[i] << " ";
//         }
//         cout << endl;
        
//         for(int i = 0; i <= n; ++i){
//             cout << oneCounts[i] << " ";
//         }
//         cout << endl;
        
        //use custom add function to avoid overflow
        return accumulate(oneCounts.begin(), oneCounts.end(), 0 ,[&MOD](int& a, int& b){return (a+b)%MOD;});
    }
};
