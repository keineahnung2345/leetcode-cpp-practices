//DFS
//TLE
//51 / 127 test cases passed.
class Solution {
public:
    unordered_map<int, unordered_set<int>> graph;
    
    void dfs(int cur, vector<bool>& visited, int jumps, int& max_jumps){
        max_jumps = max(max_jumps, jumps);
        for(const int& nei : graph[cur]){
            if(!visited[nei]){
                // cout << cur << ": " << jumps << "->" << nei << endl;
                visited[nei] = true;
                dfs(nei, visited, jumps+1, max_jumps);
                visited[nei] = false;
            }
        }
    };
    
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j <= min(i+d, n-1) && arr[i] > arr[j]; ++j){
                graph[i].insert(j);
            }
            for(int j = i-1; j >= max(i-d, 0) && arr[i] > arr[j]; --j){
                graph[i].insert(j);
            }
        }
        
        int max_jumps = 0;
        
        for(int start = 0; start < n; ++start){
            vector<bool> visited(n, false);
            visited[start] = true;
            int jumps = 0;
            dfs(start, visited, 1, jumps);
            max_jumps = max(max_jumps, jumps);
        }
        
        return max_jumps;
    }
};

//top-down dp(dfs + memo)
//https://mp.weixin.qq.com/s/kEQ00_WLqDTG6tbsjQ2Xjw
//Runtime: 76 ms, faster than 57.67% of C++ online submissions for Jump Game V.
//Memory Usage: 15.3 MB, less than 48.01% of C++ online submissions for Jump Game V.
//time: O(Nd), space: O(N)
class Solution {
public:
    int n;
    vector<int> memo;
    
    int dfs(vector<int>& arr, int& d, int i){
        if(memo[i]) return memo[i];
        
        memo[i] = 1;
        for(int k = i-1; k >= max(i-d, 0) && arr[k] < arr[i]; --k){
            memo[i] = max(memo[i], dfs(arr, d, k)+1);
        }
        for(int k = i+1; k <= min(i+d, n-1) && arr[k] < arr[i]; ++k){
            memo[i] = max(memo[i], dfs(arr, d, k)+1);
        }
        
        return memo[i];
    };
    
    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        
        memo = vector<int>(n, 0);
        int ans = 0;
        
        for(int i = 0; i < n; ++i){
            ans = max(ans, dfs(arr, d, i));
        }
        
        return ans;
    }
};


//bottom-up DP
//Hint 1: Use dynamic programming. dp[i] is max jumps you can do starting from index i. Answer is max(dp[i]).
//Hint 2: dp[i] = 1 + max (dp[j]) where j is all indices you can reach from i.
//Runtime: 80 ms, faster than 53.12% of C++ online submissions for Jump Game V.
//Memory Usage: 15.6 MB, less than 31.53% of C++ online submissions for Jump Game V.
//time: O(NlogN + Nd), space: O(N)
class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        vector<pair<int, int>> parr(n);
        
        for(int i = 0; i < n; ++i){
            parr[i] = {i, arr[i]};
        }
        
        sort(parr.begin(), parr.end(), 
            [](const pair<int, int>& p, const pair<int, int>& q){
                return (p.second == q.second) ? p.first < q.first : p.second < q.second;
            });
        
        vector<int> dp(n, INT_MIN);
        int ans = 0;
        
        for(pair<int, int>& p : parr){
            dp[p.first] = 1;
            for(int k = p.first-1; k >= max(p.first-d, 0) && arr[k] < arr[p.first]; --k){
                dp[p.first] = max(dp[p.first], dp[k]+1);
            }
            for(int k = p.first+1; k <= min(p.first+d, n-1) && arr[k] < arr[p.first]; ++k){
                dp[p.first] = max(dp[p.first], dp[k]+1);
            }
            ans = max(ans, dp[p.first]);
            // cout << p.first << ", " << dp[p.first] << ", " << ans << endl;
        }
        
        return ans;
    }
};

