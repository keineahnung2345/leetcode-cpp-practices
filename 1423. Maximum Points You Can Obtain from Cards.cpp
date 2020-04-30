//MLE
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        if(n <= k) return accumulate(cardPoints.begin(), cardPoints.end(), 0);
        cardPoints.insert(cardPoints.begin(), 0);
        cardPoints.push_back(0);
        
        vector<vector<int>> last(n+2, vector(k+1, 0));
        vector<vector<int>> cur(n+2, vector(k+1, 0));
        
        for(int width = 1; width <= n; width++){
            for(int left = 1; left + width -1 <= n; left++){
                int right = left + width -1;
                for(int taken = 1; taken <= min(k, right-left+1); taken++){
                    cur[left][taken] = max({cur[left][taken],
                        last[left+1][taken-1] + cardPoints[left],
                        last[left][taken-1] + cardPoints[right]});
                    // cout << left << " " << right << " " << taken << " " << dp[left][right][taken] << endl;
                    swap(last, cur);
                    cur = vector<vector<int>>(n+2, vector(k+1, 0));
                }
            }
        }
        
        // return last[n][k];
        return cur[n][k];
    }
};

//DP+Sliding window
//Runtime: 148 ms, faster than 76.21% of C++ online submissions for Maximum Points You Can Obtain from Cards.
//Memory Usage: 42.5 MB, less than 100.00% of C++ online submissions for Maximum Points You Can Obtain from Cards.
class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int n = cardPoints.size();
        //the remaining cards must be continuous
        int remainCount = n - k;
        int remainSum = accumulate(cardPoints.begin(), cardPoints.begin()+n-k, 0);
        int minRemainSum = remainSum;
        int totalSum = remainSum;
        
        for(int i = n-k; i < n; i++){
            remainSum += (cardPoints[i] - cardPoints[i-(n-k)]);
            minRemainSum = min(minRemainSum, remainSum);
            totalSum += cardPoints[i];
        }
        
        return totalSum - minRemainSum;
    }
};
