//backtracking
//TLE
//6 / 285 test cases passed.
class Solution {
public:
    int n;
    string s2;
    
    bool backtrack(vector<string>& split){
        if(split.size() == n){
            string merged = "";
            for(const string& s : split){
                merged += s;
            }
            return merged == s2;
        }else{
            for(int i = 0; i < split.size(); ++i){
                if(split[i].size() > 1){
                    string s = split[i];
                    vector<string> former(split.begin(), split.begin()+i);
                    vector<string> latter(split.begin()+i+1, split.end());
                    for(int j = 1; j < s.size(); ++j){
                        //split[0...i-1] + s_part1 + s_part2 + split[i+1...]
                        
                        string s_part1 = s.substr(0, j);
                        string s_part2 = s.substr(j);
                        
                        //not swap
                        vector<string> nsplit1 = former;
                        nsplit1.push_back(s_part1);
                        nsplit1.push_back(s_part2);
                        nsplit1.insert(nsplit1.end(), latter.begin(), latter.end());
                        if(backtrack(nsplit1)) return true;
                        
                        //swap
                        vector<string> nsplit2 = former;
                        nsplit2.push_back(s_part2);
                        nsplit2.push_back(s_part1);
                        nsplit2.insert(nsplit2.end(), latter.begin(), latter.end());
                        if(backtrack(nsplit2)) return true;
                    }
                }
            }
            return false;
        }
    }
    
    bool isScramble(string s1, string s2) {
        n = s1.size();
        this->s2 = s2;
        
        vector<string> split = {s1};
        
        return backtrack(split);
    }
};

//recursion
//https://leetcode.com/problems/scramble-string/discuss/29392/Share-my-4ms-c%2B%2B-recursive-solution
//Runtime: 4 ms, faster than 97.37% of C++ online submissions for Scramble String.
//Memory Usage: 12 MB, less than 59.34% of C++ online submissions for Scramble String.
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1 == s2) return true;
        
        int len = s1.size();
        
        vector<int> counter(26, 0);
        for(int i = 0; i < len; ++i){
            ++counter[s1[i]-'a'];
            --counter[s2[i]-'a'];
        }
        
        if(any_of(counter.begin(), counter.end(), 
            [](const int& e){return e != 0;})){
            return false;
        }
        
        //split at 1, 2, ..., len-1
        for(int slen = 1; slen <= len-1; ++slen){
            //not swap
            if(isScramble(s1.substr(0, slen), s2.substr(0, slen))
              && isScramble(s1.substr(slen), s2.substr(slen))){
                return true;
            }
            
            //swap: s1[slen...]-s2[0...len-slen-1] and 
            //s1[0...slen-1]-s2[len-slen...]
            if(isScramble(s1.substr(slen), s2.substr(0, len-slen))
              && isScramble(s1.substr(0, slen), s2.substr(len-slen))){
                return true;
            }
        }
        
        return false;
    }
};
