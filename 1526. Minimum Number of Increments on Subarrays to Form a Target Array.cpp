//Segment Tree
//Runtime: 396 ms, faster than 38.41% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//Memory Usage: 90.2 MB, less than 7.90% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
class SegTree {
public:
    vector<int> tree;
    int n;
    
    SegTree(vector<int>& arr){
        n = arr.size();
        tree = vector<int>(n<<2, -1);
        init(arr, 0, 0, n-1);
    }
    
    int init(vector<int>& arr, int treeIdx, int l, int r){
        //return the index of minimum value in the node's coverage
        if(l == r){
            return tree[treeIdx] = l;
        }
        
        int mid = (l+r)>>1;
        int leftMinIdx = init(arr, (treeIdx<<1)+1, l, mid);
        int rightMinIdx = init(arr, (treeIdx<<1)+2, mid+1, r);
        
        //it chooses the index corresponding to smaller value
        return tree[treeIdx] = (arr[leftMinIdx] <= arr[rightMinIdx]) ? leftMinIdx: rightMinIdx;
    }
    
    int query(vector<int>& arr, int treeIdx, int l, int r, int ql, int qr){
        //node coverage: arr[l:r]
        //query range: [ql:qr]
        if(l > qr || ql > r){
            //no overlap, return an invalid index
            return -1;
        }
        
        //early stopping, avoid TLE!!
        if(ql == l && qr == r){
            return tree[treeIdx];
        }
        
        if(l == r){
            //leaf node
            return tree[treeIdx];
        }
        
        int mid = (l+r)>>1;
        
        if(qr <= mid){
            //totally falls in left subtree
            return query(arr, (treeIdx<<1)+1, l, mid, ql, qr);
        }else if(ql > mid){
            return query(arr, (treeIdx<<1)+2, mid+1, r, ql, qr);
        }
        
        //query range becomes [ql, mid]
        int leftMinIdx = query(arr, (treeIdx<<1)+1, l, mid, ql, mid);
        //query range becomes [mid+1, qr]
        int rightMinIdx = query(arr, (treeIdx<<1)+2, mid+1, r, mid+1, qr);
        
        if(leftMinIdx == -1) return rightMinIdx;
        else if(rightMinIdx == -1) return leftMinIdx;
        
        return (arr[leftMinIdx] <= arr[rightMinIdx]) ? leftMinIdx: rightMinIdx;
    }

    int count(vector<int>& target, int ql, int qr, int curMin){
        /*
        count of incrementation needed to 
        convert from  the "initial array" filled with "curMin" 
        to "target" in the range [ql, qr]
        */
        //curMin: current minimum in the query range of updated "initial" array
        if(ql > qr) return 0;

        int minIdx = query(target, 0, 0, n-1, ql, qr);
        /*
        now we conduct "res" incrementation to convert "initial"
        which is filled with "curMin" to filled with "newMin"
        */
        int newMin = target[minIdx];
        int res = newMin - curMin;
        //divide and conquer
        res += count(target, ql, minIdx-1, newMin);
        res += count(target, minIdx+1, qr, newMin);
        return res;
    };
};

class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        SegTree* st = new SegTree(target);
        int n = target.size();
        return st->count(target, 0, n-1, 0);
    }
};
