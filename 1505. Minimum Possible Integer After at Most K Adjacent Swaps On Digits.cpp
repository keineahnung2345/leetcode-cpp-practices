//TLE
//48 / 51 test cases passed.
class Solution {
public:
    string minInteger(string num, int k) {
        int n = num.size();
        for(int i = 0; i < n && k > 0; ++i){
            //find the smallest number in window size k
            //[i:i+k]
            // cout << "i: " << i << endl;
            auto min_it = min_element(num.begin()+i, num.begin()+min(n, i+k+1));
            
            if(*min_it < num[i]){
                //do swap
                int min_idx = min_it - num.begin();
                //[0,i-1] + [i, min_idx], [min_idx+1,n-1]
                //num = num.substr(0, i) + *min_it + num.substr(i, min_idx-i) + num.substr(min_idx+1);
                // cout << "i: " << i << ", min_idx: " << min_idx << endl;
                // cout << num << "->";
                num.replace(i, min_idx-i+1, *min_it + num.substr(i, min_idx-i));
                // cout << num << endl;
                //swap from min_idx to i, that is (min_idx - i) times
                k -= (min_idx - i);
            }
        }
        
        return num;
    }
};

//recursion
//https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/discuss/720215/The-constraint-was-not-very-helpful...-C%2B%2BPython-Clean-56ms-O(n2)-solution
//TLE
//50 / 51 test cases passed.
//time: O(N^2)
class Solution {
public:
    string minInteger(string num, int k) {        
        if(k <= 0) return num;
        
        int n = num.size();
        
        if(k >= n*(n-1)/2){
            sort(num.begin(), num.end());
            return num;
        }
        
        //find '0'~'9'
        for(int i = 0; i < 10; ++i){
            int idx = num.find(to_string(i));
            if(idx >= 0 && idx <= k){
                //k-idx: move the char from idx to 0 cost "idx" swaps
                return num[idx] + minInteger(num.substr(0, idx) + num.substr(idx+1), k - idx);
            }
        }
        
        return num;
    }
};

//Segment tree
//https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/discuss/720548/O(n-logn)-or-Java-or-Heavily-Commented-or-Segment-Tree-or-Detailed-Explanation
//Runtime: 184 ms, faster than 52.63% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//Memory Usage: 13.3 MB, less than 100.00% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//time: O(NlogN)
class SegTree{
public:
    vector<int> nodes;
    int n;
    
    SegTree(int n){
        this->n = n;
        nodes = vector<int>(this->n << 2);
    }
    
    void update(int treeIdx, int l, int r, int ql, int val){
        //update [ql,ql]
        if(ql < l || ql > r){
            return;
        }
        
        if(l == r){
            //leaf node
            nodes[treeIdx] += val;
            // cout << "nodes[" << treeIdx << "] = " << nodes[treeIdx] << endl;
            return;
        }
        
        int mid = (l+r)/2;
        
        if(ql <= mid){
            //update left subtree
            update(treeIdx*2+1, l, mid, ql, val);
        }else{
            update(treeIdx*2+2, mid+1, r, ql, val);
        }
        
        nodes[treeIdx] = nodes[treeIdx*2+1] + nodes[treeIdx*2+2];
        // cout << "nodes[" << treeIdx << "] = " << nodes[treeIdx] << endl;
    }
    
    void increase(int ql){
        update(0, 0, n-1, ql, 1);
    }
    
    int query(int treeIdx, int l, int r, int ql, int qr){
        if(l > qr || r < ql){
            return 0;
        }
        
        if(ql <= l && r <= qr){
            //looking range is inside query range
            return nodes[treeIdx];
        }
        
        int mid = (l+r)/2;
        
        if(qr <= mid){
            //complete in left subtree
            return query(treeIdx*2+1, l, mid, ql, qr);
        }else if(ql > mid){
            //complete in right subtree
            return query(treeIdx*2+2, mid+1, r, ql, qr);
        }
        
        int leftRes = query(treeIdx*2+1, l, mid, ql, mid);
        int rightRes = query(treeIdx*2+2, mid+1, r, mid+1, qr);
        
        return leftRes + rightRes;
    }
    
    int queryLessThan(int qnum){
        return query(0, 0, n-1, 0, qnum-1);
    }
};

class Solution {
public:
    string minInteger(string num, int k) {
        //0-9's locations in "num"
        vector<queue<int>> qs(10);
        int n = num.size();
        
        for(int i = 0; i < n; ++i){
            qs[num[i]-'0'].push(i);
        }
        
        string ans;
        SegTree* tree = new SegTree(n);
        
        for(int i = 0; i < n; ++i){
            for(int d = 0; d <= 9; ++d){
                /*
                qs[d]: contains the positions of unshifted digit d
                */
                if(!qs[d].empty()){
                    //the nearest d's position
                    int pos = qs[d].front();
                    /*
                    how many digits in front of pos is 
                    already shifted to its right position
                    */
                    int shifted = tree->queryLessThan(pos);
                    /*
                    move from "pos" to the index "shifted"
                    */
                    if(pos - shifted <= k){
                        k -= pos-shifted;
                        //the digit originally in pos has been shifted
                        tree->increase(pos);
                        qs[d].pop();
                        ans += ('0'+d);
                        break;
                    }
                }
            }
        }
        
        return ans;
    }
};

