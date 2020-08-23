//Runtime: 488 ms, faster than 50.00% of C++ online submissions for Maximum Number of Coins You Can Get.
//Memory Usage: 53.5 MB, less than 50.00% of C++ online submissions for Maximum Number of Coins You Can Get.
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        int n = piles.size();
        
        sort(piles.rbegin(), piles.rend());
        
        int ans = 0;
        
        for(int time = 0, pos = 1; time < n/3; ++time){
            ans += piles[pos];
            pos += 2;
        }
        
        return ans;
    }
};
