//Runtime: 44 ms, faster than 61.55% of C++ online submissions for Group Anagrams.
//Memory Usage: 19.1 MB, less than 73.13% of C++ online submissions for Group Anagrams.
struct RetrieveValue
{   
    template <typename T>
    typename T::second_type operator()(T keyValuePair) const
    {   
        return keyValuePair.second;
    }
};

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for(string& str : strs){
            string sorted = str;
            sort(sorted.begin(), sorted.end());
            groups[sorted].push_back(str);
        }
        
        vector<vector<string>> ans;
        transform(groups.begin(), groups.end(), back_inserter(ans), RetrieveValue());
        
        return ans;
    }
};
