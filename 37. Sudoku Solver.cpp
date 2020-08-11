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
