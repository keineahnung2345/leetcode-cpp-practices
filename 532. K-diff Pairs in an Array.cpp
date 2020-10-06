//Runtime: 28 ms, faster than 95.45% of C++ online submissions for K-diff Pairs in an Array.
//Memory Usage: 13.4 MB, less than 83.07% of C++ online submissions for K-diff Pairs in an Array.
class Solution {
public:
    struct pair_hash_int {
        inline std::size_t operator()(const std::pair<int,int> & v) const {
            return v.first*31+v.second;
        }
    };
    
    int findPairs(vector<int>& nums, int k) {
        int n = nums.size();
        
        unordered_set<pair<int, int>, pair_hash_int> pairs;
        
        sort(nums.begin(), nums.end());
        
        // for(const int& num : nums){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        for(int i = 0, j = 1; i < n && j < n; ){
            // cout << i << ", " << j << endl;
            if(nums[j] - nums[i] == k){
                // cout << "insert" << endl;
                pairs.insert({nums[i], nums[j]});
                ++i, ++j;
            }else if(nums[j] - nums[i] < k){
                ++j;
            }else{
                ++i;
                //j cannot be same as i
                if(j == i) ++j;
            }
        }
        
        return pairs.size();
    }
};

//counter
//https://leetcode.com/problems/k-diff-pairs-in-an-array/discuss/100098/Java-O(n)-solution-one-Hashmap-easy-to-understand
//Runtime: 40 ms, faster than 75.08% of C++ online submissions for K-diff Pairs in an Array.
//Memory Usage: 14.1 MB, less than 48.00% of C++ online submissions for K-diff Pairs in an Array.
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        map<int, int> counter;
        
        for(const int& num : nums){
            ++counter[num];
        }
        
        int ans = 0;
        
        //the key is sorted
        for(const pair<int, int>& p : counter){
            if(k == 0){
                if(p.second >= 2) ++ans;
            }else{
                //since key is sorted, we only need to find in one direction
                if(counter.find(p.first+k) != counter.end()){
                    ++ans;
                }
            }
        }
        
        return ans;
    }
};

//counter, one pass
//https://leetcode.com/problems/k-diff-pairs-in-an-array/discuss/100098/Java-O(n)-solution-one-Hashmap-easy-to-understand/146186
//Runtime: 32 ms, faster than 91.00% of C++ online submissions for K-diff Pairs in an Array.
//Memory Usage: 13.6 MB, less than 62.63% of C++ online submissions for K-diff Pairs in an Array.
class Solution {
public:
    int findPairs(vector<int>& nums, int k) {
        unordered_map<int, int> counter;
        
        int ans = 0;
        
        for(const int& num : nums){
            if(counter.find(num) == counter.end()){
                if(counter.find(num-k) != counter.end()) ++ans;
                if(counter.find(num+k) != counter.end()) ++ans;
            }else if(counter[num] == 1){
                if(k == 0) ++ans;
            }
            ++counter[num];
        }
        
        return ans;
    }
};
