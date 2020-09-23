//BFS
//TLE
//127 / 142 test cases passed.
class Solution {
public:
    void backtrack(vector<int>& nums, int& p, int start, long long& cursum, int rem, int& minrem){
        if(cursum % p == 0){
            minrem = min(minrem, rem);
        }else{
            int n = nums.size();
            for(int i = start; i < n; ++i){
                cursum -= nums[i];
                backtrack(nums, p, i+1, cursum, rem+1, minrem);
                cursum += nums[i];
            }
        }
    };
    
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        
        long long total = accumulate(nums.begin(), nums.end(), 0LL);
        
        if(total % p == 0){
            return 0;
        }
        
        queue<pair<int, long long>> q;
        
        for(int i = 0; i < n; ++i){
            q.push({i, nums[i]});
        }
        
        int remlen = 1;
        
        while(!q.empty()){
            int qsize = q.size();
            
            while(qsize-- > 0){
                pair<int, long long> pr = q.front(); q.pop();
                int start = pr.first;
                long long currem = pr.second;
                
                if((total - currem) % p == 0){
                    return (remlen == n) ? -1 : remlen;
                }
                
                if(start+remlen < n){
                    q.push({start, currem+nums[start+remlen]});
                }
            }
            
            ++remlen;
        }
        
        return -1;
    }
};

//hashmap
//Runtime: 372 ms, faster than 76.44% of C++ online submissions for Make Sum Divisible by P.
//Memory Usage: 67 MB, less than 66.04% of C++ online submissions for Make Sum Divisible by P.
//time: O(N), space: O(N)
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        
        int k = accumulate(nums.begin(), nums.end(), 0LL) % p;
        
        // cout << "need: " << k << endl;
        
        if(k == 0) return 0;
        
        //need to use unordered_map, if using vector, it will give TLE!!
        unordered_map<int, int> lastidx;
        /*
        cannot set ans as "INT_MAX",
        because we should not allow the case s.t.
        we need to remove the whole array to make the sum%p=k,
        in this case, ans will be n(remove whole array)
        */
        int ans = n;
        int runsum = 0;
        
        // lastidx[0] = -1;
        for(int i = 0; i < n; ++i){
            runsum = (runsum+nums[i])%p;
            if(lastidx.count((runsum-k+p)%p)){
                /*
                nums[lastidx[?]+1...i] % p = k
                (runsum-?) % p = k
                ? = (runsum-k+p) % p
                */
                ans = min(ans, i - lastidx[(runsum-k+p)%p]);
            }
            /*
            runsum don't need to subtract anything to become k%p
            */
            if(runsum == k){
                ans = min(ans, i+1);
            }
            lastidx[runsum] = i;
            // cout << "lastidx[" << runsum << "] = " << i << endl;
        }
        
        return (ans == n) ? -1 : ans;
    }
};

//revise from above, merge the case of sum from beginning into lastidx[0] = -1;
//Runtime: 368 ms, faster than 82.78% of C++ online submissions for Make Sum Divisible by P.
//Memory Usage: 66.8 MB, less than 91.49% of C++ online submissions for Make Sum Divisible by P.
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        
        int k = accumulate(nums.begin(), nums.end(), 0LL) % p;
        
        if(k == 0) return 0;
        
        unordered_map<int, int> lastidx;
        int ans = n;
        int runsum = 0;
        
        lastidx[0] = -1;
        for(int i = 0; i < n; ++i){
            runsum = (runsum+nums[i])%p;
            if(lastidx.count((runsum-k+p)%p)){
                ans = min(ans, i - lastidx[(runsum-k+p)%p]);
            }
            lastidx[runsum] = i;
        }
        
        return (ans == n) ? -1 : ans;
    }
};
