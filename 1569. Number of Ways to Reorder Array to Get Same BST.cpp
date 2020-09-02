//https://stackoverflow.com/questions/17119116/how-many-ways-can-you-insert-a-series-of-values-into-a-bst-to-form-a-specific-tr
//Runtime: 128 ms, faster than 80.00% of C++ online submissions for Number of Ways to Reorder Array to Get Same BST.
//Memory Usage: 28.5 MB, less than 100.00% of C++ online submissions for Number of Ways to Reorder Array to Get Same BST.
class Node{
public:
    Node *left, *right;
    int val;
    
    Node(int v) : val(v), left(nullptr), right(nullptr){};
};

class BST{
public:
    Node* root;
    
    void insert(int v, Node* node = nullptr){
        if(root == nullptr){
            root = new Node(v);
        }else{
            if(node == nullptr)
                node = root;
            if(v < node->val){
                if(node->left == nullptr){
                    // cout << node->val << " l-> " << v << endl;
                    node->left = new Node(v);
                }else{
                    // cout << node->left->val << " l-> " << v << endl;
                    insert(v, node->left);
                }
            }else{
                if(node->right == nullptr){
                    // cout << node->val << " r-> " << v << endl;
                    node->right = new Node(v);
                }else{
                    // cout << node->right->val << " r-> " << v << endl;
                    insert(v, node->right);
                }
            }
        }
    }
};


class Solution {
public:
    int MOD = 1e9+7;
    unordered_map<Node*, int> counter;
    
    //fill "counter"
    int dfs(Node* node){
        if(node == nullptr) return 0;
        counter[node] = dfs(node->left) + dfs(node->right) + 1;
        return counter[node];
    };

    // Returns factorial of n 
    int fact(int n) 
    { 
        long long res = 1; 
        for (int i = 2; i <= n; i++) 
            res = (res * i) % MOD;
        return res; 
    };
    
    int power(int x, unsigned int y){ 
        if (y == 0) 
            return 1; 
        long long p = power(x, y/2) % MOD; 
        p = (p * p) % MOD; 

        return (y%2 == 0)? p : (x * p) % MOD; 
    };

    // Function to return gcd of a and b 
    int gcd(int a, int b){ 
        if (a == 0) 
            return b; 
        return gcd(b%a, a); 
    };

    // Function to find modular inverse of a under modulo m 
    // Assumption: m is prime 
    int modInverse(int a){ 
        int g = gcd(a, MOD); 
        if (g != 1){
            //Fermat's little theorem only works only when m is prime!
            return -1;
        }else{ 
            // If a and m are relatively prime, then modulo inverse 
            // is a^(m-2) mod m 
            /*
            From Fermat's little theorem,
            when a is not divisible by p,
            a^(p-1) mod m = 1
            here we choose p as m,
            so a^(m-1) mod m = 1
            this is equal to saying that
            a * a^(m-2) mod m = 1
            so we can say that a^(m-2) mod m is the inverse of a
            */
            return power(a, MOD-2);
        } 
    };
  
    int nCr(int n, int r) 
    { 
        long long fr_inverse = modInverse(fact(r));
        long long fnr_inverse = modInverse(fact(n - r));
        return ((fact(n) * fr_inverse) % MOD * fnr_inverse) % MOD; 
    };
    
    int countInsertionOrderings(Node* node) {
        if(!node) return 1;
        
       int m = counter[node->left];
       int n = counter[node->right];
       
        //number of ways to permute sequence of L and sequence of R
        long long a = nCr(m + n, n);
        //how many possible permutations of sequence L
        long long b = countInsertionOrderings(node->left);
        //how many possible permutations of sequence R
        long long c = countInsertionOrderings(node->right);
        
        return (((a*b) % MOD) * c) % MOD;
    }
    
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        
        BST* bst = new BST();
        
        for(int i = 0; i < n; ++i){
            bst->insert(nums[i]);
        }
        
        dfs(bst->root);
        
        //-1: deduce one, the original way to construct binary tree
        return countInsertionOrderings(bst->root) - 1;
    }
};

//use pascal triangle to calculate combination count
//https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/discuss/819369/C%2B%2B-Just-using-recursion-very-Clean-and-Easy-to-understand-O(n2)
//https://www.geeksforgeeks.org/calculate-ncr-using-pascals-triangle/
//Runtime: 376 ms, faster than 37.46% of C++ online submissions for Number of Ways to Reorder Array to Get Same BST.
//Memory Usage: 105.7 MB, less than 38.77% of C++ online submissions for Number of Ways to Reorder Array to Get Same BST.
class Solution {
public:
    long long MOD = 1e9+7;
    vector<vector<int>> pascal;
    
    void build_pascal(int max_num){
        pascal = vector<vector<int>>(max_num+1);
        
        for(int n = 0; n <= max_num; ++n){
            //we need nC0 to nCn
            pascal[n] = vector<int>(n+1);
        	//cout << "pascal[" << n << "]" << endl;
            
            /*
            to calculate pascal[n][n], 
            it will use pascal[n-1][n], which doesn't exist,
            so here we treat pascal[n][n] as a special case
            and do not calculate it in the loop
            */
            pascal[n][0] = pascal[n][n] = 1;
            for(int r = 1; r < n; ++r){
                pascal[n][r] = (pascal[n-1][r-1] + pascal[n-1][r]) % MOD;
            }
        }
    }
    
    int dfs(vector<int>& nums){
        int n = nums.size();
        if(n == 0) return 1;
        
        vector<int> left, right;
        
        //i starts from 1: exclude nums[0], which is root
        for(int i = 1; i < n; ++i){
            if(nums[i] < nums[0]) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }
        
        long long left_res = dfs(left);
        long long right_res = dfs(right);
        
        //(n-1)C(left.size()): choose from n-1 elements, excluding the root
        return ((pascal[n-1][left.size()] * left_res) % MOD * right_res) % MOD;
    }
    
    int numOfWays(vector<int>& nums) {
        int n = nums.size();
        build_pascal(n);
        //cout << "table built" << endl;
        
        return dfs(nums)-1;
    }
};
