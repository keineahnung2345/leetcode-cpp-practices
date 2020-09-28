//Approach #1: Binary Search on Logarithms
//Runtime: 312 ms, faster than 30.64% of C++ online submissions for Subarray Product Less Than K.
//Memory Usage: 100.5 MB, less than 6.14% of C++ online submissions for Subarray Product Less Than K.
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if(k == 0) return 0;
        int n = nums.size();
        double logk = log(k);
        
        // cout << "logk: " << logk << endl;
        
        vector<double> psum(n+1, 0);
        
        // cout << psum[0] << " ";
        for(int i = 1; i <= n; ++i){
            //psum[i]: lognums[0...i-1]
            psum[i] = psum[i-1] + log((double)nums[i-1]);
            // cout << psum[i] << " ";
        }
        // cout << endl;
        
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            /*
            binary search for j s.t.
            nums[i...j] < k and is largest,
            i.e. lognums[i...j] < logk and is largest,
            lognums[i...j] = psum[j+1]-psum[i]
            */
            int left = i, right = n-1;
            int mid;
            
            //find right boundary
            while(left <= right){
                mid = (left+right)>>1;
                // cout << left << ", " << mid << ", " << right << endl;
                if(psum[mid+1] - psum[i] >= logk - 1e-9){
                    right = mid-1;
                    //right is always valid
                }else{
                    left = mid+1;
                    //left becomes invalid
                }
            }
            
            // cout << "[" << i << ", " << right << "]" << endl;
            ans += (right - i + 1);
        }
        
        return ans;
    }
};
