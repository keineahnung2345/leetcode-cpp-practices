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
