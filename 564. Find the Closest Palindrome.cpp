//Runtime: 4 ms, faster than 59.37% of C++ online submissions for Find the Closest Palindrome.
//Memory Usage: 6.3 MB, less than 54.60% of C++ online submissions for Find the Closest Palindrome.
class Solution {
public:
    string n;
    
    string choose(string& s1, string& s2){
        if(abs(stoll(s1)-stoll(n)) == abs(stoll(s2)-stoll(n))){
            return (stoll(s1) < stoll(s2)) ? s1 : s2;
        }else{
            return (abs(stoll(s1)-stoll(n)) < abs(stoll(s2)-stoll(n))) ? s1 : s2;
        }
    };
    
    string nearestPalindromic(string n) {
        this->n = n;
        int sz = n.size();
        
        if(sz == 1){
            if(n == "0"){
                return "-1";
            }else{
                n[0] -= 1;
                return n;
            }
        }
        
        string ans = n;
        for(int i = 0; i < sz >> 1; ++i){
            ans[sz-1-i] = n[i];
        }
        
        if(ans > n){
            // cout << "ans larger" << endl;
            if(sz & 1){
                string s1 = ans;
                if(s1[sz>>1] > '0') s1[sz>>1] -= 1;
                ans = choose(s1, ans);
                
                s1 = string(sz-1, '9');
                // cout << s1 << " v.s. " << ans << endl;
                ans = choose(s1, ans);
            }else{
                // cout << "length even" << endl;
                string s1 = ans;
                if(s1[sz>>1] > '0') s1[(sz>>1)-1] = s1[sz>>1] = ans[sz>>1] - 1;
                // cout << s1 << " v.s. " << ans << endl;
                ans = choose(s1, ans);
                
                s1 = string(sz-1, '9');
                // cout << s1 << " v.s. " << ans << endl;
                ans = choose(s1, ans);
            }
        }else{
            if(sz & 1){
                string s1 = ans;
                if(s1[sz>>1] < '9') s1[sz>>1] += 1;
                ans = choose(s1, ans);
            }else{
                string s1 = ans;
                if(s1[sz>>1] < '9') s1[(sz>>1)-1] = s1[sz>>1] = ans[sz>>1] + 1;
                ans = choose(s1, ans);
            }
        }
        
        if(ans == n){
            //n is already a palindrome
            if(sz & 1){
                // cout << "sz odd" << endl;
                if(n[sz>>1] == '0'){
                    // cout << "middle 0" << endl;
                    string s1 = n;
                    s1[sz>>1] = n[sz>>1] + 1;

                    string s2 = n;
                    s2[sz>>1] = '9';
                    int shift = 1;
                    while((sz>>1)-shift >= 0 && s2[(sz>>1)-shift] == '0'){
                        s2[(sz>>1)-shift] = s2[(sz>>1)+shift] = '9';
                        ++shift;
                    }
                    
                    if((sz>>1)-shift >= 0){
                        if((sz>>1)-shift == 0 && s2[0] == '1'){
                            s2 = string(sz-1, '9');
                        }else{
                            s2[(sz>>1)-shift] = s2[(sz>>1)+shift] = n[(sz>>1)+shift]-1;
                        }
                        // cout << s1 << " v.s. " << s2 << endl;
                        ans = choose(s1, s2);
                    }else{
                        ans = "-1";
                    }
                }else if(n[sz>>1] == '9'){
                    // cout << "middle 9" << endl;
                    string s1 = n;
                    s1[sz>>1] = n[sz>>1] - 1;

                    string s2 = n;
                    s2[sz>>1] = '0';
                    int mid = sz>>1;
                    int shift = 1;
                    while((sz>>1)-shift >= 0 && s2[(sz>>1)-shift] == '9'){
                        s2[(sz>>1)-shift] = s2[(sz>>1)+shift] = '0';
                        ++shift;
                    }
                    if((sz>>1)-shift >= 0){
                        s2[(sz>>1)-shift] = s2[(sz>>1)+shift] = n[(sz>>1)+shift]+1;
                        // cout << s1 << " v.s. " << s2 << endl;
                        ans = choose(s1, s2);
                    }else{
                        ans = string(sz+1, '0');
                        ans[0] = ans[ans.size()-1] = '1';
                    }
                }else{
                    string s1 = ans;
                    s1[sz>>1] = n[sz>>1] - 1;
                    
                    string s2 = string(sz-1, '9');
                    // cout << s1 << " v.s. " << s2 << endl;
                    ans = choose(s1, s2);
                }
            }else{
                // cout << "sz even" << endl;
                if(n[sz>>1] == '0'){
                    // cout << "middle 0" << endl;
                    string s1 = n;
                    s1[(sz>>1)-1] = s1[sz>>1] = n[sz>>1] + 1;

                    string s2 = n;
                    s2[(sz>>1)-1] = s2[sz>>1] = '9';
                    int mid = sz>>1;
                    int shift = 1;
                    while((sz>>1)-1-shift >= 0 && s2[(sz>>1)-1-shift] == '0'){
                        s2[(sz>>1)-1-shift] = s2[(sz>>1)+shift] = '9';
                        ++shift;
                    }
                    if((sz>>1)-1-shift >= 0){
                        s2[(sz>>1)-1-shift] = s2[(sz>>1)+shift] = n[(sz>>1)+shift]-1;
                        // cout << s1 << " v.s. " << s2 << endl;
                        ans = choose(s1, s2);
                    }else{
                        ans = "-1";
                    }
                }else if(n[sz>>1] == '9'){
                    // cout << "middle 9" << endl;
                    string s1 = n;
                    s1[(sz>>1)-1] = s1[sz>>1] = n[sz>>1] - 1;

                    string s2 = n;
                    s2[(sz>>1)-1] = s2[sz>>1] = '0';
                    int mid = sz>>1;
                    int shift = 1;
                    while((sz>>1)-1-shift >= 0 && s2[(sz>>1)-1-shift] == '9'){
                        s2[(sz>>1)-1-shift] = s2[(sz>>1)+shift] = '0';
                        ++shift;
                    }
                    if((sz>>1)-1-shift >= 0){
                        s2[(sz>>1)-1-shift] = s2[(sz>>1)+shift] = n[(sz>>1)+shift]+1;
                        // cout << s1 << " v.s. " << s2 << endl;
                        ans = choose(s1, s2);
                    }else{
                        ans = string(sz+1, '0');
                        ans[0] = ans[ans.size()-1] = '1';
                    }
                }else{
                    // cout << "middle not 0" << endl;
                    string s1 = ans;
                    s1[(sz>>1)-1] = s1[sz>>1] = n[sz>>1] - 1;
                    
                    string s2 = string(sz-1, '9');
                    // cout << s1 << " v.s. " << s2 << endl;
                    ans = choose(s1, s2);
                }
            }
        }
        
        return ans;
    }
};

