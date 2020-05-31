//backtracking
//https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/discuss/661723/Struggling-with-probability-problems-Read-this.
//the function perm() borrows from https://leetcode.com/problems/probability-of-a-two-boxes-having-the-same-number-of-distinct-balls/discuss/661730/C%2B%2B-Backtrack-with-explanation
//Runtime: 1336 ms, faster than 100.00% of C++ online submissions for Probability of a Two Boxes Having The Same Number of Distinct Balls.
//Memory Usage: 6.7 MB, less than 100.00% of C++ online submissions for Probability of a Two Boxes Having The Same Number of Distinct Balls.
class Solution {
public:
    //use double to avoid overflow
    double good, all;
    
    double perm(vector<int>& v){
        /*
        v contains the count of balls of different colors
        e.g. v = [1, 3, 2] means the balls are 0, 1, 1, 1, 2, 2
        this function return the permutation count,
        i.e. 6!/(1!3!2!),
        here we calculate 6! by multiplying nom with ans while nom increasing,
        we calculate 1!, 3!, 2! by dividing ans by denom from 1 to v[i] for all i
        */
        // cout << "calculating perm of : " << endl;
        // for(int e : v){
        //     cout << e << " ";
        // }
        // cout << endl;
        
        double ans = 1;
        int nom = 1;
        for(int i = 0; i < v.size(); i++){
            for(int denom = 1; denom <= v[i]; denom++){
                ans = ans * nom /denom;
                // cout << " * " << nom << " / " << denom << endl;
                nom++;
            }
        }
        // cout << "perm of v: " << ans << endl;
        return ans;
    };
    
    void backtrack(vector<int>& balls, vector<int>& firstHalf, vector<int>& secondHalf, int cur){
        if(cur == balls.size()){
            //stop condition
            if(accumulate(firstHalf.begin(), firstHalf.end(), 0) !=
                accumulate(secondHalf.begin(), secondHalf.end(), 0)){
                //their count should be the same!
                return;
            }
            
            //use double to avoid overflow
            double perm1 = perm(firstHalf);
            double perm2 = perm(secondHalf);
            
            all += perm1 * perm2;
            
            //check if their distinct color counts are the same
            int dcount1 = count_if(firstHalf.begin(), firstHalf.end(), 
                                  [](const int& x){
                                      return x != 0;
                                  });
            int dcount2 = count_if(secondHalf.begin(), secondHalf.end(), 
                                  [](const int& x){
                                      return x != 0;
                                  });
            good += (dcount1 == dcount2) ? perm1 * perm2 : 0;
        }else{
            //continue until cur == balls.size()
            /*
            for the color "cur",
            there are balls[cur] balls of this color,
            distribute i balls to firstHalf,
            and the remaining to secondHalf
            */
            for(int i = 0; i <= balls[cur]; i++){
                firstHalf[cur] = i;
                secondHalf[cur] = balls[cur] - i;
                backtrack(balls, firstHalf, secondHalf, cur+1);
            }
        }
    };
    
    double getProbability(vector<int>& balls) {
        good = all = 0;
        int n = balls.size();
        vector<int> firstHalf(n, 0), secondHalf(n, 0);
        backtrack(balls, firstHalf, secondHalf, 0);
        return good/all;
    }
};
