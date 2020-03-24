//TLE
//31 / 32 test cases passed.
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        set<string> ans;
        
        for(int i = 0; i + 10 <= s.size(); i++){
            string pattern = s.substr(i, 10);
            size_t found = s.find(pattern, i+1);
            if(found != string::npos){
                ans.insert(pattern);
            }
        }
        
        return vector<string>(ans.begin(), ans.end());
    }
};

//KMP
//TLE
//31 / 32 test cases passed.
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
    vector<string> findRepeatedDnaSequences(string s) {
        vector<string> ans;
        
        for(int i = 0; i + 10 <= s.size(); i++){
            string tofind = s.substr(i+1);
            string pattern = s.substr(i, 10);
            if(find(ans.begin(), ans.end(), pattern) != ans.end()){
                continue;
            }
            vector<int> next = getTable(pattern);
            if(KMPSearch(tofind, pattern, next) != -1){
                ans.push_back(pattern);
            }
        }
        
        return ans;
    }
};
