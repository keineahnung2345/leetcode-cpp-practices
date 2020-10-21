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

//a trial of using memorization, slower than previous?
//TLE
//44 / 147 test cases passed.
class Solution {
public:
    vector<vector<unordered_map<int, int>>> memo;
    
    int backtrack(vector<int>& scores, vector<int>& ages, vector<int>& players, int pi, int last_chosen, int cur_score){
        if(memo[pi+1][last_chosen+1].find(cur_score) != memo[pi+1][last_chosen+1].end()){
            return memo[pi+1][last_chosen+1][cur_score];
        }else if(pi == players.size()){
            return memo[pi+1][last_chosen+1][cur_score] = cur_score;
        }else{
            int res = 0;
            
            //not choose cur
            res = backtrack(scores, ages, players, pi+1, last_chosen, cur_score);
            
            int p = players[pi];
            
            //don't need to check age!
            if(last_chosen == -1 || 
               !(/*ages[p] > ages[chosen.back()] && */scores[p] < scores[last_chosen])){
                //choose cur
                res = max(res, backtrack(scores, ages, players, pi+1, p, cur_score+scores[p]));
            }
            
            return memo[pi+1][last_chosen+1][cur_score] = res;
        }
    }
    
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        vector<int> players(n);
        iota(players.begin(), players.end(), 0);
        
        sort(players.begin(), players.end(), [&](int& pi1, int& pi2){
            return (ages[pi1] == ages[pi2]) ? scores[pi1] < scores[pi2] : ages[pi1] < ages[pi2];
        });
        
        memo = vector<vector<unordered_map<int, int>>>(n+2, 
            vector<unordered_map<int, int>>(n+2));
        
        return backtrack(scores, ages, players, 0, -1, 0);
    }
};

//1D DP
//each cell means the optimal can be got using the previous i players
//https://leetcode.com/problems/best-team-with-no-conflicts/discuss/899475/Fairly-easy-DP
//Runtime: 232 ms, faster than 51.78% of C++ online submissions for Best Team With No Conflicts.
//Memory Usage: 19.2 MB, less than 5.33% of C++ online submissions for Best Team With No Conflicts.
class Solution {
public:
    int bestTeamScore(vector<int>& scores, vector<int>& ages) {
        int n = scores.size();
        
        vector<int> players(n);
        iota(players.begin(), players.end(), 0);
        
        //sort 
        sort(players.begin(), players.end(), 
            [&](int& p1, int& p2){
                return (ages[p1] == ages[p2]) ? (scores[p1] < scores[p2]) : (ages[p1] < ages[p2]);
            });
        
        vector<int> dp(n);
        //the actual index
        int pi, pj;
        
        //visit the players, the younger the earlier to be visited
        for(int i = 0; i < n; ++i){
            //map to the actual index
            pi = players[i];
            dp[i] = scores[pi];
            
            //visit players younger than pi
            for(int j = 0; j < i; ++j){
                pj = players[j];
                if(scores[pj] <= scores[pi]){
                    //dp[i]: the optimal score can be got formed of players of younger than or equal to pi
                    dp[i] = max(dp[i], dp[j]+scores[pi]);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
};
