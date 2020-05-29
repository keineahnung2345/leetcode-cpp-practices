//LIS
//Runtime: 1360 ms, faster than 17.56% of C++ online submissions for Russian Doll Envelopes.
//Memory Usage: 16.5 MB, less than 16.67% of C++ online submissions for Russian Doll Envelopes.
//time: O(N^2), space: O(N)
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 0) return 0;
        
        vector<int> dp(n, 1);
        int ans = 1;

        //the envelopes with smaller width/height are put before
        sort(envelopes.begin(), envelopes.end());
        
        //LIS
        for(int j = 1; j < n; j++){
            for(int i = 0; i < j; i++){
                //stricter condition than ordinal LIS
                if(envelopes[i][0] < envelopes[j][0] && envelopes[i][1] < envelopes[j][1]){
                    dp[j] = max(dp[j], dp[i]+1);
                }
            }
            ans = max(ans, dp[j]);
        }

        return ans;
    }
};

//LIS, binary search
//https://leetcode.com/problems/russian-doll-envelopes/discuss/82763/Java-NLogN-Solution-with-Explanation
//Runtime: 92 ms, faster than 77.75% of C++ online submissions for Russian Doll Envelopes.
//Memory Usage: 16.4 MB, less than 16.67% of C++ online submissions for Russian Doll Envelopes.
//time: O(NlogN), space: O(N)
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        int n = envelopes.size();
        if(n == 0) return 0;
        
        vector<vector<int>> top;

        /*
        since we don't want [3,4] be put into [3,5],
        we won't want [3,4] to be put before [3,5],
        so we sort the sequence ascending by width and "DESCENDING" by height
        */
        sort(envelopes.begin(), envelopes.end(),
            [](const vector<int>& v1, const vector<int>& v2){
                return (v1[0] == v2[0]) ? (v1[1] > v2[1]) : (v1[0] < v2[0]);
            });
        
        // for(vector<int>& p : envelopes){
        //     cout << "(" << p[0] << ", " << p[1] << ") -> ";
        // }
        // cout << endl;
        
        for(vector<int>& p : envelopes){
            int lo = 0, hi = top.size()-1;
            
            /*
            want to find lo s.t. top[lo] is just larger than p
            */
            while(lo <= hi){
                int mid = lo + (hi-lo)/2;
                
                //this is wrong!
                // if(p[0] < top[mid][0] && p[1] < top[mid][1]){
                /*
                we only need to compare their heights,
                since their widths are already sorted
                */
                if(top[mid][1] > p[1]){
                    hi = mid-1;
                }else if(top[mid][1] == p[1]){
                    //since we want to find lower bound
                    hi = mid-1;
                }else if(top[mid][1] < p[1]){
                    lo = mid+1;
                }
            }
            
            if(lo == top.size()){
                top.push_back(p);
                // cout << "push [" << p[0] << ", " << p[1] << "]" << endl;
            }else{
                top[lo] = p;
                // cout << "reset top[" << lo << "] to " << "[" << p[0] << ", " << p[1] << "]" << endl;
            }
        }

        return top.size();
    }
};
