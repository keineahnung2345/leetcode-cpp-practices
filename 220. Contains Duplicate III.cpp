//Brute force
//TLE
//40 / 41 test cases passed.
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int n = nums.size();
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(n-1, i+k); ++j){
                if(abs((long long)nums[i]-nums[j]) <= t){
                    return true;
                }
            }
        }
        
        return false;
    }
};

//Bucket
//https://leetcode.com/problems/contains-duplicate-iii/discuss/61645/AC-O(N)-solution-in-Java-using-buckets-with-explanation
//Runtime: 28 ms, faster than 79.23% of C++ online submissions for Contains Duplicate III.
//Memory Usage: 11.4 MB, less than 36.26% of C++ online submissions for Contains Duplicate III.
//time: O(N), space: O(N)
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        //abs(i-j) = k < 1: not reasonable
        //abs(nums[i]-nums[j]) = t < 0: not reasonable
        if(k < 1 || t < 0) return false;
        
        unordered_map<long long, long long> buckets;
        int n = nums.size();
        
        for(int i = 0; i < n; ++i){
            //since nums[i] could be negative, so we add INT_MIN to make it starts from 0
            long long remappedNum = (long long)nums[i] - INT_MIN;
            long long bucket = remappedNum / ((long long)t+1);
            
            //find a number in [num-t,num+t] in the range [i-k,i+k]
            if(buckets.find(bucket) != buckets.end() || //duplicate key: valid j found!
               buckets.find(bucket-1) != buckets.end() && //find in previous bucket
               remappedNum - buckets[bucket-1] <= t ||
               buckets.find(bucket+1) != buckets.end() && //find in next bucket
               buckets[bucket+1] - remappedNum <= t
              ){
                return true;
            }
            
            if(buckets.size() >= k){
                long long lastRemappedNum = (long long)nums[i-k] - INT_MIN;
                long long lastBucket = lastRemappedNum / ((long long)t+1);
                /*
                buckets[lastBucket] must only contains nums[i-k],
                if not, that means we already found a valid j,
                at that situation, we are already returned
                */
                buckets.erase(lastBucket);
            }
            
            //currently buckets[bucket] is empty
            buckets[bucket] = remappedNum;
        }
        
        return false;
    }
};

//Tree set
//https://leetcode.com/problems/contains-duplicate-iii/discuss/61655/Java-O(N-lg-K)-solution
//time: O(NlogK), N: #insertion/deletion, K: size of the tree set
//space: O(K)
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        set<long long> vals;
        int n = nums.size();
        
        for(int i = 0; i < n; ++i){
            //smallest element >= nums[i]-t
            set<long long>::iterator floor = vals.lower_bound((long long)nums[i]-t);
            if(floor != vals.end() && *floor <= nums[i]) return true; 
            
            //smallest element > nums[i]+t
            set<long long>::iterator ceil = vals.upper_bound((long long)nums[i]+t);
            if(ceil != vals.begin()){
                //largest element <= nums[i]+t
                ceil = prev(ceil);
                if(*ceil >= nums[i]) return true;
            }
            
            vals.insert(nums[i]);
            if(i >= k) vals.erase(nums[i-k]);
        }
        
        return false;
    }
};
