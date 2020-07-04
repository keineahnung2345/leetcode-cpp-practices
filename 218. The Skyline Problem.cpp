//line sweep
//TLE
//35 / 36 test cases passed.
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int OPEN = 0, CLOSE = 1;
        int n = buildings.size();
        //vector of {x coord, open or close, height, building_id}
        vector<vector<int>> events(n*2);
        
        for(int i = 0; i < n; ++i){
            events[i*2] = {buildings[i][0], OPEN, buildings[i][2], i};
            events[i*2+1] = {buildings[i][1], CLOSE, buildings[i][2], i};
        }
    
        //actives: current opening events' event_id
        vector<int> actives;
        vector<vector<int>> ans;
        
        //sort by x coord
        sort(events.begin(), events.end());
        
        // cout << "event" << endl;
        // for(vector<int>& event : events){
        //     cout << "x: " << event[0] << ", " << (event[1] ? "CLOSE" : "OPEN") << ", height: " << event[2] << endl;
        // }
        
        int lastX = INT_MIN;
        int lastMaxHeight = INT_MIN;
        
        //vertical line sweep along x-axis
        for(int eventId = 0; eventId < events.size(); ++eventId){
            //extract the required infos
            int x = events[eventId][0];
            bool isClose = events[eventId][1];
            int height = events[eventId][2];
            
            // cout << "x: " << x << ", isClose: " << isClose << ", height: " << height << endl;
            
            if(!isClose){
                actives.push_back(eventId);
            }else{
                //find the corresponding OPEN event and remove it
                for(int i = 0; i < actives.size(); ++i){
                    if(events[actives[i]][2] == height){
                        actives.erase(actives.begin()+i);
                        break;
                    }
                }
            }
            
            // cout << "active: ";
            // for(int& active : actives){
            //     cout << active << " ";
            // }
            // cout << endl;
            
            //get the maximum height of active events
            int maxHeight = 0;
            
            //update actives
            if(!actives.empty()){
                for(int i = 0; i < actives.size(); ++i){
                    if(events[actives[i]][1] != CLOSE){
                        maxHeight = max(maxHeight, events[actives[i]][2]);
                    }
                }
            }
            
            // cout << "maxHeight: " << maxHeight << endl;
            
            //update ans only if x is leftmost or rightmost of actives
            if(actives.empty()){
                //the right boundary of connected buildings
                ans.push_back({x, maxHeight});
            }else if(!ans.empty() && x == ans.back()[0]){
                //current event and last event has same x
                //update its height
                ans.back()[1] = maxHeight;
            }else{
                //there is a change in height
                if(maxHeight != lastMaxHeight)
                    ans.push_back({x, maxHeight});
            }
            
            lastMaxHeight = maxHeight;
            lastX = x;
        }
        
        return ans;
    }
};

//line sweep + heap
//https://briangordon.github.io/2014/08/the-skyline-problem.html
//Runtime: 256 ms, faster than 5.24% of C++ online submissions for The Skyline Problem.
//Memory Usage: 18.2 MB, less than 19.85% of C++ online submissions for The Skyline Problem.
//time: O(NlogN), space: O(N)
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        int OPEN = 0, CLOSE = 1;
        //(height, x-coord, right boundary)
        vector<vector<int>> points;
        
        for(int i = 0; i < buildings.size(); ++i){
            points.push_back({buildings[i][2], buildings[i][0], buildings[i][1]});
            points.push_back({buildings[i][2], buildings[i][1], buildings[i][1]});
        }
        
        //sort by x-coordinate
        sort(points.begin(), points.end(), 
            [](const vector<int>& a, const vector<int>& b){
                return a[1] < b[1];
            });
        
        //max height on top
        priority_queue<vector<int>, vector<vector<int>>> pq;
        vector<vector<int>> ans;
        
        for(vector<int>& point : points){
            int x = point[1];
            bool isClose = (point[1] == point[2]);
            // cout << "===x: " << x << ", left: " << !isClose << "===" << endl;
            
            /*
            building whose right boundary <= x should be cleared
            */
            // if(!pq.empty()){
            //     cout << "pq top x: " << pq.top()[1] << ", h: " << pq.top()[0] << endl;
            // }
            
            // cout << "push x: " << x << ", h: " << point[0] << endl;
            pq.push(point);
            
            //pop buildings whose right boundary <= current x-coord
            while(!pq.empty() && /*pq.top()[2] == pq.top()[1] &&*/ pq.top()[2] <= x){
                // cout << "pop x: " << pq.top()[1] << ", h: " << pq.top()[0] << endl;
                pq.pop();
            }
            
            // cout << "pq: " << pq.size() << endl;
            
            int height = pq.empty() ? 0 : pq.top()[0];
            //don't pop from pq! since it could still be active!
            
            if(ans.empty()){
                ans.push_back({x, height});
                // cout << "add " << x << ", " << height << endl;
            }else if(x == ans.back()[0]){
                /*
                [[0,2,3],[2,5,3]]
                */
                if(ans.size() >= 2 && ans[ans.size()-2][1] == max(ans.back()[1], height)){
                    // cout << "erase " << ans.back()[0] << ", " << ans.back()[1] << endl;
                    ans.erase(ans.begin()+ans.size()-1);
                    // cout << "update " << x << ", " << height << endl;
                }else{
                    ans.back()[1] = max(ans.back()[1], height);
                }
            }else if(ans.back()[1] != height){
                // cout << "add " << x << ", " << height << endl;
                ans.push_back({x, height});
            }
        }
        
        return ans;
    }
};
