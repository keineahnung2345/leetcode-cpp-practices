//Runtime: 72 ms, faster than 19.86% of C++ online submissions for Number of Equivalent Domino Pairs.
//Memory Usage: 21.2 MB, less than 100.00% of C++ online submissions for Number of Equivalent Domino Pairs.
class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        for(vector<int>& domino : dominoes){
            sort(domino.begin(), domino.end());
        }
        sort(dominoes.begin(), dominoes.end());
        
        int group = 0, pair = 0;
        bool first = true;
        vector<int> cur = dominoes[0];
        
        //start from index 1!
        for(int i = 1; i < dominoes.size(); i++){
            if(dominoes[i] == cur){
                group++;
                if(first){
                    group++;
                    first = false;
                }
            }else{
                cur = dominoes[i];
                first = true;
                
                //use a new group, clean old group and update pair
                //C n takes 2
                pair += group*(group-1)/2;
                group = 0;
            }
        }
        pair += group*(group-1)/2;
        
        return pair;
    }
};
