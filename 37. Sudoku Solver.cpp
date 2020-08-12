//backtracking
//TLE
struct pair_hash {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Solution {
public:
    bool ansFound;
    vector<vector<char>> ans;
    unordered_set<char> allchar = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    
    int coord2gridIdx(int i, int j){
        /*
        grid 0: i: [0-2], j:[0-2]
        grid 1: i: [0-2], j:[3-5]
        grid 2: i: [0-2], j:[6-8]
        */
        
        return i/3 * 3 + j/3;
    };
    
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<unordered_set<char>> rows(9), cols(9), grids(9);
        pair<unordered_set<char>::iterator, bool> ret;
        
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                char c = board[i][j];
                if(c == '.') continue;
                int gridIdx = coord2gridIdx(i, j);
                ret = rows[i].insert(c);
                if(!ret.second) return false;
                ret = cols[j].insert(c);
                if(!ret.second) return false;
                ret = grids[gridIdx].insert(c);
                if(!ret.second) return false;
            }
        }
        
        return true;
    };
    
    void backtrack(vector<vector<char>>& board, 
                   unordered_set<pair<int, int>, pair_hash>& tovisit,
                   vector<unordered_set<char>>& rows, 
                   vector<unordered_set<char>>& cols, 
                   vector<unordered_set<char>>& grids){
        // cout << "tovisit: " << tovisit.size() << endl;
        if(tovisit.empty()){
                for(int i = 0; i < 9; ++i){
                    for(int j = 0; j < 9; ++j){
                        cout << board[i][j] << " ";
                    }
                    cout << endl;
                }
            if(isValidSudoku(board)){
                ansFound = true;
                return;
            }
        }else{
            for(auto it = tovisit.begin(); it != tovisit.end(); ++it){
                int i = it->first, j = it->second;
                
                // cout << "visit (" << i << ", " << j << "): " << tovisit.size() << endl;
                // cout << "(" << i << ", " << j << ")" << endl;
                
                unordered_set<char> union2, union3 = rows[i];
                copy(cols[j].begin(), cols[j].end(), 
                     inserter(union3, union3.end()));
                
                int gridIdx = coord2gridIdx(i,j);
                copy(grids[gridIdx].begin(), grids[gridIdx].end(), 
                     inserter(union3, union3.end()));
                
                unordered_set<char> choosable;
                copy_if(allchar.begin(), allchar.end(), 
                     inserter(choosable, choosable.begin()),
                    [&union3] (int needle) { return union3.find(needle) == union3.end(); });
                
                // cout << "rows[i]: " << rows[i].size() << endl;
                // for(const auto e : rows[i]){
                //     cout << e << " ";
                // }
                // cout << endl;
                // cout << "cols[j]: " << cols[j].size() << endl;
                // for(const auto e : cols[j]){
                //     cout << e << " ";
                // }
                // cout << endl;
                // cout << "grids[gridIdx]: " << grids[gridIdx].size() << endl;
                // for(const auto e : grids[gridIdx]){
                //     cout << e << " ";
                // }
                // cout << endl;
                // cout << "union3: " << union3.size() << endl;
                // for(const auto e : union3){
                //     cout << e << " ";
                // }
                // cout << endl;
                // cout << "choosable: " << choosable.size() << endl;
                // for(const auto e : choosable){
                //     cout << e << " ";
                // }
                // cout << endl;

                // cout << "found choosable: " << choosable.size() << endl;
                // cout << "tovisit erased one" << endl;
                for(char d : choosable){
                    rows[i].insert(d);
                    cols[j].insert(d);
                    grids[gridIdx].insert(d);
                    
                    // cout << "sets erased one" << endl;
                    
                    board[i][j] = d;
                    unordered_set<pair<int, int>, pair_hash> newtovisit = tovisit;
                    newtovisit.erase({i, j});
                    backtrack(board, newtovisit, rows, cols, grids);
                    if(ansFound) return;
                    board[i][j] = '.';
                    
                    rows[i].erase(d);
                    cols[j].erase(d);
                    grids[gridIdx].erase(d);
                    // cout << "sets inserted one" << endl;
                }
                // cout << "tovisit inserted one" << endl;
            }
        }
    };
    
    void solveSudoku(vector<vector<char>>& board) {
        ansFound = false;
        vector<unordered_set<char>> rows(9), cols(9), grids(9);
        unordered_set<pair<int, int>, pair_hash> tovisit;
        
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                char d = board[i][j];
                int gridIdx = coord2gridIdx(i, j);
                if(d == '.'){
                    tovisit.insert({i, j});
                }else{
                    rows[i].insert(d);
                    cols[j].insert(d);
                    grids[gridIdx].insert(d);
                }
            }
        }
        
        backtrack(board, tovisit, rows, cols, grids);
    }
};

