//Approach #1: Principle of Inclusion-Exclusion
//TLE
//46 / 76 test cases passed.
//time: O(N*2^N), space: O(N)
class Solution {
public:
    vector<int> intersect(vector<int>& rec1, vector<int>& rec2){
        //the returned rectangle will have negative side if the two input rectangles have no intersection
        return {max(rec1[0], rec2[0]),
               max(rec1[1], rec2[1]),
               min(rec1[2], rec2[2]),
               min(rec1[3], rec2[3])};
    };
    
    long area(vector<int>& rec){
        long dx = max(rec[2] - rec[0], 0);
        long dy = max(rec[3] - rec[1], 0);
        return dx*dy;
    }
    
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        
        long ans = 0;
        for(int subset = 1; subset < (1<<n); subset++){
            //subset from 0001 to 1111
            //maximum possible rectangle
            vector<int> rec = {0, 0, (int)1e9, (int)1e9};
            int parity = -1;
            //inspect the subset, start from least significant bit
            for(int bit = 0; bit < n; bit++){
                if((subset>>bit) & 1){
                    rec = intersect(rec, rectangles[bit]);
                    parity *= -1;
                }
            }
            /*
            if there are odd set bits, parity is 1
            otherwise parity is -1
            */
            ans += parity * area(rec);
        }
        
        long mod = 1e9+7;
        ans %= mod;
        
        //?
        if(ans < 0) ans += mod;
        return ans;
    }
};

//Approach #2: Coordinate Compression
//Runtime: 196 ms, faster than 6.10% of C++ online submissions for Rectangle Area II.
//Memory Usage: 8.3 MB, less than 100.00% of C++ online submissions for Rectangle Area II.
//time: O(N^3), space: O(N^2)
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        set<int> xvals, yvals;
        
        for(vector<int>& rec : rectangles){
            xvals.insert(rec[0]);
            yvals.insert(rec[1]);
            xvals.insert(rec[2]);
            yvals.insert(rec[3]);
        }
        
        vector<int> imapx(xvals.begin(), xvals.end());
        vector<int> imapy(yvals.begin(), yvals.end());
        sort(imapx.begin(), imapx.end());
        sort(imapy.begin(), imapy.end());
        
        map<int, int> mapx, mapy;
        // cout << "imapx: " << endl;
        for(int i = 0; i < imapx.size(); i++){
            mapx[imapx[i]] = i;
            // cout << i << " " << imapx[i] << endl;
        }
        // cout << "imapy: " << endl;
        for(int i = 0; i < imapy.size(); i++){
            mapy[imapy[i]] = i;
            // cout << i << " " << imapy[i] << endl;
        }
        
        vector<vector<bool>> grid = vector(imapx.size(), vector(imapy.size(), false));
        for(vector<int>& rec : rectangles){
            //fill the corresponding grids
            for(int x = mapx[rec[0]]; x < mapx[rec[2]]; x++){
                for(int y = mapy[rec[1]]; y < mapy[rec[3]]; y++){
                    grid[x][y] = true;
                }
            }
        }
        
        long ans = 0;
        
        for(int x = 0; x < grid.size(); x++){
            for(int y = 0; y < grid[0].size(); y++){
                if(grid[x][y]){
                    ans += (long)(imapx[x+1] - imapx[x]) * (imapy[y+1] - imapy[y]) % ((int)1e9+7);
                    ans %= ((int)1e9+7);
                }
            }
        }
        
        ans %= ((int)1e9+7);
        
        return ans;
    }
};

