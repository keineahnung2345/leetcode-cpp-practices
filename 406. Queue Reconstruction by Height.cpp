//Hint 1: What can you say about the position of the shortest person?
//If the position of the shortest person is i, how many people would be in front of the shortest person?
//Hint 2: Once you fix the position of the shortest person, what can you say about the position of the second shortest person?

//Runtime: 92 ms, faster than 44.28% of C++ online submissions for Queue Reconstruction by Height.
//Memory Usage: 11.5 MB, less than 100.00% of C++ online submissions for Queue Reconstruction by Height.

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int N = people.size();
        vector<vector<int>> ans(N);
        vector<bool> filled(N, false);
        
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b){return (a[0] == b[0]) ? (a[1] < b[1]) : (a[0] < b[0]);});
        
        for(int i = 0; i < N; i++){
            int value =  people[i][0], largerCount = people[i][1];
            // cout << "value & count: " << value << " " << largerCount << endl;
            //want to find a empty position with j larger values before
            //so we actually want to find (j+1)th(1-based) position which is empty or has value >= people[i][0]
            int pos, j;
            for(pos = 0, j = 0; j <= largerCount; pos++){
                if(!filled[pos] || (filled[pos] && ans[pos][0] >= value))
                    j++;
                // cout << pos << " " << j << endl;
            }
            pos--;
            // cout << pos << " " << j << endl;
           
            ans[pos] = people[i];
            filled[pos] = true;
        }
        
        return ans;
    }
};
