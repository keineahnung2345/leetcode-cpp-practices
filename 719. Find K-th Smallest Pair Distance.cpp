//TLE
//16 / 19 test cases passed.
class Solution {
public:
    priority_queue<int, vector<int>> pq;
    
    int findSmallerDistances(vector<int>& nums, int& target){
        pq = priority_queue<int, vector<int>>(); //clear
        int n = nums.size();
        
        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if(nums[j] - nums[i] <= target){
                    pq.push(nums[j] - nums[i]);
                }
            }
        }
        
        return pq.size();
    };
    
    int smallestDistancePair(vector<int>& nums, int k) {
        int left = 0;
        int right = *max_element(nums.begin(), nums.end()) - *min_element(nums.begin(), nums.end());
        
        sort(nums.begin(), nums.end());
        
        int mid, val;
        
        while(left <= right){
            mid = left + (right - left)/2;
            
            // cout << left << ", " << mid << ", " << right << ": ";
            
            int smallerCount = findSmallerDistances(nums, mid);
            
            // cout << val << endl;
            
            if(smallerCount == k){
                return pq.top();
            }else if(smallerCount < k){
                left = mid+1;
            }else if(smallerCount > k){
                right = mid-1;
                while(pq.size() > k){
                    pq.pop();
                }
                return pq.top();
            }
        }
        
        while(pq.size() > k){
            pq.pop();
        }
        
        return pq.top();
    }
};

//Approach #1: Heap [Time Limit Exceeded]
//TLE
//16 / 19 test cases passed.
//time: push: O(NlogN) + pop: O(klogN) -> O((N+k)logN) 
//space: O(N)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        
        auto comp = [&nums](const vector<int>& a, const vector<int>& b){
            //use > because we want the smaller to be popped earlier
            return nums[a[1]] - nums[a[0]] > nums[b[1]] - nums[b[0]];
            };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        
        int n = nums.size();
        for(int i = 0; i+1 < n; i++){
            pq.push(vector<int>{i, i+1});
            // cout << i << ", " << i+1 << endl;
        }
        
        vector<int> cur;
        k--;
        //pop first k-1 pairs
        while(k-- > 0){
            cur = pq.top(); pq.pop();
            // cout << cur[0] << ", " << cur[1] << endl;
            if(cur[1]+1 < n){
                pq.push({cur[0], cur[1]+1});
            }
        }
        //the kth pair
        cur = pq.top();
        // cout << "final: " << cur[0] << ", " << cur[1] << endl;
        
        return nums[cur[1]] - nums[cur[0]];
    }
};

//not understand
//Approach #2: Binary Search + Prefix Sum [Accepted]
//Runtime: 56 ms, faster than 22.59% of C++ online submissions for Find K-th Smallest Pair Distance.
//Memory Usage: 36.9 MB, less than 8.33% of C++ online submissions for Find K-th Smallest Pair Distance.
//time: sort: O(NlogN) + set "prefix": O(W) + binary search: O(logW * N), W = nums[n-1] - nums[0]
//space: O(W+N)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int width = 2 * nums[n-1];
        
        vector<int> multiplicity(n);
        //multiplicity[i]: before nums[i], there are how many element equal to nums[i]
        // cout << "multiplicity: " << endl;
        for(int i = 1; i < n; i++){
            if(nums[i] == nums[i-1]){
                multiplicity[i] = 1 + multiplicity[i-1];
            }
            // cout << multiplicity[i] << " ";
        }
        // cout << endl;
        
        //prefix[i]: how many numbers in nums <= i
        vector<int> prefix(width);
        // cout << "prefix: " << endl;
        int l = 0;
        for(int i = 0; i < width; i++){
            while(l < n && nums[l] == i) l++;
            prefix[i] = l;
            // cout << prefix[i] << " ";
        }
        // cout << endl;
        
        int left = 0;
        int right = nums[n-1] - nums[0];
        int mid;
        int count;
        
        while(left <= right){
            mid = left + (right-left)/2;
            // cout << "left: " << left << ", mid: " << mid << ", right: " << right << endl;
            //count[i]: the count of j (j>i) s.t. nums[j] - nums[i] <= mid
            count = 0;
            for(int i = 0; i < n; i++){
                //multiplicity[i] = count[i] - multiplicity[i]?
                count += prefix[nums[i]+mid] - prefix[nums[i]] + multiplicity[i];
                // cout << "prefix[" << nums[i]+mid << "]: " << prefix[nums[i]+mid] << ", prefix[" << nums[i] << "]: " << prefix[nums[i]] << ", multiplicity[" << i << "]: " << multiplicity[i] << ", add: " << prefix[nums[i]+mid] - prefix[nums[i]] + multiplicity[i] << ", count: " << count << endl;
            }
            
            if(count >= k) right = mid-1;
            else left = mid+1;
        }
        
        return left;
    }
};

//Approach #3: Binary Search + Sliding Window [Accepted]
//Runtime: 20 ms, faster than 77.27% of C++ online submissions for Find K-th Smallest Pair Distance.
//Memory Usage: 10 MB, less than 8.33% of C++ online submissions for Find K-th Smallest Pair Distance.
//time: sort: O(NlogN) + binary search: O(logW * N), W = nums[n-1] - nums[0]
//space: O(1)
class Solution {
public:
    int smallestDistancePair(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        
        int left = 0;
        int right = nums[n-1] - nums[0];
        int mid;
        int count;
        
        while(left <= right){
            mid = left + (right-left)/2;
            // cout << "left: " << left << ", mid: " << mid << ", right: " << right << endl;
            count = 0;
            int slow = 0;
            for(int fast = 0; fast < n; fast++){
                //notice that "slow" pointer increases monotonically for increasing "fast" pointer!
                while(nums[fast] - nums[slow] > mid) slow++;
                count += (fast-slow);
                // cout << "[" << slow << ", " << fast << "], count: " << count << endl;
            }
            
            if(count >= k) right = mid-1;
            else left = mid+1;
        }
        
        return left;
    }
};
