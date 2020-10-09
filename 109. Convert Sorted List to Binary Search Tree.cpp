//recursion
//Runtime: 40 ms, faster than 46.56% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//Memory Usage: 36.1 MB, less than 5.43% of C++ online submissions for Convert Sorted List to Binary Search Tree.
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
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
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        
        ListNode* dummy = new ListNode(-1);
        dummy->next = head;
        
        ListNode *slow = dummy, *fast = dummy;
        ListNode *preslow;
        
        while(fast && fast->next){
            preslow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        cout << preslow->val << ", " << slow->val << endl;
        
        //now slow is the midpoint(for odd-length list) or 
        // the node before midpoint(for even-length list)
        //preslow is the previous node of slow
        
        TreeNode* root = new TreeNode(slow->val);
        
        //cut the list's former part with the processed "slow"
        preslow->next = nullptr;
        //when slow==head, this node doesn't have left subtree
        root->left = (slow == head) ? nullptr : sortedListToBST(head);
        
        root->right = sortedListToBST(slow->next);
        
        return root;
    }
};

//recursion, without dummy
//Runtime: 40 ms, faster than 46.56% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//Memory Usage: 32.9 MB, less than 5.43% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//time: O(NlogN)
//in ith recursion(i starts from 1), we use (N/pow(2,i)) times to find middle point, do it pow(2,i-1) times
//and we will do that for logN recursions, so it sums up to NlogN/2, which is O(NlogN)
//space: O(logN)
//recursion space used by "balanced" tree
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        
        ListNode *slow = head, *fast = head;
        ListNode *preslow = nullptr;
        
        while(fast && fast->next){
            preslow = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        
        // cout << (preslow ? preslow->val : -1) << ", " << slow->val << endl;
        
        //now slow is the midpoint(for odd-length list) or 
        // the node after midpoint(for even-length list)
        //preslow is the previous node of slow
        
        TreeNode* root = new TreeNode(slow->val);
        
        //cut the list's former part with the processed "slow"
        //if slow is head, it means the list's length is 1,
        //and preslow is nullptr
        if(slow == head){
            return root;
        }
        
        //if slow != head, it has left subtree
        preslow->next = nullptr;
        
        root->left = sortedListToBST(head);
        
        root->right = sortedListToBST(slow->next);
        
        return root;
    }
};

//Approach 2: Recursion + Conversion to Array
//use more space to reduce time complexity
//Runtime: 40 ms, faster than 46.56% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//Memory Usage: 33.4 MB, less than 5.43% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//time: O(N), space: O(N)
class Solution {
public:
    TreeNode* sortedVectorToBST(vector<int>& arr, int start, int end){
        if(start > end) return nullptr;
        
        int mid = (start+end)>>1;
        TreeNode* root = new TreeNode(arr[mid]);
        
        root->left = sortedVectorToBST(arr, start, mid-1);
        root->right = sortedVectorToBST(arr, mid+1, end);
        
        return root;
    }
    
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> arr;
        
        while(head){
            arr.push_back(head->val);
            head = head->next;
        }
        
        int n = arr.size();
        
        return sortedVectorToBST(arr, 0, n-1);
    }
};

//Approach 3: Inorder Simulation
//Runtime: 40 ms, faster than 46.56% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//Memory Usage: 33.1 MB, less than 5.43% of C++ online submissions for Convert Sorted List to Binary Search Tree.
//time: O(N), space: O(logN)
class Solution {
public:
    ListNode* head;
    
    TreeNode* convertListToBST(int start, int end){
        if(start > end){
            // cout << "return nullptr" << endl;
            return nullptr;
        }
        
        int mid = (start+end) >> 1;
        
        TreeNode* left = convertListToBST(start, mid-1);
        
        // cout << start << ", " << end << ", " << this->head->val << endl;
        TreeNode* root = new TreeNode(this->head->val);
        root->left = left;
        
        this->head = this->head->next;
        
        root->right = convertListToBST(mid+1, end);
        
        // cout << "return " << root->val << endl;
        return root;
    }
    
    TreeNode* sortedListToBST(ListNode* head) {
        if(!head) return nullptr;
        
        int n = 0;
        
        ListNode* cur = head;
        
        while(cur){
            ++n;
            cur = cur->next;
        }
        
        this->head = head;
        
        return convertListToBST(0, n-1);
    }
};
