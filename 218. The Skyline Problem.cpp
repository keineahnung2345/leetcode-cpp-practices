//line sweep
//TLE
//35 / 36 test cases passed.
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int OPEN = 0, CLOSE = 1;
        int n = buildings.size();
        //vector of {x coord, open or close, height, building_id}
        vector<vector<int>> events(n*2);
        
        for(int i = 0; i < n; ++i){
            events[i*2] = {buildings[i][0], OPEN, buildings[i][2], i};
            events[i*2+1] = {buildings[i][1], CLOSE, buildings[i][2], i};
        }
    
        //actives: current opening events' event_id
        vector<int> actives;
        vector<vector<int>> ans;
        
        //sort by x coord
        sort(events.begin(), events.end());
        
        // cout << "event" << endl;
        // for(vector<int>& event : events){
        //     cout << "x: " << event[0] << ", " << (event[1] ? "CLOSE" : "OPEN") << ", height: " << event[2] << endl;
        // }
        
        int lastX = INT_MIN;
        int lastMaxHeight = INT_MIN;
        
        //vertical line sweep along x-axis
        for(int eventId = 0; eventId < events.size(); ++eventId){
            //extract the required infos
            int x = events[eventId][0];
            bool isClose = events[eventId][1];
            int height = events[eventId][2];
            
            // cout << "x: " << x << ", isClose: " << isClose << ", height: " << height << endl;
            
            if(!isClose){
                actives.push_back(eventId);
            }else{
                //find the corresponding OPEN event and remove it
                for(int i = 0; i < actives.size(); ++i){
                    if(events[actives[i]][2] == height){
                        actives.erase(actives.begin()+i);
                        break;
                    }
                }
            }
            
            // cout << "active: ";
            // for(int& active : actives){
            //     cout << active << " ";
            // }
            // cout << endl;
            
            //get the maximum height of active events
            int maxHeight = 0;
            
            //update actives
            if(!actives.empty()){
                for(int i = 0; i < actives.size(); ++i){
                    if(events[actives[i]][1] != CLOSE){
                        maxHeight = max(maxHeight, events[actives[i]][2]);
                    }
                }
            }
            
            // cout << "maxHeight: " << maxHeight << endl;
            
            //update ans only if x is leftmost or rightmost of actives
            if(actives.empty()){
                //the right boundary of connected buildings
                ans.push_back({x, maxHeight});
            }else if(!ans.empty() && x == ans.back()[0]){
                //current event and last event has same x
                //update its height
                ans.back()[1] = maxHeight;
            }else{
                //there is a change in height
                if(maxHeight != lastMaxHeight)
                    ans.push_back({x, maxHeight});
            }
            
            lastMaxHeight = maxHeight;
            lastX = x;
        }
        
        return ans;
    }
};

