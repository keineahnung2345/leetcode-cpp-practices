//TLE
//31 / 69 test cases passed.
//https://leetcode.com/problems/allocate-mailboxes/discuss/685620/JavaC%2B%2BPython-Top-down-DP-Prove-median-mailbox-O(n3)
class Solution {
public:
    /*
    1 <= houses.length <= 100
    1 <= houses[i] <= 10^4
    1 <= k <= houses.length
    
    one mailbox's cost: at most 100*1e4
    k mailboxes' cost: at most 100*100*1e4
    */
    int MAX = 1e8;
    
    int dfs(vector<int>& houses, int k, int start){
        if(k == 0 && start == houses.size()) return 0;
        if(k == 0 || start == houses.size()) return MAX;
        
        int ans = MAX;
        
        for(int end = start; end < houses.size(); end++){
            /*
            put one mailbox in [start, end] and 
            remaining k-1 mailboxes in [end+1, n-1]
            */
            int median = houses[(start+end)/2];
            int cost = 0;
            for(int i = start; i <= end; i++){
                cost += abs(houses[i] - median);
            }
            ans = min(ans, cost + dfs(houses, k-1, end+1));
        }
        
        return ans;
    };
    
    int minDistance(vector<int>& houses, int k) {
        //this is important because we need to calculate median!
        sort(houses.begin(), houses.end());
        return dfs(houses, k, 0);
    }
};
