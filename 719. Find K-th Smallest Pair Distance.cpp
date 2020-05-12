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
