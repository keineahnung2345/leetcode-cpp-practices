//TLE
//21 / 39 test cases passed.
class Solution {
public:
    string beginWord, endWord;
    vector<vector<int>> adjList;
    int minLen;
    int start, end;
    
    bool connected(string& s1, string& s2){
        int m = s1.size();
        int n = s2.size();
        if(m != n) return -1;
        
        int count = 0;
        for(int i = 0; i < m; ++i){
            if(s1[i] != s2[i]){
                ++count;
                if(count > 1) return false;
            }
        }
        return count == 1;
    };
    
    void backtrack(int cur, vector<string>& wordList, vector<bool>& visited, vector<string>& path, vector<vector<string>>& paths){
        if(path.size() > minLen){
            // cout << "early stopping" << endl;
            return;
        }else if(!path.empty() && path.back() == endWord){
            // cout << "push" << endl;
            if(paths.empty() || path.size() == minLen){
                minLen = path.size();
                paths.push_back(path);
            }else{
                //path.size() < minLen
                minLen = path.size();
                paths.clear();
                paths.push_back(path);
            }
        }else{
            // cout << "building" << endl;
            for(int nei : adjList[cur]){
                visited[nei] = true;
                path.push_back(wordList[nei]);
                backtrack(nei, wordList, visited, path, paths);
                visited[nei] = false;
                path.pop_back();
            }
        }
    };
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        this->beginWord = beginWord;
        this->endWord = endWord;
        auto it = find(wordList.begin(), wordList.end(), beginWord);
        int start;
        if(it == wordList.end()){
            wordList.push_back(beginWord);
            start = wordList.size()-1;
        }else{
            start = it - wordList.begin();
        }
        
        it = find(wordList.begin(), wordList.end(), endWord);
        if(it == wordList.end()) return vector<vector<string>>();
        int end = it - wordList.begin();
        
        // cout << "start: " << start << ", end: " << end << endl;
        
        int n = wordList.size();
        
        adjList = vector<vector<int>>(n);
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(connected(wordList[i], wordList[j])){
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                }
            }
        }
        
        minLen = wordList.size();
        vector<bool> visited(n, false);
        vector<string> path = {beginWord};
        vector<vector<string>> paths;
        
        backtrack(start, wordList, visited, path, paths);
        
        return paths;
    }
};
