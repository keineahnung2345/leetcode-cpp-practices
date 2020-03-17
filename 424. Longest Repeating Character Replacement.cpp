//Runtime: 16 ms, faster than 53.88% of C++ online submissions for Longest Repeating Character Replacement.
//Memory Usage: 8.7 MB, less than 100.00% of C++ online submissions for Longest Repeating Character Replacement.

class Solution {
public:
    int characterReplacement(string s, int k) {
        int N = s.size();
        int ans = 0;
        
        // for(int i = 0; i < 26; i++){
        //     lengths[i+'A'] = 0;
        //     used[i+'A'] = 0;
        // }
           
        for(int i = 0; i < 26; i++){
            int length = 0;
            int used = 0;
            int left = 0, right = 0;
            char c = 'A' + i;
            
            //skip the character not in s
            if(s.find(c) == string::npos)
                continue;
            // cout << c << endl;
            
            while(right < N){
                if(left > 0 && s[left-1] != c){
                    used--;
                }
                // cout << "[" << left << ", " << right << "), used: " << used << endl;
                while(right < N && (s[right] == c || used < k)){
                    if(s[right] != c){
                        used++;
                    }
                    right++;
                    // cout << "[" << left << ", " << right << "), used: " << used << endl;
                }

                length = max(length, right-left);
                // cout << "[" << left << ", " << right << "), length: " << length << ", used: " << used << endl;

                left++;
            }
            
            ans = max(length, ans);
            
            // cout << "ans: " << ans << endl;
        }
        
        return ans;
    }
};
