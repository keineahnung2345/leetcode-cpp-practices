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

    string reverseWords(string s) {
        vector<string> tokens = string_split2(s);
        
        return join(tokens.rbegin(), tokens.rend(), " ");
    }
};
