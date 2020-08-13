//Runtime Error
//4 / 68 test cases passed.
//to do: merge interval
class DSU{
public:
    vector<int> parent;
    
    DSU(int n){
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(parent[x] != x){
            //the recursion stops when x == parent[x]
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    
    int unite(int x, int y){
        //merge y into x
        parent[y] = find(parent[x]);
        
        return parent[y];
    }
};

class Solution {
public:
    unordered_map<int, int> group_head;
    unordered_map<int, int> group_size;
    int longestConsecutive(vector<int>& nums) {
        set<int> snums(nums.begin(), nums.end());
        nums = vector<int>(snums.begin(), snums.end());
        
        DSU dsu(nums.size());
        
        int ans = 0;
        
        for(int num : nums){
            // cout << "num: " << num << endl;
            int h;
            if(group_head.find(num-1) != group_head.end()){
                h = dsu.unite(num-1, num);
                group_head[num] = h;
                ++group_size[h];
            }else if(group_head.find(num+1) != group_head.end()){
                h = dsu.unite(num, num+1);
                group_head[num] = h;
                ++group_size[h];
            }else{
                group_head[num] = num;
                h = num;
                ++group_size[h];
            }
            // cout << "head: " << h << endl;
            ans = max(ans, group_size[h]);
        }
        
        return ans;
    }
};
