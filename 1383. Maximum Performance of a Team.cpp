//TLE
//23 / 53 test cases passed.
class Solution {
public:
    int ans;
    int n, k;
    vector<int> speed, efficiency;
    long mod = 1e9 + 7;
    
    void backtrack(vector<int>& ids, vector<int>& combIds, int start){
        if(combIds.size() == k){
            long perf = 0;
            int eff = INT_MAX;
            int speedSum = 0;
            for(int combId : combIds){
                eff = min(efficiency[combId], eff);
                speedSum += speed[combId];
            }
            perf = ((eff % mod) * (speedSum % mod)) % mod;
            // if((int)perf > ans){
            //     for(int i = 0; i < k; i++){
            //         cout << combIds[i] << " ";
            //     }
            //     cout << endl;
            // }
            ans = max((int)perf, ans);
        }else{
            for(int i = start; i < n; i++){
                combIds.push_back(i);
                backtrack(ids, combIds, i+1);
                combIds.pop_back();
            }
        }
    }
    
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        ans = 0;
        this->n = n;
        this->speed = speed;
        this->efficiency = efficiency;
        //we can have 1 to k engineers!
        //not necessary k!
        vector<int> combIds;
        
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0);
        
        for(int i = 1; i <= k; i++){
            this->k = i;
            backtrack(ids, combIds, 0);
        }
        
        // cout << endl;
        return ans;
    }
};
