//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Student Attendance Record I.
//Memory Usage: 8.6 MB, less than 11.11% of C++ online submissions for Student Attendance Record I.
class Solution {
public:
    bool checkRecord(string s) {
        //A student could be rewarded if his attendance record doesn't contain more than one 'A' (absent) or more than two continuous 'L' (late).
        return count(s.begin(), s.end(), 'A') <= 1 &&
            s.find("LLL") == string::npos;
    }
};
