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
