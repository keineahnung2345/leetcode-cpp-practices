//Runtime: 420 ms, faster than 100.00% of C++ online submissions for Alert Using Same Key-Card Three or More Times in a One Hour Period.
//Memory Usage: 118.4 MB, less than 25.00% of C++ online submissions for Alert Using Same Key-Card Three or More Times in a One Hour Period.
class Solution {
public:
    int time2int(string& t){
        // cout << t << endl;
        return stoi(t.substr(0, 2)) * 60 + stoi(t.substr(3));
    }
    
    bool diffInOneHour(string& t1, string& t2){
        return time2int(t2) - time2int(t1) <= 60; 
    }
    
    vector<string> alertNames(vector<string>& keyName, vector<string>& keyTime) {
        unordered_map<string, vector<string>> name2times;
        
        int n = keyName.size();
        
        for(int i = 0; i < n; ++i){
            name2times[keyName[i]].push_back(keyTime[i]);
        }
        
        vector<string> ans;
        
        for(auto it = name2times.begin(); it != name2times.end(); ++it){
            vector<string>& times = it->second;
            sort(times.begin(), times.end());
            for(int i = 2; i < times.size(); ++i){
                if(diffInOneHour(times[i-2], times[i])){
                    ans.push_back(it->first);
                    break;
                }
            }
        }
        
        sort(ans.begin(), ans.end());
        
        return ans;
    }
};
