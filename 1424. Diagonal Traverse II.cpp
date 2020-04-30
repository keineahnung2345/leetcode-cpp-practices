//53 / 56 test cases passed.
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int m = nums.size(), n = 0, total = 0;
        vector<int> ns(m, 0);
        vector<long long> diags(m, 0);
        
        for(int i = 0; i < m; i++){
            n = max((int)nums[i].size(), n);
            ns[i] = (int)nums[i].size();
            diags[i] = (long long)ns[i] + i;
            total += ns[i];
        }
        
        vector<int> ans(total, 0);
        int cur = 0;
        
        // cout << "total: " << total << endl;
        for(int diag = 0; diag <= m-1+n-1; diag++){
//             for(int i = min(diag, m-1); i >= 0; i--){
//                 // auto it = find_if(ns.begin(), ns.end(), [](int n){return n > diag - i;});
//                 // while (it != std::end(myvec))
                
                
//                 int j = diag - i;
//                 // if(nums[i].size() > j){
//                 if(ns[i] > j){
//                     // ans.push_back(nums[i][j]);
//                     ans[cur++] = nums[i][j];
//                 }
                
//             }
            
            // cout << "cur: " << cur << endl;
            if(cur == ans.size()) break;
            vector<long long>::iterator it = diags.begin();
            
            while(it != diags.end()){
                it = find_if(it, diags.end(), [&diag](long long x){
                    return x > diag;
                });

                if(it == diags.end()) break;

                // int i = (it - diags.begin());
                int i = distance(begin(diags), it);
                
                // cout << i << " " << diag-i << endl;
                
                if(diag-i < 0) break;

                ans[cur++] = nums[i][(int)(diag-i)];

                it = next(it);
                // it = diags.end();
            }
            
        }
        
        return ans;
    }
};
