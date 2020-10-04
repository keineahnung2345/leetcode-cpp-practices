//TLE
//105 / 108 test cases passed.
//time: O(nk), space: O(k)
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> servers(k);
        vector<int> counts(k);
        
        int n = arrival.size();
        int min_sid = 0;
        for(int i = 0; i < n; ++i){
            if(arrival[i] < servers[min_sid]) continue;
            for(int j = 0; j < k; ++j){
                int sid = (i%k+j)%k;
                if(servers[sid] <= arrival[i]){
                    servers[sid] = arrival[i] + load[i];
                    ++counts[sid];
                    min_sid = min_element(servers.begin(), servers.end()) - servers.begin();
                    break;
                }
            }
        }
        
        int max_count = *max_element(counts.begin(), counts.end());
        vector<int> ans;
        
        for(int i = 0; i < counts.size(); ++i){
            if(counts[i] == max_count){
                ans.push_back(i);
            }
        }
        
        return ans;
    }
};
