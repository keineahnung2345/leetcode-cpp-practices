//BFS
//Runtime: 12 ms, faster than 64.56% of C++ online submissions for Clone Graph.
//Memory Usage: 8.9 MB, less than 98.02% of C++ online submissions for Clone Graph.
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return node;
        
        queue<Node*> q;
        unordered_map<int, vector<int>> adjList;
        
        q.push(node);
        //mark "node" as existing in graph
        //also mark it as visited!
        adjList[node->val] = {};
        
        while(!q.empty()){
            Node* cur = q.front(); q.pop();
            // cout << "visit " << cur->val << endl;
            
            for(Node* nei : cur->neighbors){
                //here we actually build the graph
                adjList[cur->val].push_back(nei->val);
                if(adjList.find(nei->val) != adjList.end()) continue;
                //mark nei as visited!
                adjList[nei->val] = {};
                q.push(nei);
            }
        }
        
        int count = adjList.size();
        
        // cout << "count: " << count << endl;
        
        //dummy node
        vector<Node*> newnodes = {new Node(0)};
        
        for(int i = 1; i <= count; ++i){
            newnodes.push_back(new Node(i));
        }
        
        for(int i = 1; i <= count; ++i){
            for(const int& nei : adjList[i]){
                // cout << i << " -> " << nei << endl;
                newnodes[i]->neighbors.push_back(newnodes[nei]);
            }
        }
        
        return newnodes[1];
    }
};

//BFS, one pass
//https://leetcode.com/problems/clone-graph/discuss/42313/C%2B%2B-BFSDFS
//Runtime: 8 ms, faster than 96.13% of C++ online submissions for Clone Graph.
//Memory Usage: 8.5 MB, less than 98.02% of C++ online submissions for Clone Graph.
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if(!node) return node;
        
        unordered_map<Node*, Node*> old2new;
        
        old2new[node] = new Node(node->val);
        
        queue<Node*> q;
        
        //visit the old graph
        q.push(node);
        
        while(!q.empty()){
            Node* cur = q.front(); q.pop();
            
            for(Node* nei : cur->neighbors){
                if(old2new.find(nei) != old2new.end()){
                    //create the edge
                    old2new[cur]->neighbors.push_back(old2new[nei]);
                    continue;
                }
                old2new[nei] = new Node(nei->val);
                //visit the old graph
                q.push(nei);
                //create the edge
                old2new[cur]->neighbors.push_back(old2new[nei]);
            }
        }
        
        return old2new[node];
    }
};

//DFS
//https://leetcode.com/problems/clone-graph/discuss/42313/C%2B%2B-BFSDFS
//Runtime: 8 ms, faster than 96.13% of C++ online submissions for Clone Graph.
//Memory Usage: 9 MB, less than 98.02% of C++ online submissions for Clone Graph.
class Solution {
public:
    unordered_map<Node*, Node*> old2new;
    
    Node* cloneGraph(Node* node) {
        if(!node) return node;
        
        //this node is already visited
        if(old2new.find(node) != old2new.end())
            return old2new[node];
        
        old2new[node] = new Node(node->val);
        
        for(Node* nei : node->neighbors){
            //build new node for "nei" and then connect them together
            old2new[node]->neighbors.push_back(cloneGraph(nei));
        }
        
        return old2new[node];
    }
};
