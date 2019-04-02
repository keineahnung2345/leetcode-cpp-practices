//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.
//Memory Usage: 8.5 MB, less than 55.79% of C++ online submissions for Climbing Stairs.
class Solution {
public:
    int climbStairs(int n) {
        if(n == 1) return 1;
        vector<int> steps(n);
        
        // cout << "size: " << steps.size() << endl;
        
        steps[0] = 1; //1+0 step from the top
        steps[1] = 2; //1+1 step from the top
        
        for(int i = 2; i < n; i++){
            steps[i] = steps[i-1] + steps[i-2];
            // cout << steps[i] << endl;
        }
        
        return steps[n-1];
    }
};

//Runtime: 4 ms, faster than 100.00% of C++ online submissions for Climbing Stairs.
//Memory Usage: 8.2 MB, less than 97.68% of C++ online submissions for Climbing Stairs.
/**
class Solution {
public:
    int climbStairs(int n) {
        if(n <= 2) return n;
        
        int last = 1, last2 = 2;
        
        for(int i = 2; i < n; i++){
            int tmp = last2;
            last2 = last + last2;
            last = tmp;
            // cout << last << " " << last2 << endl;
        }
        // cout << endl;
        
        return last2;
    }
};
**/
