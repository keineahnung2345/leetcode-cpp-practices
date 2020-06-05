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
 
//binary search
//https://leetcode.com/problems/random-pick-with-weight/discuss/154044/Java-accumulated-freq-sum-and-binary-search
//Runtime: 180 ms, faster than 64.49% of C++ online submissions for Random Pick with Weight.
//Memory Usage: 40.6 MB, less than 34.54% of C++ online submissions for Random Pick with Weight.
class Solution {
public:
    //accumulated sum
    vector<int> acc;
    
    Solution(vector<int>& w) {
        this->acc = w;
        for(int i = 1; i < this->acc.size(); i++){
            this->acc[i] += this->acc[i-1];
        }
        /*
        for w = [1, 4, 2],
        we have acc = [1, 5, 7],
        this represents 3 groups: [1], [2...4], [5...7]
        
        we will random generate a number in the range [1,7],
        and then assign it to one of the groups above,
        for example if w generate idx = 3, 
        we will assign it to the group [2...4](4 is just above 3),
        and then get the group's index as answer
        */
    }
    
    int pickIndex() {
        //a number in the range [1...acc[acc.size()-1]]
        int num = rand()%acc[acc.size()-1]+1;
        
        /*
        binary search to find the index left or mid
        s.t. acc[left] > num or acc[mid] == num
        
        i.e. find left boundary
        */
        
        int left = 0, right = acc.size()-1;
        
        while(left <= right){
            int mid = left + (right-left)/2;
            
            if(num == acc[mid]){
                return mid;
            }else if(num < acc[mid]){
                right = mid-1;
            }else/* if(num > acc[mid])*/{
                left = mid+1;
            }
        }
        
        return left;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
