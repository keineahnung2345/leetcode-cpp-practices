//Recursive
//TLE
//21 / 29 test cases passed.
class Solution {
public:
    bool isPalindrome(string s){
        int n = s.size();
        for(int i = 0; i < s.size()/2; i++){
            if(s[i] != s[n-1-i]) return false;
        }
        return true;
    };
    
    int minCut(string s) {
        int ans = 0;
        if(!isPalindrome(s)){
            // cout << s << endl;
            if(s.size() == 2) return 1;
            ans = INT_MAX;
            for(int i = 1; i < s.size(); i++){
                ans = min(ans, minCut(s.substr(0, i)) + minCut(s.substr(i)));
            }
            ans++;
        }
        return ans;
    }
};

//DP
//WA
//28 / 29 test cases passed.
class Solution {
public:
    int minCut(string s) {
        int n = s.size();
        if(n == 0 || n == 1) return 0;
        
        vector<vector<int>> dp(n, vector(n, 0));
        vector<priority_queue<int, vector<int>>> widths(n);
        
        for(int w = 1; w <= n; w++){
            for(int start = 0; start+w-1 < n; start++){
                int end = start+w-1;
                if(w == 1)dp[start][end] = true;
                else if(w == 2)dp[start][end] = (s[start] == s[end]);
                else dp[start][end] = (dp[start+1][end-1] && s[start] == s[end]);
                
                if(dp[start][end]) widths[start].push(w);
            }
        }
        
        // for(int i = 0; i < n; i++){
        //     cout << maxWidths[i] << " ";
        // }
        // cout << endl;
        
        int cursor = 0;
        int ans = 0;
        
        //how many segments
        // WA when "aaabaa"
        // while(cursor < n){
        //     cursor = cursor + maxWidths[cursor];
        //     ans++;
        // }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>> pq;
        for(int i = 0; i < n; i++){
            pq.push(make_pair(widths[i].top(), i));
        }
        
        // queue<vector<int>> segments;
        // vector<int> segment;
        // segments.push({0, n-1});
        int start, end;
        vector<bool> available(n, true);
        
        while(!pq.empty() && any_of(available.begin(), available.end(), [](bool b){return b;})){
            // segment = segments.front();
            // start = segment[0];
            // end = segment[1];
            pair<int, int> p = pq.top(); pq.pop();
            start = p.second;
            end = start+p.first-1;
            
            // cout <<"[" << start << ", " << end << "]: " << s.substr(start, end-start+1) << endl;
            
            bool valid = true;
            for(int i = start; i <= end; i++){
                if(!available[i]){
                    valid = false;
                    break;
                }
            }
            
            if(!valid){
                widths[start].pop();
                if(!widths[start].empty()) pq.push(make_pair(widths[start].top(), start));
                continue;
            }
            
            // cout <<"[" << start << ", " << end << "]: " << s.substr(start, end-start+1) << endl;
            
            for(int i = start; i <= end; i++){
                available[i] = false;
            }
            
            ans++;
        }
        
        //how many cuts
        return ans-1;
    }
};
