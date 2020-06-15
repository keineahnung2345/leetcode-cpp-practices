//TLE
//9 / 10 test cases passed.
// class Node{
// public:
//     Node* parent;
//     vector<Node*> children;
//     int val;
    
//     Node(int v){
//         val = v;
//     }
// };

class TreeAncestor {
public:
    // vector<vector<int>> paths;
    // Node* root;
    // vector<Node*> nodes;
    vector<int> parent;
    
    TreeAncestor(int n, vector<int>& parent) {
        this->parent = parent;
//         for(int i = 0; i < parent.size(); i++){
//             nodes.push_back(new Node(i));
//         }
        
//         for(int i = 0; i < parent.size(); i++){
//             if(parent[i] == -1){
//                 root = nodes[i];
//             }else{
//                 Node* pnode = nodes[parent[i]];
//                 pnode->children.push_back(nodes[i]);
//             }
//         }
    }
    
    int getKthAncestor(int node, int k) {
        while(k-- >0 && node != -1){
            node = parent[node];
        }
        
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
