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
