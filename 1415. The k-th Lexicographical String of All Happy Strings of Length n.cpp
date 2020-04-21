//Runtime: 92 ms, faster than 43.96% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
//Memory Usage: 24.6 MB, less than 100.00% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
class Solution {
public:
    int n;
    
    void backtrack(vector<vector<char>>& pers, vector<char>& per, vector<char>& chars){
        if(per.size() == n){
            pers.push_back(per);
        }else{
            for(char c : chars){
                if(per.size() > 0 && per[per.size()-1] == c){
                    continue;
                }
                per.push_back(c);
                backtrack(pers, per, chars);
                per.pop_back();
            }
        }
    };
    
    string getHappyString(int n, int k) {
        int count = 3 * (1 << (n-1));
        if(k > count) return "";
        
        this->n = n;
        
        vector<vector<char>> pers;
        vector<char> per;
        vector<char> chars = {'a', 'b', 'c'};
        
        backtrack(pers, per, chars);
        
        // for(vector<char> p : pers){
        //     for(char c : p){
        //         cout << c;
        //     }
        //     cout << endl;
        // }
        // cout << endl;
        
        string ans = "";
        for(char c : pers[k-1]){
            ans += c;
        }
        
        return ans;
    }
};

//Math
//https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/discuss/585590/C%2B%2B-DFS-and-Math
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
//Memory Usage: 5.8 MB, less than 100.00% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
//time: O(N), space: O(1)
class Solution {
public:
    string getHappyString(int n, int k) {
        //there are total 3*pow(2, n-1) happy strings
        int prem = 1 << (n-1);
        if(k > 3 * prem) return "";
        
        //k falls in (1) [1, prem] -> 'a' (2) [prem+1, prem*2] -> 'b' (3) [prem*2+1, prem*3] -> 'c'
        //(k-1)/prem: which interval(0,1 or 2) current char is in
        string ans(1, 'a' + (k-1)/prem);
        
        // cout << k << " " << prem << " " << (char)('a'+(k-1)/prem) << endl;
        
        // while(prem > 1){
        while(--n > 0){
            //we have consumed one position
            /*
            (k-1)/prem: which interval current char is in
            prem: each interval's length
            previous intervals have taken "(k - 1) / prem * prem" spaces,
            so we need to remove them
            
            for 1st iteration, possible intervals are (0,1,2) (we can choose from a, b or c)
            for later iteration, possible intervals are (0,1) (we can only choose two character different from last character)
            */
            k -= (k - 1) / prem * prem;
            prem >>= 1;
            /*
            n = 3
            ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]
            
            for interval 0, choose from a or b
            for interval 1, choose from b or c
            */
            // cout << k << " " << prem << " " << (k-1)/prem << endl;
            ans += (k - 1) / prem == 0 ? 'a' + (ans.back() == 'a') : 'b' + (ans.back() != 'c');
        }
        
        return ans;
    }
};

//DFS
//https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/discuss/585590/C%2B%2B-DFS-and-Math
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
//Memory Usage: 5.9 MB, less than 100.00% of C++ online submissions for The k-th Lexicographical String of All Happy Strings of Length n.
//time: O(N*k), space: O(N)
class Solution {
public:
    string getHappyString(int n, int& k, int l = 0, char last = '\0') {
        //l: the length of building string
        //last: last character in the building string
        //note that k is passed by reference
        if(l == n){
            //we have built a happy string
            k--;
        }else{
            for(char cur = 'a'; cur <= 'c'; cur++){
                if(cur == last) continue;
                string res = getHappyString(n, k, l+1, cur);
                if(k == 0){
                    return string(1, cur) + res;
                }
            }
        }
        return "";
    }
};
