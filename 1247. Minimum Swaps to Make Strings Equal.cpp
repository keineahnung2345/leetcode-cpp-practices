//Runtime: 4 ms, faster than 53.72% of C++ online submissions for Minimum Swaps to Make Strings Equal.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for Minimum Swaps to Make Strings Equal.

class Solution {
public:
    int minimumSwap(string s1, string s2) {
        int N = s1.size();
        int i = N-1;
        while(i >= 0){
            if(s1[i] == s2[i]){
                s1.erase(i,1);
                s2.erase(i,1);
            }
            i--;
        }
        
        int xcount = count(s1.begin(), s1.end(), 'x');
        int ycount = count(s1.begin(), s1.end(), 'y');
        int ans = 0;
        
        //("xx", "yy") => 1 swap
        ans += xcount/2 + ycount/2;
        xcount %= 2; ycount %= 2;
        
        //("xy", "yx") => 2 swaps
        if(xcount == 1 && ycount == 1){
            ans += 2;
            xcount--; ycount--;
        }
        
        return (xcount == 0 && ycount == 0) ? ans : -1;
    }
};
