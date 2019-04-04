//Runtime: 16 ms, faster than 93.26% of C++ online submissions for Maximize Distance to Closest Person.
//Memory Usage: 10.3 MB, less than 72.29% of C++ online submissions for Maximize Distance to Closest Person.

class Solution {
public:
    int dist(int d){
        //input: the distance btw two seated seats
        //output: if one person seat btw them, what's the distance of him to the closest person?
        return d/2;
    }
    int maxDistToClosest(vector<int>& seats) {
        int N = seats.size();
        vector<int> seated;
        int ans = 1;
        
        for(int i = 0; i < N; i++){
            if(seats[i] == 1) seated.push_back(i);
        }
        
        //only one seat seated
        if(seated.size() == 1) return max(N-1-seated[0], seated[0]);
        
        //multiple seats seated
        //boundary condition: seats at first position
        ans = seated[0];
        for(int i = 1; i < seated.size(); i++){
            // cout << seated[i] << " " << seated[i-1] << " " << dist(seated[i] - seated[i-1]) << endl;
            ans = max(ans, dist(seated[i] - seated[i-1]));
        }
        //boundary condition: seats at last position
        ans = max(ans, N-1-seated[seated.size()-1]);
        
        return ans;
    }
};

/**
Approach #1: Next Array [Accepted]
first calculate the distance to left/right person
**/

/**
time: O(N), space: O(N)
**/

//Runtime: 16 ms, faster than 93.26% of C++ online submissions for Maximize Distance to Closest Person.
//Memory Usage: 10.7 MB, less than 19.28% of C++ online submissions for Maximize Distance to Closest Person.

/**
class Solution {
public:
    int maxDistToClosest(vector<int>& seats) {
        int N = seats.size();
        //the distance of a seat to its left/right person
        //note that we initialize the two vectors with value N
        
        //for [1,0,0,0]:
        //right is [0,6,5,4]
        //left is [0,1,2,3]
        //and we use min(left, right), so when we look at the area behind the last 1, right is invalid
        
        //for [0,0,0,1]
        //left is [4,5,6,0]
        //right is [3,2,1,0]
        //similarily, left is invalid when looking at the area behore the first 1
        
        vector<int> left(N, N), right(N, N);
        
        for(int i = 0; i < N; i++){
            if(seats[i] == 1) left[i] = 0;
            else if(i > 0) left[i] = left[i-1] + 1;
        }
        
        for (int i = N-1; i >= 0; --i) {
            if (seats[i] == 1) right[i] = 0;
            else if(i < N-1) right[i] = right[i+1] + 1;
        }
        
//         for(int i = 0; i < N; i++){
//             cout << left[i] << " ";
//         }
//         cout << endl;
        
//         for(int i = 0; i < N; i++){
//             cout << right[i] << " ";
//         }
//         cout << endl;
        
        int ans = 0;
        for(int i = 0; i < N; i++){
            if(seats[i] == 0)
                ans = max(ans, min(left[i], right[i]));
        }
        return ans;
    }
};
**/
