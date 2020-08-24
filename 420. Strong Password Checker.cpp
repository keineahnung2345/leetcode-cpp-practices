//https://leetcode.com/problems/strong-password-checker/discuss/91008/Simple-Python-solution
//Runtime: 4 ms, faster than 28.21% of C++ online submissions for Strong Password Checker.
//Memory Usage: 6.1 MB, less than 58.62% of C++ online submissions for Strong Password Checker.
class Solution {
public:
    int strongPasswordChecker(string s) {
        int n = s.size();
        
        int missing_type = 3;
        
        if(any_of(s.begin(), s.end(), [](char& a){return a >= 'a' && a <= 'z';})){
            --missing_type;
        }
        if(any_of(s.begin(), s.end(), [](char& a){return a >= 'A' && a <= 'Z';})){
            --missing_type;
        }
        if(any_of(s.begin(), s.end(), [](char& a){return a >= '0' && a <= '9';})){
            --missing_type;
        }
        
        // cout << "missing_type: " << missing_type << endl;
        
        int change = 0;
        int one = 0, two = 0;
        int pos = 2;
        
        while(pos < n){
            int len = 0;
            if(s[pos-2] == s[pos-1] && s[pos-1] == s[pos]){
                len = 3;
                
                while(pos+1 < n && s[pos] == s[pos+1]){
                    ++len;
                    ++pos;
                }
                
                if(len%3 == 0){
                    //delete one char, so need one less changes
                    ++one;
                }else if(len%3 == 1){
                    //reduce one changes by deleting two chars
                    ++two;
                }
                /*
                assume repeating chars' length is 3's multiple + 2,
                need len/3 changes
                */
                change += len/3;  
            }
            ++pos;
        }
        
        if(n < 6){
            //need 6-n insertion or missing_type replacement/insertion
            /*
            if missing_type = 0:
            "aaaA1", insert one char to break "aaa"
            if missing_type = 1:
            "aaaaA", insert one char to break "aaaa"
            if missing_type = 2:
            "aaaaa", replace one "a" and insert one char
            */
            return max(missing_type, 6-n);
        }else if(n <= 20){
            return max(missing_type, change);
        }else{
            /*
            this is the quote of chars to be deleted,
            they are not yet actually deleted!
            */
            int del = n - 20;
            int del_quota = del;
            
            /*
            we have "del_quota" quota chars to delete,
            and here we choose the chars corresponding to "one" for deleting
            */
            change -= min(del_quota, one);
            //decrease the quota
            del_quota = max(del_quota-one, 0);
            
            /*
            choosing "two"*2 chars for deleting,
            so we need two*2 less "change"
            */
            change -= min(del_quota, two*2) / 2;
            del_quota = max(del_quota - 2*two, 0);
            
            /*
            replace the change with delete
            */
            change -= del_quota/3;
                
            return del + max(missing_type, change);
        }
    }
};
