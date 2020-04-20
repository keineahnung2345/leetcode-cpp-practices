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