//segment tree
//not understand
//https://leetcode.com/problems/jump-game-v/discuss/497004/C%2B%2B-Segment-Tree
//Runtime: 88 ms, faster than 44.60% of C++ online submissions for Jump Game V.
//Memory Usage: 17.5 MB, less than 17.90% of C++ online submissions for Jump Game V.
//time: O(NlogN)
class Solution {
private:
    vector<int> tree;

public:
    int query(int x, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) {
            return 0;
        }
        if (ql <= l && r <= qr) {
            return tree[x];
        }
        int mid = (l + r) / 2;
        return max(query(x * 2, l, mid, ql, qr), query(x * 2 + 1, mid + 1, r, ql, qr));
    }

    void update(int x, int l, int r, int u, int value) {
        if (l > u || r < u) {
            return;
        }
        if (l == r) {
            tree[x] = value;
            return;
        }
        int mid = (l + r) / 2;
        update(x * 2, l, mid, u, value);
        update(x * 2 + 1, mid + 1, r, u, value);
        tree[x] = max(tree[x * 2], tree[x * 2 + 1]);
    }

    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> bound_l(n), bound_r(n);

        stack<int> stk;
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && arr[stk.top()] <= arr[i]) {
                bound_r[stk.top()] = min(i - 1, stk.top() + d);
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            bound_r[stk.top()] = min(n - 1, stk.top() + d);
            stk.pop();
        }

        for (int i = n - 1; i >= 0; --i) {
            while (!stk.empty() && arr[stk.top()] <= arr[i]) {
                bound_l[stk.top()] = max(i + 1, stk.top() - d);
                stk.pop();
            }
            stk.push(i);
        }
        while (!stk.empty()) {
            bound_l[stk.top()] = max(0, stk.top() - d);
            stk.pop();
        }

        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {return arr[i] < arr[j];});

        vector<int> f(n);
        tree.resize(n * 4 + 10);
        for (int id: order) {
            int prev = 0;
            if (bound_l[id] < id) {
                prev = max(prev, query(1, 0, n - 1, bound_l[id], id - 1));
            }
            if (id < bound_r[id]) {
                prev = max(prev, query(1, 0, n - 1, id + 1, bound_r[id]));
            }
            f[id] = prev + 1;
            update(1, 0, n - 1, id, f[id]);
        }

        return *max_element(f.begin(), f.end());
    }
};

//dp, monotonic stack
//not understand
//https://mp.weixin.qq.com/s/kEQ00_WLqDTG6tbsjQ2Xjw
//Runtime: 48 ms, faster than 96.87% of C++ online submissions for Jump Game V.
//Memory Usage: 15.1 MB, less than 77.56% of C++ online submissions for Jump Game V.
//time: O(N), space: O(N)
class Solution {
public:
    void print_stack(stack<int>& stk){
        int* end   = &stk.top() + 1;
        int* begin = end - stk.size();
        vector<int> stack_contents(begin, end);
        for(int& e : stack_contents){
            cout << e << " ";
        }
        cout << endl;
    };
    
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        
        vector<int> dp(n+1, 1);
        //monotonic stack, bottom element is the highest
        stack<int> stk, stk2;
        
        //use to clear "stk"
        arr.push_back(INT_MAX);
        
        for(int i = 0; i <= n; ++i){
            // cout << "i: " << i << endl;
            //while we can jump from i to some previous index
            while(!stk.empty() && arr[stk.top()] < arr[i]){
                //stk.top() is current lowest element in "stk"
                //"stk"'s bottom element is the highest
                int pre_h = arr[stk.top()];
                // cout << "stk: " << endl;
                // print_stack(stk);
                while(!stk.empty() && arr[stk.top()] == pre_h){
                    int j = stk.top(); stk.pop();
                    if(i - j <= d){
                        //the index in "stk" are all visited
                        //jump from i to j
                        dp[i] = max(dp[i], dp[j]+1);
                        // cout << "dp[" << i << "], jump to " << j << ": " << dp[j]+1 << endl;
                    }
                    stk2.push(j);
                }
                // cout << "stk2: " << endl;
                // print_stack(stk2);
                while(!stk2.empty()){
                    int j = stk2.top(); stk2.pop();
                    if(!stk.empty() && j - stk.top() <= d){
                        //j's height is smaller than all element in "stk"
                        //jump from stk.top() to j
                        dp[stk.top()] = max(dp[stk.top()], dp[j]+1);
                        // cout << "dp[" << stk.top() << "], jump to " << j << ": " << dp[j]+1 << endl;
                    }
                }
            }
            stk.push(i);
        }
        
        return *max_element(dp.begin(), dp.begin()+n);
    }
};
