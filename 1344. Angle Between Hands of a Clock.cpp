//Runtime: 0 ms, faster than 100.00% of C++ online submissions for Angle Between Hands of a Clock.
//Memory Usage: 7.4 MB, less than 100.00% of C++ online submissions for Angle Between Hands of a Clock.

class Solution {
public:
    double angleClock(int hour, int minutes) {
        float hAngle, mAngle;
        float diff;
        
        hour = hour % 12;
        minutes = minutes % 60;
        
        //will lead to WA
        // mAngle = minutes/60.0f*360.0f;
        // hAngle = hour%12/12.0f*360.0f + minutes/60.0f*30.0f;
        
        mAngle = minutes*6.0f;
        hAngle = hour*30.0f + minutes/2.0f;
        
        diff = abs(mAngle-hAngle);
        diff = min(360.0f-diff, diff);
        
        return diff;
    }
};
