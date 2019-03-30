/**
Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, which contains initial elements from the stream. For each call to the method KthLargest.add, return the element representing the kth largest element in the stream.

Example:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
Note: 
You may assume that nums' length ≥ k-1 and k ≥ 1.
**/

//Runtime: 192 ms, faster than 11.41% of C++ online submissions for Kth Largest Element in a Stream.
//Memory Usage: 19.5 MB, less than 47.71% of C++ online submissions for Kth Largest Element in a Stream.

class KthLargest {
private:
    vector<int> kLargest;
public:
    /**
    solution.cpp: In static member function 'static KthLargest*      __DriverSolution__::__helperConstructor__(const string&, const std::vector<std::__cxx11::basic_string<char> >&)':
    Line 99: Char 41: error: cannot bind non-const lvalue reference of type 'std::vector<int>&' to an rvalue of type 'std::vector<int>'
    **/
    // KthLargest(int k, vector<int>& nums) {
    KthLargest(int k, vector<int> nums) {
        kLargest = vector<int>();
        if(nums.size() > 0){
            sort(nums.begin(), nums.end());
            //(nums.size(), k , nums.size()-1-k) = (1, 1, 18446744073709551615)??
            //push until kLargest has k elements or nums has been iterated
            for(vector<int>::reverse_iterator rit = nums.rbegin(); rit < nums.rbegin() + k && rit != nums.rend(); rit++){
                kLargest.push_back(*rit);
            }
        }
        //keep insert 
        for(int i = kLargest.size(); i < k; i++){
            kLargest.push_back(INT_MIN);
        }
    }
    
    int add(int val) {
        int k = kLargest.size();
        kLargest.push_back(val);
        
        for(int i = 0; i < k; i++){
            if(val >= kLargest[i]){
                kLargest.insert(kLargest.begin()+i, val);
                break;
            }
        }
        kLargest.resize(k);
        return kLargest[k-1];
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
 
