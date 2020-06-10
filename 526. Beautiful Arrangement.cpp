//backtrack
//Runtime: 536 ms, faster than 19.94% of C++ online submissions for Beautiful Arrangement.
//Memory Usage: 6 MB, less than 71.95% of C++ online submissions for Beautiful Arrangement.
class Solution {
public:
    int N;
    
    void backtrack(int& count, vector<int>& perm, vector<bool>& used){
        if(perm.size() == N){
            count++;
        }else{
            for(int i = 0; i < N; i++){
                //i+1: the value to be inserted
                //perm.size()+1: the value's index in perm(1-based)
                if(!used[i] && ((i+1) % (perm.size()+1) == 0 || (perm.size()+1) % (i+1) == 0)){
                    used[i] = true;
                    perm.push_back(i);
                    backtrack(count, perm, used);
                    used[i] = false;
                    perm.pop_back();
                }
            }
        }
    }
    
    int countArrangement(int N) {
        this->N = N;
        int count = 0;
        vector<int> perm;
        vector<bool> used(N, false);
        backtrack(count, perm, used);

        return count;
    }
};