//line sweep + heap
//https://briangordon.github.io/2014/08/the-skyline-problem.html
//Runtime: 256 ms, faster than 5.24% of C++ online submissions for The Skyline Problem.
//Memory Usage: 18.2 MB, less than 19.85% of C++ online submissions for The Skyline Problem.
//time: O(NlogN), space: O(N)
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int OPEN = 0, CLOSE = 1;
        //(height, x-coord, right boundary)
        vector<vector<int>> points;
        
        for(int i = 0; i < buildings.size(); ++i){
            points.push_back({buildings[i][2], buildings[i][0], buildings[i][1]});
            points.push_back({buildings[i][2], buildings[i][1], buildings[i][1]});
        }
        
        //sort by x-coordinate
        sort(points.begin(), points.end(), 
            [](const vector<int>& a, const vector<int>& b){
                return a[1] < b[1];
            });
        
        //max height on top
        priority_queue<vector<int>, vector<vector<int>>> pq;
        vector<vector<int>> ans;
        
        for(vector<int>& point : points){
            int x = point[1];
            bool isClose = (point[1] == point[2]);
            // cout << "===x: " << x << ", left: " << !isClose << "===" << endl;
            
            /*
            building whose right boundary <= x should be cleared
            */
            // if(!pq.empty()){
            //     cout << "pq top x: " << pq.top()[1] << ", h: " << pq.top()[0] << endl;
            // }
            
            // cout << "push x: " << x << ", h: " << point[0] << endl;
            pq.push(point);
            
            //pop buildings whose right boundary <= current x-coord
            while(!pq.empty() && /*pq.top()[2] == pq.top()[1] &&*/ pq.top()[2] <= x){
                // cout << "pop x: " << pq.top()[1] << ", h: " << pq.top()[0] << endl;
                pq.pop();
            }
            
            // cout << "pq: " << pq.size() << endl;
            
            int height = pq.empty() ? 0 : pq.top()[0];
            //don't pop from pq! since it could still be active!
            
            if(ans.empty()){
                ans.push_back({x, height});
                // cout << "add " << x << ", " << height << endl;
            }else if(x == ans.back()[0]){
                /*
                [[0,2,3],[2,5,3]]
                */
                if(ans.size() >= 2 && ans[ans.size()-2][1] == max(ans.back()[1], height)){
                    // cout << "erase " << ans.back()[0] << ", " << ans.back()[1] << endl;
                    ans.erase(ans.begin()+ans.size()-1);
                    // cout << "update " << x << ", " << height << endl;
                }else{
                    ans.back()[1] = max(ans.back()[1], height);
                }
            }else if(ans.back()[1] != height){
                // cout << "add " << x << ", " << height << endl;
                ans.push_back({x, height});
            }
        }
        
        return ans;
    }
};

//line sweep + heap with remove()
//https://briangordon.github.io/2014/08/the-skyline-problem.html
//https://leetcode.com/problems/the-skyline-problem/discuss/61197/(Guaranteed)-Really-Detailed-and-Good-(Perfect)-Explanation-of-The-Skyline-Problem/62461
//TLE
class compare_height{
public:
    compare_height(){}
    bool operator() (const vector<int>& b1, const vector<int>& b2) const{
        return b1[2] < b2[2];
    }
};

//equip the original priority_queue with "remove"
template<typename T>
class custom_priority_queue : public std::priority_queue<T, std::vector<T>, compare_height>{
public:
    bool remove(const T& value) {
        auto it = std::find(this->c.begin(), this->c.end(), value);
        if (it != this->c.end()) {
            this->c.erase(it);
            std::make_heap(this->c.begin(), this->c.end(), this->comp);
            return true;
       } else {
            return false;
       }
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //points sorted by their x-coord
        map<int, vector<vector<int>>> points;
        
        for(vector<int>& building : buildings){
            points[building[0]].push_back(building);
            points[building[1]].push_back(building);
        }
        
        custom_priority_queue<vector<int>> pq;
        
        vector<vector<int>> ans;
        
        for(auto it = points.begin(); it != points.end(); ++it){
            int x = it->first;
            vector<vector<int>> bs = it->second;
            
            //update heap
            for(vector<int>& b : bs){
                if(x == b[0]){
                    //left edge
                    pq.push(b);
                }else{
                    //x == b[1], right edge
                    pq.remove(b);
                }
            }
            
            //update ans
            if(pq.empty()){
                ans.push_back({x, 0});
            }else{
                int h = pq.top()[2];
                if(ans.empty() || h != ans.back()[1]){
                    ans.push_back({x, h});
                }
            }
        }
        
        return ans;
    }
};

