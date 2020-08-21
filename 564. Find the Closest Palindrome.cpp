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
