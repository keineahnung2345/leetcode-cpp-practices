//https://leetcode.com/problems/decode-string/discuss/87662/Python-solution-using-stack
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Decode String.
//Memory Usage: 6.8 MB, less than 9.68% of C++ online submissions for Decode String.
class Solution {
public:
    string decodeString(string s) {
        stack<string> stks;
        stack<int> stki;
        
        string curs = "";
        int curi = 0;
        
        for(char& c : s){
            if(c == '['){
                stks.push(curs);
                stki.push(curi);
                curs = "";
                curi = 0;
            }else if(c == ']'){
                /*
                between [ and ], there is only chars,
                so here we only use curs, not curi
                
                we can see the string until ] as:
                pres + prei[curs],
                and we need to set curs as the parsed string
                */
                string pres = stks.top(); stks.pop();
                int prei = stki.top(); stki.pop();
                
                string tmp;
                for(int i = 0; i < prei; ++i){
                    tmp += curs;
                }
                curs = pres + tmp;
            }else if(isdigit(c)){
                curi = curi*10 + (c-'0');
            }else{
                curs += c;
            }
        }
        
        return curs;
    }
};
