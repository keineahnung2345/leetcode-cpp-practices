//DFS, recursive
//Runtime: 652 ms, faster than 24.40% of C++ online submissions for Time Needed to Inform All Employees.
//Memory Usage: 86 MB, less than 100.00% of C++ online submissions for Time Needed to Inform All Employees.
class Solution {
public:
    unordered_map<int, vector<int>> children;
    vector<int> informTime;
    int totalTime = 0;
    
    void dfs(int node, int curTime){
        totalTime = max(totalTime, curTime);
        for(int child : children[node]){
            dfs(child, curTime + informTime[node]);
        }
    }
    
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        for(int i = 0; i < manager.size(); i++){
            //i's manager is manager[i]
            children[manager[i]].push_back(i);
        }
        
        this->informTime = informTime;
        
        dfs(headID, 0);
        
        return totalTime;
    }
};

//DFS, iterative
//https://leetcode.com/problems/time-needed-to-inform-all-employees/discuss/532680/Python3-dfs-recursively-and-iteratively
//Runtime: 680 ms, faster than 21.86% of C++ online submissions for Time Needed to Inform All Employees.
//Memory Usage: 88.4 MB, less than 100.00% of C++ online submissions for Time Needed to Inform All Employees.
class Solution {
public:
    int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) {
        unordered_map<int, vector<int>> children;
        
        for(int i = 0; i < n; i++){
            //don't need to record root's parent
            // if(i == headID) continue;
            children[manager[i]].push_back(i);
        }
        
        stack<pair<int, int>> stk;
        int ans = 0;
        
        stk.push(make_pair(headID, 0));
        
        while(!stk.empty()){
            pair<int,int> p = stk.top(); stk.pop();
            int node = p.first, curTime = p.second;
            
            // cout << node << " " << curTime << endl;
            
            ans = max(ans, curTime);
            
            for(int child : children[node]){
                stk.push(make_pair(child, curTime+informTime[node]));
            }
        }
        
        return ans;
    }
};
