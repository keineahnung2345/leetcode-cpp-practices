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
