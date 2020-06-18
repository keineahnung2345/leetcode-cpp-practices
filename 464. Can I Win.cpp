//brute force
//https://leetcode.com/problems/can-i-win/discuss/155321/From-Brute-Force-to-Top-down-DP
//TLE
//5 / 54 test cases passed.
class Solution {
public:
    bool canWin(vector<bool>& choosable, int target){
        if(none_of(choosable.begin(), choosable.end(),
            [](const bool b){return b;})){
            return false;
        }
        
        if(target <= 0){
            return false;
        }
        
        int maxChoosable;
        for(int i = choosable.size()-1; i >= 1; i--){
            if(choosable[i]){
                maxChoosable = i;
                break;
            }
        }
        
        if(target <= maxChoosable){
            //we can go to the number >= target
            return true;
        }
        
        //once we can make the next player lose, we win
        for(int i = 1; i < choosable.size(); i++){
            if(choosable[i]){
                bool nextCanWin;
                choosable[i] = false;
                nextCanWin = canWin(choosable, target-i);
                choosable[i] = true;
                if(!nextCanWin) return true;
            }
        }
        //the next player will win anyway
        return false;
    }
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= maxChoosableInteger){
            return true;
        }
        
        if((1+maxChoosableInteger)*maxChoosableInteger/2 < desiredTotal){
            return false;
        }
        
        //0 for padding
        vector<bool> choosable(maxChoosableInteger+1, true);
        return canWin(choosable, desiredTotal);
    }
};

//top-down DP
//https://leetcode.com/problems/can-i-win/discuss/155321/From-Brute-Force-to-Top-down-DP
//Runtime: 872 ms, faster than 5.08% of C++ online submissions for Can I Win.
//Memory Usage: 71.4 MB, less than 12.41% of C++ online submissions for Can I Win.
class Solution {
public:
    unordered_map<string, bool> memo;
    
    bool canWin(vector<bool>& choosable, int target){
        if(none_of(choosable.begin(), choosable.end(),
            [](const bool b){return b;})){
            return false;
        }
        
        if(target <= 0){
            return false;
        }
        
        int maxChoosable;
        //choosable[0] is just for padding, so we end at 1!
        for(int i = choosable.size()-1; i >= 1; i--){
            if(choosable[i]){
                maxChoosable = i;
                break;
            }
        }
        
        if(target <= maxChoosable){
            //we can go to the number >= target
            return true;
        }
        
        /*
        don't need to track "target", 
        since target can be calculated from "desiredTotal" and 
        current "choosable"!
        */
        string key = string(choosable.begin(), choosable.end());
        
        if(memo.find(key) != memo.end()){
            return memo[key];
        }
        
        //once we can make the next player lose, we win
        //choosable[0] is just for padding, so we start from 1!
        for(int i = 1; i < choosable.size(); i++){
            if(choosable[i]){
                bool nextCanWin;
                choosable[i] = false;
                nextCanWin = canWin(choosable, target-i);
                choosable[i] = true;
                if(!nextCanWin) return memo[key] = true;
            }
        }
        //the next player will win anyway
        return memo[key] = false;
    }
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= maxChoosableInteger){
            return true;
        }
        
        if((1+maxChoosableInteger)*maxChoosableInteger/2 < desiredTotal){
            return false;
        }
        
        //0 for padding
        vector<bool> choosable(maxChoosableInteger+1, true);
        return canWin(choosable, desiredTotal);
    }
};

//top-bottom dp, use vector<int> 
//https://leetcode.com/problems/can-i-win/discuss/95320/Clean-C%2B%2B-beat-98.4-DFS-with-early-termination-check-(detailed-explanation)
//Runtime: 48 ms, faster than 63.89% of C++ online submissions for Can I Win.
//Memory Usage: 149.1 MB, less than 7.81% of C++ online submissions for Can I Win.
class Solution {
public:
    vector<int> memo;
    // int memo[1<<20];
    
    int canWin(int maxChoosableInteger, int state, int target){
        /*
        state: can be thought as bits s.t. 
        ith bit represents integer i+1 is chosen or not
        */
        // cout << state << endl;
        if(memo[state] != 0){
            return memo[state] == 1;
        }
        
        if(target <= 0){
            return false;
        }
        
        //once we can make the next player lose, we win
        /*
        i's range is [0, maxChoosableInteger-1], 
        but it represents for the numbers to be chosen: [1, maxChoosableInteger]
        */
        for(int i = 0; i < maxChoosableInteger; i++){
            /*
            state&(1<<i): ith bit of state, represents for i+1 is chosen or not
            state|(1<<i): saying that ith bit is already chosen
            */
            if(!(state&(1<<i)) && !canWin(maxChoosableInteger, state|(1<<i), target-(i+1))){
                memo[state] = 1;
                return true;
            }
        }
        //the next player will win anyway
        memo[state] = -1;
        return false;
    }
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= maxChoosableInteger){
            return true;
        }
        
        int sum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        
        /*
        can't make up desiredTotal using [1, maxChoosableInteger],
        so neither can win
        */
        if(sum < desiredTotal){
            return false;
        }else if(sum == desiredTotal){
            /*
            we will reach desiredTotal at last step,
            so the player who choose the last integer will win,
            i.e. when maxChoosableInteger is odd, 1st player will win
            */
            return maxChoosableInteger % 2;
        }
        
        memo = vector<int>(1<<20, 0);
        return canWin(maxChoosableInteger, 0, desiredTotal);
    }
};

//top-bottom dp, use int array
//Runtime: 16 ms, faster than 90.35% of C++ online submissions for Can I Win.
//Memory Usage: 10.5 MB, less than 93.88% of C++ online submissions for Can I Win.
class Solution {
public:
    // vector<int> memo;
    int memo[1<<20];
    
    int canWin(int maxChoosableInteger, int state, int target){
        /*
        state: can be thought as bits s.t. 
        ith bit represents integer i+1 is chosen or not
        */
        // cout << state << endl;
        if(memo[state] != 0){
            return memo[state] == 1;
        }
        
        if(target <= 0){
            return false;
        }
        
        //once we can make the next player lose, we win
        /*
        i's range is [0, maxChoosableInteger-1], 
        but it represents for the numbers to be chosen: [1, maxChoosableInteger]
        */
        for(int i = 0; i < maxChoosableInteger; i++){
            /*
            state&(1<<i): ith bit of state, represents for i+1 is chosen or not
            state|(1<<i): saying that ith bit is already chosen
            */
            if(!(state&(1<<i)) && !canWin(maxChoosableInteger, state|(1<<i), target-(i+1))){
                memo[state] = 1;
                return true;
            }
        }
        //the next player will win anyway
        memo[state] = -1;
        return false;
    }
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        if(desiredTotal <= maxChoosableInteger){
            return true;
        }
        
        int sum = (1+maxChoosableInteger)*maxChoosableInteger/2;
        
        /*
        can't make up desiredTotal using [1, maxChoosableInteger],
        so neither can win
        */
        if(sum < desiredTotal){
            return false;
        }else if(sum == desiredTotal){
            /*
            we will reach desiredTotal at last step,
            so the player who choose the last integer will win,
            i.e. when maxChoosableInteger is odd, 1st player will win
            */
            return maxChoosableInteger % 2;
        }
        
        // memo = vector<int>(1<<20, 0);
        return canWin(maxChoosableInteger, 0, desiredTotal);
    }
};
