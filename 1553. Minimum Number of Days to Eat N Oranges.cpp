//BFS
//Runtime: 140 ms, faster than 28.57% of C++ online submissions for Minimum Number of Days to Eat N Oranges.
//Memory Usage: 22.5 MB, less than 14.29% of C++ online submissions for Minimum Number of Days to Eat N Oranges.
class Solution {
public:
    int minDays(int n) {
        queue<int> q;
        
        q.push(n);
        int level = 0;
        
        unordered_set<int> visited;
        visited.insert(n);
        
        while(!q.empty()){
            int level_size = q.size();
            
            while(level_size-- > 0){
                int cur = q.front(); q.pop();
                
                if(cur == 0){
                    return level;
                }
                
                if(visited.find(cur-1) == visited.end()){
                    visited.insert(cur-1);
                    q.push(cur-1);
                }
                if(!(cur&1) && visited.find(cur>>1) == visited.end()){
                    visited.insert(cur>>1);
                    q.push(cur>>1);
                }
                if(cur%3==0 && visited.find(cur%3) == visited.end()){
                    visited.insert(cur/3);
                    q.push(cur/3);
                }
            }
            
            ++level;
        }
        
        return level;
    }
};
