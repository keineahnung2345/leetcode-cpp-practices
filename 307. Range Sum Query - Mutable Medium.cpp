//Runtime: 516 ms, faster than 5.03% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.5 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
class NumArray {
public:
    vector<int> nums;
    vector<int> sum;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        this->sum = vector<int>(nums.size(), 0);
        for(int i = 0; i < nums.size(); i++){
            sum[i] = ((i-1>=0)?sum[i-1]:0) + nums[i];
        }
    }
    
    void update(int i, int val) {
        for(int cur = i; cur < sum.size(); cur++){
            sum[cur] += (val - nums[i]);
        }
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        return sum[j] - ((i-1>=0)?sum[i-1]:0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
 
//Approach 2: Sqrt Decomposition
//Runtime: 52 ms, faster than 38.63% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.6 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//time: preprocessing - O(n), range sum query - O(sqrt(n)), update query - O(1)
//space: O(sqrt(n))
class NumArray {
public:
    vector<int> blocks;
    vector<int> nums;
    int len;
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        /*
        9 -> 3
        10 -> 4
        */
        if(nums.size() == 0){
            this->len = 0;
        }else{
            this->len = ceil(nums.size()/sqrt(nums.size()));
        }
        this->blocks = vector<int>(len, 0);
        for(int i = 0; i < nums.size(); i++){
            blocks[i/len] += nums[i];
        }
    }
    
    void update(int i, int val) {
        int blockId = i/len;
        blocks[blockId] += (val - nums[i]);
        nums[i] = val;
    }
    
    int sumRange(int i, int j) {
        int sum = 0;
        
        int startBlock = i/len, endBlock = j/len;
        
        if(startBlock == endBlock){
            for(int k = i; k <= j; k++){
                sum += nums[k];
            }
        }else{
            /*
            startBlock+1: the next block's id
            (startBlock+1)*len: the next block's start position
            (startBlock+1)*len-1: the current block's end position
            */
            for(int k = i; k <= (startBlock+1)*len -1; k++){
                sum += nums[k];
            }
            for(int k = startBlock+1; k <= endBlock-1; k++){
                sum += blocks[k];
            }
            for(int k = endBlock*len; k <= j; k++){
                sum += nums[k];
            }
        }
        
        return sum;
    }
};

//Approach 3: Segment Tree, iterative version
//tree[0] is not used in this implementation, only tree[1...2n-1] are meaningful
//Runtime: 44 ms, faster than 50.75% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.7 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//Build segment tree - time O(n), space O(n)
//Update segment tree - time O(logn), space O(1)
//Range Sum Query - time O(logn), space O(1)
class NumArray {
public:
    vector<int> tree;
    int n;
    
    NumArray(vector<int>& nums) {
        if(nums.size() > 0){
            n = nums.size();
            buildTree(nums);
        }
    }
    
    void buildTree(vector<int>& nums){
        tree = vector<int>(n*2);
        //tree[n ... 2n-1] = nums[0 ... n-1]
        for(int i = n, j = 0; i < n*2; i++, j++){
            tree[i] = nums[j];
        }
        /*
        tree[n-1] = tree[2n-2] + tree[2n-1]
        if n = 8
        tree[7] = tree[14] + tree[15]
        tree[6] = tree[12] + tree[13]
        tree[5] = tree[10] + tree[11]
        tree[4] = tree[8] + tree[9]
        
        tree[3] = tree[6] + tree[7]
        tree[2] = tree[4] + tree[5]
        
        tree[1] = tree[2] + tree[3]
        
        if n = 3
        tree[2] = tree[4] + tree[5]
        tree[1] = tree[2] + tree[3] //total sum of leaves
        */
        //note that tree[0] is meaningless
        for(int i = n-1; i > 0; i--){
            tree[i] = tree[i*2] + tree[i*2+1];
        }
    };
    
    void update(int i, int val) {
        //recall that the leaf node takes tree[n ... 2n-1]
        i += n;
        tree[i] = val;
        //note that tree[0] is meaningless
        while(i > 0){
            int left = i;
            int right = i;
            if(i % 2 == 0){
                //it's left ndoe
                right = i+1;
            }else{
                //it's right node
                left = i-1;
            }
            tree[i/2] = tree[left] + tree[right];
            i /= 2;
        }
    }
    
    int sumRange(int i, int j){
        //recall that the leaf node takes tree[n ... 2n-1]
        i += n;
        j += n;
        
        int sum = 0;
        
        while(i <= j){
            // cout << "[" << i << ", " << j << "]" << endl;
            if(i % 2 == 1){
                /*
                if i is right child of its parent,
                then we cannot use its parent's value
                */
                // cout << "l: " << i << endl;
                sum += tree[i];
                /*
                we will go to its right neighbor, 
                and then go up to its parent
                */
                i++;
            }
            if(j % 2 == 0){
                /*
                if r is left child of its parent,
                then we cannot use its parent's value
                */
                // cout << "r: " << j << endl;
                sum += tree[j];
                /*
                we will go to its left neighbor, 
                and then go up to its parent
                */
                j--;
            }
            i /= 2;
            j /= 2;
        }
        
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

//Segment tree, recursive version
//https://leetcode.com/articles/a-recursive-approach-to-segment-trees-range-sum-queries-lazy-propagation/
//Runtime: 44 ms, faster than 50.75% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 17 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
//Build segment tree - time O(n), space O(n)
//Update segment tree - time O(logn), space O(1)
//Range Sum Query - time O(logn), space O(1)
class NumArray {
public:
    vector<int> tree;
    int n;
    
    int merge(int a, int b){
        return a+b;
    }
    
    void buildSegTree(vector<int>& arr, int treeIndex, int lo, int hi){
        if(lo == hi){
            tree[treeIndex] = arr[lo];
            return;
        }
        
        int mid = (lo + hi)/2;
        buildSegTree(arr, treeIndex*2+1, lo, mid);
        buildSegTree(arr, treeIndex*2+2, mid+1, hi);
        
        tree[treeIndex] = merge(tree[treeIndex*2+1], tree[treeIndex*2+2]);
    };
    
    int querySegTree(int treeIndex, int lo, int hi, int i, int j){
        // cout << "treeIndex: " << treeIndex << ", lo: " << lo << ", hi: " << hi << ", i: " << i << ", j: " << j << endl;
        //query for arr[i ... j]
        //we are currently looking at tree[lo ... hi]
        if(lo > j || hi < i){
            //the part we are looking has no intersection with arr[i...j]
            return 0;
        }
        
        if(i <= lo && hi <= j){
            //tree[treeIndex] is inside [i...j]
            return tree[treeIndex];
        }
        
        int mid = (lo+hi)/2;
        
        // cout << "mid: " << mid << endl;
        
        //when the query range falls into either left or right part of current subtree
        if(i > mid){
            // cout << "i > mid, go right" << endl;
            //the query range is completely in right subtree?
            return querySegTree(treeIndex*2+2, mid+1, hi, i, j);
        }else if(j <= mid){
            // cout << "j <= mid, go left" << endl;
            //the query range is completely in left subtree?
            return querySegTree(treeIndex*2+1, lo, mid, i, j);
        }
        
        //the query range cross the middle point of current subtree
        //divide and conquer
        // cout << "leftQuery" << endl;
        int leftQuery = querySegTree(treeIndex*2+1, lo, mid, i, mid);
        // cout << "rightQuery" << endl;
        int rightQuery = querySegTree(treeIndex*2+2, mid+1, hi, mid+1, j);
        
        return merge(leftQuery, rightQuery);
    };
    
    void updateValSegTree(int treeIndex, int lo, int hi, int arrayIndex, int val){
        // cout << "treeIndex: " << treeIndex << ", lo: " << lo << ", hi: " << hi << endl;
        if(lo == hi){
            tree[treeIndex] = val;
            return;
        }
        
        int mid = (lo + hi)/2;
        
        if(arrayIndex > mid){
            //find in right subtree
            updateValSegTree(treeIndex*2+2, mid+1, hi, arrayIndex, val);
        }else{
            //find in left subtree
            updateValSegTree(treeIndex*2+1, lo, mid, arrayIndex, val);
        }
        
        tree[treeIndex] = merge(tree[treeIndex*2+1], tree[treeIndex*2+2]);
    };
    
    NumArray(vector<int>& nums) {
        n = nums.size();
        if(n > 0){
            //A segment tree for an nn element range can be comfortably represented using an array of size is approximately 4∗n.
            tree = vector<int>(4*n, 0);
            buildSegTree(nums, 0, 0, n-1);
            // for(int i = 0; i < 4*n; i++){
            //     cout << tree[i] << " ";
            // }
            // cout << endl;
        }
    }
    
    void update(int i, int val) {
        updateValSegTree(0, 0, n-1, i, val);
    }
    
    int sumRange(int i, int j) {
        // cout << endl << "query " << i << ", " << j << endl;
        int sum = querySegTree(0, 0, n-1, i, j);
        // cout << endl;
        return sum;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

//Binary Indexed Tree
//https://leetcode.com/problems/range-sum-query-mutable/discuss/75753/Java-using-Binary-Indexed-Tree-with-clear-explanation
//https://cs.stackexchange.com/questions/10538/bit-what-is-the-intuition-behind-a-binary-indexed-tree-and-how-was-it-thought-a
//Runtime: 48 ms, faster than 46.27% of C++ online submissions for Range Sum Query - Mutable.
//Memory Usage: 16.7 MB, less than 100.00% of C++ online submissions for Range Sum Query - Mutable.
class NumArray {
public:
    vector<int> nums;
    vector<int> BIT;
    int n;
    
    void init(int i, int val){
        i++;
        // cout << "init: ";
        while(i <= n){
            // cout << i << " ";
            BIT[i] += val;
            //double least significant bit
            /*
            current node is next node's left child or grandson,
            so next node's value should contain current node's value
            */
            i += (i&-i);
        }
        // cout << endl;
    };
    
    NumArray(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();
        BIT = vector<int>(n+1);
        for(int i = 0; i < n; i++){
            init(i, nums[i]);
        }
        
        // cout << "BIT: ";
        // for(int i = 1; i <= n; i++){
        //     cout << BIT[i] << " ";
        // }
        // cout << endl;
    }
    
    void update(int i, int val) {
        int diff = val - nums[i];
        nums[i] = val;
        init(i, diff);
    }
    
    int getSum(int i){
        int sum = 0;
        
        i++;
        
        // cout << "getSum: ";
        while(i > 0){
            // cout << i << " ";
            sum += BIT[i];
            //remove least significant bit
            /*
            current node is next node's right child or grandson,
            so next node's value doesn't contain current node's value.
            So to get cumulative sum, we should continue to add next node's value
            */
            i -= (i&-i);
        }
        // cout << endl;
        
        return sum;
    };
    
    int sumRange(int i, int j) {
        return getSum(j) - getSum(i-1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */
