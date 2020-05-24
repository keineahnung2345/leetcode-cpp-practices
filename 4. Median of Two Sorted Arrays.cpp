//binary search
//https://www.youtube.com/watch?v=LPFhl65R7ww&feature=emb_logo
//Runtime: 36 ms, faster than 48.68% of C++ online submissions for Median of Two Sorted Arrays.
//Memory Usage: 89.2 MB, less than 5.16% of C++ online submissions for Median of Two Sorted Arrays.
//time: O(log(min(m,n)), space: O(1)
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

//binary search, revise to inclusive boundary on both sides(uglier)
//Runtime: 40 ms, faster than 43.83% of C++ online submissions for Median of Two Sorted Arrays.
//Memory Usage: 89.3 MB, less than 5.16% of C++ online submissions for Median of Two Sorted Arrays.
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
        int xend = m-1;
        int xmid, ymid;
        
        while(xstart <= xend + 1){
            /*
            used to partition x into 2 parts,
            xmid is the last index of left part in x,
            xmid+1 is the left part's size
            */
            /*
            need to take the minimum!
            [100001]
            [100000]
            */
            xmid = min(xstart, xend) + (xend-xstart)/2;
            /*
            the last index of left part in y,
            ymid+1 is the right part's size,
            so (xmid+1) + (ymid+1) is equal to (m+n+1)/2
            */
            ymid = (m+n+1)/2 - (xmid+2);
            
            // cout << "[" << xstart << ", " << xend << "], " << xmid << ", " << ymid << endl;
            
            int maxLeftX = (xmid >= 0) ? nums1[xmid] : INT_MIN;
            int minRightX = (xmid+1 < m) ? nums1[xmid+1] : INT_MAX;
            
            int maxLeftY = (ymid >= 0) ? nums2[ymid] : INT_MIN;
            int minRightY = (ymid+1 < n) ? nums2[ymid+1] : INT_MAX;
            
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
            
            // cout << xstart << ", " << xend << endl;
        }
        
        return 0.0;
    }
};

//binary search, official solution
//Runtime: 36 ms, faster than 48.68% of C++ online submissions for Median of Two Sorted Arrays.
//Memory Usage: 89.2 MB, less than 5.16% of C++ online submissions for Median of Two Sorted Arrays.
//time: O(log(min(m,n)), space: O(1)
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
        
        int xstart = 0;
        int xend = m;
        
        while(xstart <= xend){
            //xmid ranges from 0 to m
            int xmid = (xstart+xend)/2;
            //if m > n, ymid may be negative!
            int ymid = (m+n+1)/2 - xmid;
            
            if(xmid < m && ymid > 0 && nums2[ymid-1] > nums1[xmid]){
                //xmid is too small
                xstart = xmid+1;
            }else if(xmid > 0 && ymid < n && nums1[xmid-1] > nums2[ymid]){
                //xmid is too large
                xend = xmid-1;
            }else{
                int maxLeft = max(xmid > 0 ? nums1[xmid-1] : INT_MIN, 
                                  ymid > 0 ? nums2[ymid-1] : INT_MIN);
                if((m+n) % 2 == 1) return maxLeft;
                
                int minRight = min(xmid < m ? nums1[xmid] : INT_MAX, 
                                   ymid < n ? nums2[ymid] : INT_MAX);
                
                return (maxLeft+minRight)/2.0;
            }
        }
        
        return 0.0;
    }
};
