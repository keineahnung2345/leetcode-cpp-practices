//Runtime: 12 ms, faster than 17.82% of C++ online submissions for Most Common Word.
//Memory Usage: 10.4 MB, less than 7.69% of C++ online submissions for Most Common Word.

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
    
    string mostCommonWord(string paragraph, vector<string>& banned) {
        //replace !?',;. with ' '
        std::string toRemove = "!?',;.";
        std::replace_if(paragraph.begin(), paragraph.end(),
            [toRemove](char c) { return toRemove.find(c) != std::string::npos;}, ' ');
        
        //remove duplicate spaces
        paragraph.erase(
            std::unique(paragraph.begin(), paragraph.end(),
                [](const char& lhs, const char& rhs){return lhs == ' ' && (lhs == rhs);}
            ),
            paragraph.end()
        );
        
        transform(paragraph.begin(), paragraph.end(), 
                  paragraph.begin(), [](unsigned char c){return tolower(c);});
        map<string, int> count;
        string max_word;
        int max_count = 0;
        
        for(string word : string_split(paragraph, " ")){
            if(find(banned.begin(), banned.end(), word) == banned.end()){
                count[word]++;
                if(count[word] > max_count){
                    max_word = word;
                    max_count = count[word];
                }
            }
        }
        
        return max_word;
    }
};
