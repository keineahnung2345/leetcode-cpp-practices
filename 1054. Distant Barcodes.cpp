//Runtime: 356 ms, faster than 10.71% of C++ online submissions for Distant Barcodes.
//Memory Usage: 20.7 MB, less than 100.00% of C++ online submissions for Distant Barcodes.
class Solution {
public:
    vector<int> rearrangeBarcodes(vector<int>& barcodes) {
        unordered_map<int, int> counter;
        for(int barcode : barcodes){
            counter[barcode]++;
        }
        
        //the larger count, the earlier to be popped
        priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> pq;
        
        //now the pair becomes (count, barcode)
        for(auto it = counter.begin(); it != counter.end(); it++){
            pq.push(make_pair(it->second, it->first));
        }
        
        vector<int> ans;
        
        while(pq.size() >= 2){
            pair<int, int> a = pq.top(); pq.pop();
            pair<int, int> b = pq.top(); pq.pop();
            
            //second : barcode
            ans.push_back(a.second);
            ans.push_back(b.second);
            
            //first : count
            a.first--;
            b.first--;
            
            if(a.first > 0) pq.push(a);
            if(b.first > 0) pq.push(b);
        }
        
        if(pq.size() > 0){
            pair<int, int> a = pq.top(); pq.pop();
            ans.push_back(a.second);
        }
        
        return ans;
    }
};
