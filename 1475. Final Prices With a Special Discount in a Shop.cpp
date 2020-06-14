//Runtime: 12 ms, faster than 33.33% of C++ online submissions for Final Prices With a Special Discount in a Shop.
//Memory Usage: 10 MB, less than 100.00% of C++ online submissions for Final Prices With a Special Discount in a Shop.
class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        int n = prices.size();
        vector<int> ans(n);
        
        for(int i = 0; i < n; i++){
            int j;
            for(j = i+1; j < n; j++){
                if(prices[j] <= prices[i]){
                    break;
                }
            }
            if(j < n && prices[j] <= prices[i]){
                prices[i] -= prices[j];
            }
        }
        
        return prices;
    }
};
