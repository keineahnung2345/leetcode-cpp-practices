//https://leetcode.com/problems/falling-squares/discuss/108770/O(nlogn)-C%2B%2B-Segment-Tree
//https://leetcode.com/articles/a-recursive-approach-to-segment-trees-range-sum-queries-lazy-propagation/
//Approach 4: Segment Tree with Lazy Propagation
//time: O(NlogN), space: O(N)
//Runtime: 68 ms, faster than 34.15% of C++ online submissions for Falling Squares.
//Memory Usage: 13.1 MB, less than 100.00% of C++ online submissions for Falling Squares.
class LazySegTree {
public:
    int n;
    vector<int> tree, lazy;
    
    //tree's index start from 0
    
    LazySegTree(int n){
        this->n = n;
        tree = vector<int>(n*4, 0);
        lazy = vector<int>(n*4, 0);
    };
    
    void print(){
        for(int e : tree){
            cout << e << " ";
        }
        cout << endl;
        
        for(int e : lazy){
            cout << e << " ";
        }
        cout << endl;
    }
    
    void push_up(int treeIndex) {
        //update i by its children
        tree[treeIndex] = max(tree[treeIndex*2+1], tree[treeIndex*2+2]);
    }

    void push_down(int treeIndex) {
        //remove laziness of i
        if (lazy[treeIndex]) {
            lazy[treeIndex*2+1] = lazy[treeIndex*2+2] = lazy[treeIndex];
            tree[treeIndex*2+1] = tree[treeIndex*2+2] = lazy[treeIndex];
            lazy[treeIndex] = 0;
        }
    }

    void update(int treeIndex, int l, int r, int ql, int qr, int val) {
        //looking at [l,r], which totally falls in [ql,qr]
        if (ql <= l && r <= qr) {
            tree[treeIndex] = val;
            //don't need to remove laziness first?
            lazy[treeIndex] = val;
            return;
        }
        push_down(treeIndex);
        int mid = l + (r-l)/2;
        if (ql < mid) update(treeIndex*2+1, l, mid, ql, qr, val);
        if (qr > mid) update(treeIndex*2+2, mid, r, ql, qr, val);
        push_up(treeIndex);
    }

    int query(int treeIndex, int l, int r, int ql, int qr) {
        //looking at [l,r], which totally falls in [ql,qr]
        if (ql <= l && r <= qr) return tree[treeIndex];
        int res = 0;
        
        //remove laziness
        push_down(treeIndex);

        int mid = l + (r-l)/2;
        /*
        ql...mid...qr or ql...qr...mid
        if query range has intersection with left subtree,
        then recursively query in left subtree
        */
        if (ql < mid) res = max(res, query(treeIndex*2+1, l, mid, ql, min(mid,qr)));
        /*
        ql...mid...qr or mid...ql...qr
        if query range has intersection with right subtree,
        then recursively query in right subtree
        */
        if (qr > mid) res = max(res, query(treeIndex*2+2, mid, r, max(mid,ql), qr));
        
        return res;
    }
};

class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> coords;
        vector<int> sortedCoords;
        vector<int> res;
        map<int, int> index;
        
        for (auto& pos : positions) {
            coords.insert(pos[0]);
            coords.insert(pos[0]+pos[1]);
        }
        
        sortedCoords = vector<int>(coords.begin(), coords.end());
        sort(sortedCoords.begin(), sortedCoords.end());
        
        // cout << "sorted: ";
        for(int i = 0; i < sortedCoords.size(); i++){
            index[sortedCoords[i]] = i;
            // cout << sortedCoords[i] << " ";
        }
        // cout << endl;
    
        LazySegTree tree((int)sortedCoords.size());
        
        for (auto& pos : positions) {
            int l = index[pos[0]];
            int r = index[pos[0]+pos[1]];
            // cout << "[" << l << ", " << r << "]" << endl;
            int maxh = tree.query(0, 0, tree.n-1, l, r);
            // tree.print();
            tree.update(0, 0, tree.n-1, l, r, maxh+pos[1]);
            // tree.print();
            res.push_back(tree.query(0, 0, tree.n-1, 0, tree.n-1));
        }
        
        return res;
    }
};

