//Brute force
//Runtime: 116 ms, faster than 53.82% of C++ online submissions for Image Overlap.
//Memory Usage: 9.3 MB, less than 57.43% of C++ online submissions for Image Overlap.
//time: O(N^4), space: O(1)
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

//Approach 2: Linear Transformation
//Runtime: 212 ms, faster than 26.11% of C++ online submissions for Image Overlap.
//Memory Usage: 12.8 MB, less than 13.66% of C++ online submissions for Image Overlap.
//time: O(N^4), space: O(N^2)
class Solution {
public:
    struct pair_hash_int {
        inline std::size_t operator()(const std::pair<int,int> & v) const {
            return v.first*31+v.second;
        }
    };
    
    void non_zero_cells(vector<vector<int>>& mat,
                       vector<pair<int, int>>& ones){
        int n = mat.size();
        
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(mat[i][j]){
                    ones.push_back({i, j});
                }
            }
        }
    };
    
    int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<pair<int, int>> A_ones;
        vector<pair<int, int>> B_ones;
        
        non_zero_cells(A, A_ones);
        non_zero_cells(B, B_ones);
        
        int maxOverlaps = 0;
        unordered_map<pair<int, int>, int, pair_hash_int> groupCount;
        
        for(pair<int, int>& a : A_ones){
            for(pair<int, int>& b : B_ones){
                pair<int, int> v = {b.first-a.first, b.second-a.second};
                ++groupCount[v];
                maxOverlaps = max(maxOverlaps, groupCount[v]);
            }
        }
        
        return maxOverlaps;
    }
};
