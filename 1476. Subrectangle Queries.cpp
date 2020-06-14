//Runtime: 104 ms, faster than 100.00% of C++ online submissions for Subrectangle Queries.
//Memory Usage: 18.7 MB, less than 66.67% of C++ online submissions for Subrectangle Queries.
class SubrectangleQueries {
public:
    vector<vector<int>> rect;
    
    SubrectangleQueries(vector<vector<int>>& rectangle) {
        this->rect = rectangle;
    }
    
    void updateSubrectangle(int row1, int col1, int row2, int col2, int newValue) {
        for(int r = row1; r <= row2; r++){
            for(int c = col1; c <= col2; c++){
                rect[r][c] = newValue;
            }
        }
    }
    
    int getValue(int row, int col) {
        return rect[row][col];
    }
};

/**
 * Your SubrectangleQueries object will be instantiated and called as such:
 * SubrectangleQueries* obj = new SubrectangleQueries(rectangle);
 * obj->updateSubrectangle(row1,col1,row2,col2,newValue);
 * int param_2 = obj->getValue(row,col);
 */
 
