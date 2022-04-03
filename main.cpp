#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <cmath>
#include <algorithm>
using namespace std;
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::system_clock;

#include "Line.cpp"

vector<Point> res;
vector<Point> aboveLine;
vector<Point> belowLine;
void setUp(string path)
{
    fstream inFile;
    inFile.open(path);
    string temp;
    getline(inFile, temp);

    vector<Point> points;
    while(!inFile.eof())
    {
        getline(inFile, temp);
        if("" == temp)
        {
            break;
        }
        points.push_back(Point(temp));
    }
    inFile.close();

    int leftestPoint = 0;
    int rightestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(points[i].x<points[leftestPoint].x)
        {
            leftestPoint = i;
        }
        if(points[i].x>points[rightestPoint].x)
        {
            rightestPoint = i;
        }
    }
    res.push_back(points[leftestPoint]);
    res.push_back(points[rightestPoint]);

    Line middleLine{points[leftestPoint], points[rightestPoint]};
    for(int i=0; i<points.size(); i++)
    {
        if(i == leftestPoint || i == rightestPoint)
        {
            continue;
        }
        if(middleLine.isAbove(points[i]))
        {
            aboveLine.push_back(points[i]);
        }
        else
        {
            belowLine.push_back(points[i]);
        }
    }
}

void solveAbove(vector<Point>& points, Point left, Point right)
{
    if(points.empty())
    {
        return;
    }
    Line l{left, right};
    int furthestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(l.distanceFrom(points[furthestPoint]) < l.distanceFrom(points[i]))
        {
            furthestPoint = i;
        }
    }
    res.push_back(points[furthestPoint]);
    Line l1{left, points[furthestPoint]};
    Line l2{points[furthestPoint], right};
    vector<Point> points1;
    vector<Point> points2;
    for(int i=0; i<points.size(); i++)
    {
        if(furthestPoint == i)
        {
            continue;
        }
        if(l1.isAbove(points[i]))
        {
            points1.push_back(points[i]);
        }
        else if(l2.isAbove(points[i]))
        {
            points2.push_back(points[i]);
        }
    }
    solveAbove(points1, left, points[furthestPoint]);
    solveAbove(points2, points[furthestPoint], right);
}
void solveBelow(vector<Point>& points, Point left, Point right)
{
    if(points.empty())
    {
        return;
    }
    Line l{left, right};
    int furthestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(l.distanceFrom(points[furthestPoint]) < l.distanceFrom(points[i]))
        {
            furthestPoint = i;
        }
    }
    res.push_back(points[furthestPoint]);
    Line l1{left, points[furthestPoint]};
    Line l2{points[furthestPoint], right};
    vector<Point> points1;
    vector<Point> points2;
    for(int i=0; i<points.size(); i++)
    {
        if(furthestPoint == i)
        {
            continue;
        }
        if(l1.isBelow(points[i]))
        {
            points1.push_back(points[i]);
        }
        else if(l2.isBelow(points[i]))
        {
            points2.push_back(points[i]);
        }
    }
    solveBelow(points1, left, points[furthestPoint]);
    solveBelow(points2, points[furthestPoint], right);
}

Point center;
struct comp 
{
public:
    bool operator()(Point& a, Point& b)
    {
        double aAngle = atan((a.y-center.y)/(a.x-center.x));
        if(a.x-center.x<0)
        {
            aAngle += M_PI;
        }
        double bAngle = atan((b.y-center.y)/(b.x-center.x));
        if(b.x-center.x<0)
        {
            bAngle += M_PI;
        }
        return aAngle<bAngle;
    }
};

int main(int argc, char** argv)
{
    string inputPath = "test/";
    inputPath += argv[1];
    /*
    auto begin = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    auto end = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    cout << end-begin << endl;
    */
    setUp(inputPath);
    solveAbove(aboveLine, res[0], res[1]);
    solveBelow(belowLine, res[0], res[1]);
    
    double tempX = 0;
    double tempY = 0;
    for(Point& p : res)
    {
        tempX += p.x;
        tempY += p.y;
    }
    center.x = tempX/((double)res.size());
    center.y = tempY/((double)res.size());

    sort(res.begin(), res.end(), comp());
    cout << res.size() << endl;
    int startIndex = 0;
    for(int i=1; i<res.size(); i++)
    {
        if(res[startIndex].y > res[i].y)
        {
            startIndex = i;
        }
        else if(res[startIndex].y == res[i].y)
        {
            if(res[startIndex].x > res[i].x)
            {
                startIndex = i;
            }
        }
    }
    int endIndex = startIndex-1;
    if(endIndex<0)
    {
        endIndex += res.size();
    }
    while(startIndex != endIndex)
    {
        res[startIndex].print();
        startIndex++;
        startIndex %= res.size();
    }
    res[endIndex].print();
    
    return 0;
}
