//Segment Tree
//https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/discuss/757373/C%2B%2B-Segment-Tree-Solution-w-explanation-Accepted
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

//https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/discuss/754623/Detailed-Explanation
//Runtime: 368 ms, faster than 43.51% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//Memory Usage: 73.2 MB, less than 66.61% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//time: O(N), space: O(1)
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int totalOps = target[0];
        int usableOps = target[0];
        
        int n = target.size();
        
        for(int i = 1; i < n; ++i){
            if(target[i] <= usableOps){
                usableOps = target[i];
            }else{
                //target[i] > usableOps
                totalOps += (target[i] - usableOps);
                usableOps = target[i];
            }
        }
        
        return totalOps;
    }
};

//refactored
//Runtime: 296 ms, faster than 73.27% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//Memory Usage: 73.4 MB, less than 44.42% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//time: O(N), space: O(1)
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int totalOps = target[0];
        
        int n = target.size();
        
        for(int i = 1; i < n; ++i){
            //target[i-1] serves as operationsWeCanReuse
            if(target[i] > target[i-1]){
                //extra operations needed: target[i] - target[i-1]
                totalOps += (target[i] - target[i-1]);
            }
            //every time usableOps will be updated to target[i]
        }
        
        return totalOps;
    }
};

//shortest
//https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/discuss/754674/JavaC%2B%2BPython-Comparison-of-Consecutive-Elements
//Runtime: 376 ms, faster than 41.85% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//Memory Usage: 73.2 MB, less than 78.18% of C++ online submissions for Minimum Number of Increments on Subarrays to Form a Target Array.
//time: O(N), space: O(1)
class Solution {
public:
    int minNumberOperations(vector<int>& target) {
        int totalOps = target[0];
        
        int n = target.size();
        
        for(int i = 1; i < n; ++i){
            totalOps += max(target[i]-target[i-1], 0);
        }
        
        return totalOps;
    }
};