//line sweep + heap, optimized
//Runtime: 152 ms, faster than 15.75% of C++ online submissions for The Skyline Problem.
//Memory Usage: 21.6 MB, less than 9.56% of C++ online submissions for The Skyline Problem.
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //points sorted by their x-coord
        map<int, vector<vector<int>>> points;
        
        for(vector<int>& building : buildings){
            points[building[0]].push_back(building);
            points[building[1]].push_back(building);
        }
        
        //building with larger height will be put on top
        auto comp = [](const vector<int>& b1, const vector<int>& b2){
            return b1[2] < b2[2];
        };
        
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> pq(comp);
        
        vector<vector<int>> ans;
        
        for(auto it = points.begin(); it != points.end(); ++it){
            int x = it->first;
            vector<vector<int>> bs = it->second;
            
            //update heap
            for(vector<int>& b : bs){
                if(x == b[0]){
                    //left edge
                    pq.push(b);
                }else{
                    //x == b[1], right edge
                    // pq.remove(b);
                }
            }
            
            /*
            when you hit the right edge of a building 
            you pop nodes off the top of the heap repeatedly 
            until the top node is a building
            whose right edge is still ahead.
            */
            while(!pq.empty() && pq.top()[1] <= x){
                pq.pop();
            }
            
            //update ans
            if(pq.empty()){
                ans.push_back({x, 0});
            }else{
                int h = pq.top()[2];
                if(ans.empty() || h != ans.back()[1]){
                    ans.push_back({x, h});
                }
            }
        }
        
        return ans;
    }
};

//line sweep + multiset
//multiset: elements are sorted, and have O(logN) "find" function
//https://leetcode.com/problems/the-skyline-problem/discuss/61197/(Guaranteed)-Really-Detailed-and-Good-(Perfect)-Explanation-of-The-Skyline-Problem/62455
//Runtime: 124 ms, faster than 29.41% of C++ online submissions for The Skyline Problem.
//Memory Usage: 18 MB, less than 20.70% of C++ online submissions for The Skyline Problem.
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //always sorted
        multiset<vector<int>> points;
        
        for(vector<int>& building : buildings){
            //negative height marks left boundary
            points.insert({building[0], -building[2]});
            points.insert({building[1], building[2]});
        }
        
        /*
        works just like the priority queue,
        but equipped with O(logN) "find" function
        */
        multiset<int> heights;
        vector<vector<int>> ans;
        
        for(const vector<int>& point : points){
            if(point[1] < 0){
                //left boundary
                heights.insert(-point[1]);
            }else{
                /*
                meet right boundary,
                erase previously inserted left boundary
                */
                heights.erase(heights.find(point[1]));
            }
            
            if(heights.empty()){
                ans.push_back({point[0], 0});
            }else{
                int h = *heights.rbegin();
                if(ans.empty() || h != ans.back()[1]){
                    ans.push_back({point[0], h});
                }
            }
        }
        
        return ans;
    }
};

//segment tree
//https://leetcode.com/problems/the-skyline-problem/discuss/61313/A-segment-tree-solution/185639
//TLE
//35 / 36 test cases passed.
class SegTree{
public:
    vector<int> tree;
    
    SegTree(int n){
        //tree[0] is meaningless
        //tree[1] is meaningful
        tree = vector<int>(n);
    }
    
