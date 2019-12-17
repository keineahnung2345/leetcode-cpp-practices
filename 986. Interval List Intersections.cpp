//Runtime: 52 ms, faster than 77.74% of C++ online submissions for Interval List Intersections.
//Memory Usage: 15.7 MB, less than 100.00% of C++ online submissions for Interval List Intersections.

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        int i = 0, j = 0;
        vector<vector<int>> intersection;
        
        while(i < A.size() && j < B.size()){
            // cout << i << " " << j << endl;
            vector<int> &block1 = A[i], &block2 = B[j];
            if(block1[0] <= block2[0] && block1[1] >= block2[1]){
                //block1 contains block2
                intersection.push_back(block2);
            }else if(block1[0] >= block2[0] && block1[1] <= block2[1]){
                //block2 contains block1
                intersection.push_back(block1);
            }else if(min(block1[1] - block2[0], block2[1] - block1[0]) >= 0){
                //block1 and block2 share one part
                if(block1[1] - block2[0] <= block2[1] - block1[0]){
                    intersection.push_back({block2[0], block1[1]});
                }else{
                    intersection.push_back({block1[0], block2[1]});
                }
            }
            //wrong!
            // if(block1[0] < block2[0]){
            //     i++;
            // }else if(block1[0] > block2[0]){
            //     j++;
            // }else if(block1[1] > block2[1]){
            //     //two blocks' left boundaries are the same
            //     j++;
            // }else{
            //     i++;
            // }
            
            if(block1[1] < block2[1]){
                //move the one whose right boundary is smaller
                i++;
            }else if(block1[1] > block2[1]){
                //move the one whose right boundary is smaller
                j++;
            }else if(block1[0] <= block2[0]){
                //two blocks' right boundaries match
                //, then move the one whose left boundary is smaller
                i++;
            }else{
                //two blocks' right boundaries match
                //, then move the one whose left boundary is smaller
                j++;
            }
        }
        // cout << endl;
        
        return intersection;
    }
};

//https://leetcode.com/problems/interval-list-intersections/solution/
//Runtime: 44 ms, faster than 97.77% of C++ online submissions for Interval List Intersections.
//Memory Usage: 15.8 MB, less than 96.00% of C++ online submissions for Interval List Intersections.
//time complexity: O(M+N), space complexity: O(M+N)

class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        int i = 0, j = 0;
        vector<vector<int>> intersection;
        
        while(i < A.size() && j < B.size()){
            int low = max(A[i][0], B[j][0]);
            int high = min(A[i][1], B[j][1]);
            
            if(low <= high){
                intersection.push_back({low, high});
            }
            
            if(A[i][1] < B[j][1]){
                i++;
            }else{
                j++;
            }
        }
        
        return intersection;
    }
};
