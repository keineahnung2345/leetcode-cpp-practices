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