    void update(int treeIdx, int left, int right, int qleft, int qright, int val){
        if(left > right || qright < left || qleft > right){
            /*
            left > right: looking at wrong range
            qright < left || qleft > right: 
            looking range and query range has no intersection
            */
            return;
        }
        
        // cout << "tree(" << treeIdx << ") covers [" << left << ", " << right << "], query for " << "[" << qleft << ", " << qright << "], val: " << val << endl;
        
        if(left == right){
            //stop when the node is a leaf(it covers length-1 range)
            //need to take max because a node can be updated multiple times!
            tree[treeIdx] = max(tree[treeIdx], val);
        }else{
            int mid = (left + right) >> 1;

            /*
            current node range: [left, right]
            left subtree range: [left, mid]
            right subtree range: [mid+1, right]
            */
            
            if(qright <= mid){
                //query range completely in left subtree
                // cout << "complete in left subtree" << endl;
                update(treeIdx << 1, left, mid, qleft, qright, val);
                /*
                need to update the internal node so that 
                it represents for the max in the range it covers
                */
                tree[treeIdx] = max(tree[treeIdx], tree[treeIdx << 1]);
            }else if(qleft > mid){
                //query range completely in right subtree
                // // cout << "complete in right subtree" << endl;
                update(treeIdx << 1 | 1, mid+1, right, qleft, qright, val);
                tree[treeIdx] = max(tree[treeIdx], tree[treeIdx << 1 | 1]);
            }else{
                //query range cross left and right subtree

                //note: qright becomes mid
                // cout << "first go to left subtree" << endl;
                update(treeIdx << 1, left, mid, qleft, mid, val);

                //note: qleft becoems mid+1
                // cout << "then go to right subtree" << endl;
                update(treeIdx << 1 | 1, mid+1, right, mid+1, qright, val);
                tree[treeIdx] = max({tree[treeIdx], tree[treeIdx << 1], tree[treeIdx << 1 | 1]});
            }
            
            /*
            or simply
            update(treeIdx << 1, left, mid, qleft, min(mid, qright), val);
            update(treeIdx << 1 | 1, mid+1, right, max(mid+1, qleft), qright, val);
            tree[treeIdx] = max({tree[treeIdx], tree[treeIdx << 1], tree[treeIdx << 1 | 1]});
            */
        }
        
    }
    
    int query(int treeIdx, int left, int right, int qIdx){
        if(left > qIdx || right < qIdx) return -1;
        
        // cout << "tree(" << treeIdx << ") covers [" << left << ", " << right << "], query for " << qIdx << endl;
        
        if(left == right){
            //stop when the node is a leaf(it covers length-1 range)
            /*
            it can be optimized by stopping at internal nodes?
            not in this problem, because our query interval is always length one!
            */
            // cout << "tree(" << treeIdx << "), arr(" << left << ") val: " << tree[treeIdx] << endl;
            return tree[treeIdx];
        }
        
        int mid = (left + right) >> 1;
        
        if(qIdx <= mid){
            int res = query(treeIdx << 1, left, mid, qIdx);
            // cout << "tree(" << treeIdx << ") val: " << res << endl;
            /*
            different than lazy version,
            don't need to take max of tree[treeIdx] and this subresult!
            */
            return res;
        }else if(qIdx > mid){
            int res = query(treeIdx << 1 | 1, mid+1, right, qIdx);
            // cout << "tree(" << treeIdx << ") val: " << res << endl;
            return res;
        }

        return -1;
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        //its elements are sorted!
        set<int> points;
        
        for(vector<int>& b : buildings){
            points.insert(b[0]);
            points.insert(b[1]);
        }
        
        unordered_map<int, int> fw, bw;
        int n = 0;
        
        for(const int& point : points){
            fw[point] = n;
            bw[n] = point;
            // cout << n << " <---> " << point << endl;
            ++n;
        }
        
        SegTree* tree = new SegTree(n << 4);
        
        for(vector<int>& b : buildings){
            //tree[1]: seg tree's root
            //[0,n-1]: range covered by current node
            /*
            only update the range[b's left, b's right-1],
            note that we don't set b's right to b[2]!
            */
            // cout << "========" << endl;
            tree->update(1, 0, n-1, fw[b[0]], fw[b[1]]-1, b[2]);
        }
        
        //build ans
        vector<vector<int>> ans;
        
        int preH = INT_MIN, h;
        
        for(int i = 0; i < n; ++i){
            // cout << "========" << endl;
            //qeury in [0, n-1] for "i"th critical point
            h = tree->query(1, 0, n-1, i);
            //ignore different 
            if(h == preH) continue;
            ans.push_back({bw[i], h});
            preH = h;
        }
        
        return ans;
    }
};

