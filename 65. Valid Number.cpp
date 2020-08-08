//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Valid Number.
//Memory Usage: 6.1 MB, less than 36.30% of C++ online submissions for Valid Number.
class Solution {
public:
    static inline void trim_left(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    // trim from end (in place)
    static inline void trim_right(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    // trim from both ends (in place)
    static inline void trim_all(std::string &s) {
        trim_left(s);
        trim_right(s);
    }
    
    bool isPosNegCorrect(string& s){
        //check if the count and pos of '+' or '-' is correct
        //this function also remove '+' and '-' for later process
        if(s == "+" || s == "-") return false;
        int pos_count = count(s.begin(), s.end(), '+');
        int neg_count = count(s.begin(), s.end(), '-');
        if(pos_count > 1) return false;
        if(neg_count > 1) return false;
        if(pos_count + neg_count > 1) return false;
        
        int pos;
        if((pos = s.find('+')) != string::npos &&  pos > 0) return false;
        if((pos = s.find('-')) != string::npos &&  pos > 0) return false;
        
        if(s[0] == '+') s.erase(0,1);
        if(s[0] == '-') s.erase(0,1);
        
        return true;
    }
    
    bool isNumber(string s) {
        //remove spaces
        trim_all(s);
        //" " is invalid
        if(s.empty()) return false;
        
        //contains something not in 0-9, "e", "+", "-", "."
        if(!s.empty() && s.find_first_not_of("0123456789e+-.") != string::npos)
            return false;
        
        //process and remove 'e'
        int e_count;
        if((e_count = count(s.begin(), s.end(), 'e')) > 1) return false;
        
        string s_before_e, s_after_e;
        
        if(e_count == 1){
            int pos = s.find('e');
            s_before_e = s.substr(0, pos);
            s_after_e = s.substr(pos+1);
            // cout << "e at : " << pos << ", " << s_before_e << " " << s_after_e << endl;
            if(s_before_e.empty() || s_after_e.empty()) return false;
        }else{
            // e_count == 0
            s_before_e = s;
            // cout << "s: " << s << endl;
        }
        
        //process and remove '+' and '-'
        if(!s_before_e.empty() && !isPosNegCorrect(s_before_e)) return false;
        if(!s_after_e.empty() && !isPosNegCorrect(s_after_e)) return false;
        
        // cout << "after removing + and -: " << s_before_e << " " << s_after_e << endl;
        
        //"." is invalid
        if(s_before_e == ".") return false;
        
        //"0.1", 0." and ".1" are valid
        if(count(s_before_e.begin(), s_before_e.end(), '.') > 1){
            return false;
        }
        if(!s_after_e.empty() && count(s_after_e.begin(), s_after_e.end(), '.') > 0){
            return false;
        }
        
        return true;
    }
};
