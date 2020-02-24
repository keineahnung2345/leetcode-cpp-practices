//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Find Positive Integer Solution for a Given Equation.
//Memory Usage: 8.6 MB, less than 100.00% of C++ online submissions for Find Positive Integer Solution for a Given Equation.

/*
 * // This is the custom function interface.
 * // You should not implement it, or speculate about its implementation
 * class CustomFunction {
 * public:
 *     // Returns f(x, y) for any given positive integers x and y.
 *     // Note that f(x, y) is increasing with respect to both x and y.
 *     // i.e. f(x, y) < f(x + 1, y), f(x, y) < f(x, y + 1)
 *     int f(int x, int y);
 * };
 */

class Solution {
public:
    vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        vector<vector<int>> ans;
        
        int x = 1, y;
        
        for(y = 1; customfunction.f(x, y) <= z; y++){
            // cout << x << " " << y << " " << customfunction.f(x, y) << endl;
            if(customfunction.f(x, y) == z){
                ans.push_back({x, y});
                break;
            }
        }
        
        //customfunction.f(x, 1) <= z: break if smallest y will make f(x,y) > z
        for(x = 2; customfunction.f(x, y) >= z && customfunction.f(x, 1) <= z; x++){
            for(; customfunction.f(x, y) >= z && y > 0; y--){
                // cout << x << " " << y << " " << customfunction.f(x, y) << endl;
                if(customfunction.f(x, y) == z){
                    ans.push_back({x, y});
                    break;
                }
            }
            y++;
        }
        
        return ans;
    }
};
