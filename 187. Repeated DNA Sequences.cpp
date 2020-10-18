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

//Bit manipulation + Hashmap
//https://leetcode.com/problems/repeated-dna-sequences/discuss/53867/Clean-Java-solution-(hashmap-%2B-bits-manipulation)
//Runtime: 140 ms, faster than 32.45% of C++ online submissions for Repeated DNA Sequences.
//Memory Usage: 15.6 MB, less than 13.54% of C++ online submissions for Repeated DNA Sequences.
class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        unordered_set<int> words; //substrings that appear once
        unordered_set<int> doubleWords; //appear twice
        unordered_map<char, int> bitRepresentation;
        
        //we use 2 bit to represent a char
        bitRepresentation['A'] = 0;
        bitRepresentation['C'] = 1;
        bitRepresentation['G'] = 2;
        bitRepresentation['T'] = 3;
        
        vector<string> ans;
        
        // cout << s.size() << " " << (int)s.size() - 10 + 1 << endl;
        
        /*
        (int)s.size():
        Need to convert it from size_t to int!!
        Because size_t is unsigned, and (size_t)0-10+1 will be 18446744073709551607 which is larger than 0!
        */
        for(int i = 0; i < (int)s.size() - 10 + 1; i++){
            //convert s.substr(i, 10) into its bit representation
            int value = 0;
            for(int j = i; j < i+10; j++){
                value = (value << 2) + bitRepresentation[s[j]];
            }
            
            //if the substring appear once but not twice
            //a.k.a, it's the second time the substring appears
            if(!words.insert(value).second && doubleWords.insert(value).second){
                ans.push_back(s.substr(i, 10));
            }
        }
        
        return ans;
    }
};
