#include <algorithm>
// Source: https://molchevskyi.medium.com/best-solutions-for-codility-lessons-lesson-6-sorting-770f931b65ad

int solution(vector<int> &v) {
    const auto MAX_INTERSECTIONS = 10000000;
    size_t v_size = v.size();

    vector<int> start(v_size, 0), end(v_size, 0);

    // Assume circles as segments on the coordinate axis.
    // Count all start and end points of the segments intersects on each point of the axis
    for (size_t i = 0; i < v_size; ++i) {
        // If radius of the circle is bigger than distance to the origin 
        // of the coordinate axis or
        // the radius is bigger than length of the given array
        // add this segment to the first point or to the last point.
        // We do this to avoid of scanning from MIN_INT to MAX_INT
        // because the task defines the range started from 0 to end of the given array.
        // We don't need to work outside of this range        
        start[max(0, static_cast<int>(i) - v[i])]++;
        end[min(v_size - 1, i + v[i])]++;
    }

     // Number of "active" segments that is segments which intersect at the point i
    int active = 0;
     // Total number of intersections.
    int intersections = 0;
    for (size_t i = 0; i < v_size; i++) {
/*
 Walk by the array and count the segments which contain the current point “i” on the axis.
 Whenever a new segment starts at location “i”, it intersects with all existing segment (disks) at that location.
 That's why we have “active * start[i]” part in the formula. We also need to add the number of intersections for all
 the segments that just started at location “i”, i.e., the number of intersections within themselves excluding whatever
 already existed “(start[i] * (start[i] - 1)) / 2”.  For example if started 5 segments (disks) in one point,
 it will increased by (1+2+3+4+5 intersections, or 5*(5-1) / 2.
 */
        intersections += active * start[i] + (start[i] * (start[i] - 1)) / 2;
        if (intersections > MAX_INTERSECTIONS) {
            return -1;
        }
        active += start[i] - end[i];
    }
    return intersections;
}
