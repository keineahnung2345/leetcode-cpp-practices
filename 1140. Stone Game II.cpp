//https://leetcode.com/problems/stone-game-ii/discuss/345354/Java-DP-with-memorization-easy-to-understand(with-explanation)
//Runtime: 4 ms, faster than 91.96% of C++ online submissions for Stone Game II.
//Memory Usage: 8.2 MB, less than 100.00% of C++ online submissions for Stone Game II.

class Solution {
public:
    vector<int> sum;
    vector<vector<int>> hash;
    int N;
    
    int helper(vector<int>& piles, int start, int M){
        if(start == N) return 0;
        //the remaining size <= max stones we can take
        if(N-start <= 2*M) return sum[start];
        //this cell has already been filled
        if(hash[start][M] != 0) return hash[start][M];
        
        int opponent = INT_MAX; //the minimum stone your oppenent can take
        for(int i = 1; i <= 2*M; i++){
            opponent = min(opponent, helper(piles, start+i, max(M, i)));
        }
        hash[start][M] = sum[start] - opponent;
        return hash[start][M];
    }
    
    int stoneGameII(vector<int>& piles) {
        N = piles.size();
        if(N == 0) return 0;
        
        sum = piles;
        for(int i = N-2; i >= 0; i--){
            sum[i] = sum[i+1] + piles[i];
        }
        
        hash = vector<vector<int>>(N, vector<int>(N, 0));
        return helper(piles, 0, 1);
    }
};
