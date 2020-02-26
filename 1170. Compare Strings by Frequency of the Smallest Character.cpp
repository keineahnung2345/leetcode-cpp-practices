//Runtime: 24 ms, faster than 66.29% of C++ online submissions for Compare Strings by Frequency of the Smallest Character.
//Memory Usage: 10.9 MB, less than 100.00% of C++ online submissions for Compare Strings by Frequency of the Smallest Character.

class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector<int> queries_f(queries.size());
        vector<int> words_f(words.size());
        
        for(int i = 0; i < queries.size(); i++){
            queries_f[i] = count(queries[i].begin(), queries[i].end(),
                *min_element(queries[i].begin(), queries[i].end()));
        }
        
        for(int i = 0; i < words.size(); i++){
            words_f[i] = count(words[i].begin(), words[i].end(),
                *min_element(words[i].begin(), words[i].end())
            );
        }
        
        //sort in descending order
        sort(words_f.begin(), words_f.end(), greater<int>());
        
//         copy(queries_f.begin(), queries_f.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
//         copy(words_f.begin(), words_f.end(), ostream_iterator<int>(cout, " "));
//         cout << endl;
        
        for(int i = 0; i < queries.size(); i++){
            //find the index j which words_f[j] <= queries_f[i]
            //so there are j elements in words_f <= queries_f[i]
            queries_f[i] = find_if(
                words_f.begin(), words_f.end(), 
                [&queries_f, i](int e){return e <= queries_f[i];})
                - words_f.begin();
        }
        
        return queries_f;
    }
};
