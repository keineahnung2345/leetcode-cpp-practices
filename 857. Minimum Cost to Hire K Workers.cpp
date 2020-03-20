//Runtime: 944 ms, faster than 6.75% of C++ online submissions for Minimum Cost to Hire K Workers.
//Memory Usage: 10.3 MB, less than 100.00% of C++ online submissions for Minimum Cost to Hire K Workers.
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        vector<pair<int, int>> qws;
        int N = quality.size();
        
        for(int i = 0; i < N; i++){
            qws.push_back(make_pair(quality[i], wage[i]));
        }
        
        //sort by wage/quality ratio, ascending
        sort(qws.begin(), qws.end(), 
            [](const pair<int, int>& p1, const pair<int, int>& p2){
                return (double)p1.second/p1.first < (double)p2.second/p2.first;
            });
        
        // for(int i = 0; i < N; i++){
        //     cout << qws[i].first << " " << qws[i].second << " " << (double)qws[i].second/qws[i].first << endl;
        // }
        
        //multiply the sum of quality with current wage/quality ratio
        double ans = DBL_MAX;
        double wqRatio;
        vector<int> qualities;
        
        for(int i = 0; i < N; i++){
            pair<int, int> p = qws[i];
            int q = p.first, w = p.second;
            // cout << q << " " << w << endl;
            
            //insert to right place so that we can access K smallest q(until now) quickly
            auto it = upper_bound(qualities.begin(), qualities.end(), q);
            if(it == qualities.end()){
                qualities.push_back(q);
            }else{
                qualities.insert(it, q);
            }
            
            wqRatio = (double)w/q;
            // cout << "wqRatio: " << wqRatio << endl;
            
            if(i+1 >= K){
                int qualitySum = accumulate(qualities.begin(), qualities.begin() + K, 0);
                ans = min(ans, qualitySum * wqRatio);
            }
            
        }
        
        return ans;
    }
};

//Approach 1: Greedy
//TLE
//41 / 46 test cases passed.
//time: O(N^2logN), space: O(N)
class Solution {
public:
    double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int K) {
        int N = quality.size();
        double ans = DBL_MAX;
        
        for(int captin = 0; captin < N; captin++){
            double factor = (double)wage[captin]/quality[captin];
            vector<double> prices; //the price of workers whose wq ratio above factor
            for(int worker = 0; worker < N; worker++){
                double price = factor * quality[worker];
                if(price >= wage[worker]){
                    prices.push_back(price);
                }
            }
            
            if(prices.size() < K) continue;
            
            sort(prices.begin(), prices.end());
            ans = min(ans, accumulate(prices.begin(), prices.begin()+K, 0.0));
        }
        
        return ans;
    }
};
