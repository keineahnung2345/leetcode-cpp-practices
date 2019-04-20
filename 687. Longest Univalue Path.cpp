//Runtime: 196 ms, faster than 9.46% of C++ online submissions for Longest Univalue Path.
//Memory Usage: 50.5 MB, less than 16.07% of C++ online submissions for Longest Univalue Path.

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
    struct paths {
        int a; //length of path can be elongated
        int b; //length of path can't be elongated
        paths() {};
        paths(int init_a, int init_b) {
            a = init_a;
            b = init_b;
        }
    };
    
    paths rLongestUnivaluePath(TreeNode* root){
        if(root==NULL) return paths(0, 0);
        //leaf node
        if(root->left==NULL && root->right==NULL) return paths(0, 0);
        
        paths pl = rLongestUnivaluePath(root->left);
        paths pr = rLongestUnivaluePath(root->right);
        
        //only one side
        if(root->left!=NULL && root->right==NULL){
            if(root->val == root->left->val){
                return paths(pl.a+1, pl.b);
            }else{
                return paths(0, max(pl.a, pl.b));
            }
        }
        if(root->right!=NULL && root->left==NULL){
            if(root->val == root->right->val){
                return paths(pr.a+1, pr.b);
            }else{
                return paths(0, max(pr.a, pr.b));
            }
        }
        if(root->val == root->left->val && root->val == root->right->val){
            return paths(max(pl.a, pr.a)+1, max(pl.a+pr.a+2, max(pl.b, pr.b)));
        }else if(root->val == root->left->val){
            //need to consider the other side when calculating b!
            return paths(pl.a+1, max(max(pr.a, pr.b), pl.b));
        }else if(root->val == root->right->val){
            return paths(pr.a+1, max(max(pl.a, pl.b), pr.b));
        }
        // cout << pl.a << " " << pl.b << " " << pr.a << " "  << pr.b << endl; 
        return paths(0, max(max(pl.a, pl.b), max(pr.a, pr.b)));
    }
    
    int longestUnivaluePath(TreeNode* root) {
        paths p = rLongestUnivaluePath(root);
        return max(p.a, p.b);
    }
};

//solution: recursion
//Runtime: 140 ms, faster than 86.08% of C++ online submissions for Longest Univalue Path.
//Memory Usage: 49.5 MB, less than 100.00% of C++ online submissions for Longest Univalue Path.
//Time Complexity: O(N), where N is the number of nodes in the tree. We process every node once.
//Space Complexity: O(H), where H is the height of the tree. Our recursive call stack could be up to H layers deep.

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
    int ans;
    int arrowLength(TreeNode* node){
        if(!node) return 0;
        int l = arrowLength(node->left);
        int r = arrowLength(node->right);
        int arrL = 0, arrR = 0;
        //if the two conditions do not hold,
        //it means the path breaks here,
        //so arrL and arrR will be 0
        if(node->left && node->left->val == node->val){
            //arrL will remain 0 if the condition do not hold
            arrL = l+1;
        }
        if(node->right && node->right->val == node->val){
            arrR = r+1;
        }
        //arrL + arrR is the length of univaluepath of current node
        //ans stores the max of them
        ans = max(ans, arrL + arrR);
        //the length of uni direction path
        return max(arrL, arrR);
    }
    
    int longestUnivaluePath(TreeNode* root) {
        ans = 0;
        arrowLength(root);
        return ans;
    }
};
