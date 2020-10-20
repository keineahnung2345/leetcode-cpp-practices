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

//sort + backtrack
//TLE
//52 / 147 test cases passed.
//how to do memorization? There are at most 1000 players, hard to use bitmask as state!
class Solution {
public:
    int max_score;
    
    void backtrack(vector<int>& scores, vector<int>& ages, vector<int>& players, int pi, vector<int>& chosen){
        if(pi == players.size()){
            int cur_score = 0;
            for(const int& p : chosen){
                // cout << scores[p] << " ";
                cur_score += scores[p];
            }
            // cout << endl;
            max_score = max(max_score, cur_score);
        }else{
            //not choose cur
            backtrack(scores, ages, players, pi+1, chosen);
            
            int p = players[pi];
            /*
            sort scores ascending so 
            the last player in its age's group will have max score,
            here we compare current player's score with last chosen player's score,
            and we know that last chosen player's score is the highest in its age
            */
            //actually we don't need to check age!
            if(chosen.empty() || 
               !(/*ages[p] > ages[chosen.back()] && */ scores[p] < scores[chosen.back()])){
                //choose cur
                chosen.push_back(p);
                backtrack(scores, ages, players, pi+1, chosen);
                chosen.pop_back();
            }
        }
    }
    
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<int> players(n);
        iota(players.begin(), players.end(), 0);
        
        //ascending by age, ascending by score
        sort(players.begin(), players.end(), [&](int& pi1, int& pi2){
            return (ages[pi1] == ages[pi2]) ? scores[pi1] < scores[pi2] : ages[pi1] < ages[pi2];
        });
        
        max_score = 0;
        
        vector<int> chosen;
        backtrack(scores, ages, players, 0, chosen);
        
        return max_score;
    }
};

//simplify backtrack argument: use two int instead of a vector
//TLE
//60 / 147 test cases passed.
class Solution {
public:
    int max_score;
    
    void backtrack(vector<int>& scores, vector<int>& ages, vector<int>& players, int pi, int last_chosen, int cur_score){
        if(pi == players.size()){
            max_score = max(max_score, cur_score);
        }else{
            //not choose cur
            backtrack(scores, ages, players, pi+1, last_chosen, cur_score);
            
            int p = players[pi];
            /*
            sort scores ascending so 
            the last player in its age's group will have max score,
            here we compare current player's score with last chosen player's score,
            and we know that last chosen player's score is the highest in its age
            */
            if(last_chosen == -1 || 
               !(/*ages[p] > ages[chosen.back()] && */scores[p] < scores[last_chosen])){
                //choose cur
                backtrack(scores, ages, players, pi+1, p, cur_score+scores[p]);
            }
        }
    }
    
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<int> players(n);
        iota(players.begin(), players.end(), 0);
        
        //ascending by age, ascending by score
        sort(players.begin(), players.end(), [&](int& pi1, int& pi2){
            return (ages[pi1] == ages[pi2]) ? scores[pi1] < scores[pi2] : ages[pi1] < ages[pi2];
        });
        
        max_score = 0;
        
        backtrack(scores, ages, players, 0, -1, 0);
        
        return max_score;
    }
};
