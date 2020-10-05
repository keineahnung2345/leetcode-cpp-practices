//bfs
//TLE
//127 / 308 test cases passed.
class Solution {
public:
    int minimumOneBitOperations(int n) {
        queue<int> q;
        int level = 0;
        
        q.push(0);
        
        unordered_set<int> visited;
        visited.insert(0);
        
        while(!q.empty()){
            int levelSize = q.size();
            
            while(levelSize-- > 0){
                int cur = q.front(); q.pop();
                
                if(cur == n){
                    return level;
                }
                
                if(visited.find(cur^1) == visited.end()){
                    q.push(cur^1);
                    visited.insert(cur^1);
                }
                
                for(int i = 0, mask = 1; cur >= 1<<i; ++i, mask += 1<<i){
                    // cout << "cur: " << cur << ", i: " << i << ", mask: " << mask << endl;
                    if((cur & mask) == (1<<i)){
                        int next = cur^(1<<(i+1));
                        // cout << "next: " << next << endl;
                        if(visited.find(next) == visited.end()){
                            q.push(next);
                            visited.insert(next);
                        }
                        break;
                    }
                }
                
            }
            
            ++level;
        }
        
        return -1;
    }
};
