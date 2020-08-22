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
 
