//Approach 1: Stack
//Runtime: 4 ms, faster than 58.93% of C++ online submissions for Tag Validator.
//Memory Usage: 6.4 MB, less than 60.71% of C++ online submissions for Tag Validator.
class Solution {
public:
    stack<string> stk;
    bool containsTag;
    
    bool isValidTagName(string s, bool ending){
        if(s.size() < 1 || s.size() > 9)
            return false;
        
        for(int i = 0; i < s.size(); ++i){
            if(s[i] < 'A' || s[i] > 'Z')
                return false;
        }
        
        if(ending){
            if(!stk.empty() && stk.top() == s){
                //find the matching start tag
                stk.pop();
            }else{
                //cannot find the matching start tag
                return false;
            }
        }else{
            //update containsTag when we find a start tag
            containsTag = true;
            stk.push(s);
        }
        
        return true;
    };
    
    bool isValidCdata(string s){
        return s.find("[CDATA[") == 0;
    };
    
    bool isValid(string code) {
        if(code[0] != '<' || code.back() != '>'){
            return false;
        }
        //initialize, it is set when we find a valid start tag
        containsTag = false;
        
        for(int i = 0; i < code.size(); ++i){
            bool ending = false;
            int closeIndex;
            
            if(containsTag && stk.empty()){
                /*
                if we have met a start tag, 
                the stack should contain its tag name
                o.w. it means that the subsequent substring is 
                something outside that tag
                
                e.g. "<A></A><B></B>"
                */
                return false;
            }
            
            if(code[i] == '<'){
                if(!stk.empty() && code[i+1] == '!'){
                    //"<!]]>" is wrapped by a tag
                    closeIndex = code.find("]]>", i+1);
                    // cout << "potential cdata: " << code.substr(i+2, closeIndex-(i+2)) << endl;
                    if(closeIndex == string::npos || 
                      !isValidCdata(code.substr(i+2, closeIndex-(i+2)))){
                        return false;
                    }
                }else{
                    if(code[i+1] == '/'){
                        ++i;
                        ending = true;
                    }
                    closeIndex = code.find('>', i+1);
                    // cout << "potential tagname: " << code.substr(i+1, closeIndex-(i+1)) << endl;
                    if(closeIndex < 0 || 
                      !isValidTagName(code.substr(i+1, closeIndex-(i+1)), ending)){
                        return false;
                    }
                }
                //next time start from a char behind cdata or tag's end
                i = closeIndex;
            }
        }
        return stk.empty() && containsTag;
    }
};

//Approach 2: Regex, catastrophic backtracking
//TLE
//0 / 256 test cases passed.
class Solution {
public:
    bool isValid(string code) {
        /*
        (1) <([A-Z]{1,9})>: outermost start-tag
        all upper-case alphabets with length btw 1 to 9 inside <...>
        
        (2) [^<]*: TAG_CONTENT except CDATA
        all chars except '<' occurring 0 or more times
        
        (3) (<\/?[A-Z]{1,9}>): start tag or end tag
        
        (4) (<!\[CDATA\[(.*?)]]>): CDATA
        matches any char within <!\[CDATA\[...]]>
        
        (5) <\/1>: outermost end-tag
        using "back-reference"
        //https://www.regular-expressions.info/backref.html
        
        (6) (.*?): match all chars until "]]>"
        (inside (4)) using "non-greedy mode"
        */
        /*
        this regex will lead to catastrophic backtracking
        https://www.regular-expressions.info/catastrophic.html
        */
        regex pattern("<([A-Z]{1,9})>([^<]*((<\/?[A-Z]{1,9}>)|(<!\[CDATA\[(.*?)]]>))?[^<]*)*<\/1>");
        return regex_match(code, pattern);
    }
};
