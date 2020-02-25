//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Occurrences After Bigram.
//Memory Usage: 8.8 MB, less than 100.00% of C++ online submissions for Occurrences After Bigram.
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
    
    vector<string> findOcurrences(string text, string first, string second) {
        vector<string> split = string_split(text, " ");
        vector<string> ans;
        
        for(int i = 0; i < split.size() - 1; i++){
            if(split[i] == first && split[i+1] == second && i+2 < split.size()){
                ans.push_back(split[i+2]);
            }
        }
        return ans;
    }
};
