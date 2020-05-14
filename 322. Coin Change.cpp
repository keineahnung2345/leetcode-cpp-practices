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
