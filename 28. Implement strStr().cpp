//https://gist.github.com/hsinewu/44a1ce38a1baf47893922e3f54807713
//Runtime: 12 ms, faster than 25.32% of C++ online submissions for Implement strStr().
//Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Implement strStr().
class Solution {
public:
    vector<int> getTable(string& pattern){
        vector<int> next(pattern.size(), -1);

        for(int r = 1, l = -1; r < pattern.size(); r++) {
            /*
            if l is -1, we compare from the start of pattern
            */
            /*
            compare pattern[l+1] and pattern[r],
            if they are different, 
            we go back to compare next[l]+1 with r
            */
            while(l != -1 && pattern[l+1] != pattern[r]){
                l = next[l];
            }

            // assert( l == -1 || pattern[l+1] == pattern[r]);
            if( pattern[l+1] == pattern[r]){
                /*
                pattern[?:l+1] and patter[?:r] are the same substring,
                when next time we fail to match pattern[r+1],
                we will fallback to l+2
                
                "next" table stores the end position of the last same substring
                */
                next[r] = l+1;
                l++;
            }
        }

        return next;
    };
    
    int KMPSearch(string& text, string& pattern, vector<int>& next){
        int tail = -1;
        
        for(int i = 0; i < text.size(); i++){
            /*
            if tail == -1, that means we will match from the start of "pattern"
            */
            while(tail != -1 && text[i] != pattern[tail+1]){
                /*
                if tail+1 and i don't match, we then fall back to compare former part of "pattern" to current part of "text"
                */
                tail = next[tail];
            }

            if(text[i] == pattern[tail+1]){
                tail++;
            }
            //we can consider tail as the current matched length

            if( tail == pattern.size()-1){
                return i - tail;
            }
        }
        
        return -1;
    };
    
    int strStr(string haystack, string needle) {
        if(needle == "") return 0;
        int i = 0, j = 0;
        
        vector<int> next = getTable(needle);
        
        // for(int i = 0; i < next.size(); i++){
        //     cout << next[i];
        // }
        // cout << endl;
        
        return KMPSearch(haystack, needle, next);
    }
};
