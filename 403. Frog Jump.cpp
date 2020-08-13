//BFS, unordered_set
//Runtime: 1836 ms, faster than 5.05% of C++ online submissions for Frog Jump.
//Memory Usage: 42.3 MB, less than 34.48% of C++ online submissions for Frog Jump.
/*
if using ordinary set:
//TLE
//25 / 39 test cases passed.
*/
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Solution {
public:
    bool canCross(vector<int>& stones) {
        int goal = stones.back();
        
        unordered_map<int, int> pos2idx;
        for(int i = 0; i < stones.size(); ++i){
            pos2idx[stones[i]] = i;
        }
        
        queue<pair<int, int>> q;
        pair<int, int> cur = {0, 1};
        unordered_set<pair<int, int>, pair_hash> visited;
        
        q.push(cur);
        visited.insert(cur);
        
        while(!q.empty()){
            cur = q.front(); q.pop();
            int pos = cur.first, step = cur.second;
            // cout << pos << ", " << step << endl;
            if(pos == goal) return true;
            
            int npos = pos+step;
            int nstep;
            
            //next position must be a stone
            if(find(stones.begin(), stones.end(), npos) == stones.end()){
                continue;
            }
            
            for(int i = -1; i <= 1; ++i){
                nstep = step+i;
                if(nstep <= 0) continue;
                if(visited.find({npos, nstep}) == visited.end()){
                    visited.insert({npos, nstep});
                    q.push({npos, nstep});
                }
            }
        }
        
        return false;
    }
};
