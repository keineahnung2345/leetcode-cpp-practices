//Runtime: 4 ms, faster than 82.75% of C++ online submissions for Minimum Number of Flips to Convert Binary Matrix to Zero Matrix.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Minimum Number of Flips to Convert Binary Matrix to Zero Matrix.

class Solution {
public:
    int m, n;
    
    int matrixSum(vector<vector<int>>& mat){
        int sum = 0;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                sum += mat[i][j];
            }
        }
        return sum;
    }
    
    void flip(vector<vector<int>>& mat, vector<int>& isFlip){
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                // cout << i << " " << j << endl;
                if(isFlip[i * n + j]){
                    mat[i][j] = 1 - mat[i][j];
                    
                    if(i - 1 >= 0){
                        mat[i-1][j] = 1 - mat[i-1][j];
                    }
                    
                    if(j - 1 >= 0){
                        mat[i][j-1] = 1 - mat[i][j-1];
                    }
                    
                    if(i + 1 < m){
                        mat[i+1][j] = 1 - mat[i+1][j];
                    }
                    
                    if(j + 1 < n){
                        mat[i][j+1] = 1 - mat[i][j+1];
                    }
                }
            }
        }
    }
    
    int minFlips(vector<vector<int>>& mat) {
        queue<vector<int>> q;
        m = mat.size(); n = mat[0].size();
        vector<int> isFlip = vector<int>(m * n), tmpIsFlip;
        vector<vector<int>> tmpMat;
        
        if(matrixSum(mat) == 0){
            return 0;
        }
        
        q.push(isFlip);
        
        while(!q.empty()){
            tmpIsFlip = q.front(); q.pop();
            
            // for(int i = 0; i < tmpIsFlip.size(); i++){
            //     cout << tmpIsFlip[i];
            // }
            // cout << endl;
            
            tmpMat = mat;
            flip(tmpMat, tmpIsFlip);
            // for(int i = 0; i < tmpMat.size(); i++){
            //     for(int j = 0; j < n; j++){
            //         cout << tmpMat[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            
            if(matrixSum(tmpMat) == 0){
                return accumulate(tmpIsFlip.begin(), tmpIsFlip.end(), 0);
            }
            
            //push children
            int cursor = 0;
            if(find(tmpIsFlip.rbegin(), tmpIsFlip.rend(), 1) != tmpIsFlip.rend()){
                //-1: for adjustment btw reverse iterator and normal iterator
                //+1: find the element next to the last "1"
                cursor = distance(tmpIsFlip.begin(), find(tmpIsFlip.rbegin(), tmpIsFlip.rend(), 1).base()) - 1 + 1;
            }
            
            for(; cursor < tmpIsFlip.size(); cursor++){
                vector<int> child = tmpIsFlip;
                child[cursor] = 1;
                q.push(child);
            }
            // cout << endl;
        }
        
        return -1;
    }
};
