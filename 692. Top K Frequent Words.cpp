//Runtime: 24 ms, faster than 13.26% of C++ online submissions for Top K Frequent Words.
//Memory Usage: 9.1 MB, less than 100.00% of C++ online submissions for Top K Frequent Words.
class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        //use unordered_map rather than map to speed up
        unordered_map<string, int> counter;
        
        auto comp = [&counter](const string& lhs, const string& rhs){
            /*if we want an element to be popped from priority queue earlier,
            then we need to make it rank lower in the sorted array
            */
            // cout << lhs << " " << counter[lhs] << " " << rhs << " " << counter[rhs] << endl;
            // cout << lhs << " " << rhs << " " << (lhs > rhs) << endl;
            return (counter[lhs] == counter[rhs]) ? (lhs > rhs) : 
                (counter[lhs] < counter[rhs]);
        };
        
        priority_queue<string , vector<string>, decltype(comp)> pq(comp);
        vector<string> ans;
        
        for(string& word : words){
            counter[word]++;
        }
        
        /*
        only when we have looked through words, 
        counter has correct count of each word's occurrence
        */
        for(auto it = counter.begin(); it != counter.end(); it++){
            pq.push(it->first);
        }
        
        while(k-- > 0){
            ans.push_back(pq.top());
            pq.pop();
        }
        
        return ans;
    }
};
