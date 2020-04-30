//TLE
//53 / 56 test cases passed.
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int m = nums.size(), n = 0, total = 0;
        vector<int> ns(m, 0);
        vector<long long> diags(m, 0);
        
        for(int i = 0; i < m; i++){
            n = max((int)nums[i].size(), n);
            ns[i] = (int)nums[i].size();
            diags[i] = (long long)ns[i] + i;
            total += ns[i];
        }
        
        vector<int> ans(total, 0);
        int cur = 0;
        
        // cout << "total: " << total << endl;
        for(int diag = 0; diag <= m-1+n-1; diag++){
//             for(int i = min(diag, m-1); i >= 0; i--){
//                 // auto it = find_if(ns.begin(), ns.end(), [](int n){return n > diag - i;});
//                 // while (it != std::end(myvec))
                
                
//                 int j = diag - i;
//                 // if(nums[i].size() > j){
//                 if(ns[i] > j){
//                     // ans.push_back(nums[i][j]);
//                     ans[cur++] = nums[i][j];
//                 }
                
//             }
            
            // cout << "cur: " << cur << endl;
            if(cur == ans.size()) break;
            vector<long long>::iterator it = diags.begin();
            
            while(it != diags.end()){
                it = find_if(it, diags.end(), [&diag](long long x){
                    return x > diag;
                });

                if(it == diags.end()) break;

                // int i = (it - diags.begin());
                int i = distance(begin(diags), it);
                
                // cout << i << " " << diag-i << endl;
                
                if(diag-i < 0) break;

                ans[cur++] = nums[i][(int)(diag-i)];

                it = next(it);
                // it = diags.end();
            }
            
        }
        
        return ans;
    }
};

//sort
//Runtime: 1436 ms, faster than 7.58% of C++ online submissions for Diagonal Traverse II.
//Memory Usage: 99.4 MB, less than 100.00% of C++ online submissions for Diagonal Traverse II.
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int m = nums.size();
        if(m == 0) return vector<int>();
        vector<vector<int>> tuples;
        
        for(int i = 0; i < m; i++){
            for(int j = 0; j < nums[i].size(); j++){
                /*
                first sort by row index + col index, ascending,  
                and then by row index, descending
                */
                tuples.push_back({i+j, -i, nums[i][j]});
            }
        }
        
        sort(tuples.begin(), tuples.end());
        
        vector<int> ans(tuples.size());
        
        for(int i = 0; i < ans.size(); i++){
            ans[i] = tuples[i][2];
        }
        
        return ans;
    }
};

//bucket(hashmap)
//https://leetcode.com/problems/diagonal-traverse-ii/discuss/597741/Clean-Simple-Easiest-Explanation-with-a-picture-and-code-with-comments
//Runtime: 504 ms, faster than 86.78% of C++ online submissions for Diagonal Traverse II.
//Memory Usage: 94.3 MB, less than 100.00% of C++ online submissions for Diagonal Traverse II.
class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        unordered_map<int, vector<int>> bucket;
        int maxKey = INT_MIN;
        int count = 0;
        
        for(int i = 0; i < nums.size(); i++){
            for(int j = 0; j < nums[i].size(); j++){
                bucket[i+j].push_back(nums[i][j]);
                maxKey = max(maxKey, i+j);
                count++;
            }
        }
        
        vector<int> ans(count);
        int idx = 0;
        
        for(int i = 0; i <= maxKey; i++){
            for(int j = bucket[i].size()-1; j >= 0; j--){
                ans[idx++] = bucket[i][j];
            }
        }
        
        return ans;
    }
};
