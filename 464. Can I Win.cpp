//TLE
//5 / 54 test cases passed.
class Solution {
public:
    bool canWin(vector<bool>& choosable, int target){
        if(std::all_of(choosable.begin(), choosable.end(), [](const bool& b){return b == false;})){
            return false;
        }
        
        auto it = std::find_if(choosable.rbegin(), choosable.rend(), 
                    [](const bool b){return b == true;});
        int maxChoosable = distance(it, choosable.rend()-1)+1;
        
        if(target <= maxChoosable){
            //we can go to the number >= target
            return true;
        }else{
            //once we can make the next player lose, we win
            for(int i = 0; i < choosable.size(); i++){
                if(choosable[i]){
                    bool nextCanWin;
                    choosable[i] = false;
                    nextCanWin = canWin(choosable, target-(i+1));
                    choosable[i] = true;
                    if(!nextCanWin) return true;
                }
            }
            //the next player will win anyway
            return false;
        }
    }
    
    bool canIWin(int maxChoosableInteger, int desiredTotal) {
        vector<bool> choosable(maxChoosableInteger, true);
        return canWin(choosable, desiredTotal);
    }
};
