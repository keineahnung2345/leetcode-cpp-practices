/*
WA
success:
["w","wo","wor","worl","world"]
["a", "banana", "app", "appl", "ap", "apply", "apple"]
["m","mo","moc","moch","mocha","l","la","lat","latt","latte","c","ca","cat"]
["yo","ew","fc","zrc","yodn","fcm","qm","qmo","fcmz","z","ewq","yod","ewqz","y"]
["ogz","eyj","e","ey","hmn","v","hm","ogznkb","ogzn","hmnm","eyjuo","vuq","ogznk","og","eyjuoi","d"]

fail:
["rac","rs","ra","on","r","otif","o","onpdu","rsf","rs","ot","oti","racy","onpd"]
*/
class Solution {
public:
    string longestWord(vector<string>& words) {
        sort(words.begin(), words.end());
        copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
        string acc = words[0].size() == 1 ? words[0] : "-";
        vector<string> candidates;
        for(int i = 1; i < words.size(); i++){
            //the accumulation process doesn't start or it ends
            if(acc == "-" || words[i].size() <= acc.size()){
                if(acc != "-") candidates.push_back(acc);
                acc = words[i].size() == 1 ? words[i] : "-";
            }
            if(words[i].size() == acc.size()+1 && words[i].rfind(acc, 0) == 0){
                acc = words[i];
            }
        }
        candidates.push_back(acc);
        copy(candidates.begin(), candidates.end(), ostream_iterator<string>(cout, " "));
        cout << endl;
        
        sort(candidates.begin(), candidates.end(), 
             [](const string& a, const string& b) -> bool{
                 //first sort by length and then by lexicographical order
                 //if length are the same, check their lexicographical order
                 //ow, directly sort by their length
                 return (a.size() == b.size()) ? a < b : a.size() > b.size();
             }
        );
        return candidates[0];
    }
};

/*
Hint 1
For every word in the input list, we can check whether all prefixes of that word are in the input list by using a Set.
*/

class Solution {
public:
    string longestWord(vector<string>& words) {
        vector<string> candidates;
        
        for(string word : words){
            bool valid = true;
            for(int i = word.size() - 1; i >= 1; i--){
                string prefix = word.substr(0, i);
                // cout << prefix << endl;
                if(find(words.begin(), words.end(), prefix) == words.end()){
                    valid = false;
                    break;
                }
            }
            if(valid)candidates.push_back(word);
        }
        // cout << candidates.size() << endl;
        // copy(candidates.begin(), candidates.end(), ostream_iterator<string>(cout, " "));

        sort(candidates.begin(), candidates.end(), 
             [](const string& a, const string& b){
                 return a.size() == b.size() ? a < b : a.size() > b.size();
             }
            );
        return candidates[0];
    }
};
