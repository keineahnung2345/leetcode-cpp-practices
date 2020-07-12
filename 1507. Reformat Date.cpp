//Runtime: 4 ms, faster than 50.00% of C++ online submissions for Reformat Date.
//Memory Usage: 6.1 MB, less than 100.00% of C++ online submissions for Reformat Date.
class Solution {
public:
    std::vector<std::string> string_split(std::string str)
    {  
        // Used to split string around spaces.
        std::istringstream ss(str);
        std::vector<std::string> result;
        std::string word;

        //need to check whether the reading success before using it
        while(ss >> word){
            result.push_back(word);
        }

        return result;
    }
    
    string reformatDate(string date) {
        vector<string> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        
        vector<string> tokens = string_split(date);
        
        string ans = tokens[2];
        
        string monthStr = to_string(find(months.begin(), months.end(), tokens[1]) - months.begin() + 1);
        if(monthStr.size() == 1) monthStr = "0" + monthStr;
        
        string dayStr = tokens[0].substr(0, tokens[0].size()-2);
        if(dayStr.size() == 1) dayStr = "0" + dayStr;
        
        return tokens[2] + "-" + monthStr + "-" + dayStr;
    }
};
