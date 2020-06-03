//Runtime: 204 ms, faster than 82.11% of C++ online submissions for Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts.
//Memory Usage: 32.3 MB, less than 100.00% of C++ online submissions for Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts.
class Solution {
public:
    long long moduloMultiplication(long long a, 
                            long long b, 
                            long long mod) 
    { 
        long long res = 0; // Initialize result 

        // Update a if it is more than 
        // or equal to mod 
        a %= mod; 

        while (b) 
        { 
            // If b is odd, add a with result 
            if (b & 1) 
                res = (res + a) % mod; 

            // Here we assume that doing 2*a 
            // doesn't cause overflow 
            a = (2 * a) % mod; 

            b >>= 1; // b = b / 2 
        } 

        return res; 
    } 

    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        int maxh = INT_MIN, maxw = INT_MIN;
        
        for(int i = 0; i < horizontalCuts.size(); i++){
            maxh = max(maxh, horizontalCuts[i] - ((i > 0) ? horizontalCuts[i-1] : 0));
        }
        maxh = max(maxh, h - horizontalCuts[horizontalCuts.size()-1]);
        
        for(int i = 0; i < verticalCuts.size(); i++){
            maxw = max(maxw, verticalCuts[i] - ((i > 0) ? verticalCuts[i-1] : 0));
        }
        maxw = max(maxw, w - verticalCuts[verticalCuts.size()-1]);
        
        return moduloMultiplication(maxh, maxw, 1e9+7);
    }
};
