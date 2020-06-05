//http://www.cplusplus.com/reference/random/discrete_distribution/
//https://stackoverflow.com/questions/1761626/weighted-random-numbers
//Runtime: 188 ms, faster than 50.33% of C++ online submissions for Random Pick with Weight.
//Memory Usage: 42 MB, less than 5.06% of C++ online submissions for Random Pick with Weight.
class Solution {
public:
    vector<int> w;
    std::discrete_distribution<int> dist;;
    std::mt19937 gen;
    
    Solution(vector<int>& w) {
        this->w = w;
        this->dist = std::discrete_distribution<int>(std::begin(w), std::end(w));
        // this->gen.seed(time(0));//if you want different results from different runs
    }
    
    int pickIndex() {
        //cannot initialize dist and gen here!!
        return dist(gen);
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
 