//Approach 1: Offline Propagation
//Runtime: 84 ms, faster than 18.90% of C++ online submissions for Falling Squares.
//Memory Usage: 9 MB, less than 100.00% of C++ online submissions for Falling Squares.
//time: O(N^2), space: O(N)
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> qans(positions.size());
        for(int i = 0; i < positions.size(); i++){
            int left = positions[i][0];
            int height = positions[i][1];
            int right = left + height -1;
            qans[i] += height;
            
            // for(int j = 0; j < i; j++){ //why not?
            for(int j = i+1; j < positions.size(); j++){
                int left2 = positions[j][0];
                int height2 = positions[j][1];
                int right2 = left2 + height2 -1;
                if(left2 <= right && right2 >= left){
                    //the two squares have intersection
                    qans[j] = max(qans[j], qans[i]);
                }
            }
        }
        
        vector<int> ans;
        int cur = -1;
        for(int h : qans){
            cur = max(cur, h);
            ans.push_back(cur);
        }
        
        return ans;
    }
};

//Approach 2: Brute Force with Coordinate Compression
//time: O(N^2), space: O(N)
//Runtime: 100 ms, faster than 15.66% of C++ online submissions for Falling Squares.
//Memory Usage: 12.3 MB, less than 100.00% of C++ online submissions for Falling Squares.
class Solution {
public:
    vector<int> heights;
    
    int query(int L, int R){
        return *max_element(heights.begin()+L, heights.begin()+R+1);
    }
    
    void update(int L, int R, int h){
        for(int i = L; i <= R; i++){
            // heights[i] = max(h, heights[i]);
            heights[i] = h;
        }
    }
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> coords;
        for(vector<int>& pos : positions){
            coords.insert(pos[0]);
            coords.insert(pos[0]+pos[1]-1);
        }
        
        vector<int> sortedCoords(coords.begin(), coords.end());
        sort(sortedCoords.begin(), sortedCoords.end());
        
        map<int, int> index;
        for(int i = 0; i < sortedCoords.size(); i++){
            index[sortedCoords[i]] = i;
        }
        
        heights =vector<int>(sortedCoords.size());
        int best = 0;
        vector<int> ans;
        
        for(vector<int>& pos : positions){
            int L = index[pos[0]];
            int R = index[pos[0]+pos[1]-1];
            int h = query(L, R) + pos[1];
            update(L, R, h);
            best = max(best, h);
            ans.push_back(best);
        }
        
        return ans;
    }
};

//Approach 3: Block (Square Root) Decomposition
//time: O(Nsqrt(N)), space: O(N)
//Runtime: 60 ms, faster than 45.78% of C++ online submissions for Falling Squares.
//Memory Usage: 12.6 MB, less than 100.00% of C++ online submissions for Falling Squares.
class Solution {
public:
    vector<int> heights;
    vector<int> blocks;
    vector<int> blocks_read;
    int B;
    
    int query(int left, int right){
        int ans = 0;
        
        //left is not at the beginning of a block
        while(left % B > 0 && left <= right){
            ans = max(ans, heights[left]);
            //?
            ans = max(ans, blocks[left/B]);
            left++;
        }
        
        //right is not at the end of a block
        while(right % B != B-1 && left <= right){
            ans = max(ans, heights[right]);
            ans = max(ans, blocks[right/B]);
            right--;
        }
        
        //now left is at the beginning and right is at the end of block
        while(left <= right){
            ans = max(ans, blocks[left/B]);
            //?
            ans = max(ans, blocks_read[left/B]);
            left += B;
        }
        
        return ans;
    }
    
    void update(int left, int right, int h){
        while(left % B > 0 && left <= right){
            heights[left] = max(heights[left], h);
            blocks_read[left/B] = max(blocks_read[left/B], h);
            left++;
        }
        while(right % B != B-1 && left <= right){
            heights[right] = max(heights[right], h);
            blocks_read[right/B] = max(blocks_read[right/B], h);
            right--;
        }
        while(left <= right){
            blocks[left/B] = max(blocks[left/B], h);
            left+=B;
        }
    }
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        set<int> coords;
        for(vector<int>& pos : positions){
            coords.insert(pos[0]);
            coords.insert(pos[0]+pos[1]-1);
        }
        
        vector<int> sortedCoords(coords.begin(), coords.end());
        sort(sortedCoords.begin(), sortedCoords.end());
        
        map<int, int> index;
        for(int i = 0; i < sortedCoords.size(); i++){
            index[sortedCoords[i]] = i;
        }
        
        heights = vector<int>(sortedCoords.size());
        B = (int)sqrt(sortedCoords.size());
        blocks = vector<int>(B+2, 0);
        blocks_read = vector<int>(B+2, 0);
        
        int best = 0;
        vector<int> ans;
        
        for(vector<int>& pos : positions){
            int L = index[pos[0]];
            int R = index[pos[0]+pos[1]-1];
            int h = query(L, R) + pos[1];
            update(L, R, h);
            best = max(best, h);
            ans.push_back(best);
        }
        
        return ans;
    }
};
