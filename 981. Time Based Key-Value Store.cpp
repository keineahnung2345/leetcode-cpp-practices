//TLE
//44 / 45 test cases passed.
class TimeMap {
public:
    map<string, vector<pair<int, string>>> db;
    
    /** Initialize your data structure here. */
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        db[key].push_back(make_pair(timestamp, value));
        //actually the input is already sorted by timestamp, so we don't this
        // sort(db[key].begin(), db[key].end());
    }
    
    string get(string key, int timestamp) {
        // cout << "finding " << timestamp << endl;
        if(db.find(key) == db.end()){
            return "";
        }else{
            vector<pair<int, string>> values = db[key];
            int l = 0, r = values.size()-1;
            while(l <= r){
                int mid = (l+r)/2;
                // cout << l << " " << mid << " " << r << endl;
                if(timestamp == values[mid].first){
                    return values[mid].second;
                }else if(timestamp < values[mid].first){
                    //values[r] becomes the largest value < values[mid]
                    r = mid-1;
                }else {
                    //when mid and r are N-1, l will become N and break the loop
                    l = mid+1;
                }
            }
            // cout << "ends at " << r << endl;
            if(r < 0) return "";
            return values[r].second;
        }
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
 
