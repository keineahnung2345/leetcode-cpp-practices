//backtracking
//TLE
//4 / 12 test cases passed.
//testcase: 4
class Solution {
public:
    int n;
    vector<int> ans;
    
    void backtrack(vector<int>& perm, vector<bool>& used){
        if(all_of(used.begin(), used.end(), [](const bool& b){return b;})){
            bool valid = true;
            for(int i = 0; i+1 < n; ++i){
                if(__builtin_popcount(perm[i]^perm[i+1]) != 1){
                    valid = false;
                    break;
                }
            }
            if(valid){
                ans = perm;
            }
        }else{
            for(int i = 0; i < n; ++i){
                if(used[i]) continue;
                perm.push_back(i);
                used[i] = true;
                backtrack(perm, used);
                if(!ans.empty()) return;
                perm.pop_back();
                used[i] = false;
            }
        }
    }
    
    vector<int> grayCode(int n) {
        this->n = 1<<n;
        vector<int> perm;
        vector<bool> used(1<<n, false);
        backtrack(perm, used);
        return ans;
    }
};

//speed up from above
//6 / 12 test cases passed.
//testcase: 10
class Solution {
public:
    int n;
    vector<int> ans;
    
    void backtrack(vector<int>& perm, vector<bool>& used){
        if(all_of(used.begin(), used.end(), [](const bool& b){return b;})){
            bool valid = true;
            // for(int i = 0; i+1 < n; ++i){
            //     if(__builtin_popcount(perm[i]^perm[i+1]) != 1){
            //         valid = false;
            //         break;
            //     }
            // }
            if(valid){
                ans = perm;
            }
        }else{
            for(int i = 0; i < n; ++i){
                if(used[i]) continue;
                if(!perm.empty() && 
                   __builtin_popcount(perm.back()^i) != 1) continue;
                perm.push_back(i);
                used[i] = true;
                backtrack(perm, used);
                if(!ans.empty()) return;
                perm.pop_back();
                used[i] = false;
            }
        }
    }
    
    vector<int> grayCode(int n) {
        this->n = 1<<n;
        vector<int> perm;
        vector<bool> used(1<<n, false);
        backtrack(perm, used);
        return ans;
    }
};

//backtracking, faster
//https://leetcode.com/problems/gray-code/discuss/400651/Java-Solutions-with-Detailed-Comments-and-Explanations-(Backtracking-Prepending)
//Runtime: 4 ms, faster than 25.43% of C++ online submissions for Gray Code.
//Memory Usage: 7.8 MB, less than 6.92% of C++ online submissions for Gray Code.
class Solution {
public:
    int p2n, n;
    vector<int> ans;
    
    bool diffByOneBit(int a, int b){
        int x = a^b;
        
        //x==0 <-> a==b
        //x&(x-1): remove x's last bit
        //((x&(x-1)) == 0): x has only one digit
        
        return (x!=0) && ((x&(x-1)) == 0);
    }
    
    void backtrack(vector<int>& res, vector<bool>& used){
        if(res.size() == p2n){
            if(diffByOneBit(res[0], res.back())){
                ans = res;
            }
        }else{
            const int last = res.back();
            for(int i = 0; i < n; ++i){
                int cur = last ^ (1<<i);
                if(used[cur]) continue;
                res.push_back(cur);
                used[cur] = true;
                backtrack(res, used);
                if(!ans.empty()) return;
                res.pop_back();
                used[cur] = false;
            }
        }
    }
    
    vector<int> grayCode(int n) {
        if(n == 0) return {0};
        this->n = n;
        this->p2n = (1<<n);
        
        vector<int> res;
        vector<bool> used(this->p2n, false);
        
        res = {0};
        used[0] = true;
        
        backtrack(res, used);
        
        return ans;
    }
};

//iterative
//https://leetcode.com/problems/gray-code/discuss/400651/Java-Solutions-with-Detailed-Comments-and-Explanations-(Backtracking-Prepending)
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Gray Code.
//Memory Usage: 6.7 MB, less than 48.06% of C++ online submissions for Gray Code.
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> res = {0};
        
        for(int i = 0; i < n; ++i){
            /*
            in ith iteration, 
            we change res of size 1<<i to
            res of size 1<<(i+1)
            
            in ith iteration,
            the range of res is [0,1<<(i+1)),
            we already have range [0,1<<i),
            now we need to add range[1<<i,1<<(i+1)),
            and we can create it by 
            adding 1<<i to the old range
            */
            int prependVal = 1 << i;
            int oldSize = res.size();
            //double the size of res
            for(int j = oldSize-1; j >= 0; --j){
                res.push_back(prependVal + res[j]);
            }
            /*
            the numbers in the later half all diff by one bit,
            because they are created from the old res
            
            res[oldSize-1] and res[oldSize] diff by one bit
            (the most significant bit)
            
            res[newSize-1] and res[0] diff by one bit
            (the most significant bit)
            */
        }
        
        return res;
    }
};
