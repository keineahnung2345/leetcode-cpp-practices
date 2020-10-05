//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Special Array With X Elements Greater Than or Equal X.
//Memory Usage: 8.6 MB, less than 16.67% of C++ online submissions for Special Array With X Elements Greater Than or Equal X.
class Solution {
public:
    int specialArray(vector<int>& nums) {
        int n = nums.size();
        
        sort(nums.begin(), nums.end());
        
        int cur = 0;
        for(int x = 0; x <= n; ++x){
            while(cur < n && nums[cur] < x){
                ++cur;
            }
            
            //cur : count of elements < x
            //n-cur: count of elements >= x
            // cout << x << " : " << n-cur << endl;
            if(n-cur == x) return x;
        }
        
        return -1;
    }
};
