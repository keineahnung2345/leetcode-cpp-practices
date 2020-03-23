//Runtime: 12 ms, faster than 13.62% of C++ online submissions for Reorganize String.
//Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Reorganize String.
class Solution {
public:
    string reorganizeString(string S) {
        unordered_map<char, int> counter;
        
        for(char c : S){
            counter[c]++;
        }
        
        auto comp = [](const pair<char, int>& a, const pair<char, int>& b){
            return (a.second == b.second) ? (a.first > b.first) : a.second < b.second;};
        
        //the larger count, the earlier be popped
        //the smaller char order, the earlier be popped
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(comp)> pq(comp);
        
        for(auto it = counter.begin(); it != counter.end(); it++){
            pq.push(make_pair(it->first, it->second));
        }
        
        string ans = "";
        
        while(!pq.empty()){
            //pop two elements at a time
            pair<char, int> cur = pq.top(); pq.pop();
            pair<char, int> next = make_pair(' ', 0);
            
            // cout << cur.first << " " << cur.second << endl;
            
            if(pq.size() > 0){
                next = pq.top(); pq.pop();
                cout << next.first << " " << next.second << endl;
            }
            
            cur.second--;
            if(ans.size() > 0 && cur.first == ans[ans.size()-1]) return "";
            ans += cur.first;
            
            if(next.first != ' '){
                next.second--;
                if(ans.size() > 0 && next.first == ans[ans.size()-1]) return "";
                ans += next.first;
            }
            
            //push them back to the queue
            if(cur.second > 0){
                pq.push(cur);
            }
            
            if(next.second > 0){
                pq.push(next);
            }
        }
        
        return ans;
    }
};
