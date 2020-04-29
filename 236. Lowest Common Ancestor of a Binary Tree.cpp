//Runtime: 40 ms, faster than 12.32% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 15.9 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int pLevel = -1, qLevel = -1;
        
        queue<TreeNode*> bfsq;
        TreeNode* cur;
        int levelCount = 0;
        int level = 0;
        map<TreeNode*, TreeNode*> parents;
        
        bfsq.push(root);
        parents[root] = nullptr;
        levelCount++;
        
        while(!bfsq.empty()){
            // cout << level << " " << levelCount << endl;
            while(levelCount-- > 0){
                cur = bfsq.front(); bfsq.pop();
                if(cur == p){
                    pLevel = level;
                }
                if(cur == q){
                    qLevel = level;
                }
                if(cur->left){
                    bfsq.push(cur->left);
                    parents[cur->left] = cur;
                }
                if(cur->right){
                    bfsq.push(cur->right);
                    parents[cur->right] = cur;
                }
            }
            level++;
            levelCount = bfsq.size();
        }
        
        //lift the lower one to the same level
        while(qLevel > pLevel){
            qLevel--;
            q = parents[q];
        }
        
        while(pLevel > qLevel){
            pLevel--;
            p = parents[p];
        }
        
        //now p and q are at same level
        if(p == q) return p;
        
        while(p != q){
            p = parents[p];
            q = parents[q];
        }
        
        // cout << pLevel << " " << qLevel << endl;
        
        return p;
    }
};

//Approach 1: Recursive Approach
//Runtime: 20 ms, faster than 79.55% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 14.3 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//time: O(N), space: O(N)
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
    TreeNode *p, *q, *ans;
    
    bool recurseTree(TreeNode* cur){
        if(cur == nullptr) return false;
        
        int mid = (int)(cur == p || cur == q);
        int left = (int)recurseTree(cur->left);
        int right = (int)recurseTree(cur->right);
        
        /*
        mid & left : current node is lca
        mid & right: current node is lca
        left& right: their parent, which is current node, is lca
        */
        if(mid + left + right >= 2){
            ans = cur;
        }
        
        //if itself or one of its children is p or q's ancestor
        return mid + left + right > 0;
    };
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        this->p = p;
        this->q = q;
        recurseTree(root);
        return ans;
    }
};

//Approach 2: Iterative using parent pointers
//Runtime: 44 ms, faster than 10.21% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 17.8 MB, less than 20.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//time: O(N), space: O(N)
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, TreeNode*> parents;
        stack<TreeNode*> stk;
        TreeNode *cur;
        
        parents[root] = nullptr;
        stk.push(root);
        
        //either p or q is not visited
        while(parents.find(p) == parents.end() || parents.find(q) == parents.end()){
            cur = stk.top(); stk.pop();
            
            if(cur->left){
                parents[cur->left] = cur;
                stk.push(cur->left);
            }
            if(cur->right){
                parents[cur->right] = cur;
                stk.push(cur->right);
            }
        }
        
        //record all p's ancestors(including itself) into a set
        set<TreeNode*> pAncestors;
        while(p){
            pAncestors.insert(p);
            p = parents[p];
        }
        
        //find q's least ancestor which is also p's ancestor
        while(pAncestors.find(q) == pAncestors.end()){
            q = parents[q];
        }
        
        return q;
    }
};

//Approach 3: Iterative without parent pointers
//Runtime: 28 ms, faster than 19.72% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//Memory Usage: 15.1 MB, less than 100.00% of C++ online submissions for Lowest Common Ancestor of a Binary Tree.
//time: O(N), space: O(N)
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
enum class State{
    BP, //BOTH_PENDING
    LD, //LEFT_DONE
    BD //BOTH_DONE
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<pair<TreeNode*, State>> stk;
        
        stk.push(make_pair(root, State::BP));
        bool foundOne = false; //either found p or q
        TreeNode* LCA = nullptr;
        TreeNode *cur = nullptr, *child = nullptr;
        State curState;
        
        while(!stk.empty()){
            pair<TreeNode*, State> top = stk.top();
            cur = top.first;
            curState = top.second;
            
            if(curState != State::BD){
                if(curState == State::BP){
                    if(cur == p || cur == q){
                        if(foundOne){
                            //we have found the second
                            return LCA;
                        }else{
                            foundOne = true;
                            LCA = cur;
                        }
                    }

                    child = cur->left;
                }else{
                    child = cur->right;
                }
            
                //revise cur's state
                stk.pop();
                stk.push(make_pair(cur, (State)((int)curState+1)));

                if(child){
                    stk.push(make_pair(child, State::BP));
                }
            }else{
                TreeNode* tmp = stk.top().first;
                stk.pop();
                if(LCA == tmp && foundOne){
                    LCA = stk.top().first;
                }
            }
        }
        
        return nullptr;
    }
};
