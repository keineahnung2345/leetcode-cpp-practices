//backtrack
//TLE
//49 / 147 test cases passed.
class Solution {
public:
    int n;
    int ans;
    
    bool check(vector<int>& scores, vector<int>& ages, vector<int>& chosen, int cur){
        for(const int& p : chosen){
            if(ages[cur] < ages[p] && scores[cur] > scores[p])
                return false;
            if(ages[cur] > ages[p] && scores[cur] < scores[p])
                return false;
        }
        
        return true;
    }
    
    void backtrack(vector<int>& scores, vector<int>& ages, vector<int>& chosen, int cur, int score){
        if(cur == n){
            ans = max(ans, score);
        }else{
            //not choose cur
            backtrack(scores, ages, chosen, cur+1, score);
            
            //choose cur
            if(check(scores, ages, chosen, cur)){
                chosen.push_back(cur);
                backtrack(scores, ages, chosen, cur+1, score+scores[cur]);
                chosen.pop_back();
            }
        }
    }
    
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        n = scores.size();
        
        vector<int> chosen;
        backtrack(scores, ages, chosen, 0, 0);
        
        return ans;
    }
};