//https://leetcode.com/problems/find-the-closest-palindrome/discuss/102391/Python-Simple-with-Explanation
//Runtime: 8 ms, faster than 16.56% of C++ online submissions for Find the Closest Palindrome.
//Memory Usage: 6.2 MB, less than 71.34% of C++ online submissions for Find the Closest Palindrome.
class Solution {
public:
    string nearestPalindromic(string n) {
        int l = n.size();
        
        unordered_set<string> cands;
        cands.insert("1" + string(l-1, '0') + "1"); //999->1001, one more digit
        if(l-1 > 0) cands.insert(string(l-1, '9')); //1001->999, one less digit
        
        /*
        If the final answer has the same number of digits as the input string S, then the answer must be the middle digits + (-1, 0, or 1) flipped into a palindrome.
        0:  12345 -> 12321
        -1: 99100 -> 99099
        +1: 10299 -> 10300
        */
        string former = n.substr(0, l&1 ? (l>>1)+1 : l>>1);
        // cout << former << endl;
        vector<string> formers = {to_string(stoll(former)-1), 
                                  former, 
                                  to_string(stoll(former)+1)};
        
        for(string& f : formers){
            string later = f.substr(0, l&1 ? f.size()-1 : f.size());
            reverse(later.begin(), later.end());
            // cout << "insert " << f+later << endl;
            cands.insert(f + later);
        }
        
        cands.erase(n);
        
        // cout << "cands: ";
        // for(const string& cand : cands){
        //     cout << cand << "#";
        // }
        // cout << endl;
        
        return *min_element(cands.begin(), cands.end(),
            [&n](const string& c1, const string& c2){
                return (abs(stoll(n) - stoll(c1)) == abs(stoll(n) - stoll(c2))) ? 
                    stoll(c1) < stoll(c2) :
                    (abs(stoll(n) - stoll(c1)) < abs(stoll(n) - stoll(c2)));
            });
    }
};
