#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>
#include <limits>
#include <set>
#include <cmath>

using namespace std;

struct Point
{
    double x;
    double y;
    Point(const double p_x, const double p_y) : x(p_x), y(p_y) {}
    Point()
    {
        x = 0;
        y = 0;
    }
};

ostream &operator<<(ostream &os, const Point &x) //print point info
{
    os << " x: " << x.x << " y: " << x.y;
    return os;
}

bool less_than_x(const Point &a, const Point &b)
{
    return a.x < b.x;
}

struct less_than_y
{
    bool operator()(const Point &a, const Point &b)
    {
        return a.y < b.y;
    }
};

tuple<double, Point, Point> closest_pair(vector<Point> &points)
{
    sort(points.begin(), points.end(), less_than_x);
    double min_dis = numeric_limits<double>::max(); //init
    set<Point, less_than_y> rectangle_area;
    Point answer_1, answer_2;
    rectangle_area.insert(points[0]);
    int left = 0;
    for (int i = 1; i < points.size(); ++i)
    {
        while (left < i && points[i].x - points[left].x > min_dis)
        {
            rectangle_area.erase(points[left++]); //维护左侧边界
        }

        for (auto itr = rectangle_area.lower_bound(Point(points[i].x - min_dis, points[i].y - min_dis)); itr != rectangle_area.end() && points[i].y + min_dis >= itr->y; itr++) //维护上下边界
        {
            double dis_now = sqrt(pow(points[i].x - itr->x, 2.0) + pow(points[i].y - itr->y, 2.0));
            if (dis_now < min_dis) // 更新最小点对的信息
            {
                min_dis = dis_now;
                answer_1 = points[i];
                answer_2 = (*itr);
            }
        }
        rectangle_area.insert(points[i]);
    }
    return tuple<double, Point, Point>(min_dis, answer_1, answer_2);
}

int main()
{
    vector<Point> pts; //points
    double temp_x, temp_y;
    char temp_char;
    while (cin >> temp_char >> temp_char >> temp_x >> temp_char >> temp_y >> temp_char)
    {
        pts.push_back(Point(temp_x, temp_y));
    }
    tuple<double, Point, Point> ans = closest_pair(pts);
    cout << get<0>(ans) << get<1>(ans) << get<2>(ans);
}