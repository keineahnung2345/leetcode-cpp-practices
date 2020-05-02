//Runtime error(MLE)
//209 / 211 test cases passed.
//time: O(N*k), space: O(k)
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //0th element for padding
        vector<int> holds(k+1, INT_MIN);
        vector<int> cashs(k+1, 0);
        int ans = 0;
        
        for(int price : prices){
            // cout << "price: " << price << endl;
            for(int i = k; i >= 1; i--){
                /*
                we should update cashs[i] and then holds[i]!
                because when we update cashs[i],
                we need holds[i] in last iteration!
                */
                /*
                hold-cash makes a transaction,
                so holds[i]+price means 
                selling the stock bought in ith transaction
                */
                cashs[i] = max(cashs[i], holds[i]+price);
                holds[i] = max(holds[i], cashs[i-1]-price);
                // cout << i << ", " << holds[i] << ", " << cashs[i] << endl;
                ans = max(ans, cashs[i]);
            }
        }
        
        return ans;
    }
};

//Time Limit Exceeded
//209 / 211 test cases passed.
//time: O(N*k), space: O(min(n,k))
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        //0th element for padding
        vector<int> holds(min(n,k)+1, INT_MIN);
        vector<int> cashs(min(n,k)+1, 0);
        int ans = 0;
        
        for(int price : prices){
            // cout << "price: " << price << endl;
            for(int i = min(n,k); i >= 1; i--){
                /*
                we should update cashs[i] and then holds[i]!
                because when we update cashs[i],
                we need holds[i] in last iteration!
                */
                /*
                hold-cash makes a transaction,
                so holds[i]+price means 
                selling the stock bought in ith transaction
                */
                cashs[i] = max(cashs[i], holds[i]+price);
                holds[i] = max(holds[i], cashs[i-1]-price);
                // cout << i << ", " << holds[i] << ", " << cashs[i] << endl;
                ans = max(ans, cashs[i]);
            }
        }
        
        return ans;
    }
};
