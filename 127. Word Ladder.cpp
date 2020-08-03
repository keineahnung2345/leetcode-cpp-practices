//Graph, BFS
//Runtime: 652 ms, faster than 27.76% of C++ online submissions for Word Ladder.
//Memory Usage: 14.3 MB, less than 47.16% of C++ online submissions for Word Ladder.
class Solution {
public:
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
    
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        auto it = find(wordList.begin(), wordList.end(), beginWord);
        int start;
        if(it == wordList.end()){
            wordList.push_back(beginWord);
            start = wordList.size()-1;
        }else{
            start = it - wordList.begin();
        }
        
        it = find(wordList.begin(), wordList.end(), endWord);
        if(it == wordList.end()) return 0;
        int end = it - wordList.begin();
        
        // cout << "start: " << start << ", end: " << end << endl;
        
        int n = wordList.size();
        
        vector<vector<int>> adjList(n);
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(connected(wordList[i], wordList[j])){
                    adjList[i].push_back(j);
                    adjList[j].push_back(i);
                    // cout << wordList[i] << " <-> " << wordList[j] << endl;
                }
            }
        }
        
        //BFS
        queue<int> q;
        int cur;
        int level = 1; //the length of the path containing only start
        vector<bool> visited(n, false);
        q.push(start);
        visited[start] = true;
        
        while(!q.empty()){
            int levelSize = q.size();
            // cout << "level: " << level << ", levelSize: " << levelSize << endl;
            
            while(levelSize-- > 0){
                cur = q.front(); q.pop();
                // cout << wordList[cur] << endl;
            
                if(cur == end){
                    return level;
                }
                
                for(int nei : adjList[cur]){
                    if(!visited[nei]){
                        visited[nei] = true;
                        q.push(nei);
                    }
                }
            }
            
            ++level;
        }
        
        //cannot find a path
        return 0;
    }
};

//Approach 1: Breadth First Search
//Runtime: 156 ms, faster than 71.95% of C++ online submissions for Word Ladder.
//Memory Usage: 23.9 MB, less than 21.59% of C++ online submissions for Word Ladder.
//time: O(M^2*N), space: O(M^2*N)
//M is the length of each word and N is the total number of words in the input word list
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        auto it = find(wordList.begin(), wordList.end(), beginWord);
        int start;
        if(it == wordList.end()){
            wordList.push_back(beginWord);
            start = wordList.size()-1;
        }else{
            start = it - wordList.begin();
        }
        
        it = find(wordList.begin(), wordList.end(), endWord);
        if(it == wordList.end()) return 0;
        int end = it - wordList.begin();
        
        int m = beginWord.size();
        int n = wordList.size();
        //(generic word, id in wordList)
        unordered_map<string, vector<int>> allComboDict;
        
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j){
                //replace ith char with '*'
                string newword = wordList[i].substr(0, j) + '*' + wordList[i].substr(j+1);
                allComboDict[newword].push_back(i);
            }
        }
        
        //BFS
        queue<int> q;
        int cur;
        int level = 1; //the length of the path containing only start
        vector<bool> visited(n, false);
        q.push(start);
        visited[start] = true;
        
        while(!q.empty()){
            int levelSize = q.size();
            // cout << "level: " << level << ", levelSize: " << levelSize << endl;
            
            while(levelSize-- > 0){
                cur = q.front(); q.pop();
                // cout << wordList[cur] << endl;
            
                if(cur == end){
                    return level;
                }
                
                //iterate all char and build its generic word
                for(int i = 0; i < m; ++i){
                    string newword = wordList[cur].substr(0, i) + '*' + wordList[cur].substr(i+1);
                    
                    //use this generic word to find its neighbor
                    for(int nei : allComboDict[newword]){
                        if(!visited[nei]){
                            visited[nei] = true;
                            q.push(nei);
                        }
                    }
                }
            }
            
            ++level;
        }
        
        //cannot find a path
        return 0;
    }
};
