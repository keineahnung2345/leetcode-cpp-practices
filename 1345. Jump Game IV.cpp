//BFS
//Runtime: 492 ms, faster than 24.29% of C++ online submissions for Jump Game IV.
//Memory Usage: 61.6 MB, less than 18.84% of C++ online submissions for Jump Game IV.
class Solution {
public:
    int minJumps(vector<int>& arr) {
        unordered_map<int, unordered_set<int>> val2idx;
        int n = arr.size();
        
        for(int i = 0; i < n; ++i){
            val2idx[arr[i]].insert(i);
        }
        
        int cur = 0, jumps = 0;
        queue<int> q;
        q.push(cur);
        
        vector<int> visited(n, false);
        visited[cur] = true;
        
        while(!q.empty()){
            int level_size = q.size();
            
            while(level_size-- > 0){
                cur = q.front(); q.pop();
                if(cur == n-1) return jumps;
                
                if(cur+1 < n && !visited[cur+1]){
                    visited[cur+1] = true;
                    q.push(cur+1);
                }
                
                if(cur-1 >= 0 && !visited[cur-1]){
                    visited[cur-1] = true;
                    q.push(cur-1);
                }
                
                //unordered_map<int, vector<int>> val2idx;
                //TLE
                // for(int j : val2idx[arr[cur]]){
                //     if(!visited[j]){
                //         visited[j] = true;
                //         q.push(j);
                //     }
                // }
                
                for(auto it = val2idx[arr[cur]].begin(); it != val2idx[arr[cur]].end(); ){
                    if(!visited[(*it)]){
                        visited[(*it)] = true;
                        q.push((*it));
                        it = val2idx[arr[cur]].erase(it);
                    }else{
                        ++it;
                    }
                }
            }
            
            
            ++jumps;
        }
        
        return jumps;
    }
};
