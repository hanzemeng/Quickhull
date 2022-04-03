#include <string>
#include <cmath>
#include <iostream>
using namespace std;

struct Point
{
    Point(double a=0, double b=0)
    {
        x = a;
        y = b;
    }
    Point(string data)
    {
        string temp = "";
        for(int i=0; i<data.size(); i++)
        {
            if(',' == data[i])
            {
                x = stod(temp);
                i++;
                temp = "";
            }
            else
            {
                temp += data[i];
            }
        }
        y = stod(temp);
    }
    void print()
    {
        cout << "(" << x << ", " << y << ")" << endl;
        //cout << x << ", " << y <<  endl;
    }
    double x;
    double y;
};

const double threshold = 0.00000001;
struct Line
{
    //y=mx+b
    Line(Point& p1, Point& p2)
    {
        m = (p1.y-p2.y)/(p1.x-p2.x);
        b = p1.y-m*p1.x;
    }
    bool isAbove(Point& a)
    {
        double lineY = m*a.x+b;
        if(abs(lineY-a.y)<threshold)
        {
            return false;
        }
        return a.y>lineY;
    }
    bool isBelow(Point& a)
    {
        double lineY = m*a.x+b;
        if(abs(lineY-a.y)<threshold)
        {
            return false;
        }
        return a.y<lineY;
    }
    double distanceFrom(Point& a)
    {
        double top = abs(m*a.x-a.y+b);
        double bottom = sqrt(m*m+1);
        return top/bottom;
    }
    void print()
    {
        cout << m << "x+" << b << endl;
    }
    double m;
    double b;
};