//backtracking
//https://leetcode.com/problems/sudoku-solver/discuss/15752/Straight-Forward-Java-Solution-Using-Backtracking
//Runtime: 28 ms, faster than 58.89% of C++ online submissions for Sudoku Solver.
//Memory Usage: 6.5 MB, less than 82.12% of C++ online submissions for Sudoku Solver.
class Solution {
public:
    int coord2gridIdx(int i, int j){
        /*
        grid 0: i: [0-2], j:[0-2]
        grid 1: i: [0-2], j:[3-5]
        grid 2: i: [0-2], j:[6-8]
        */
        
        return i/3 * 3 + j/3;
    };
    
    bool isValidSudokuCell(vector<vector<char>>& board, int row, int col, char d) {
        /*
        want to find board[row][col] with d,
        check if it will be valid
        */
        for(int i = 0; i < 9; ++i){
            //check row
            if(board[i][col] == d) return false;
            //check col
            if(board[row][i] == d) return false;
            //check 3*3 block
            if(board[3 *(row/3)+i/3][3*(col/3)+i%3] == d) return false;
        }
        
        return true;
    };
    
    bool helper(vector<vector<char>>& board) {
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(board[i][j] != '.') continue;
                for(char d = '1'; d <= '9'; ++d){
                    if(!isValidSudokuCell(board, i, j, d)) continue;
                    board[i][j] = d;
                    bool res = helper(board);
                    if(res) return true;
                    board[i][j] = '.';
                }
                
                //this cell cannot be filled with '1'-'9'
                return false;
            }
        }
        
        return true;
    };
    
    void solveSudoku(vector<vector<char>>& board) {
        helper(board);
    }
};

//backtracking, improved from above
//https://leetcode.com/problems/sudoku-solver/discuss/15752/Straight-Forward-Java-Solution-Using-Backtracking/15800
//Runtime: 20 ms, faster than 75.81% of C++ online submissions for Sudoku Solver.
//Memory Usage: 6.6 MB, less than 69.50% of C++ online submissions for Sudoku Solver.
class Solution {
public:
    bool isValidSudokuCell(vector<vector<char>>& board, int row, int col, char d) {
        /*
        want to find board[row][col] with d,
        check if it will be valid
        */
        for(int i = 0; i < 9; ++i){
            //check row
            if(board[i][col] == d) return false;
            //check col
            if(board[row][i] == d) return false;
            //check 3*3 block
            if(board[3 *(row/3)+i/3][3*(col/3)+i%3] == d) return false;
        }
        
        return true;
    };
    
    bool helper(vector<vector<char>>& board, int start_row, int start_col) {
        for(int i = start_row; i < 9; ++i, start_col = 0){
            //at "start_row", we starts from "start_col"
            //in later rows, we starts from 0
            for(int j = start_col; j < 9; ++j){
                if(board[i][j] != '.') continue;
                for(char d = '1'; d <= '9'; ++d){
                    if(!isValidSudokuCell(board, i, j, d)) continue;
                    board[i][j] = d;
                    bool res = helper(board, i, j+1);
                    if(res) return true;
                    board[i][j] = '.';
                }
                
                //this cell cannot be filled with '1'-'9'
                return false;
            }
        }
        
        return true;
    };
    
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
};

