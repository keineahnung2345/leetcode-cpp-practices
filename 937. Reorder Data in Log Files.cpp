//Runtime: 12 ms, faster than 88.74% of C++ online submissions for Reorder Data in Log Files.
//Memory Usage: 13.8 MB, less than 47.06% of C++ online submissions for Reorder Data in Log Files.

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
    
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<vector<string>> split_logs(logs.size());
        vector<string> ans(logs.size());
        
        for(int i = 0; i < logs.size(); i++){
            split_logs[i] = string_split(logs[i], " ");
        }
        
        for(int i = logs.size() - 1, j = logs.size() - 1; i >= 0; i--){
            //[0]: convert from string to char
            if(isdigit(split_logs[i][1][0])){
                ans[j--] = logs[i];
                logs.erase(logs.begin() + i);
                split_logs.erase(split_logs.begin() + i);
            }
        }
        
        vector<int> indices(split_logs.size());
        iota(indices.begin(), indices.end(), 0);
        
        //move identifier to the end
        for(int i = 0; i < split_logs.size(); i++){
            split_logs[i].push_back(split_logs[i][0]);
            split_logs[i].erase(split_logs[i].begin());
        }
        
        sort(indices.begin(), indices.end(), 
            [&split_logs](const int i, const int j){
                return split_logs[i] < split_logs[j];
            });
        
        for(int i = 0; i < indices.size(); i++){
            ans[i] = logs[indices[i]];
        }
        
        return ans;
    }
};
