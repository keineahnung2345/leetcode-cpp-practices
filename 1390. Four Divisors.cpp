//Runtime: 304 ms, faster than 24.76% of C++ online submissions for Four Divisors.
//Memory Usage: 22.2 MB, less than 100.00% of C++ online submissions for Four Divisors.
class Solution {
public:
    map<int, vector<int>> divisors;
    
    void getDivisorCount(int num){
        // cout << "num: " << num << endl;
        if(divisors.find(num) == divisors.end()){
            for(int i = 1; i <= sqrt(num); i++){
                // cout << i << endl;
                if(num % i == 0){
                    divisors[num].push_back(i);
                    if(i != sqrt(num))divisors[num].push_back(num/i);
                }
            }
        }
    }
    
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;
        for(int num : nums){
            getDivisorCount(num);
            if(divisors[num].size() == 4){
                ans += accumulate(divisors[num].begin(), divisors[num].end(), 0);
            }
        }
        return ans;
    }
};
