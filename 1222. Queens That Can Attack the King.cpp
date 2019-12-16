//Runtime: 4 ms, faster than 91.87% of C++ online submissions for Queens That Can Attack the King.
//Memory Usage: 9.8 MB, less than 100.00% of C++ online submissions for Queens That Can Attack the King.

class Solution {
public:
    vector<vector<int>> queens;
    vector<vector<int>> ans;
    
    bool inQueens(vector<int>& cur){
        bool found = false;
        if(find(queens.begin(), queens.end(), cur) != queens.end()){
            ans.push_back(cur);
            found = true;
        }
        return found;
    }
    
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<int> cur;
        this->queens = queens;
        
        for(int i = king[0]; i >= 0; i--){
            cur = {i, king[1]};
            if(inQueens(cur)) break;
        }
        
        for(int i = king[0]; i < 8; i++){
            cur = {i, king[1]};
            if(inQueens(cur)) break;
        }
        
        for(int j = king[1]; j >= 0; j--){
            cur = {king[0], j};
            if(inQueens(cur)) break;
        }
        
        for(int j = king[1]; j < 8; j++){
            cur = {king[0], j};
            if(inQueens(cur)) break;
        }
        
        for(int i = king[0], j = king[1]; i >= 0 && j >= 0; i--, j--){
            cur = {i, j};
            if(inQueens(cur)) break;
        }
        
        for(int i = king[0], j = king[1]; i < 8 && j < 8; i++, j++){
            cur = {i, j};
            if(inQueens(cur)) break;
        }
        
        for(int i = king[0], j = king[1]; i < 8 && j >= 0; i++, j--){
            cur = {i, j};
            if(inQueens(cur)) break;
        }
        
        for(int i = king[0], j = king[1]; i >= 0 && j < 8; i--, j++){
            cur = {i, j};
            if(inQueens(cur)) break;
        }
        
        return ans;
    }
};
