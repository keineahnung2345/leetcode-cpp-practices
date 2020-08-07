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

//BFS + DFS(backtracking)
//https://leetcode.com/problems/word-ladder-ii/discuss/40475/My-concise-JAVA-solution-based-on-BFS-and-DFS/145572
//TLE
//29 / 39 test cases passed.
class Solution {
public:
    int n;
    
    void getNextLevel(int begin, vector<string>& wordList, vector<int>& neighbors){
        string beginWord = wordList[begin];
        vector<string>::iterator it;
        
        for(int i = 0; i < beginWord.size(); ++i){
            for(char c = 'a'; c <= 'z'; ++c){
                if(beginWord[i] == c) continue;
                char oldC = beginWord[i];
                beginWord[i] = c;
                if((it = find(wordList.begin(), wordList.end(), beginWord)) != 
                  wordList.end()){
                    // cout << wordList[it - wordList.begin()] << " ";
                    neighbors.push_back(it - wordList.begin());
                }
                beginWord[i] = oldC;
            }
        }
        
        // cout << endl;
    };
    
    void buildGraph(int begin, int end, vector<string>& wordList, unordered_map<int, unordered_set<int>>& graph){
        unordered_set<int> visited, tovisit;
        
        queue<int> q;
        //0th level
        q.push(begin);
        // tovisit.insert(begin); //don't need this
        tovisit.insert(begin);
        
        bool foundEnd = false;
        
        while(!q.empty()){
            visited.insert(tovisit.begin(), tovisit.end());
            tovisit.clear();
            
            int levelSize = q.size();
            
            for(int i = 0; i < levelSize; ++i){
                int cur = q.front(); q.pop();
                
                // cout << "cur: " << wordList[cur] << ", neighbors: ";
                
                vector<int> neighbors;
                getNextLevel(cur, wordList, neighbors);
                
                // cout << "found " << neighbors.size() << " neighbors." << endl;
                
                for(int nei : neighbors){
                    if(nei == end) foundEnd = true;
                    // if(!visited[nei]){
                    if(visited.find(nei) == visited.end()){
                        //there could be a duplicate, so we use set
                        graph[cur].insert(nei);
                        // cout << "nei: " << wordList[nei] << endl;
                    }
                    
                    /*
                    in a graph, a node can be reached from multiple parents,
                    so we use the "tovisit" to avoid 
                    visiting the same node in the same level twice
                    */
                    // if(!visited[nei] && !tovisit[nei]){
                    if(visited.find(nei) == visited.end() && tovisit.find(nei) == tovisit.end()){
                        q.push(nei);
                        // cout << "to visit " << wordList[nei] << endl;
                        // tovisit[nei] = true;
                        tovisit.insert(nei);
                    }
                }
                // cout << endl;
            }
            
            //stopping building graph once we find the goal
            if(foundEnd) break;
        }
        // cout << endl;
    };
    
    void dfs(int cur, int end, vector<string>& wordList, 
             unordered_map<int, unordered_set<int>>& graph, 
             vector<string>& path, vector<vector<string>>& paths){
        path.push_back(wordList[cur]);
        
        if(cur == end){
            paths.push_back(path);
        }else{
            for(int nei : graph[cur]){
                dfs(nei, end, wordList, graph, path, paths);
            }
        }
        
        path.pop_back();
    }
    
    void backtrack(int cur, int end, vector<string>& wordList, 
             unordered_map<int, unordered_set<int>>& graph, 
             vector<string>& path, vector<vector<string>>& paths){
        if(cur == end){
            paths.push_back(path);
        }else{
            for(int nei : graph[cur]){
                // cout << wordList[cur] << " -> " << wordList[nei] << endl;
                path.push_back(wordList[nei]);
                backtrack(nei, end, wordList, graph, path, paths);
                path.pop_back();
            }
        }
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int begin, end;
        
        auto it = find(wordList.begin(), wordList.end(), beginWord);
        if(it != wordList.end()){
            begin = it - wordList.begin();
        }else{
            wordList.push_back(beginWord);
            begin = wordList.size()-1;
        }
        
        it = find(wordList.begin(), wordList.end(), endWord);
        if(it != wordList.end()){
            end = it - wordList.begin();
        }else{
            return vector<vector<string>>();
        }
        
        n = wordList.size();
        vector<string> path;
        vector<vector<string>> paths;
        unordered_map<int, unordered_set<int>> graph;
        
        // cout << "begin: " << begin << ", end: " << end << ", n: " << n << endl;
        
        buildGraph(begin, end, wordList, graph);
        
        // for(int i = 0; i < n; ++i){
        //     cout << wordList[i] << " has " << graph[i].size() << " neighbors: ";
        //     for(int j : graph[i]){
        //         cout << wordList[j] << " ";
        //     }
        //     cout << endl;
        // }
        // dfs(begin, end, wordList, graph, path, paths);
        path = {wordList[begin]};
        backtrack(begin, end, wordList, graph, path, paths);
        
        return paths;
    }
};

