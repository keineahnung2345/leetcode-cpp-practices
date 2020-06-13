//WA
//35 / 41 test cases passed.
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return nums;
        vector<vector<int>> subsets;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < n; i++){
            for(vector<int>& subset : subsets){
                if(nums[i] % subset.back() == 0){
                    subset.push_back(nums[i]);
                }
            }
            subsets.push_back({nums[i]});
        }
        
        // for(vector<int>& subset : subsets){
        //     for(int e : subset){
        //         cout << e << " ";
        //     }
        //     cout << endl;
        // }
        
        sort(subsets.begin(), subsets.end(),
            [](const vector<int>& a, const vector<int>& b){
                return (a.size() == b.size()) ? a[0] < b[0] : a.size() > b.size();
            });
        
        return subsets[0];
    }
};

//LIS
//https://leetcode.com/problems/largest-divisible-subset/discuss/84006/Classic-DP-solution-similar-to-LIS-O(n2)
//Runtime: 36 ms, faster than 94.57% of C++ online submissions for Largest Divisible Subset.
//Memory Usage: 8.5 MB, less than 67.33% of C++ online submissions for Largest Divisible Subset.
//time: O(N^2), space: O(N)
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return nums;
        vector<int> length(n, 1); //length of subset
        vector<int> pre(n, -1); //the index of the previous element in the same subset
        
        //this is important!
        sort(nums.begin(), nums.end());
        //record the largest subset and its last element's index
        int maxLength = 0, maxIndex = -1;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
            // for(int j = i-1; j >= 0; j--){
                if(nums[i] % nums[j] == 0){
                    //can choose to append nums[i] after nums[j]'s subset
                    if(length[j] + 1 > length[i]){
                        /*
                        append nums[i] after nums[j]'s subset: 
                        get subset of length[j] + 1
                        not append nums[i] after nums[j]'s subst:
                        i's subset's length remains length[i]
                        */
                        length[i] = length[j] + 1;
                        pre[i] = j;
                    }
                }
            }
            if(length[i] > maxLength){
                maxLength = length[i];
                maxIndex = i;
            }
        }
        
        //backtracking to get the max subset
        cout << length[maxIndex] << ", " << maxLength << endl;
        vector<int> ans(length[maxIndex]);
        int index = maxIndex;
        
        for(int i = ans.size()-1; i >= 0; i--){
            ans[i] = nums[index];
            index = pre[index];
        }
        
        return ans;
    }
};
