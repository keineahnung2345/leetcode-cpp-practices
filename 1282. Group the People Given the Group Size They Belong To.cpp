class Solution {
public:
    //declare it here to avoid 
    //'groupSize' is not captured
    int groupSize = 1;
    
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        vector<vector<int> > groups;
        vector<int>::iterator iter;
        int remaining = groupSizes.size();
        
        while(remaining > 0){
            iter = groupSizes.begin();
            vector<int> group;
            //use "[&](int& e)" instead of "[](int& e)" to avoid:
            //'groupSize' is not captured
            //and
            //'this' was not captured for this lambda function
            while ((iter = find_if(iter, groupSizes.end(), [&](int& e) { return e == groupSize; })) != groupSizes.end()){
                group.push_back(iter - groupSizes.begin());
                if(group.size() == groupSize){
                    groups.push_back(group);
                    group = vector<int>();
                }
                iter++;
                remaining--;
            }
            groupSize++;
        }
        return groups;
    }
};
