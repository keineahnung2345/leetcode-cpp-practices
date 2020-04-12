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
