//Runtime: 28 ms, faster than 50.39% of C++ online submissions for Kth Smallest Number in Multiplication Table.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for Kth Smallest Number in Multiplication Table.
class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        int lo = 1, hi = m*n;
        int mid;
        
        while(lo <= hi){
            mid = lo + (hi-lo)/2;
            
            //get the count of numbers <= mid
            int count = 0;
            for(int i = 1; i <= m; i++){
                count += min(n, mid/i);
            }
            
            // cout << lo << ", " << mid << ", " << hi << ": " << count << endl;
            
            if(k > count){
                lo = mid+1;
            }else if(k <= count){
                hi = mid-1;
            }
        }
        
        return lo;
    }
};
