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

//cycle detection
//https://leetcode.com/problems/strange-printer-ii/discuss/854151/C%2B%2B-O(n3)-solution-checking-cycle-in-dependency-graph
//https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
//Runtime: 452 ms, faster than 24.32% of C++ online submissions for Strange Printer II.
//Memory Usage: 22.8 MB, less than 40.22% of C++ online submissions for Strange Printer II.
class Solution {
public:
    bool hasCycle(int cur, vector<unordered_set<int>>& graph, 
        vector<bool>& visited, vector<bool>& recStack){
        if(!visited[cur]){
            visited[cur] = true;
            recStack[cur] = true;

            for(const int& nei : graph[cur]){
                if(recStack[nei]) return true;
                if(!visited[nei] && hasCycle(nei, graph, visited, recStack))
                    return true;
            }
        }
        
        recStack[cur] = false;
        
        return false;
    }
    
    bool isPrintable(vector<vector<int>>& targetGrid) {
        //valid range: [1,60]
        vector<unordered_set<int>> color2dep(61);
        int m = targetGrid.size();
        int n = targetGrid[0].size();
        
        for(int c = 1; c <= 60; ++c){
            int left = INT_MAX, up = INT_MAX;
            int right = INT_MIN, down = INT_MIN;
            
            for(int i = 0; i < m; ++i){
                for(int j = 0; j < n; ++j){
                    if(targetGrid[i][j] == c){
                        left = min(left, j);
                        right = max(right, j);
                        up = min(up, i);
                        down = max(down, i);
                    }
                }
            }
            
            for(int i = up; i <= down; ++i){
                for(int j = left; j <= right; ++j){
                    if(targetGrid[i][j] != c){
                        color2dep[c].insert(targetGrid[i][j]);
                        // cout << c << " depends on " << targetGrid[i][j] << endl;
                    }
                }
            }
        }
        
        vector<bool> visited(61, false);
        vector<bool> recStack(61, false);
        for(int c = 1; c <= 60; ++c){
            // cout << "color " << c << endl;
            if(!color2dep[c].empty() && 
               !visited[c] && hasCycle(c, color2dep, visited, recStack)){
                return false;
            }
        }
        
        return true;
    }
};
