//TLE
//62 / 69 test cases passed.
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        
        vector<int> accsum = nums;
        
        // cout << accsum[0] << " ";
        for(int i = 1; i < n; ++i){
            accsum[i] += accsum[i-1];
            // cout << accsum[i] << " ";
        }
        // cout << endl;
        
        int cursum = 0;
        vector<int>::iterator it;
        vector<pair<int, int>> dp(n); //(count, end)
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            cursum = (i > 0) ? accsum[i-1] : 0;
            // cout << "i: " << i << endl;
            // cout << "cursum: " << cursum << endl;
            // cout << "finding " << cursum + target << endl;
            if((it = find(accsum.begin()+i, accsum.end(), cursum+target)) != 
               accsum.end()){
                int curend = it - accsum.begin();
                // cout << "accsum[" << curend << "]: " << accsum[curend] << endl;
                
                dp[i] = {1, curend};
                for(int j = 0; j < i; ++j){
                    if(dp[j].second < i && dp[j].first >= 1){
                        //no overlap
                        dp[i] = {dp[j].first+1, curend};
                    }
                }
                
                // cout << "[" << i << ", " << dp[i].second << "]: " << dp[i].first << endl; //"\t";
                ans = max(ans, dp[i].first);
            }
        }
        // cout << endl;
        
        return ans;
    }
};

//improved from above, using unordered_map
//TLE
//66 / 69 test cases passed.
class Solution {
public:
    int maxNonOverlapping(vector<int>& nums, int target) {
        int n = nums.size();
        
        vector<int> accsum = nums;
        unordered_map<int, vector<int>> accsum2idx;
        
        // cout << accsum[0] << " ";
        accsum2idx[accsum[0]].push_back(0);
        for(int i = 1; i < n; ++i){
            accsum[i] += accsum[i-1];
            accsum2idx[accsum[i]].push_back(i);
            // cout << accsum[i] << " ";
        }
        // cout << endl;
        
        int cursum = 0;
        vector<int>::iterator it;
        vector<pair<int, int>> dp(n); //(count, end)
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            cursum = (i > 0) ? accsum[i-1] : 0;
            // cout << "i: " << i << endl;
            // cout << "cursum: " << cursum << endl;
            // cout << "finding " << cursum + target << endl;
            // if((it = find(accsum.begin()+i, accsum.end(), cursum+target)) != 
            //    accsum.end()){
            
            while(!accsum2idx[cursum+target].empty() && accsum2idx[cursum+target].front() < i){
                accsum2idx[cursum+target].erase(accsum2idx[cursum+target].begin());
            }
            if(!accsum2idx[cursum+target].empty()){
                int curend = accsum2idx[cursum+target].front();
                // int curend = it - accsum.begin();
                // cout << "accsum[" << curend << "]: " << accsum[curend] << endl;
                
                dp[i] = {1, curend};
                for(int j = i-1; j >= 0; --j){
                    if(dp[j].second < i && dp[j].first >= 1){
                        //no overlap
                        dp[i] = {dp[j].first+1, curend};
                        break;
                    }
                }
                
                // cout << "[" << i << ", " << dp[i].second << "]: " << dp[i].first << endl; //"\t";
                ans = max(ans, dp[i].first);
            }
        }
        // cout << endl;
        
        return ans;
    }
};
