//DP
//TLE
//58 / 182 test cases passed.
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        //padding ahead
        vector<int> count(amount+1, INT_MAX);
        
        //base case
        for(int coin : coins){
            //to ensure it won't exceed the array's size
            if(coin <= amount) count[coin] = 1;
        }
        
        // for(int i = 1; i <= amount; i++){
        //     cout << i << ", " << count[i] << " | ";
        // }
        // cout << endl;
        
        for(int i = 1; i <= amount; i++){
            for(int j = 1; j <= i/2; j++){
                if(count[j] == INT_MAX || count[i-j] == INT_MAX){
                    //skip this split
                    continue;
                }else{
                    count[i] = min(count[i], count[j] + count[i-j]);
                }
            }
            // cout << i << ", " << count[i] << endl;
        }
        // cout << "===========" << endl;
        
        return count[amount] == INT_MAX ? -1 : count[amount];
    }
};

//DP
//Runtime: 124 ms, faster than 29.29% of C++ online submissions for Coin Change.
//Memory Usage: 14.1 MB, less than 27.45% of C++ online submissions for Coin Change.
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        if(amount == 0) return 0;
        //padding ahead
        vector<int> count(amount+1, INT_MAX);
        
        //base case
        for(int coin : coins){
            //to ensure it won't exceed the array's size
            if(coin <= amount) count[coin] = 1;
        }
        
        // for(int i = 1; i <= amount; i++){
        //     cout << i << ", " << count[i] << " | ";
        // }
        // cout << endl;
        
        for(int i = 1; i <= amount; i++){
            for(int coin : coins){
                if(i < coin) continue;
                if(count[i-coin] == INT_MAX) continue;
                count[i] = min(count[i], count[i-coin]+1);
            }
            // cout << i << ", " << count[i] << endl;
        }
        // cout << "===========" << endl;
        
        return count[amount] == INT_MAX ? -1 : count[amount];
    }
};

//recursion
//Runtime: 1128 ms, faster than 5.02% of C++ online submissions for Coin Change.
//Memory Usage: 66.5 MB, less than 5.88% of C++ online submissions for Coin Change.
class Solution {
public:
    unordered_map<int, int> memo;
    
    int coinChange(vector<int>& coins, int amount) {
        if(memo.find(amount) != memo.end()) return memo[amount];
        
        if(amount == 0){
            memo[amount] = 0;
            return memo[0];
        }
        
        if(coins.size() > 0 && amount < *min_element(coins.begin(), coins.end())){
            memo[amount] = -1;
            return memo[amount];
        }
        
        int count = INT_MAX;
        for(int coin : coins){
            if(amount == coin){
                memo[amount] = 1;
                return memo[amount];
            }
            int remainCount = coinChange(coins, amount-coin);
            if(remainCount == -1) continue;
            // cout << coin << " + " << amount - coin << " : " << 1 + remainCount << endl;
            count = min(count, 1 + remainCount);
        }
        
        if(count == INT_MAX) count = -1;
        
        memo[amount] = count;
        
        return memo[amount];
    }
};