//revised from above, represent wordList as unordered_set
//Runtime: 324 ms, faster than 73.15% of C++ online submissions for Word Ladder II.
//Memory Usage: 32.5 MB, less than 69.39% of C++ online submissions for Word Ladder II.
class Solution {
public:
    int n;
    
    void getNextLevel(string& beginWord, unordered_set<string>& wordList, vector<string>& neighbors){
        vector<string>::iterator it;
        
        for(int i = 0; i < beginWord.size(); ++i){
            for(char c = 'a'; c <= 'z'; ++c){
                if(beginWord[i] == c) continue;
                char oldC = beginWord[i];
                beginWord[i] = c;
                if(wordList.find(beginWord) != wordList.end()){
                    neighbors.push_back(beginWord);
                }
                beginWord[i] = oldC;
            }
        }
    };
    
    void buildGraph(string& beginWord, string& endWord, unordered_set<string>& wordList, unordered_map<string, unordered_set<string>>& graph){
        unordered_set<string> visited, tovisit;
        
        queue<string> q;
        q.push(beginWord);
        tovisit.insert(beginWord);
        
        bool foundEnd = false;
        
        while(!q.empty()){
            visited.insert(tovisit.begin(), tovisit.end());
            tovisit.clear();
            
            int levelSize = q.size();
            
            for(int i = 0; i < levelSize; ++i){
                string cur = q.front(); q.pop();
                
                vector<string> neighbors;
                getNextLevel(cur, wordList, neighbors);
                
                for(string nei : neighbors){
                    if(nei == endWord) foundEnd = true;
                    if(visited.find(nei) == visited.end()){
                        graph[cur].insert(nei);
                    }
                
                    if(visited.find(nei) == visited.end() && tovisit.find(nei) == tovisit.end()){
                        q.push(nei);
                        tovisit.insert(nei);
                    }
                }
            }
            
            if(foundEnd) break;
        }
    };
    
    void backtrack(string& cur, string& endWord, unordered_set<string>& wordList, 
             unordered_map<string, unordered_set<string>>& graph, 
             vector<string>& path, vector<vector<string>>& paths){
        if(cur == endWord){
            paths.push_back(path);
        }else{
            for(string nei : graph[cur]){
                path.push_back(nei);
                backtrack(nei, endWord, wordList, graph, path, paths);
                path.pop_back();
            }
        }
    }
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        auto it = find(wordList.begin(), wordList.end(), beginWord);
        if(it == wordList.end()){
            wordList.push_back(beginWord);
        }
        
        it = find(wordList.begin(), wordList.end(), endWord);
        if(it == wordList.end()){
            return vector<vector<string>>();
        }
        
        unordered_set<string> words(wordList.begin(), wordList.end());
        
        n = words.size();
        vector<string> path;
        vector<vector<string>> paths;
        unordered_map<string, unordered_set<string>> graph;
        
        buildGraph(beginWord, endWord, words, graph);
        
        path = {beginWord};
        backtrack(beginWord, endWord, words, graph, path, paths);
        
        return paths;
    }
};



//BFS, view a path as a node
//https://leetcode.com/problems/word-ladder-ii/discuss/40434/C%2B%2B-solution-using-standard-BFS-method-no-DFS-or-backtracking
//Runtime: 968 ms, faster than 43.36% of C++ online submissions for Word Ladder II.
//Memory Usage: 180.1 MB, less than 28.57% of C++ online submissions for Word Ladder II.
class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int level = 1;
        int minLevel = INT_MAX;
        queue<vector<string>> q;
        vector<vector<string>> ans;
        unordered_set<string> visited;
        
        //represent vector as unordered_set is the key to avoid TLE!!!
        unordered_set<string> words(wordList.begin(), wordList.end());
        
        q.push({beginWord});
        
        while(!q.empty()){
            vector<string> path = q.front(); q.pop();
            
            if(path.size() > minLevel){
                break;
            }
            
            if(path.size() > level){
                // visited.clear(); //add this line will make it slower
                //reach a new level, erase the unneeded words
                for(const string& word : visited){
                    words.erase(word);
                }
                
                level = path.size();
            }
            
            string cur = path.back();
            
            if(cur == endWord){
                minLevel = level;
                ans.push_back(path);
            }
            
            for(int i = 0; i < cur.size(); ++i){
                char oldC = cur[i];
                
                for(char c = 'a'; c <= 'z'; ++c){
                    if(c == oldC) continue;
                    cur[i] = c;
                    
                    if(words.find(cur) != words.end()){
                        vector<string> nextpath = path;
                        nextpath.push_back(cur);
                        visited.insert(cur);
                        q.push(nextpath);
                    }
                }
                
                cur[i] = oldC;
            }
        }
        
        return ans;
    }
};

