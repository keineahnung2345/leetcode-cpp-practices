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
