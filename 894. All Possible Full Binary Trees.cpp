/**
A full binary tree is a binary tree where each node has exactly 0 or 2 children.

Return a list of all possible full binary trees with N nodes.  Each element of the answer is the root node of one possible tree.

Each node of each tree in the answer must have node.val = 0.

You may return the final list of trees in any order.

Input: 7
Output: [[0,0,0,null,null,0,0,null,null,0,0],[0,0,0,null,null,0,0,0,0],[0,0,0,0,0,0,0],[0,0,0,0,0,null,null,null,null,0,0],[0,0,0,0,0,null,null,0,0]]
Explanation:
Note:

1 <= N <= 20
**/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//Your runtime beats 36.47 % of cpp submissions.
class Solution {
public:
    vector<TreeNode*> allPossibleFBT(int N) {
        if(N==1){
            vector<TreeNode*> ans;
            TreeNode* node = new TreeNode(0);
            ans.push_back(node);
            return ans;
        }else if(N%2==0){
            vector<TreeNode*> ans;
            return ans;
        }else{
            vector<TreeNode*> ans;
            
            for(int lnum=1; lnum<=N-1-1; lnum+=2){
                int rnum = N-1-lnum;
                vector<TreeNode*> ltree = allPossibleFBT(lnum);
                vector<TreeNode*> rtree = allPossibleFBT(rnum);
                for(int ltreeix = 0; ltreeix < ltree.size(); ltreeix++){
                    for(int rtreeix = 0; rtreeix < rtree.size(); rtreeix++){
                        TreeNode* node = new TreeNode(0);
                        node->left = ltree[ltreeix];
                        node->right = rtree[rtreeix];
                        ans.push_back(node);
                    }
                }
            }
            return ans;
        }
    }
};

/**
Approach 1: Recursion
Intuition and Algorithm

Let \text{FBT}(N)FBT(N) be the list of all possible full binary trees with NN nodes.

Every full binary tree TT with 3 or more nodes, has 2 children at its root. Each of those children left and right are themselves full binary trees.

Thus, for N \geq 3N≥3, we can formulate the recursion: \text{FBT}(N) =FBT(N)= [All trees with left child from \text{FBT}(x)FBT(x) and right child from \text{FBT}(N-1-x)FBT(N−1−x), for all xx].

Also, by a simple counting argument, there are no full binary trees with a positive, even number of nodes.

Finally, we should cache previous results of the function \text{FBT}FBT so that we don't have to recalculate them in our recursion.
**/

//Your runtime beats 36.47 % of cpp submissions.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    map<int, vector<TreeNode*> > size2tree;
    
    vector<TreeNode*> allPossibleFBT(int N) {
        if(size2tree.find(N)!=size2tree.end()){
            return size2tree.at(N);
        }else{
            vector<TreeNode*> ans;
            if(N==1){
                TreeNode* node = new TreeNode(0);
                ans.push_back(node);
            }else if(N%2==1){
                for(int lnum=1; lnum<=N-1-1; lnum+=2){
                    int rnum = N-1-lnum;
                    vector<TreeNode*> ltree = allPossibleFBT(lnum);
                    vector<TreeNode*> rtree = allPossibleFBT(rnum);
                    for(int ltreeix = 0; ltreeix < ltree.size(); ltreeix++){
                        for(int rtreeix = 0; rtreeix < rtree.size(); rtreeix++){
                            TreeNode* node = new TreeNode(0);
                            node->left = ltree[ltreeix];
                            node->right = rtree[rtreeix];
                            ans.push_back(node);
                        }
                    }
                }
            }
            size2tree.insert(make_pair(N, ans));
            return ans;
        }
    }
};

/**
Complexity Analysis

Time Complexity: O(2^N). For odd N, let N = 2k + 1. Then, |FBT(N)| = C_k
, the k-th catalan number; and \sum\limits_{k < N/2}C_
  (the complexity involved in computing intermediate results required) is bounded by O(2^N).
However, the proof is beyond the scope of this article.

Space Complexity: O(2^N). 
**/