//Bidirectional Breadth First Search
//https://leetcode.com/problems/word-ladder-ii/discuss/269012/Python-BFS%2BBacktrack-Greatly-Improved-by-bi-directional-BFS
//Runtime: 68 ms, faster than 93.13% of C++ online submissions for Word Ladder II.
//Memory Usage: 15.8 MB, less than 97.96% of C++ online submissions for Word Ladder II.
class Solution {
public:
    void backtrack(string cur, string& endWord, unordered_map<string, unordered_set<string>>& graph,
                   vector<string>& path, vector<vector<string>>& paths){
        //cout << "cur: " << cur << endl;
        if(cur == endWord){
            paths.push_back(path);
        }else{
            //cout << "neighbors: " << graph[cur].size() << endl;
            for(const string& nei : graph[cur]){
                path.push_back(nei);
                backtrack(nei, endWord, graph, path, paths);
                path.pop_back();
            }
        }
    };
    
    bool visitLevel(unordered_set<string>& words, unordered_map<string, unordered_set<string>>& graph,
                      queue<string>& q, unordered_set<string>& visited, unordered_set<string>& visited_other, bool reversed){
        int levelSize = q.size();
        bool foundEnd = false;
        unordered_set<string> visiting;
        
        //visited: visited node for previous levels
        //visiting: the nodes visit in current level
        
        while(levelSize-- > 0){
            string cur = q.front(); q.pop();
            //cout << cur << " : ";

            string nei = cur;
            
            for(int i = 0; i < cur.size(); ++i){
                char oldC = nei[i];
                for(char c = 'a'; c <= 'z'; ++c){
                    if(c == oldC) continue;
                    nei[i] = c;

                    if(words.find(nei) != words.end()){
                        if(visited_other.find(nei) != visited_other.end()){
                            //cout << "found end ";
                            foundEnd = true;
                        }

                        //if nei isn't in previous levels
                        if(visited.find(nei) == visited.end()){
                            /*
                            Here we don't mark "nei" as "visited",
                            because we want that "nei" can be visited by
                            multiple nodes in current level!!!
                            */
                            visiting.insert(nei);
                            q.push(nei);

                            if(!reversed){
                                graph[cur].insert(nei);
                            }else{
                                graph[nei].insert(cur);
                            }
                            //cout << nei << " ";
                        }
                    }

                }
                nei[i] = oldC;
            }
            //cout << endl;
        }
        
        //the nodes in visiting are actually visited in current level
        visited.insert(visiting.begin(), visiting.end());
        
        return foundEnd;
    };
    
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_map<string, unordered_set<string>> graph;
        int n = words.size();
        
        if(words.find(endWord) == words.end()) return vector<vector<string>>();
        
        //cout << "word: ";
        //for(const string& word : words){
        //    cout << word << " ";
        //}
        //cout << endl;
        
        bool foundEnd = false;
        queue<string> q1, q2;
        unordered_set<string> visited1, visited2;
        queue<string> qnext;
        bool reversed = false;
        
        q1.push(beginWord);
        q2.push(endWord);
        visited1.insert(beginWord);
        visited2.insert(endWord);
        
        while(!q1.empty() && !q2.empty() && !foundEnd){
            if(q1.size() < q2.size()){
                //cout << "forward: " << endl;
                foundEnd = visitLevel(words, graph, q1, visited1, visited2, false);
            }else{
                //cout << "backward: " << endl;
                foundEnd = visitLevel(words, graph, q2, visited2, visited1, true);
            }
        }
        
        //for(auto p : graph){
        //    cout << p.first << " -> ";
        //    for(const string& nei : p.second){
        //        cout << nei << " ";
        //    }
        //    cout << endl;
        //}
        
        vector<string> path = {beginWord};
        vector<vector<string>> paths;
        
        backtrack(beginWord, endWord, graph, path, paths);
        
        return paths;
    }
};
