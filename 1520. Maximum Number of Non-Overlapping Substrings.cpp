//Greedy
//https://leetcode.com/problems/maximum-number-of-non-overlapping-substrings/discuss/743223/C%2B%2BJava-Greedy-O(n)
//Runtime: 156 ms, faster than 98.13% of C++ online submissions for Maximum Number of Non-Overlapping Substrings.
//Memory Usage: 20 MB, less than 100.00% of C++ online submissions for Maximum Number of Non-Overlapping Substrings.
//time: O(N), because the inner loop will be executed at most 26 times, this is ensured by "if(l[s[i]-'a'] == i)"
//space: O(1)
class Solution {
public:
    int checkSubstr(string& s, int i, vector<int>& l, vector<int>& r){
        //check: all other chars in [l[c], r[c]] don't start before i
        //also find the new "right" to include all occurences of those chars
        //this logic will ensure that we find the valid substring with the smallest right edge
        int right = r[s[i]-'a'];
        
        for(int j = i; j <= right; ++j){
            if(l[s[j]-'a'] < i){
                return -1;
            }
            right = max(right, r[s[j]-'a']);
        }
        
        return right;
    };
    
    vector<string> maxNumOfSubstrings(string s) {
        vector<int> l(26, INT_MAX), r(26, INT_MIN);
        int n = s.size();
        
        for(int i = 0; i < n; ++i){
            l[s[i]-'a'] = min(l[s[i]-'a'], i);
            r[s[i]-'a'] = max(r[s[i]-'a'], i);
        }
        
        vector<string> ans;
        int right = INT_MAX;
        for(int i = 0; i < n; ++i){
            if(l[s[i]-'a'] == i){
                /*
                current char is the start of its kind of char, 
                it's candidate valid substring
                */
                
                int newright = checkSubstr(s, i, l, r);
                if(newright != -1){
                    if(i > right || ans.empty()){
                        /*
                        "right" is the right boundary of previous valid substring
                        if "i > right", then current substring doesn't overlap
                        with previous substring,
                        so the previous valid substring doesn't need to be
                        overwritten
                        */
                        ans.push_back("");
                    }
                    right = newright;
                    //overwrite the previous valid substring
                    /*
                    greedy:
                    
                    If we find a valid substring, 
                    and then another valid substring 
                    within the first substring - 
                    we can ignore the larger substring.
                    
                    E.g. if we find "abccba", and then "bccb", 
                    and then "cc", we only care about "cc". 
                    This can be easily proven by a contradition.
                    
                    When two valid substring overlap,
                    one substring must contain another?
                    */
                    ans.back() = s.substr(i, right-i+1);
                }
            }
        }
        
        return ans;
    }
};
