//Runtime: 12 ms, faster than 65.37% of C++ online submissions for Reverse Vowels of a String.
//Memory Usage: 10 MB, less than 81.82% of C++ online submissions for Reverse Vowels of a String.

class Solution {
public:
    string reverseVowels(string s) {
        int l = 0, r = s.size()-1;
        string vowels = "aeiouAEIOU";
        char tmp;
        
        // cout << s.size() << endl;
        
        while(l < r){
            while(l < s.size() && vowels.find(s[l]) == string::npos){
                l++;
            }
            
            while(r >= 0 && vowels.find(s[r]) == string::npos){
                r--;
            }
            
            // cout << l << ", " << r << endl;
            
            if(l < r){
                tmp = s[l];
                s[l] = s[r];
                s[r] = tmp;
            }
            
            l++; r--;
        }
        
        return s;
    }
};
