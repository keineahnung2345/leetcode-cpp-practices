//O(N^2)
//TLE
//15 / 16 test cases passed.
class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(nums[i] > nums[j]){
                    ++ans[i];
                }
            }
        }
        
        return ans;
    }
};

//Segment Tree
//TLE
//15 / 16 test cases passed.
class SegTree{
public:
    vector<int> arr;
    vector<int> tree;
    int n;
    
    SegTree(vector<int>& arr){
        this->arr = arr;
        this->n = arr.size();
        tree = vector<int>(this->n << 2, 0);
        //tree[0] is meaningful
        //left child: 2*i+1, right child: 2*i+2
    }
    
    void increase(int treeIdx, int l, int r, int ql, int qr, int num){
        //increase [ql, qr] by 1
        if(l > qr || ql > r){
            return;
        }
        
        if(l == r){
            if(arr[l] > num){
                ++tree[treeIdx];
                // cout << l << " : " << tree[treeIdx] << endl;
            }
            return;
        }
        
        int mid = (l+r) >> 1;
        
        if(qr <= mid){
            increase(treeIdx*2+1, l, mid, ql, qr, num);
        }else if(ql > mid){
            increase(treeIdx*2+2, mid+1, r, ql, qr, num);
        }else{
            increase(treeIdx*2+1, l, mid, ql, mid, num);
            increase(treeIdx*2+2, mid+1, r, mid+1, qr, num);
        }
        
        tree[treeIdx] = tree[treeIdx*2+1]+tree[treeIdx*2+2];
    }
    
    int query(int treeIdx, int l, int r, int q){
        if(l == r && l == q){
            return tree[treeIdx];
        }
        
        int mid = (l+r) >> 1;
        
        if(q <= mid){
            return query(treeIdx*2+1, l, mid, q);
        }else{
            return query(treeIdx*2+2, mid+1, r, q);
        }
    }
};

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        
        SegTree st(nums);
        
        for(int i = 1; i < n; ++i){
            st.increase(0, 0, n-1, 0, i-1, nums[i]);
        }
        
        vector<int> ans(n);
        
        for(int i = 0; i < n; ++i){
            ans[i] = st.query(0, 0, n-1, i);
        }
        
        return ans;
    }
};
