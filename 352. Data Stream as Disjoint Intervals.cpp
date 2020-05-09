//binary search
//Runtime: 80 ms, faster than 99.62% of C++ online submissions for Data Stream as Disjoint Intervals.
//Memory Usage: 31.1 MB, less than 100.00% of C++ online submissions for Data Stream as Disjoint Intervals.
class SummaryRanges {
public:
    vector<vector<int>> intvls;
    
//     bool compareEnd(vector<int>& v1, vector<int>& v2){
//         return v1[1] < v2[1];
//     }
    
//     bool compareStart(vector<int>& v1, vector<int>& v2){
//         return v1[0] > v2[0];
//     }
    
    //functors as argument to lower_bound and upper_bound
    class compareEnd{
    public:
        compareEnd(){}
        // bool operator() (vector<int>& v1, vector<int>& v2) const{
        //     return v1[1] < v2[1];
        // }
        // for lower_bound
        bool operator() (vector<int>& v1, const int& v2) {
            return v1[1] < v2;
        }
    };
    
    class compareStart{
    public:
        compareStart(){}
        // bool operator() (vector<int>& v1, vector<int>& v2) const{
        //     return v1[0] > v2[0];
        // }
        // for lower_bound
        // bool operator() (vector<int>& v1, const int& v2) {
        //     return v1[0] < v2;
        // }
        //for upper_bound
        bool operator() (const int& v1, vector<int>& v2) {
            return v1 < v2[0];
        }
    };
    
    compareEnd ce;
    compareStart cs;
    
    /** Initialize your data structure here. */
    SummaryRanges() {
        
    }
    
    void addNum(int val) {
        //find interval whose start > val
        auto itStart = upper_bound(intvls.begin(), intvls.end(), val, cs);
        //find interval whose start <= val
        //https://stackoverflow.com/questions/9989731/algorithm-function-for-finding-last-item-less-than-or-equal-to-like-lower-bou
        if(itStart != intvls.begin()) itStart = prev(itStart);
        //find interval whose end >= val
        auto itEnd = lower_bound(intvls.begin(), intvls.end(), val, ce);
        int idxStart = itStart - intvls.begin();
        int idxEnd = itEnd - intvls.begin();
        // cout << "add " << val << endl;
        // cout << "start: " << idxStart << ", end: " << idxEnd << endl;
        if(itEnd == intvls.end()){
            //val is larger than all intervals' end
            // cout << "not found interval whose end >= " << val << endl;
            if(idxEnd > 0 && intvls[idxEnd-1][1] + 1 == val){
                //expand the interval before val
                intvls[idxEnd-1][1] = val;
                // cout << "expand end of last interval" << endl;
            }else{
                intvls.push_back({val, val});
                // cout << "push back" << endl;
            }
        }else if(itStart == intvls.begin() && (*itStart)[0] > val){
            //val is smaller than all intervals' start
            // cout << "not found interval whose start <= " << val << endl;
            if(val + 1 == intvls[idxEnd][0]){
                //expand the interval before val
                intvls[idxEnd][0] = val;
                // cout << "expand start of next interval" << endl;
            }else{
                intvls.insert(intvls.begin(), {val, val});
                // cout << "insert front" << endl;
            }
        }else if(itStart == itEnd && ((*itEnd)[1] >= val || (*itStart)[0] <= val)){
            //val has been added, ignore
            // cout << val << " already exists!" << endl;
        }else{
            bool combined = false;
            
            if(idxStart >= 0 && intvls[idxStart][1] + 1 == val){
                //expand the interval before val
                intvls[idxStart][1] = val;
                combined = true;
                // cout << "expand end of last interval" << endl;
            }

            if(val+1 == intvls[idxEnd][0]){
                //expand the interval after val
                intvls[idxEnd][0] = val;
                combined = true;
                // cout << "expand start of next interval" << endl;
            }
            
            //if the surrounding intervals touch each other
            if(combined && intvls[idxStart][1] >= intvls[idxEnd][0]){
                //merge former interval with next interval
                intvls[idxEnd][0] = intvls[idxStart][0];
                intvls.erase(intvls.begin()+idxStart);
                // cout << "merge last and next intervals, size: " << intvls.size() << endl;
            }else if(!combined){
                //val touch neither the boundaries of its surrounding interval
                intvls.insert(itEnd, {val, val});
                // cout << "not touch surrounding intervals, insert" << endl;
            }
        }
        // cout << "===================" << endl;
    }
    
    vector<vector<int>> getIntervals() {
        return intvls;
    }
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
 
