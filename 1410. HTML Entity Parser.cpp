//Once accepted answer
/*
151 / 154 test cases passed.
Input: "&amp;amp;"
Output: "&"
Expected: "&amp;"
*/
//Runtime: 1204 ms
//Memory Usage: 16.4 MB
class Solution {
public:
    string entityParser(string text) {
        map<string, string> entityMap = {
            {"&quot;" , "\""},
            {"&apos;",  "'"}, 
            {"&amp;" , "&"}, 
            {"&gt;" , ">"}, 
            {"&lt;" , "<"}, 
            {"&frasl;" , "/"}
            };
        
        for(auto it = entityMap.begin(); it != entityMap.end(); it++){
            size_t pos = 0;

            while((pos = text.find(it->first, pos)) != string::npos){
                text.replace(pos, (it->first).length(), it->second);
            }
        }
        
        return text;
    }
};
