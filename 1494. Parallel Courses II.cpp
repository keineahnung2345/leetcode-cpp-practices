//WA
//29 / 53 test cases passed.
class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        vector<bool> visited(n+1, false);
        set<int> sources;
        vector<vector<int>> edges(n+1);
        set<int>::iterator it;
        
        for(int i = 1; i <= n; ++i){
            sources.insert(i);
        }
        
        for(vector<int> dep : dependencies){
            if((it = sources.find(dep[1])) != sources.end()){
                sources.erase(it);
            }
            edges[dep[0]].push_back(dep[1]);
        }
        
        /*
        cout << "sources: ";
        for(const int& source : sources){
            cout << source << " ";
        }
        cout << endl;
        */
        
        int ans = 0;
        
        set<int> next_sources;
        while(!sources.empty()){
            /*
            cout << "sources: ";
            for(const int& source : sources){
                cout << source << " ";
            }
            cout << endl;
            cout << "add: " << ceil((double)sources.size()/k) << endl;
            */
            ans += ceil((double)sources.size()/k);
            for(int source : sources){
                next_sources.insert(edges[source].begin(), edges[source].end());
            }
            swap(sources, next_sources);
            next_sources.clear();
        }
        
        
        return ans;
    }
};

//dp, bitmask
//https://leetcode.com/problems/parallel-courses-ii/discuss/708263/Can-anyone-explain-the-bit-mask-method
//Runtime: 440 ms, faster than 13.11% of C++ online submissions for Parallel Courses II.
//Memory Usage: 8.3 MB, less than 83.33% of C++ online submissions for Parallel Courses II.
class Solution {
public:
    int minNumberOfSemesters(int n, vector<vector<int>>& dependencies, int k) {
        /*
        prerequisite of n courses
        if course i is dependent on course j,
        then pre[i]'s jth bit will be set
        */
        vector<int> pre(n);
        
        for(vector<int>& dep : dependencies){
            pre[dep[1]-1] |= (1 << (dep[0]-1));
        }
        
        /*
        key: the combination of courses(bit representation)
        value: minimum days to take all the courses
        */
        vector<int> dp(1<<n, n);
        
        //require 0 days to take 0 courses
        dp[0] = 0;
        
        /*
        need to go into the loop even if cur is 0,
        because in there we will update dp[cur|subnext]!
        */
        for(int cur = 0; cur < (1<<n); ++cur){
            /*
            if we have taken all courses specified by "cur",
            we can take the courses specified by "next"
            */
            int next = 0;
            
            for(int j = 0; j < n; ++j){
                /*
                if we have taken all prerequisites of course "j",
                we can then take course "j" now
                */
                if((cur & pre[j]) == pre[j]){
                    /*
                    cur is the superset of pre[j],
                    that means in current state,
                    we have taken all prerequisites of course j
                    */
                    next |= (1<<j);
                }
            }
            
            /*
            now "next" specify the course we are able to taken,
            but we don't need to take the courses that are already taken
            (which are specified by cur)
            so ""&= ~cur" to exclude those courses
            */
            next &= ~cur;
            
            /*
            https://cp-algorithms.com/algebra/all-submasks.html
            enumerate all the bit 1 combinations(submask)?
            */
            for(int subnext = next; subnext; subnext = (subnext-1) & next){
                if(__builtin_popcount(subnext) <= k){
                    //we can take at most k courses in a day
                    dp[cur|subnext] = min(dp[cur|subnext], dp[cur]+1);
                }
            }
        }
        
        return dp.back();
    }
};
