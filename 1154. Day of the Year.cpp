//Runtime: 4 ms, faster than 57.01% of C++ online submissions for Day of the Year.
//Memory Usage: 8.5 MB, less than 100.00% of C++ online submissions for Day of the Year.

class Solution {
public:
    std::vector<std::string> string_split(std::string str, std::string delimiter){
        size_t pos = 0;
        std::string token;
        std::vector<std::string> result;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            result.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        result.push_back(str);
        return result;
    }
    
    int dayOfYear(string date) {
        vector<string> vs = string_split(date, "-");
        vector<int> ymd;
        int ans;
        
        std::transform(vs.begin(), vs.end(), std::back_inserter(ymd),
            [](const std::string& s) { return std::stoi(s); });
        
        ans = ymd[2]; //d
        
        for(int m = 1; m < ymd[1]; m++){
            if(m == 2){
                ans += 28;
                if(ymd[0] % 400 == 0){
                    ans += 1;
                }else if(ymd[0] % 100 == 0){
                    //100's multiple, not 400's multiple
                    //is not leap year
                }else if(ymd[0] % 4 == 0){
                    ans += 1;
                }
            }else if(m < 8){
                if(m % 2 == 1) ans += 31;
                else ans += 30;
            }else{
                if(m % 2 == 1) ans += 30;
                else ans += 31;
            }
        }
        
        return ans;
    }
};
