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
