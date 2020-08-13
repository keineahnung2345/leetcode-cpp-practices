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

//Brute force
//TLE
//66 / 68 test cases passed.
//time: O(N^3), space: O(1)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int maxStreak = 0;
        
        for(int num : nums){ //O(n)
            int cur = num;
            while(find(nums.begin(), nums.end(), cur+1) != nums.end()){ 
                //while loop: O(n)
                //find: O(n)
                ++cur;
            }
            //cur in nums, cur+1 not in nums
            maxStreak = max(maxStreak, cur-num+1);
            // cout << num << ", " << cur << ", " << maxStreak << endl;
        }
        
        return maxStreak;
    }
};

//Sorting
//Runtime: 16 ms, faster than 93.81% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 11 MB, less than 59.85% of C++ online submissions for Longest Consecutive Sequence.
//time: O(NlogN), space: O(1) or O(N)
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        int maxStreak = 0;
        
        unordered_set<int> snums(nums.begin(), nums.end());
        nums = vector<int>(snums.begin(), snums.end());
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        for(int i = 0; i < n; ){
            int j = i;
            while(j+1 < n && nums[j]+1 == nums[j+1]){
                ++j;
            }
            //nums[i...j] is a group
            maxStreak = max(maxStreak, j-i+1);
            i = j+1;
        }
        
        return maxStreak;
    }
};

//Sorting, with duplicate
//Runtime: 16 ms, faster than 93.81% of C++ online submissions for Longest Consecutive Sequence.
//Memory Usage: 9.8 MB, less than 98.38% of C++ online submissions for Longest Consecutive Sequence.
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.empty()) return 0;
        
        int curStreak = 1;
        int maxStreak = 1;
        
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        
        for(int i = 1; i < n; ++i){
            if(nums[i] == nums[i-1]) continue;
            if(nums[i] == nums[i-1]+1){
                //extend old group
                ++curStreak;
            }else{
                //start a new group
                maxStreak = max(maxStreak, curStreak);
                curStreak = 1;
            }
        }
        
        //update with last group
        maxStreak = max(maxStreak, curStreak);
        
        return maxStreak;
    }
};
