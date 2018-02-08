#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#pragma warning(disable:4996)

#define ComputeTriangleVectorArea CTVA
using namespace std;
struct Point
{
	double x, y;
};
vector <Point> PointsM;
vector <Point> PointsN;
double ComputeTriangleVectorArea(Point p1, Point p2, Point p3)
{   
    return (double)0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));   
}
double Compute(vector <Point> PointSet)
{
	if (PointSet.empty()) return 0.0;
	double area = 0.0;
	Point O;
	O.x = O.y = 0;
	for (register vector<Point>::iterator ii = PointSet.begin(); ii != PointSet.end() - 1; ++ii)
	{
		area += CTVA(O,(*ii),(*(ii + 1)));
	}
	area += CTVA(O,PointSet[PointSet.size() - 1], PointSet[0]);
	return abs(area);
}
 
Point GetCrossPoint(Point a, Point b, Point c, Point d)
{
	double k1, b1, k2, b2;
	if (b.x - a.x == 0)
	{
		
	}
	k1 = (b.y - a.y) / (b.x - a.x);
	b1 = a.y - k1 * a.x;
	k2 = (d.y - c.y) / (d.x - c.x);
	b2 = c.y - k2 * c.x;
	
}
int N, M;
int main()
{
//	freopen("area.in", "r", stdin);
//  freopen("area.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> N;hypot()
	for (register int i = 1; i <= N; ++i)
	{
		Point tmp;
		cin >> tmp.x >> tmp.y;
		PointsN.push_back(tmp);
	}
	cin >> M;
	for (register int i = 1; i <= M; ++i)
	{
		Point tmp;
		cin >> tmp.x >> tmp.y;
		PointsM.push_back(tmp);
	}
	for (register vector <Point>::iterator i = PointsN.begin(); i != PointsN.end(); ++i)
	{
		Point Nexti;
		if (i == PointsN.end() - 1) Nexti = *PointsN.begin();
		else Nexti = *(i + 1);
		for (register vector <Point>::iterator j = PointsM.begin(); j != PointsM.end(); ++j)
		{
			Point Nextj;
			if (j == PointsM.end() - 1) Nextj = *PointsM.begin();
			else Nextj = *(j + 1);
			
		}
	}
	printf("%0.1lf\n",Compute(Points));
	return 0;
}
