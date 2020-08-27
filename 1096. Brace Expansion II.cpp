//not understand
//https://leetcode.com/problems/brace-expansion-ii/discuss/317623/Python3-Clear-and-Short-Recursive-Solution
//Runtime: 28 ms, faster than 75.42% of C++ online submissions for Brace Expansion II.
//Memory Usage: 13.6 MB, less than 13.96% of C++ online submissions for Brace Expansion II.
class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        vector<vector<vector<string>>> groups = {{}};
        
        int level = 0;
        int n = expression.size();
        int start;
        
        for(int i = 0; i < n; ++i){
            char c = expression[i];
            // cout << i << " " << c << endl;
            if(c == '{'){
                if(level == 0){
                    start = i+1;
                }
                ++level;
            }else if(c == '}'){
                --level;
                if(level == 0){
                    //recursively process something inbetween first level {}
                    groups.back().push_back(
                        braceExpansionII(
                            expression.substr(start, i-start)));
                    // cout << "return from recursion: ";
                    // for(string& s : groups.back().back()){
                    //     cout << s << " ";
                    // }
                    // cout << endl;
                }
            }else if(level == 0){
                if(c == ','){
                    groups.push_back(vector<vector<string>>());
                }else{
                    groups.back().push_back({string(1,c)});
                    // cout << "push {" << c << "}" << endl;
                }
            }
        }
        
        // cout << "groups: " << groups.size() << endl;
        
        set<string> wordset;
        
        for(auto group : groups){
            // cout << "group: " << group.size() << endl;
            while(group.size() > 1){
                vector<string> last = group.back(); group.erase(group.end()-1);
                vector<string> sec_last = group.back(); group.erase(group.end()-1);
                vector<string> tmp;
                for(string& se : sec_last){
                    for(string& le : last){
                        tmp.push_back(se+le);
                    }
                }
                group.push_back(tmp);
            }
            
            vector<string> first = *group.begin();
            
            for(string& s : first){
                wordset.insert(s);
            }
        }
        
        // cout << "wordset: " << wordset.size() << endl;
        
        return vector<string>(wordset.begin(), wordset.end());
    }
};