//segment tree, optimized
//https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/discuss/720548/O(n-logn)-or-Java-or-Heavily-Commented-or-Segment-Tree-or-Detailed-Explanation/606367
//Runtime: 92 ms, faster than 75.82% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//Memory Usage: 13.9 MB, less than 100.00% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//time: O(NlogN)
class SegTree{
public:
    vector<int> nodes;
    int n;
    
    SegTree(int n){
        this->n = n;
        nodes = vector<int>(this->n << 2);
    }
    
    void update(int treeIdx, int l, int r, int ql, int val){
        if(ql < l || ql > r){
            return;
        }
        
        if(l == r){
            nodes[treeIdx] += val;
            return;
        }
        
        int mid = (l+r) >> 1;
        
        if(ql <= mid){
            update((treeIdx<<1)|1, l, mid, ql, val);
        }else{
            update((treeIdx<<1)+2, mid+1, r, ql, val);
        }
        
        nodes[treeIdx] = nodes[(treeIdx<<1)|1] + nodes[(treeIdx<<1)+2];
    }
    
    void increase(int ql){
        update(0, 0, n-1, ql, 1);
    }
    
    int query(int treeIdx, int l, int r, int ql, int qr){
        if(l > qr || r < ql){
            return 0;
        }
        
        if(ql <= l && r <= qr){
            return nodes[treeIdx];
        }
        
        int mid = (l+r) >> 1;
        
        if(qr <= mid){
            return query((treeIdx<<1)|1, l, mid, ql, qr);
        }else if(ql > mid){
            return query((treeIdx<<1)+2, mid+1, r, ql, qr);
        }
        
        int leftRes = query((treeIdx<<1)|1, l, mid, ql, mid);
        int rightRes = query((treeIdx<<1)+2, mid+1, r, mid+1, qr);
        
        return leftRes + rightRes;
    }
    
    int queryLessThan(int qnum){
        return query(0, 0, n-1, 0, qnum-1);
    }
};

class Solution {
public:
    string minInteger(string num, int k) {
        vector<queue<int>> qs(10);
        int n = num.size();
        
        for(int i = 0; i < n; ++i){
            qs[num[i]-'0'].push(i);
        }
        
        string lhs;
        vector<bool> removed(n, false);
        SegTree* tree = new SegTree(n);
        
        while(k > 0){
            bool found = false;
            for(int d = 0; d <= 9; ++d){
                if(!qs[d].empty()){
                    int pos = qs[d].front();
                    int shifted = tree->queryLessThan(pos);
                    if(pos - shifted <= k){
                        k -= pos-shifted;
                        tree->increase(pos);
                        qs[d].pop();
                        lhs += ('0'+d);
                        removed[pos] = true;
                        found = true;
                        break;
                    }
                }
            }
            if(!found) break;
        }
        
        string rhs;
        for(int i = 0; i < n; ++i){
            if(!removed[i]){
                rhs += num[i];
            }
        }
        
        return lhs + rhs;
    }
};

//Binary Indexed Tree
//since query range all start from 0, and the query indices are in ascending order, so we can rewrite it as BIT?
//https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/discuss/720548/O(n-logn)-or-Java-or-Heavily-Commented-or-Segment-Tree-or-Detailed-Explanation/606367
//Runtime: 60 ms, faster than 90.59% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//Memory Usage: 11.6 MB, less than 100.00% of C++ online submissions for Minimum Possible Integer After at Most K Adjacent Swaps On Digits.
//time: O(NlogN)
class BIT{
public:
    int n;
    vector<int> nodes;
    
    BIT(int n){
        this->n = n;
        nodes = vector<int>(n+1);
    }
    
    void update(int i, int delta){
        ++i;
        while(i <= n){
            nodes[i] += delta;
            i += (i&-i);
        }
    }
    
    int query(int i){
        ++i;
        int sum = 0;
        
        while(i > 0){
            sum += nodes[i];
            i -= (i&-i);
        }
        
        return sum;
    }
};

class Solution {
public:
    string minInteger(string num, int k) {
        vector<queue<int>> qs(10);
        int n = num.size();
        
        for(int i = 0; i < n; ++i){
            qs[num[i]-'0'].push(i);
        }
        
        string lhs;
        vector<bool> removed(n, false);
        BIT* tree = new BIT(n);
        
        while(k > 0){
            bool found = false;
            for(int d = 0; d <= 9; ++d){
                if(!qs[d].empty()){
                    int pos = qs[d].front();
                    int shifted = tree->query(pos-1);
                    if(pos - shifted <= k){
                        k -= pos-shifted;
                        tree->update(pos, 1);
                        qs[d].pop();
                        lhs += ('0'+d);
                        removed[pos] = true;
                        found = true;
                        break;
                    }
                }
            }
            if(!found) break;
        }
        
        string rhs;
        for(int i = 0; i < n; ++i){
            if(!removed[i]){
                rhs += num[i];
            }
        }
        
        return lhs + rhs;
    }
};