//reactive-network + backtracking
//https://leetcode.com/problems/sudoku-solver/discuss/15748/Sharing-my-2ms-C%2B%2B-solution-with-comments-and-explanations.
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Sudoku Solver.
//Memory Usage: 6.7 MB, less than 48.20% of C++ online submissions for Sudoku Solver.
struct cell{
    uint8_t val;
    uint8_t numPossibilities;
    //if bitset[i] is 1, then current cell cannot be i
    bitset<10> constraints;
    
    cell(): val(0), numPossibilities(9), constraints() {};
};

class Solution {
public:
    array<array<cell, 9>, 9> cells;
    
    vector<pair<int, int>> emptys;
    
    bool updateConstraints(int i, int j, int excludedVal){
        cell& c = cells[i][j];
        
        //already excluded
        if(c.constraints[excludedVal]) return true;
        //found a conflict
        if(c.val == excludedVal) return false;
        
        c.constraints.set(excludedVal);
        --c.numPossibilities;
        if(c.numPossibilities > 1) return true;
        
        //now c.numPossibilities == 1
        //so cells[i][j] is determined
        for(int v = 1; v <= 9; ++v){
            if(!c.constraints[v]){
                return setCell(i, j, v);
            }
        }
        
        //can never reach here
        // assert(false);
        return false;
    };
    
    bool setCell(int i, int j, int v){
        cell& c = cells[i][j];
        
        //this cell has already been set
        if(c.val == v) return true;
        
        //found a conflict
        if(c.constraints[v]) return false;
        
        //1111111110
        c.constraints = bitset<10>(0x3FE);
        //because the value of current cell is determined
        c.constraints.reset(v);
        c.numPossibilities = 1;
        c.val = v;
        
        for(int k = 0; k < 9; ++k){
            int gi = i/3*3+k/3, gj = j/3*3+k%3;
            if(i != k && !updateConstraints(k, j, v)){
                return false;
            } 
            if(j != k && !updateConstraints(i, k, v)){
                return false;
            }
            if(i != gi && j != gj && !updateConstraints(gi, gj, v)){
                return false;
            }
        }
        
        return true;
    };
    
    bool findValuesForEmptyCells(){
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(cells[i][j].val == 0){
                    emptys.push_back({i, j});
                }
            }
        }
        
        sort(emptys.begin(), emptys.end(), 
             [this](const pair<int, int>& a, const pair<int, int>& b){
                 return cells[a.first][a.second].numPossibilities < cells[b.first][b.second].numPossibilities;
             });
        
        //false for fail
        return backtrack(0);
    };
    
    bool backtrack(int k){
        //all cells set
        if(k >= emptys.size()) return true;
        auto p = emptys[k];
        int i = p.first, j = p.second;

        cell& c = cells[i][j];
        //current cell already set, continue the next
        if(c.val) return backtrack(k+1);

        array<array<cell, 9>, 9> snapshot(cells);

        //try 1-9 for current cell
        for(int v = 1; v <= 9; ++v){
            //cannot fill v into current cell
            if(c.constraints[v]) continue;

            if(setCell(i, j, v)){
                bool res = backtrack(k+1);
                if(res) return res;
            }

            cells = snapshot;
        }
        
        return false;
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(board[i][j] == '.') continue;
                if(!setCell(i, j, board[i][j]-'0')){
                    //there is a conflict
                    return;
                }
            }
        }
        
        if(!findValuesForEmptyCells()){
            //there is a conflict, the sudoku is unsolvable
            return;
        }
        
        for(int i = 0; i < 9; ++i){
            for(int j = 0; j < 9; ++j){
                if(cells[i][j].val){
                    board[i][j] = cells[i][j].val + '0';
                }
            }
        }
    }
};
