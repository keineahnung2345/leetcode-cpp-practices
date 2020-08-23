//dfs + memorization, using unordered_map
//Runtime: 1424 ms, faster than 12.50% of C++ online submissions for Stone Game V.
//Memory Usage: 34.6 MB, less than 12.50% of C++ online submissions for Stone Game V.
struct pair_hash_int {
    inline std::size_t operator()(const std::pair<int,int> & v) const {
        return v.first*31+v.second;
    }
};

class Solution {
public:
    unordered_map<pair<int, int>, int, pair_hash_int> memo;
    
    int stoneGameV(vector<int>& stoneValue, int start = -1, int end = -1) {
        int score = 0;
        if(start == -1) start = 0;
        if(end == -1) end = stoneValue.size();
        if(end-start <= 1) return score;
        
        if(memo.find({start, end}) != memo.end()){
            return memo[{start, end}];
        }
        
        int sum = accumulate(stoneValue.begin()+start, stoneValue.begin()+end, 0);
        int leftsum = 0;

        //left part: [0...i]
        for(int i = start; i < end; ++i){
            leftsum += stoneValue[i];
            
            if(leftsum > sum-leftsum){
                //discard left
                //remain [pos+1...]
                // cout << "add " << sum-leftsum << endl;
                score = max(score, sum-leftsum + stoneGameV(stoneValue, i+1, end));
            }else if(leftsum < sum-leftsum){
                //discard right
                //remain [0...pos]
                // cout << "add " << leftsum << endl;
                score = max(score, leftsum + stoneGameV(stoneValue, start, i+1));
            }else{
                //leftsum == sum-leftsum
                int leftres = stoneGameV(stoneValue, start, i+1);
                int rightres = stoneGameV(stoneValue, i+1, end);
                // cout << "add " << leftsum << endl;
                score = max(score, leftsum + max(leftres, rightres));
            }
        }
        
        return memo[{start, end}] = score;
    }
};

//dfs + memorization, using 2d array rather than unordered_map for speed up
//Runtime: 204 ms, faster than 37.50% of C++ online submissions for Stone Game V.
//Memory Usage: 10.7 MB, less than 50.00% of C++ online submissions for Stone Game V.
class Solution {
public:
    int memo[501][501];
    
    int stoneGameV(vector<int>& stoneValue, int start, int end) {
        int score = 0;
        if(start == -1) start = 0;
        if(end == -1) end = stoneValue.size();
        if(end-start <= 1) return score;
        
        if(memo[start][end] != -1){
            return memo[start][end];
        }
        
        int sum = accumulate(stoneValue.begin()+start, stoneValue.begin()+end, 0);
        int leftsum = 0;

        //left part: [0...i]
        for(int i = start; i < end; ++i){
            leftsum += stoneValue[i];
            
            if(leftsum > sum-leftsum){
                //discard left
                //remain [pos+1...]
                // cout << "add " << sum-leftsum << endl;
                score = max(score, sum-leftsum + stoneGameV(stoneValue, i+1, end));
            }else if(leftsum < sum-leftsum){
                //discard right
                //remain [0...pos]
                // cout << "add " << leftsum << endl;
                score = max(score, leftsum + stoneGameV(stoneValue, start, i+1));
            }else{
                //leftsum == sum-leftsum
                int leftres = stoneGameV(stoneValue, start, i+1);
                int rightres = stoneGameV(stoneValue, i+1, end);
                // cout << "add " << leftsum << endl;
                score = max(score, leftsum + max(leftres, rightres));
            }
        }
        
        return memo[start][end] = score;
    } 
    
    int stoneGameV(vector<int>& stoneValue) {
        memset(&memo[0][0], -1, sizeof(memo));
        return stoneGameV(stoneValue, -1, -1);
    }
};