//Approach #3: Line Sweep
//Runtime: 16 ms, faster than 43.29% of C++ online submissions for Rectangle Area II.
//Memory Usage: 7.1 MB, less than 100.00% of C++ online submissions for Rectangle Area II.
//time: O(N^2* logN), space: O(N^2)
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int OPEN = 0, CLOSE = 1;
        int n = rectangles.size();
        //every rectangle form two events
        vector<vector<int>> events(n*2);
        
        int i = 0;
        for(vector<int>& rec : rectangles){
            //horizontal line(y-coordinate), open or close, x1, x2
            events[i++] = {rec[1], OPEN, rec[0], rec[2]};
            events[i++] = {rec[3], CLOSE, rec[0], rec[2]};
        }
        //sort by y
        sort(events.begin(), events.end(),
            [](vector<int>& a, vector<int>& b){
                return a[0] < b[0];
            });
        
        //actives: vector of (x1,x2), currently opening events
        vector<vector<int>> actives;
        int last_y = events[0][0];
        long ans = 0;
        for(vector<int>& event : events){
            int y = event[0];
            bool isClose = event[1];
            int x1 = event[2], x2 = event[3];
            
            /*
            query: on current horizontal line, 
            the length of intervals formed by active events
            */
            long query = 0;
            int cur = INT_MIN;
            // cout << "y: [" << last_y << ", " << y << "]" << endl;
            for(vector<int>& active : actives){
                cur = max(cur, active[0]);
                // cout << "x: [" << active[0] << ", " << active[1] << "], cur: " << cur << ", width: " << max(active[1] - cur, 0) << endl;
                /*
                cur: last right boundary, 
                since rectangles may overlap,
                so we need the max()
                */
                query += max(active[1] - cur, 0);
                cur = max(cur, active[1]);
            }
            
            // cout << "width: " << query << ", height: " << y - last_y << endl;
            /*
            query: the total length in horizontal direction
            y - last_y: the height of current rectangle
            */
            ans += query * (y - last_y);
            
            //update actives(current open events)
            if(!isClose){
                actives.push_back({x1, x2});
                sort(actives.begin(), actives.end(),
                    [](vector<int>& a, vector<int>& b){
                        return a[0] < b[0];
                    });
            }else{
                //find out the corresponding open active event and erase it
                for(auto it = actives.begin(); it != actives.end(); it++){
                    if((*it)[0] == x1 && (*it)[1] == x2){
                        actives.erase(it);
                        break;
                    }
                }
            }
            
            // cout << "actives: ";
            // for(auto it = actives.begin(); it != actives.end(); it++){
            //     cout << (*it)[0] << ", " << (*it)[1] << " | ";
            // }
            // cout << endl;
            
            last_y = y;
        }
        
        ans %= (int)1e9+7;
        return ans;
    }
};

//Approach #4: Segment Tree
//Runtime: 24 ms, faster than 26.22% of C++ online submissions for Rectangle Area II.
//Memory Usage: 20.8 MB, less than 25.00% of C++ online submissions for Rectangle Area II.
//time: O(N* logN), space: O(N)
class Node {
public:
    int start, end;
    vector<int> X;
    Node *left, *right;
    int count;
    long total;
    
    Node(int start, int end, vector<int> X){
        this->start = start;
        this->end = end;
        this->X = X;
        left = nullptr;
        right = nullptr;
        count = 0;
        total = 0;
    }
    
    int getRangeMid(){
        return start + (end-start)/2;
    }
    
    Node* getLeft(){
        if(left == nullptr) left = new Node(start, getRangeMid(), X);
        return left;
    }
    
    Node* getRight(){
        if(right == nullptr) right = new Node(getRangeMid(), end, X);
        return right;
    }
    
    long update(int i, int j, int val){
        if(i >= j) return 0;
        if(start == i && end == j){
            count += val;
        }else{
            getLeft()->update(i, min(getRangeMid(), j), val);
            getRight()->update(max(getRangeMid(), i), j, val);
        }
        
        if(count > 0) total = X[end] - X[start];
        else total = getLeft()->total + getRight()->total;
        
        return total;
    }
};

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int OPEN = 1, CLOSE = -1;
        int n = rectangles.size();
        vector<vector<int>> events(n*2);
        set<int> xvals_set;
        
        int i = 0;
        for(vector<int>& rec : rectangles){
            //horizontal line, open or close, x1, x2
            events[i++] = {rec[1], OPEN, rec[0], rec[2]};
            events[i++] = {rec[3], CLOSE, rec[0], rec[2]};
            xvals_set.insert(rec[0]);
            xvals_set.insert(rec[2]);
        }
        //sort by y
        sort(events.begin(), events.end(),
            [](vector<int>& a, vector<int>& b){
                return a[0] < b[0];
            });
        
        vector<int> xvals(xvals_set.begin(), xvals_set.end());
        sort(xvals.begin(), xvals.end());
        
        map<int, int> rxvals;
        for(int i = 0; i < xvals.size(); i++){
            rxvals[xvals[i]] = i;
        }
        
        int last_y = events[0][0];
        long ans = 0;
        long cur_x_sum = 0;
        Node active(0, xvals.size()-1, xvals);
        
        for(vector<int>& event : events){
            int y = event[0];
            int type = event[1];
            int x1 = event[2], x2 = event[3];
            
            ans += cur_x_sum * (y - last_y);
            cur_x_sum = active.update(rxvals[x1], rxvals[x2], type);
            last_y = y;
        }
        
        ans %= (int)1e9+7;
        return ans;
    }
};
