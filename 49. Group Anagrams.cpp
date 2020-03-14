//Runtime: 44 ms, faster than 61.55% of C++ online submissions for Group Anagrams.
//Memory Usage: 19.1 MB, less than 73.13% of C++ online submissions for Group Anagrams.
//time: O(NKlogK), space: O(NK), K is the maximum length of string in "strs"
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

//Approach 2: Categorize by Count(no sorting)
//Runtime: 136 ms, faster than 7.61% of C++ online submissions for Group Anagrams.
//Memory Usage: 29.1 MB, less than 5.97% of C++ online submissions for Group Anagrams.
//time: O(NK), space: O(NK)

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
            vector<int> count(26, 0);
            for(char c : str){
                count[c-'a']++;
            }
            
            string scount = "";
            for(int& e : count){
                scount += (to_string(e)+"#");
            }
            
            groups[scount].push_back(str);
        }
        
        vector<vector<string>> ans;
        
        transform(groups.begin(), groups.end(), back_inserter(ans), RetrieveValue());
        
        return ans;
    }
};
