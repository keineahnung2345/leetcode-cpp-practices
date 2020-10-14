//sorting
//Runtime: 8 ms, faster than 98.12% of C++ online submissions for Maximum Gap.
//Memory Usage: 8.9 MB, less than 10.99% of C++ online submissions for Maximum Gap.
//time: O(NlogN)
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        
        sort(nums.begin(), nums.end());
        
        int ans = 0;
        
        for(int i = 1; i < n; ++i){
            ans = max(ans, nums[i] - nums[i-1]);
        }
        
        return ans;
    }
};

//radix sort
//https://openhome.cc/Gossip/AlgorithmGossip/RadixSort.htm
//Runtime: 20 ms, faster than 22.30% of C++ online submissions for Maximum Gap.
//Memory Usage: 12.7 MB, less than 10.99% of C++ online submissions for Maximum Gap.
class Solution {
public:
    void radixSort(vector<int>& nums){
        vector<vector<int>> buckets(10);
        
        int max_digit = 1 + log10(*max_element(nums.begin(), nums.end()));
        
        //least significant digital
        for(int digit = 1; digit <= max_digit; ++digit){
            for(const int& num : nums){
                buckets[num%(int)pow(10, digit)/pow(10, digit-1)].push_back(num);
            }
            
            vector<int> tmp;
            
            for(const vector<int>& bucket : buckets){
                tmp.insert(tmp.end(), bucket.begin(), bucket.end());
            }
            
            nums.swap(tmp);
            buckets = vector<vector<int>>(10);
        }
        
    }
    
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        if(n < 2) return 0;
        
        radixSort(nums);
        
        // for(int num : nums){
        //     cout << num << " ";
        // }
        // cout << endl;
        
        int ans = 0;
        
        for(int i = 1; i < n; ++i){
            ans = max(ans, nums[i] - nums[i-1]);
        }
        
        return ans;
    }
};
