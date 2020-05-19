//decreasing stack
//Runtime: 612 ms, faster than 6.81% of C++ online submissions for Online Stock Span.
//Memory Usage: 84.6 MB, less than 7.69% of C++ online submissions for Online Stock Span.
//time: O(query), space: O(query)
class StockSpanner {
public:
    //decreasing stack(the bottom element is the largest)
    stack<int> prices;
    //number of elements popped before pushing corresponding "price" + 1
    stack<int> weights;
    
    StockSpanner() {
        
    }
    
    int next(int price) {
        int w = 1; //current element
        while(!prices.empty() && prices.top() <= price){
            prices.pop();
            w += weights.top(); weights.pop(); //number of elements skipped by prices.top()
        }
        
        prices.push(price);
        weights.push(w);
        return w;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
 
