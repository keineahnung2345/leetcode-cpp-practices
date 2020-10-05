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

//use set and priority_queue to finding available servers
//https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/discuss/876793/Java-O(nlogn)-use-both-TreeSet-and-PriorityQueue
//Runtime: 1016 ms, faster than 50.00% of C++ online submissions for Find Servers That Handled Most Number of Requests.
//Memory Usage: 118.3 MB, less than 25.00% of C++ online submissions for Find Servers That Handled Most Number of Requests.
//time: O(nlogk), space: O(k)
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> counts(k);
        set<int> availables;
        
        for(int i = 0; i < k; ++i){
            availables.insert(i);
        }
        
        //(end time, server id)
        //the smaller end time, the earlier popped
        auto comp = [](pair<int,int>& p1, pair<int,int>& p2){
            return p1.first > p2.first;};
        priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> busys(comp);
        
        int n = arrival.size();
        int min_sid = 0;
        for(int i = 0; i < n; ++i){
            int start = arrival[i];
            int end = arrival[i] + load[i];
            while(!busys.empty() && start >= busys.top().first){
                pair<int,int> p = busys.top(); busys.pop();
                availables.insert(p.second);
            }
            if(availables.empty()) continue;
            //find >=
            auto it = availables.lower_bound(i%k);
            int sid;
            if(it == availables.end()){
                sid = *availables.begin();
            }else{
                sid = *it;
            }
            busys.push({end, sid});
            ++counts[sid];
            availables.erase(sid);
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
