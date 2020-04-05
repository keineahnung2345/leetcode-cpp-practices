//Runtime: 12 ms, faster than 42.86% of C++ online submissions for Reducing Dishes.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Reducing Dishes.
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        bool allPos = true, allNeg = true;
        for(int s : satisfaction){
            if(s > 0) allNeg = false;
            if(s < 0) allPos = false;
            if(!allPos && !allNeg) break;
        }
        if(allNeg) return 0;
        
        int ltc = 0;
        
        sort(satisfaction.begin(), satisfaction.end());
        for(int i = 0; i < satisfaction.size(); i++){
            // cout << i << " " << satisfaction[i] << endl;
            ltc += (i+1) * satisfaction[i];
        }
        
        if(allPos){
            return ltc;
        }
        
        // cout << "ltc: " << ltc << endl;
        
        //part neg, part pos
        int ans = 0;
        int sum = accumulate(satisfaction.begin(), satisfaction.end(), 0);
        for(int i = 0; i < satisfaction.size(); i++){
            if(i > 0){
                //update ltc
                ltc -= sum;
                sum -= satisfaction[i-1];
            }
            // cout << ltc << " " << sum << endl;
            ans = max(ans, ltc);
        }
        
        return ans;
    }
};

//clean
//https://leetcode.com/problems/reducing-dishes/discuss/563384/JavaC%2B%2BPython-Easy-and-Concise
//Runtime: 8 ms, faster than 42.86% of C++ online submissions for Reducing Dishes.
//Memory Usage: 6.5 MB, less than 100.00% of C++ online submissions for Reducing Dishes.
//time: O(NlogN), space: O(1)
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        //descending order
        sort(satisfaction.rbegin(), satisfaction.rend());
        
        int ans = 0, sum = 0, ltc = 0;
        
        /*
        because we will add (original sum + satisfaction[i]) to ans,
        we don't want it to be negative, 
        so we jump out if satisfaction[i] + sum <= 0
        */
        for(int i = 0; i < satisfaction.size() && satisfaction[i] + sum > 0; i++){
            //cumulative sum : satisfaction[0...i]
            sum += satisfaction[i];
            //we add (original sum + satisfaction[i]) to ans
            //[0...i-1]'s cooking time is increased by 1
            //, and newly add satisfaction[i]
            ans += sum;
        }
        
        return ans;
    }
};
