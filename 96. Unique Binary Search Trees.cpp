//https://ithelp.ithome.com.tw/articles/10216235
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Unique Binary Search Trees.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Unique Binary Search Trees.
class Solution {
public:
    int numTrees(int n) {
        vector<int> T(n+1, 0);
        
        T[0] = T[1] = 1;
        
        for(int r = 2; r <= n; r++){
            for(int mid = 1; mid <= r; mid++){
                /*
                if the tree is rooted at mid,
                the left and right subtree would be:
                [1...mid-1] and [mid+1...r]
                since the right subtree's max size is r-1,
                so mid starts from 1,
                and since the left subtree's max size is r-1,
                so mid ends at r
                */
                T[r] += T[mid-1] * T[r-mid];
            }
            // cout << T[r] << " ";
        }
        // cout << endl;
        
        return T[n];
    }
};
