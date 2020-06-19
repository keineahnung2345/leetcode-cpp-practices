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

//dp
//binary lifting
//https://leetcode.com/problems/kth-ancestor-of-a-tree-node/discuss/686362/JavaC%2B%2BPython-Binary-Lifting
//Runtime: 844 ms, faster than 71.18% of C++ online submissions for Kth Ancestor of a Tree Node.
//Memory Usage: 107.3 MB, less than 100.00% of C++ online submissions for Kth Ancestor of a Tree Node.
//class TreeAncestor {
public:
    int maxJump;
    vector<vector<int>> jump;
    
    TreeAncestor(int n, vector<int>& parent) {
        /*
        for a tree of n nodes,
        we can jump at most "maxJump" times
        */
        maxJump = ceil(log(n));
        //from 0 to maxJump
        jump = vector<vector<int>>(maxJump+1, vector<int>(n));
        
        //jump 2^0 steps upward
        jump[0] = parent;
        
        for(int j = 1; j <= maxJump; j++){
            for(int node = 0; node < n; node++){
                //from node, jump 2^(j-1) steps upward
                int halfway = jump[j-1][node];
                jump[j][node] = (halfway == -1) ? -1 : jump[j-1][halfway];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        int j = maxJump;
        while(node != -1 && k > 0){
            if(k >= (1 << j)){
                node = jump[j][node];
                k -= (1 << j);
            }else{
                j--;
            }
        }
        /*
        jump out the loop when either node doesn't exist or 
        we have jump all k steps upward
        */
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

//dp + bit manipulation
//https://leetcode.com/problems/kth-ancestor-of-a-tree-node/discuss/686362/JavaC%2B%2BPython-Binary-Lifting
//fails when set "maxJump = ceil(log(n));" (log is different from log2!!)
//Runtime: 556 ms, faster than 90.22% of C++ online submissions for Kth Ancestor of a Tree Node.
//Memory Usage: 110.3 MB, less than 100.00% of C++ online submissions for Kth Ancestor of a Tree Node.
class TreeAncestor {
public:
    int maxJump;
    vector<vector<int>> jump;
    
    TreeAncestor(int n, vector<int>& parent) {
        /*
        for a tree of n nodes,
        we can jump at most "maxJump" times
        */
        //notice the difference between log(it's natural log!) and log2(2-based)!!!
        maxJump = ceil(log2(n))+1;
        // maxJump = 20;
        //from 0 to maxJump
        jump = vector<vector<int>>(maxJump+1, vector<int>(n));
        
        //jump 2^0 steps upward
        jump[0] = parent;
        
        for(int j = 1; j <= maxJump; j++){
            for(int node = 0; node < n; node++){
                //from node, jump 2^(j-1) steps upward
                int halfway = jump[j-1][node];
                jump[j][node] = (halfway == -1) ? -1 : jump[j-1][halfway];
            }
        }
    }
    
    int getKthAncestor(int node, int k) {
        // cout << "k: " << k << ", j: ";
        for(int j = 0; j <= maxJump; j++){
            if(k & (1 << j)){
                /*
                view "k" as a bitset,
                and we are decompose "k" into the powers of 2
                when "k"'s "j"th bit is set,
                that means one of the component of k is 2^j,
                so we jump up 2^j steps upward
                */
                // cout << j << " ";
                node = jump[j][node];
                if(node == -1) break;
            }
        }
        // cout << endl;
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */
