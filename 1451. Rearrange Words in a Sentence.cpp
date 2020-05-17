//Runtime: 224 ms, faster than 25.00% of C++ online submissions for Rearrange Words in a Sentence.
//Memory Usage: 20.3 MB, less than 100.00% of C++ online submissions for Rearrange Words in a Sentence.
class Solution {
public:
    std::vector<std::string> string_split2(std::string str)
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
    
    template <typename Iter>
    std::string join(Iter begin, Iter end, std::string const& separator)
    {
        std::ostringstream result;
        result.precision(2); //for floating point
        if (begin != end)
            result << *begin++;
        while (begin != end)
            //std::fixed : for floating point
            result << std::fixed << separator << *begin++;
        return result.str();
    }
    
    string arrangeWords(string text) {
        vector<string> tokens = string_split2(text);
        
        if(tokens.size() <= 1) return text;
        
        tokens[0][0] += ('a' - 'A');
        
        stable_sort(tokens.begin(), tokens.end(), 
            [](const string& a, const string& b){
                return a.size() < b.size();
            });
        
        tokens[0][0] += ('A'-'a');
        
        string ans = "";
        
        ans = join(tokens.begin(), tokens.end(), " ");
        
        return ans;
    }
};
