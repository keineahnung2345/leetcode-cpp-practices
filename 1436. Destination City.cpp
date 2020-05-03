//Runtime: 24 ms, faster than 75.00% of C++ online submissions for Destination City.
//Memory Usage: 10.9 MB, less than 100.00% of C++ online submissions for Destination City.
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        set<string> cities;
        
        for(vector<string>& path: paths){
            cities.insert(path[1]);
        }
        
        /*
        need to do two-pass!!
        cannot delete start point while adding ending point,
        e.g. [["pYyNGfBYbm","wxAscRuzOl"],["kzwEQHfwce","pYyNGfBYbm"]]
        "pYyNGfBYbm" will not be deleted in one-pass method
        */
        for(vector<string>& path: paths){
            // auto it = cities.find(path[0]);
            // if(it != cities.end()){
            //     cities.erase(it);
            // }
            cities.erase(path[0]);
        }
        
        return *cities.begin();
    }
};
