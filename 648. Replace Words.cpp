//Approach #1: Prefix Hash
//Runtime: 388 ms, faster than 10.41% of C++ online submissions for Replace Words.
//Memory Usage: 275.6 MB, less than 14.29% of C++ online submissions for Replace Words.
//time: O(sigma(wi^2)), wi is the length of ith word
//space: O(N), N is the length of sentence
class Solution {
public:
    string replaceWords(vector<string>& dict, string sentence) {
        set<string> dictset;
        string ans = "";
        istringstream is(sentence);
        string token;
        
        //convert dict from string to set
        for(string& word : dict){
            dictset.insert(word);
        }
        
        //iterate through sentence
        while(is >> token){
            //create "prefix" from current token
            string prefix = "";
            for(int i = 1; i <= token.size(); i++){
                prefix = token.substr(0, i);
                //find prefix in dictset
                if(dictset.find(prefix) != dictset.end()){
                    break;
                }
            }
            //add space between tokens
            if(ans.size() > 0){
                ans += " ";
            }
            // cout << token << " " << prefix << endl;
            ans += prefix;
        };
        
        return ans;
    }
};