//segment tree with lazy propagation
//https://leetcode.com/problems/the-skyline-problem/discuss/61313/A-segment-tree-solution/185639
//Runtime: 120 ms, faster than 32.77% of C++ online submissions for The Skyline Problem.
//Memory Usage: 17.4 MB, less than 24.52% of C++ online submissions for The Skyline Problem.
class SegTree{
public:
    vector<int> tree;
    
    SegTree(int n){
        tree = vector<int>(n);
    }
    
    void update(int treeIdx, int left, int right, int qleft, int qright, int val){
        if(left > right || qright < left || qleft > right){
            return;
        }
        
        // cout << "tree(" << treeIdx << ") covers [" << left << ", " << right << "], query for " << "[" << qleft << ", " << qright << "], val: " << val << endl;
        
        if(left == qleft && right == qright){
            /*
            not lazy version stops when left == right
            (a leaf node)
            
            lazy propagation: stop updating when 
            looking range matches update range
            (so it may stop at interval nodes)
            */
            //take max because a node can be updated multiple times
            tree[treeIdx] = max(tree[treeIdx], val);
        }else{
            int mid = (left + right) >> 1;

            if(qright <= mid){
                // cout << "complete in left subtree" << endl;
                update(treeIdx << 1, left, mid, qleft, qright, val);
            }else if(qleft > mid){
                // // cout << "complete in right subtree" << endl;
                update(treeIdx << 1 | 1, mid+1, right, qleft, qright, val);
            }else{
                // cout << "first go to left subtree" << endl;
                update(treeIdx << 1, left, mid, qleft, mid, val);

                // cout << "then go to right subtree" << endl;
                update(treeIdx << 1 | 1, mid+1, right, mid+1, qright, val);
            }
            
            /*
            or simply
            update(treeIdx << 1, left, mid, qleft, min(mid, qright), val);
            update(treeIdx << 1 | 1, mid+1, right, max(mid+1, qleft), qright, val);
            */
        }
        
        // cout << "tree(" << treeIdx << ") covers [" << left << ", " << right << "], query for " << "[" << qleft << ", " << qright << "], set to: " << val << endl;
    }
    
    int query(int treeIdx, int left, int right, int qIdx){
        if(left > qIdx || right < qIdx) return -1;
        
        // cout << "tree(" << treeIdx << ") covers [" << left << ", " << right << "], query for " << qIdx << endl;
        
        if(left == right){
            /*
            for lazy version,
            we can't stop query until
            we are at a leaf node
            */
            // cout << "tree(" << treeIdx << "), arr(" << left << ") val: " << tree[treeIdx] << endl;
            return tree[treeIdx];
        }
        
        int mid = (left + right) >> 1;
        
        int res;
        
        /*
        lazy propagation
        query in left subtree or right subtree,
        cannot return directly after return from subtree 
        */
        if(qIdx <= mid){
            res = query(treeIdx << 1, left, mid, qIdx);
            // cout << "tree(" << treeIdx << ") val: " << max(tree[treeIdx], res) << endl;
        }else if(qIdx > mid){
            res = query(treeIdx << 1 | 1, mid+1, right, qIdx);
            // cout << "tree(" << treeIdx << ") val: " << max(tree[treeIdx], res) << endl;    
        }
        
        // cout << "tree(" << treeIdx << "), arr(" << left << ", " << right << ") val: " << max(tree[treeIdx], res) << endl;
         // cout << "tree(" << treeIdx << "), arr(" << left << ", " << right << ") val: " << res << endl; 
        /*
        for interval nodes,
        we don't update its value if
        the update range doesn't perfectly match its coverage
        (this can be confirmed in "left != right" part,
        in which we don't update tree[treeIdx]!)
        
        so while querying, only looking at a interval node
        is not enough to determine the range max,
        we need to go through all of its leaves
        to determine the range max!!
        */
        return max(tree[treeIdx], res);
    }
};

