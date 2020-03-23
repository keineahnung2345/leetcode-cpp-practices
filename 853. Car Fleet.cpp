//WA
//18 / 44 test cases passed.
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int N = position.size();
        vector<pair<int, int>> pss(N);
        int fleets = N; //every car is a fleet initially
        
        for(int i = 0; i < N; i++){
            pss[i] = make_pair(position[i], speed[i]);
        }
        
        sort(pss.begin(), pss.end());
        
        for(int i = 0; i < N; i++){
            cout << "(" << pss[i].first << "," << pss[i].second << ") ";
        }
        cout << endl;
        
        double lastMeet = target;
        
        for(int i = N-2; i >= 0; i--){
            if(pss[i].second > pss[i+1].second){
                //current car's speed > the car in front of it
                double t = (double)(pss[i+1].first - pss[i].first)/(pss[i].second - pss[i+1].second);
                double meet = pss[i].first + t * pss[i].second;
                cout << i << " and " << i+1 << "th car meet at: " << meet << endl;
                if(meet <= lastMeet){
                    fleets--;
                    //ith car is blocked by i+1 th car
                    pss[i].second = pss[i+1].second;
                    cout << i << "th car's speed becomes " << pss[i].second << endl;
                    lastMeet = meet;
                }
            }
        }
        
        return fleets;
    }
};

//use approach time to determine whether to merge two cars
//Approach 1: Sort
//Runtime: 56 ms, faster than 45.36% of C++ online submissions for Car Fleet.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Car Fleet.
//time: O(NlogN), space: O(N)
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int N = position.size();
        vector<pair<int, double>> pts(N);
        for(int i = 0; i < N; i++){
            pts[i] = make_pair(position[i], (double)(target - position[i])/speed[i]);
        }
        sort(pts.begin(), pts.end());
        
        int ans = N; //we have N fleets initially
        for(int i = N-2; i >= 0; i--){
            //if car i will catch car (i+1) some time, we merge them
            if(pts[i].second <= pts[i+1].second){
                ans--;
                //car i's speed is set to that of car i+1
                pts[i].second = pts[i+1].second;
            }
        }
        
        return ans;
    }
};
