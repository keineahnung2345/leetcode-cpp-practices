//straight forward
//https://leetcode.com/problems/strange-printer-ii/discuss/854193/Python-Straight-Forward
//Runtime: 80 ms, faster than 88.34% of C++ online submissions for Strange Printer II.
//Memory Usage: 14.4 MB, less than 78.87% of C++ online submissions for Strange Printer II.
//time: O(CCMN), space: O(4C)
struct bound{
    int up, down, left, right;
    
    bound(){
        up = left = INT_MAX;
        down = right = INT_MIN;
    }
};

class Solution {
public:
    bool isPrintable(vector<vector<int>>& targetGrid) {
        unordered_map<int, bound> color2bound;
        
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        
        unordered_map<int, bool> filled;
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int& c = targetGrid[i][j];
                bound& b = color2bound[c];
                b.left = min(b.left, j);
                b.right = max(b.right, j);
                b.up = min(b.up, i);
                b.down = max(b.down, i);
                filled[c] = false;
            }
        }
        
        int color_count = color2bound.size();
        while(color_count-- > 0){
            //want to erase "color_count" colors
            for(auto it = color2bound.begin(); it != color2bound.end(); ++it){
                //find the color which is fillable
                const int& c = it->first;
                const bound& b = it->second;
                if(filled[c]) continue;
                bool fillable = true;
                for(int i = b.up; i <= b.down; ++i){
                    for(int j = b.left; j <= b.right; ++j){
                        if(targetGrid[i][j] != 0 && targetGrid[i][j] != c){
                            fillable = false;
                            break;
                        }
                    }
                    if(!fillable) break;
                }
                
                if(fillable){
                    // cout << "fill " << c << endl;
                    for(int i = b.up; i <= b.down; ++i)
                        for(int j = b.left; j <= b.right; ++j)
                            targetGrid[i][j] = 0;
                    filled[c] = true;
                    break;
                }
            }
        }
        
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(targetGrid[i][j] != 0){
                    return false;
                }
            }
        }
        
        return true;
    }
};
