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
//TLE
//128 / 142 test cases passed.
class Solution {
public:
    int minSubarray(vector<int>& nums, int p) {
        int n = nums.size();
        
        int k = accumulate(nums.begin(), nums.end(), 0LL) % p;
        
        if(k == 0) return 0;
        
        vector<int> lastidx(p, -1);
        int ans = INT_MAX;
        int runsum = 0;
        
        for(int i = 0; i < n; ++i){
            /*
            nums[0...i]: psum[i]
            nums[0...lastidx]: psum[i]-k
            (psum[i] - psum[lastidx]) % p == k
            -> (psum[i]-k)%p = psum[lastidx]
            */
            runsum = (runsum+nums[i])%p;
            if(lastidx[(runsum-k+p)%p] >= 0){
                ans = min(ans, i - lastidx[(runsum-k+p)%p]);
            }
            if(lastidx[k] >= 0){
                ans = min(ans, lastidx[k]+1);
            }
            lastidx[runsum%p] = i;
            // cout << "lastidx[" << psum[i]%p << "] = " << i << endl;
        }
        
        return (ans == INT_MAX) ? -1 : ans;
    }
};
