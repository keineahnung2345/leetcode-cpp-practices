//TLE
//2 / 35 test cases passed.
struct vector_hash {
    inline std::size_t operator()(const std::vector<int> & v) const {
        return v[0]*31+v[1];
    }
};

class Solution {
public:
    unordered_set<vector<int>, vector_hash> points;
    
    Solution(vector<vector<int>>& rects) {
        for(vector<int>& rect : rects){
            int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
            
            for(int x = x1; x <= x2; ++x){
                for(int y = y1; y <= y2; ++y){
                    points.insert({x, y});
                }
            }
        }
    }
    
    vector<int> pick() {
        int idx = rand() % points.size();
        auto it = points.begin();
        advance(it, idx);
        return *it;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */
 
//use rand() once
//https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/discuss/155456/Java-solution-with-just-call-one-Random()-for-each-Pick()!!!666
//https://leetcode.com/problems/random-point-in-non-overlapping-rectangles/discuss/154130/Java-Solution.-Randomly-pick-a-rectangle-then-pick-a-point-inside./235726
//Runtime: 136 ms, faster than 55.87% of C++ online submissions for Random Point in Non-overlapping Rectangles.
//Memory Usage: 68.6 MB, less than 31.92% of C++ online submissions for Random Point in Non-overlapping Rectangles.
class Solution {
public:
    vector<vector<int>> rects;
    //(accumulated area sum, index of rect)
    map<int, int> accArea2idx;
    int accArea;
    
    Solution(vector<vector<int>>& rects) {
        this->rects = rects;
        accArea = 0;
        for(int i = 0; i < rects.size(); ++i){
            int x1 = rects[i][0], y1 = rects[i][1], x2 = rects[i][2], y2 = rects[i][3];
            //we know that the rects are non-overlapping
            accArea += (x2-x1+1) * (y2-y1+1);
            accArea2idx[accArea] = i;
        }
    }
    
    vector<int> pick() {
        //choose a random number in the range: [1, accArea]
        int ri = rand() % accArea + 1;
        /*
        important!!!
        in C++: lower_bound: >= , upper_bound: >
        in Java: floorKey: <=, ceilingKey: >=
        so here we translate the Java ceilingKey into lower_bound!!!
        */
        auto rit = accArea2idx.lower_bound(ri);
        //the index of rectangle
        int ridx = rit->second;
        //the index of point in the rectangle
        
        vector<int> rect = rects[ridx];
        int x1 = rect[0], y1 = rect[1], x2 = rect[2], y2 = rect[3];
        
        //method 1: use rand() twice
        // ri = rand() % ((x2-x1+1)*(y2-y1+1));
        
        //method 2: use rand() once
        ri = rit->first - ri;
        //sanity check
        // if(ri <= 0)
        //     cout << rit->first << ", " << ri << endl;
        int x = x1 + ri % (x2-x1+1);
        int y = y1 + ri / (x2-x1+1);
        return {x, y};
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(rects);
 * vector<int> param_1 = obj->pick();
 */
