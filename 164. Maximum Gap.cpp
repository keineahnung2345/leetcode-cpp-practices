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

//Approach 2: Radix Sort(official)
//Radix sort uses Counting sort as a subroutine.
//Runtime: 16 ms, faster than 48.38% of C++ online submissions for Maximum Gap.
//Memory Usage: 9.1 MB, less than 10.99% of C++ online submissions for Maximum Gap.
// radix sort: time: O(d*(n+radix)), space: O(n)
// counting sort: time: O(n + radix), space: O(radix)
class Solution {
public:
    void radixSort(vector<int>& nums){
        int exp = 1;
        int radix = 10;
        
        int maxVal = *max_element(nums.begin(), nums.end());
        
        vector<int> tmp(nums.size());
        
        while(maxVal/exp > 0){
            // counting sort to sort current digit
            vector<int> counter(radix, 0);
            
            for(const int& num : nums){
                //say exp = pow(radix, p), then (num/exp)%radix is pth digit
                ++counter[(num/exp)%radix];
            }
            
            vector<int> counter_acc(counter.size());
            /*
            this is just like:
            for(int i = 1; i < radix; ++i){
                counter[i] += counter[i-1];
            }
            */
            partial_sum(counter.begin(), counter.end(), counter_acc.begin());
            
            //fill from begin: so the sorting is stable
            for(auto it = nums.rbegin(); it != nums.rend(); ++it){
                tmp[--counter_acc[(*it/exp)%radix]] = *it;
            }
            
            swap(nums, tmp);
            
            exp *= 10;
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

//Approach 3: Buckets and The Pigeonhole Principle
//Runtime: 12 ms, faster than 84.36% of C++ online submissions for Maximum Gap.
//Memory Usage: 9.2 MB, less than 10.95% of C++ online submissions for Maximum Gap.
//time: O(n + b) = O(n)
//space: O(b*2) = O(b)
struct Bucket{
    bool used;
    int maxv, minv;
    
    Bucket(): used(false), minv(INT_MAX), maxv(INT_MIN) {};
};

class Solution {
public:
    int maximumGap(vector<int>& nums) {
        int n = nums.size();
        
        if(n <= 1) return 0;
        
        int maxn = *max_element(nums.begin(), nums.end());
        int minn = *min_element(nums.begin(), nums.end());
        
        /*
        we can get min possible gap by assuming
        the n elements are uniformly distributed in [minn, maxn]
        
        e.g. [1,4,7,10]: max gap = 3,
        if the array is not uniformly distrubted,
        e.g. [1,3,7,10]: the max gap will become 4
        */
        double min_possible_gap = (double)(maxn - minn)/(n-1);
        
        /*
        the gap in a bucket will be bucket_size-1,
        by setting bucket size be <= min_possible_gap,
        we know that the gap in any bucket will < min_possible_gap,
        so we only need to find max gap at two buckets's boundary,
        not need to find within buckets
        */
        //bucket_size should be at least 1
        int bucket_size = max(1, (int)floor(min_possible_gap));
        
        int bucket_count = ceil((double)(1LL + maxn - minn)/bucket_size);
        
        vector<Bucket> buckets(bucket_count);
        
        for(int& num : nums){
            int bucket_id = (num-minn)/bucket_size;
            buckets[bucket_id].used = true;
            buckets[bucket_id].minv = min(buckets[bucket_id].minv, num);
            buckets[bucket_id].maxv = max(buckets[bucket_id].maxv, num);
        }
        
        int max_gap = 0;
        int last_maxv = buckets[0].minv;
        for(Bucket& bucket : buckets){
            //ignore empty bucket
            if(!bucket.used) continue;
            max_gap = max(max_gap, bucket.minv - last_maxv);
            last_maxv = bucket.maxv;
        }
        
        // cout << max_gap << endl;
        
        return max_gap;
    }
};
