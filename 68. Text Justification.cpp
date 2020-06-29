//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Text Justification.
//Memory Usage: 7.5 MB, less than 53.09% of C++ online submissions for Text Justification.
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> line;
        int lineSize = 0;
        int cur = 0;
        int n = words.size();
        vector<string> ans;
        
        while(cur < n){
            // cout << "cur: " << cur << endl;
            if(lineSize + (line.size()-1) + (1+words[cur].size()) <= maxWidth){
                // cout << "build line" << endl;
                lineSize += words[cur].size();
                line.push_back(words[cur]);
                ++cur;
            }else{
                // cout << "flush" << endl;
                //cannot add words into this line anymore
                string str = "";
                if(line.size() == 1){
                    str += line[0];
                    str += string(maxWidth - str.size(), ' ');
                }else{
                    int quot = (maxWidth - lineSize)/(line.size()-1);
                    int mod = (maxWidth - lineSize)%(line.size()-1);
                    
                    for(int i = 0; i < line.size(); ++i){
                        str += line[i];
                        if(i != line.size()-1)
                            str += string(quot + (i<mod), ' ');
                    }
                }
                ans.push_back(str);
                line.clear();
                lineSize = 0;
            }
            // ++cur;
        }
        
        //flush the last line
        string str = "";
        //last line must be left-justified
        for(int i = 0; i < line.size(); ++i){
            str += line[i];
            if(i != line.size()-1) str += " ";
        }
        str += string(maxWidth - str.size(), ' ');
        ans.push_back(str);
        line.clear();
        lineSize = 0;
        
        ans.back() += string(maxWidth-ans.back().size(), ' ');
        
        return ans;
    }
};
