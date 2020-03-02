//Runtime: 12 ms, faster than 72.49% of C++ online submissions for Construct Binary Tree from Preorder and Postorder Traversal.
//Memory Usage: 15 MB, less than 16.67% of C++ online submissions for Construct Binary Tree from Preorder and Postorder Traversal.
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
    TreeNode* constructFromPrePostR(vector<int>& pre, vector<int>& post, int preStart, int preEnd, int postStart, int postEnd) {
        // cout << "[" << preStart << ", " << preEnd << "]" << "[" << postStart << ", " << postEnd << "]" << endl;
        assert(pre[preStart] == post[postEnd]);
        TreeNode* root = new TreeNode(pre[preStart]);
        int N = preEnd - preStart + 1;
        
        if(N > 1){
            //pre[preStart+1]: left subtree's root
            int postLeftEnd = find(post.begin()+postStart, post.end()+postEnd+1, pre[preStart+1]) - post.begin();
            //left subtree's size: postLeftEnd - postStart + 1
            int leftSize = postLeftEnd - postStart + 1;
            int rightSize = N - leftSize - 1;
            // cout << "postLeftEnd: " << postLeftEnd << endl;
            // cout << "size: " << leftSize << ", " << rightSize << endl;
            if(leftSize >= 1){
                // cout << "left" << endl;
                root->left = constructFromPrePostR(pre, post, preStart+1, preStart+1+leftSize-1, postStart, postLeftEnd);
            }

            if(rightSize >= 1){
                // cout << "right" << endl;
                // cout << "preStart: " << preStart << ", leftSize: " << leftSize << ", preEnd: " << preEnd << ", postLeftEnd: " << postLeftEnd << ", postEnd: " << postEnd << endl;
                root->right = constructFromPrePostR(pre, post, preStart+1+leftSize, preEnd, postLeftEnd+1, postEnd-1);
            }
        }
        
        return root;
    }
    
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        int N = pre.size();
        assert(pre[0] == post[N-1]);
        TreeNode* root = new TreeNode(pre[0]);
        
        if(N > 1){
            int postLeftEnd = find(post.begin(), post.end(), pre[1]) - post.begin();
            int leftSize = postLeftEnd + 1;
            int rightSize = N - leftSize - 1;
            // cout << "postLeftEnd: " << postLeftEnd << endl;
            // cout << "postLeftEnd: " << find(post.begin(), post.end(), 2) - post.begin() << endl;
            // cout << "postLeftEnd: " << (find(post.begin(), post.end(), 2) == post.end()) << endl;
            // cout << "post: " << post.size() << endl;
            //left subtree's size is postSplit+1
            //preEnd = 1 + leftsubtree's size(0-based)
            
            if(leftSize){
                // cout << "left" << endl;
                root->left = constructFromPrePostR(pre, post, 1, 1+leftSize-1, 0, postLeftEnd);
            }
            
            if(rightSize){
                //preStart: next element of preEnd in left subtree
                // cout << "right" << endl;
                root->right = constructFromPrePostR(pre, post, leftSize+1, N-1, postLeftEnd+1, N-2);
            }
        }
        
        return root;
    }
};

//Approach 2: Recursion (Space Saving Variant)
//time: O(N^2), space: O(N)
//Runtime: 12 ms, faster than 72.49% of C++ online submissions for Construct Binary Tree from Preorder and Postorder Traversal.
//Memory Usage: 15.1 MB, less than 16.67% of C++ online submissions for Construct Binary Tree from Preorder and Postorder Traversal.

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
    vector<int> pre, post;
    
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) {
        this->pre = pre;
        this->post = post;
        return make(0, 0, pre.size());
    }
    
    TreeNode* make(int preStart, int postStart, int N){
        if(N == 0) return NULL;
        TreeNode* root = new TreeNode(pre[preStart]);
        if(N == 1) return root;
        
        //left subtree's size
        int L = find(post.begin()+postStart, post.begin()+postStart+N, pre[preStart+1]) - (post.begin()+postStart)+1;
        
        root->left = make(preStart+1, postStart, L);
        root->right = make(preStart+1+L, postStart+L,N-L-1);
        return root;
    }
};
