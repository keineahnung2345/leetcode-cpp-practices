//priority queue
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

//Approach #1: Sort by Count
//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Reorganize String.
//Memory Usage: 6.2 MB, less than 100.00% of C++ online submissions for Reorganize String.
//A: size of the alphabet, N: ength of S
//time: O(AN + AlogA), space: O(N)
class Solution {
public:
    string reorganizeString(string S) {
        int N = S.size();
        //a hash calculated by count and its lexicographic order
        vector<int> countLex(26, 0);
        
        //count part
        for(char c: S){
            countLex[c-'a'] += 26;
        }
        //lexicographic part
        for(int i = 0; i < 26; i++){
            countLex[i] += i;
        }
        
        //we start from the char with smaller count
        sort(countLex.begin(), countLex.end());
        
        vector<char> ans(N);
        int cursor = 1;
        for(int code : countLex){
            int count = code/26;
            char c = 'a' + (code%26);
            /*
            if S's length is 3, a character cannot appear more than 2 times
            if S's length is 4, a character cannot appear more than 2 times
            */
            if(count > (N+1)/2) return "";
            for(int i = 0; i < count; i++){
                /*
                the latter char(char with larger count) will start from 0
                for example, in "abaca", 'a' is processed at last, 
                and it will fill 0,2,4th position
                */
                if(cursor >= N) cursor = 0;
                // cout << cursor << " " << c << endl;
                ans[cursor] = c;
                //jump to next next position
                cursor += 2;
            }
        }
        
        return string(ans.begin(), ans.end());
    }
};

//Approach #2: Greedy with Heap
//priority queue, process two char at a time
//Runtime: 4 ms, faster than 64.77% of C++ online submissions for Reorganize String.
//Memory Usage: 6.6 MB, less than 100.00% of C++ online submissions for Reorganize String.
//time: O(NlogA), space: O(A)
class Solution {
public:
    string reorganizeString(string S) {
        int N = S.size();
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
            //early stopping
            if(it->second > (N+1)/2) return "";
            pq.push(make_pair(it->first, it->second));
        }
        
        string ans = "";
        
        while(pq.size() >= 2){
            //pop two elements at a time
            pair<char, int> cur = pq.top(); pq.pop();
            pair<char, int> next = pq.top(); pq.pop();
            
            //we don't need this check now, because we process two different char at one time 
            // if(ans.size() > 0 && cur.first == ans[ans.size()-1]) return "";
            ans += cur.first;
            
            // if(ans.size() > 0 && next.first == ans[ans.size()-1]) return "";
            ans += next.first;
            
            //push them back to the queue
            if(--cur.second > 0) pq.push(cur);
            if(--next.second > 0) pq.push(next);
        }
        
        //we jump out the loop when its size is 0 or 1
        if(!pq.empty()) ans += pq.top().first;
        
        return ans;
    }
};
