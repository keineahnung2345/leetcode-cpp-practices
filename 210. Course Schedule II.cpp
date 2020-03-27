//Approach 2: Using Node Indegree
//Runtime: 24 ms, faster than 81.55% of C++ online submissions for Course Schedule II.
//Memory Usage: 10.9 MB, less than 100.00% of C++ online submissions for Course Schedule II.
//time: O(N), space: O(N)
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> incomingEdgeCount(numCourses, 0);
        vector<vector<int>> edges(numCourses);
        
        for(vector<int>& pre : prerequisites){
            incomingEdgeCount[pre[0]]++;
            edges[pre[1]].push_back(pre[0]);
        }
        
        queue<int> qNoIncomingEdges;
        for(int i = 0; i < numCourses; i++){
            if(incomingEdgeCount[i] == 0){
                qNoIncomingEdges.push(i);
            }
        }
        
        int remainingEdgeCount = prerequisites.size();
        vector<int> ans;
        while(!qNoIncomingEdges.empty()){
            int cur = qNoIncomingEdges.front(); qNoIncomingEdges.pop();
            ans.push_back(cur);
            for(int nei : edges[cur]){
                remainingEdgeCount--;
                if(--incomingEdgeCount[nei] == 0){
                    qNoIncomingEdges.push(nei);
                }
            }
        }
        
        if(remainingEdgeCount != 0) ans.clear();
        
        return ans;
    }
};

//Approach 1: Using Depth First Search
//Runtime: 36 ms, faster than 23.25% of C++ online submissions for Course Schedule II.
//Memory Usage: 13 MB, less than 100.00% of C++ online submissions for Course Schedule II.
//time: O(N), space: O(N)
enum class Color{
    WHITE, GRAY, BLACK
};

class Solution {
public:
    bool isCyclic;
    unordered_map<int, Color> color;
    unordered_map<int, vector<int>> adjList;
    vector<int> topologicalOrder;
    
    void init(int numCourses){
        this->isCyclic = false;
        
        for(int i = 0; i < numCourses; i++){
            this->color[i]= Color::WHITE;
        }
    }
    
    void dfs(int node){
        if(this->isCyclic) return;
        
        this->color[node] = Color::GRAY;
        
        for(int nei : this->adjList[node]){
            if(this->color[nei] == Color::WHITE){
                this->dfs(nei);
            }else if(this->color[nei] == Color::GRAY){
                this->isCyclic = true;
            }
        }
        
        this->color[node] = Color::BLACK;
        this->topologicalOrder.push_back(node);
    }
    
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        this->init(numCourses);
        
        for(vector<int>& pre : prerequisites){
            adjList[pre[1]].push_back(pre[0]);
        }
        
        for(int i = 0; i < numCourses; i++){
            if(this->color[i] == Color::WHITE){
                this->dfs(i);
            }
        }
        
        vector<int> order;
        if(!this->isCyclic){
            order = vector<int>(numCourses, 0);
            for(int i = 0; i < numCourses; i++){
                order[i] = this->topologicalOrder[numCourses-i-1];
            }
        }
        
        return order;
    }
};
