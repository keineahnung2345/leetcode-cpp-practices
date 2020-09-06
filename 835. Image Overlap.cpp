//Brute force
//Runtime: 116 ms, faster than 53.82% of C++ online submissions for Image Overlap.
//Memory Usage: 9.3 MB, less than 57.43% of C++ online submissions for Image Overlap.
class Solution {
public:
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        int n = A.size();
        int max_overlap = 0;
        
        for(int rshift = -(n-1); rshift <= n-1; ++rshift){
            for(int cshift = -(n-1); cshift <= n-1; ++cshift){
                //only shift A
                int overlap = 0;
                for(int r = max(0, -rshift); r < min(n, n-rshift); ++r){
                    for(int c = max(0, -cshift); c < min(n, n-cshift); ++c){
                        overlap += A[r+rshift][c+cshift] * B[r][c];
                    }
                }
                max_overlap = max(max_overlap, overlap);
            }
        }
        
        return max_overlap;
    }
};
