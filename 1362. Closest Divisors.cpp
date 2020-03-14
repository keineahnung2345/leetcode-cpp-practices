//Runtime: 12 ms, faster than 50.05% of C++ online submissions for Closest Divisors.
//Memory Usage: 7.4 MB, less than 100.00% of C++ online submissions for Closest Divisors.
class Solution {
public:
    vector<int> closestDivisors(int num) {
        int a = num+1, b = num+2;
        int dist = INT_MAX;
        vector<int> ans;
        for(int i = 1; i <= int(sqrt(a)); i++){
            if(a % i == 0){
                if(abs(i - a/i) < dist){
                    dist = abs(i - b/i);
                    ans = {i, a/i};
                }
            }
        }
        
        for(int i = 1; i <= int(sqrt(b)); i++){
            if(b % i == 0){
                if(abs(i - b/i) < dist){
                    dist = abs(i - b/i);
                    ans = {i, b/i};
                }
            }
        }
        
        return ans;
    }
};
