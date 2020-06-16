//Runtime: 4 ms, faster than 37.03% of C++ online submissions for Validate IP Address.
//Memory Usage: 6.3 MB, less than 82.33% of C++ online submissions for Validate IP Address.
class Solution {
public:
    bool isnum(std::string s){
        return !s.empty() && s.find_first_not_of("0123456789") == std::string::npos;
    };
    
    bool isalnum(std::string s){
        return !s.empty() && std::all_of(s.begin(), s.end(), [](const char c){return std::isalnum(c);});
    };
    
    bool ishex(std::string s){
        return !s.empty() && s.find_first_not_of("0123456789abcdef") == std::string::npos;
    };
    
    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;
        while(true){
            pos = str.find(delimiter);
            //works even if pos is string::npos
            token = str.substr(0, pos);
            result.push_back(token);
            if(pos == string::npos) break;
            //pos+1 equals to 0, so the line below can't handle this situation
            str.erase(0, pos+delimiter.length());
        }
        return result;
    }
    
    string validIPAddress(string IP) {
        if(IP.find(".") != string::npos){
            if(count(IP.begin(), IP.end(), '.') != 3)
                return "Neither";
            vector<string> tokens = string_split(IP, ".");
            for(string token : tokens){
                if(token.size() > 3){
                    return "Neither";
                }else if(!isnum(token)){
                    return "Neither";
                }else if(token.rfind("0", 0) == 0 && token.size() > 1){
                    return "Neither";
                }else{
                    int num = stoi(token);
                    if(num < 0 || num > 255) return "Neither";
                }
            }
            return "IPv4";
        }else if(IP.find(":") != string::npos){
            if(count(IP.begin(), IP.end(), ':') != 7)
                return "Neither";
            std::transform(IP.begin(), IP.end(), IP.begin(), 
                           [](unsigned char c){return std::tolower(c);});
            vector<string> tokens = string_split(IP, ":");
            for(string token : tokens){
                if(token.size() == 0 || token.size() > 4){
                    return "Neither";
                }else if(!ishex(token)){
                    return "Neither";
                }
            }
            return "IPv6";
        }
        
        return "Neither";
    }
};
