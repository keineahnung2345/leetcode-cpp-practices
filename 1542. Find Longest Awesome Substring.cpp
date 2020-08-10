//Bitmask
//https://leetcode.com/problems/find-longest-awesome-substring/discuss/779893/C%2B%2BJavaPython3-with-picture-(similar-to-1371)
//time: O(Nk), k: #unique chars
//space: O(2^k)
class Solution {
public:
    int longestAwesome(string s) {
        int n = s.size();
        int mask = 0;
        int ans = 0;
        //dp[mask]: the smallest index with that state(mask)
        //n: a large, out-of-range number
        vector<int> dp(1024, n);

        /*
        for a index i in which the mask is 0,
        s[-1+1...i] is s[0...i],
        that means s[0...i]'s all digits all have even counts
        */
        dp[0] = -1;

        for(int i = 0; i < n; ++i){
            /*
            mask is a bitmask of length 10,
            the ith bit corresponds to the digit i,
            if the digit i's count is even,
            then mask's ith bit will be 0,
            o.w. it will be 1
            */
            mask ^= (1 << (s[i]-'0'));

            /*
            the exactly same state(mask) occurs at
            dp[mask], which is j,
            so s[j+1...i]'s digits all have even counts
            */
            ans = max(ans, i - dp[mask]);
            /*
            differ by one digit,
            suppose dp[mask^(1<<d)] is j,
            that means s[j+1...i]'s digits all have even counts,
            except one(the digit d)
            */
            for(int d = 0; d <= 9; ++d){
                ans = max(ans, i - dp[mask^(1<<d)]);
            }

            //the first index with that state(mask)
            if(dp[mask] == n) dp[mask] = i;
        }

        return ans;
    }
};
