#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#define IMP -INT_MAX
#pragma warning(disable:4996)

#define ComputeTriangleVectorArea CTVA
using namespace std;

struct line
{
	double k, b;
};
struct Point
{
	double x, y;
	bool operator==(const Point b) const
	{
		return (this->x == b.x && this->y == b.y);
	}
	bool operator!=(const Point b) const
	{
		return (this->x != b.x || this->y != b.y);
	}
	Point& operator =(const Point& p)
    {
        this->x = p.x;
        this->y = p.y;
        return *this;
    }
};
vector <Point> PointsM;
vector <Point> PointsN;
int N, M;
vector <Point> Points;

line GetLineFromPoint(Point a, Point b)
{
	if (a.y == b.y) return (line) { 0, a.y };
	if (b.x == a.x) return (line) { INT_MAX, a.x };
	double k = (b.y - a.y) / (b.x - a.x);
	double b1 = a.y - k * a.x;
	return (line) { k, b1 };
}

inline Point GetCrossPoint(line l1, line l2)
{
	if (l1.k == l2.k) return (Point) { IMP, IMP };
	double x = (l2.b - l1.b) / (l1.k - l2.k);
	double y = l1.k * x + l1.b;
	return (Point) { x, y };
}

inline double ComputeTriangleVectorArea(Point p1, Point p2, Point p3)
{
	return (double)0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));   
}

inline double ComputeAns(vector <Point> PointSet)
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

inline bool CheckAns(Point aa, Point bb, Point cc, Point dd, Point res)
{
	if (aa.x > bb.x) swap(aa, bb);
	if (cc.x > dd.x) swap(cc, dd);
	return (aa.x <= res.x && res.x <= bb.x && cc.x <= res.x && res.x <= dd.x);
}

inline Point GetCross(Point a, Point b, Point c, Point d)
{
	double k1, b1, k2, b2;
	if (b.x == a.x)
	{
		if (c.x == d.x)
			return (Point) { IMP, IMP };
		if ((c.x <= a.x && a.x <= d.x) || (c.x >= a.x && a.x >= d.x))
		{
			line l = GetLineFromPoint(c, d);
			double y = l.k * a.x + l.b;
			return (Point) { a.x, y };
		}
	}
	else
		if (c.x == d.x)
		{
			if ((a.x <= c.x && c.x <= b.x) || (a.x >= c.x && c.x >= b.x))
			{
				line l = GetLineFromPoint(a, b);
				double y = l.k * c.x + l.b;
				return (Point) { c.x, y };
			}
		}
		else
		{
			line l1 = GetLineFromPoint(a, b);
			line l2 = GetLineFromPoint(c, d);
			
			Point res = GetCrossPoint(l1, l2);
			Point aa = a, bb = b, cc = c, dd = d;
			if (aa.x > bb.x) swap(aa, bb);
			if (cc.x > dd.x) swap(cc, dd);

			if (res != (Point) { IMP, IMP })
			{
				if (aa.x <= res.x && res.x <= bb.x && cc.x <= res.x && res.x <= dd.x)
				{
					return res;
				}
				else
					return (Point) { IMP, IMP };
			}
		}
}

bool PointCmp(const Point &a, const Point &b, const Point &center)
{
	if (a.x >= 0 && b.x < 0)
		return true;
	if (a.x == 0 && b.x == 0)
		return a.y > b.y;

	double det = (double)(a.x - center.x) * (b.y - center.y) - (double)(b.x - center.x) * (a.y - center.y);
	
	if (det < 0) return true;//顺时针
	if (det > 0) return false;//逆时针

	double d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
	double d2 = (b.x - center.x) * (b.x - center.y) + (b.y - center.y) * (b.y - center.y);

	return d1 > d2;
}


inline Point Gravity(vector <Point> PointSet)
{
	double x = 0, y = 0;
	for (register vector<Point>::iterator i = PointSet.begin(); i != PointSet.end(); ++i)
	{
		x += (*i).x;
		y += (*i).y;
	}
	return (Point) {(double) x / PointSet.size(), (double)y / PointSet.size() };
}

inline void swap(Point &a, Point &b)
{
	Point t;
	t = a, a = b, b = t;
}
inline void ClockwiseSortPoints(vector<Point> &vPoints)
{
	Point center = Gravity(vPoints);
	
	for (int i = 0; i < vPoints.size() - 1; i++)
	{
		for (int j = 0; j < vPoints.size() - i - 1; j++)
		{
			if (PointCmp(vPoints[j], vPoints[j + 1], center))
			{
				swap(vPoints[j], vPoints[j + 1]);
			}
		}
	}
}

int main()
{
	//freopen("area.in", "r", stdin);
	//freopen("area.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin >> N;
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
		vector <Point>::iterator Nexti;
		if (i == PointsN.end() - 1) Nexti = PointsN.begin();
		else Nexti = i + 1;
		for (register vector <Point>::iterator j = PointsM.begin(); j != PointsM.end(); ++j)
		{
			vector <Point>::iterator Nextj;
			if (j == PointsM.end() - 1) Nextj = PointsM.begin();
			else Nextj = j + 1;
			if (GetCross(*i, *Nexti, *j, *Nextj) != (Point) { IMP, IMP })
				Points.push_back(GetCross(*i, *Nexti, *j, *Nextj));

		}
	}

	Point P;
	P.x = INT_MAX, P.y = INT_MAX;//将极长的线段看为射线
	for (register vector <Point>::iterator i = PointsN.begin(); i != PointsN.end(); ++i)
	{
		line l = GetLineFromPoint(P, (*i));
		int tot = 0;
		for (register vector <Point>::iterator j = PointsM.begin(); j != PointsM.end(); ++j)
		{
			vector <Point>::iterator Nextj;
			if (j == PointsM.end() - 1) Nextj = PointsM.begin();
			else Nextj = j + 1;
			line l2 = GetLineFromPoint(*j, *Nextj);
			if (GetCrossPoint(l, l2) != (Point) { IMP, IMP })
			{
				if (CheckAns(P, (*i), *j, *Nextj, GetCrossPoint(l, l2)))
					tot++;
			}
		}
		if (tot == 1) Points.push_back(*i);
	}

	for (register vector <Point>::iterator i = PointsM.begin(); i != PointsM.end(); ++i)
	{
		line l = GetLineFromPoint(P, (*i));
		int tot = 0;
		for (register vector <Point>::iterator j = PointsN.begin(); j != PointsN.end(); ++j)
		{
			vector <Point>::iterator Nextj;
			if (j == PointsN.end() - 1) Nextj = PointsN.begin();
			else Nextj = j + 1;
			line l2 = GetLineFromPoint(*j, *Nextj);
			if (GetCrossPoint(l, l2) != (Point) { IMP, IMP })
			{
				if (CheckAns(P, (*i), *j, *Nextj, GetCrossPoint(l, l2)))
					tot++;
			}
		}
		if (tot == 1) Points.push_back(*i);
	}
	//PointCmp((Point){ })
	
	ClockwiseSortPoints(Points);
	
	for (register vector <Point>::iterator i = Points.begin(); i != Points.end(); ++i)
	{
		printf("%0.3lf %0.3lf\n", (*i).x, (*i).y);
		
	}
	printf("%0.3lf\n",ComputeAns(Points));
	cout << PointCmp(Points[0],Points[Points.size() - 3], Gravity(Points));
	return 0;
}
