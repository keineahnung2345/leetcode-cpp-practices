//Binary Search
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> nm = binaryMatrix.dimensions();
        int n = nm[0], m = nm[1];
        int ans = INT_MAX;
        
        //n * m matrix
        for(int i = 0; i < n; i++){
            //binary search on each row
            int l = 0, r = m-1;
            while(l < r){
                int mid = l + (r-l)/2;
                if(binaryMatrix.get(i, mid) == 0){
                    //search right part
                    l = mid+1;
                }else{
                    //search left part
                    //retain the 1 met
                    r = mid;
                }
            }
            //now r is the index of leftmost 1
            if(binaryMatrix.get(i, r) == 1)
                ans = min(ans, r);
        }
        
        return (ans == INT_MAX) ? -1 : ans;
    }
};

//Hint 2, greedy
/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * class BinaryMatrix {
 *   public:
 *     int get(int x, int y);
 *     vector<int> dimensions();
 * };
 */

class Solution {
public:
    int leftMostColumnWithOne(BinaryMatrix &binaryMatrix) {
        vector<int> nm = binaryMatrix.dimensions();
        int n = nm[0], m = nm[1];
        
        int i = 0, j = m-1;
        int ans = INT_MAX;
        
        while(i < n && j >= 0){
            if(binaryMatrix.get(i, j) == 0){
                i++;
            }else{
                ans = min(ans, j);
                j--;
            }
        }
        
        return (ans == INT_MAX) ? -1 : ans;
    }
};
