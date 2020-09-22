//Binary indexed tree, Range Updates and Point Queries
//Runtime: 864 ms, faster than 74.80% of C++ online submissions for Maximum Sum Obtained of Any Permutation.
//Memory Usage: 98.3 MB, less than 55.20% of C++ online submissions for Maximum Sum Obtained of Any Permutation.
//https://www.geeksforgeeks.org/binary-indexed-tree-range-updates-point-queries/
//getElement -> getSum: now we the prefix sum of index i BITree[0...i] means arr[i]
//updateBIT -> update: update BITree[l] and BITree[r-1] so range sum of arr[l...r] is updated
class BIT{
public:
    int n;
    vector<int> BITree;
    
    void updateBIT(int index, int val) 
    { 
        // index in BITree[] is 1 more than the index in arr[] 
        index = index + 1; 

        // Traverse all ancestors and add 'val' 
        while (index <= n) 
        { 
            // Add 'val' to current node of BI Tree 
            BITree[index] += val; 

            // Update index to that of parent in update View 
            index += index & (-index); 
        } 
    } 

//     // Constructs and returns a Binary Indexed Tree for given 
//     // array of size n. 
//     void init(vector<int>& arr, int n) 
//     { 
//         // Create and initialize BITree[] as 0 
//         BITree = vector<int>(n+1, 0);

//         // Store the actual values in BITree[] using update() 
//         for (int i=0; i<n; i++) 
//             updateBIT(i, arr[i]);
//     } 
    
    BIT(int n){
        this->n = n;
        BITree = vector<int>(n+1, 0);
    }

    // SERVES THE PURPOSE OF getElement() 
    // Returns sum of arr[0..index]. This function assumes 
    // that the array is preprocessed and partial sums of 
    // array elements are stored in BITree[] 
    int getSum(int index) 
    { 
        int sum = 0; // Iniialize result 

        // index in BITree[] is 1 more than the index in arr[] 
        index = index + 1; 

        // Traverse ancestors of BITree[index] 
        while (index>0) 
        { 
            // Add current element of BITree to sum 
            sum += BITree[index]; 

            // Move index to parent node in getSum View 
            index -= index & (-index); 
        } 
        return sum; 
    } 

    // Updates such that getElement() gets an increased 
    // value when queried from l to r. 
    void update(int l, int r, int val) 
    { 
        // Increase value at 'l' by 'val' 
        updateBIT(l, val); 

        // Decrease value at 'r+1' by 'val' 
        updateBIT(r+1, -val); 
    } 
};

class Solution {
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        
        vector<int> counter(n, 0);
        
        BIT* bit = new BIT(n);
        
        for(vector<int>& req : requests){
            bit->update(req[0], req[1], 1);
        }
        
        for(int i = 0; i < n; ++i){
            counter[i] = bit->getSum(i);
        }
        
        sort(counter.begin(), counter.end());
        sort(nums.begin(), nums.end());
        
        long long ans = 0;
        int MOD = 1e9 + 7;
        
        for(int i = 0; i < n; ++i){
            long long prod = (1LL * nums[i] * counter[i]) % MOD;
            ans = (ans + prod) % MOD;
        }
        
        return ans;
    }
};
