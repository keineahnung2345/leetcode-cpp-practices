//Runtime: 36 ms, faster than 69.49% of C++ online submissions for Delete Node in a BST.
//Memory Usage: 15.3 MB, less than 55.49% of C++ online submissions for Delete Node in a BST.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if(!root) return root;

        TreeNode *par = root, *cur = root;

        while(cur && cur->val != key){
            if(key < cur->val){
                par = cur;
                cur = cur->left;
            }else{
                //key > cur->val
                par = cur;
                cur = cur->right;
            }
        }

        //cannot find key in tree
        if(!cur) return root;
        
        if(!cur->left && !cur->right){
            if(cur == root) return nullptr;
            if(par->left == cur) par->left = nullptr;
            else par->right = nullptr;
        }else if(cur->left){
            //predecessor of deleted node
            TreeNode *pred = cur->left;
            //parent of predecessor
            par = pred;
            while(pred->right){
                par = pred;
                pred = pred->right;
            }
            cur->val = pred->val;
            /*
            pred->right is always empty,
            when predecessor is the left child of the node to be deleted,
            we move pred's left subtree one level up
            (set left subtree's parent as cur),
            if not, pred is then it's parent's right child,
            here we also move pred's left subtree one level up
            (set left subtree's parent as par)
            */
            if(cur->left == pred) cur->left = pred->left; 
            else par->right = pred->left;
        }else{
            TreeNode *succ = cur->right;
            par = succ;
            while(succ->left){
                par = succ;
                succ = succ->left;
            }
            cur->val = succ->val;
            if(cur->right == succ) cur->right = succ->right; 
            else par->left = succ->right;
        }

        return root;
    }
};
