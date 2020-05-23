//binary search
//https://www.youtube.com/watch?v=LPFhl65R7ww&feature=emb_logo
//Runtime: 36 ms, faster than 48.68% of C++ online submissions for Median of Two Sorted Arrays.
//Memory Usage: 89.2 MB, less than 5.16% of C++ online submissions for Median of Two Sorted Arrays.
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        //need to ensure that nums1 is shorter than or equal to nums2
        if(m > n){
            swap(nums1, nums2);
            swap(m, n);
        }
        
        // cout << nums1.size() << ", " << nums2.size() << ", " << m << ", " << n << endl;
        
        int xstart = 0;
        int xend = m;
        int xmid, ymid;
        
        while(xstart <= xend){
            /*
            used to partition x into 2 parts,
            xmid is the first index of right part in x,
            also can be seen as left part's size
            */
            xmid = (xstart+xend)/2;
            /*
            the first index of right part in y,
            also can be seen as left part's size
            */
            ymid = (m+n+1)/2 - xmid;
            
            // cout << "[" << xstart << ", " << xend << "], " << xmid << ", " << ymid << endl;
            
            int maxLeftX = (xmid > 0) ? nums1[xmid-1] : INT_MIN;
            int minRightX = (xmid < m) ? nums1[xmid] : INT_MAX;
            
            int maxLeftY = (ymid > 0) ? nums2[ymid-1] : INT_MIN;
            int minRightY = (ymid < n) ? nums2[ymid] : INT_MAX;
            
            // cout << maxLeftX << ", " << minRightX << ", " << maxLeftY << ", " << minRightY << endl;
            
            if((maxLeftX <= minRightY) && (maxLeftY <= minRightX)){
                if((m+n) % 2 == 1){
                    return max(maxLeftX, maxLeftY);
                }else{
                    return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
                }
            }
            
            if(maxLeftX > minRightY){
                //x's left part is too large, so move left
                xend = xmid-1;
            }else if(maxLeftX < minRightY){
                //x's left part is too small, move right
                xstart = xmid+1;
            }
        }
        
        return 0.0;
    }
};