class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        set<int> points;
        
        for(vector<int>& b : buildings){
            points.insert(b[0]);
            points.insert(b[1]);
        }
        
        unordered_map<int, int> fw, bw;
        int n = 0;
        
        for(const int& point : points){
            fw[point] = n;
            bw[n] = point;
            // cout << n << " <---> " << point << endl;
            ++n;
        }
        
        SegTree* tree = new SegTree(n << 4);
        
        for(vector<int>& b : buildings){
            // cout << "========" << endl;
            tree->update(1, 0, n-1, fw[b[0]], fw[b[1]]-1, b[2]);
        }
        
        vector<vector<int>> ans;
        
        int preH = INT_MIN, h;
        
        for(int i = 0; i < n; ++i){
            // cout << "========" << endl;
            h = tree->query(1, 0, n-1, i);
            if(h == preH) continue;
            ans.push_back({bw[i], h});
            preH = h;
        }
        
        return ans;
    }
};

//binary indexed tree(not understand?)
//https://leetcode.com/problems/the-skyline-problem/discuss/61198/My-O(nlogn)-solution-using-Binary-Indexed-Tree(BIT)Fenwick-Tree/62473
//Runtime: 136 ms, faster than 22.81% of C++ online submissions for The Skyline Problem.
//Memory Usage: 17.2 MB, less than 28.04% of C++ online submissions for The Skyline Problem.
class Solution {
public:
    /*
    here the direction of "add" and "find" are
    opposite to that in "307. Range Sum Query - Mutable Medium",
    that's because here the interval node is 
    the summary of itself and its right child?
    (not left child just like "307"?)
    */
    void add(vector<int>& BIT, int i, int h){
        //i is already BIT's index, not nums's
        
        while(i > 0){
            BIT[i] = max(BIT[i], h);
            // cout << "BIT[" << i << "]: " << BIT[i] << endl;
            i -= i&(-i);
        }
    };
    
    int find(vector<int>& BIT, int i){
        //i is already BIT's index, not nums's
        
        int h = 0;
        
        while(i < BIT.size()){
            h = max(h, BIT[i]);
            // cout << "BIT[" << i << "]: " << BIT[i] << endl;
            i += i&(-i);
        }
        
        return h;
    };
    
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        vector<vector<int>> points;
        int OPEN = 0, CLOSE = 1;
        
        for(int i = 0; i < buildings.size(); ++i){
            points.push_back({buildings[i][0], OPEN, i});
            points.push_back({buildings[i][1], CLOSE, i});
        }
        
        //sort by OPEN and CLOSE is important!!
        sort(points.begin(), points.end(),
             [](vector<int>& a, vector<int>& b){
                 return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0];
             });
        
        unordered_map<int, int> fw;
        int n = 1;
        
        //index starts from 1, aligned with "BIT"!!
        for(const vector<int>& point : points){
            fw[point[0]] = n;
            // cout << n << " <---> " << point[0] << endl;
            ++n;
        }
        
        vector<int> BIT(n+1);
        
        vector<vector<int>> ans;
        
        int preH = INT_MIN, h;
        
        for(const vector<int>& point : points){
            // cout << "========" << endl;
            // cout << "x: " << point[0] << endl;
            if(point[1] == OPEN){
                //only update BIT when we meet left boundary
                //set "arr[fw[point[1]]-1]" to the building's height
                //-1 because right boundary won't contribute to skyline
                // cout << "add: (" << fw[point[1]]-1 << ", " << point[2] << ")" << endl;
                add(BIT, fw[buildings[point[2]][1]]-1, buildings[point[2]][2]);
            }
            // cout << "========" << endl;
            //query for current x-coord
            h = find(BIT, fw[point[0]]);
            // cout << "query: " << fw[point[0]] << " -> " << h << endl;
            if(h == preH) continue;
            if(!ans.empty() && ans.back()[0] == point[0]){
                ans.back()[1] = max(ans.back()[1], h);
            }else{
                ans.push_back({point[0], h});
            }
            preH = h;
        }
        
        return ans;
    }
};

