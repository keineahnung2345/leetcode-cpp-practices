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

//https://leetcode.com/problems/queue-reconstruction-by-height/discuss/89345/Easy-concept-with-PythonC%2B%2BJava-Solution
//construct a subarray an then insert one by one
//Runtime: 80 ms, faster than 76.98% of C++ online submissions for Queue Reconstruction by Height.
//Memory Usage: 11.8 MB, less than 100.00% of C++ online submissions for Queue Reconstruction by Height.

class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int N = people.size();
        //need to return empty 2d array for empty input
        if(N == 0) return vector<vector<int>>();
        vector<vector<int>> ans;
        //cannot simply use this?
        // vector<vector<int>> ans = vector<vector<int>>();
        
        //first sort by "h"(descending), and then by "k"(ascending)
        sort(people.begin(), people.end(), [](vector<int>& a, vector<int>& b){return (a[0] == b[0]) ? (a[1] < b[1]) : a[0] > b[0];});
        
        int maxh = people[0][0];
        
        //create subarray containing people with max height
        for(int i = 0; i < N; i++){
            if(people[i][0] == maxh){
                ans.push_back(people[i]);
            }else{
                ans.insert(ans.begin()+people[i][1], people[i]);
            }
        }
        
        return ans;
    }
};
