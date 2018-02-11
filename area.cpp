#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>
#define DOUBLE_MAX INT_MAX
#define DOUBLE_MIN -INT_MAX
#define IMP DOUBLE_MIN
#pragma warning(disable:4996)

#define ComputeTriangleVectorArea CTVA
using namespace std;

struct line
{
	double k, b;
	bool slope_exist; //If Slope exits, the line equation will be y=kx+b, or it will be x=b
	friend ostream &operator<<(ostream &os, const line &l)
    {
    	if (l.slope_exist && l.k != 0) os << "y = " << l.k << "x + " << l.b;	
    	else if (l.slope_exist) os << "y = " << l.b;
    	else os << "x = " << l.b;
    	return os;
	}
};

struct Point
{
	double x, y;
	bool operator==(const Point b) const
	{
		return (abs(this->x - b.x) <= 1e-100 && abs(this->y - b.y) <= 1e-100);
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
    friend ostream &operator<<(ostream &os, const Point &P)
    {
    	os << "(" << P.x << ',' << P.y << ')';
    	return os;
	}
};

typedef vector <Point> Polygon;
Polygon PointsM;
Polygon PointsN;
int N, M;
Polygon Points;

line GetLineFromPoint(Point a, Point b)
{
	if (a.y == b.y) return (line) { 0, a.y, 1 };
	if (b.x == a.x) return (line) { 0, a.x, 0 };
	double k = (b.y - a.y) / (b.x - a.x);
	double b1 = a.y - k * a.x;
	return (line) { k, b1, 1 };
}

inline Point GetCrossPoint(line l1, line l2)
{
	if (l1.slope_exist && l2.slope_exist)
	{
		if (l1.k == l2.k) return (Point) { IMP, IMP };
		double x = (l2.b - l1.b) / (l1.k - l2.k);
		double y = l1.k * x + l1.b;
		return (Point) { x, y };
	}
	else
		if (l1.slope_exist && (!l2.slope_exist))
		{
			double x = l2.b;
			double y = l1.k * x + l1.b;
			return (Point) { x, y };
		}
		else
			if ((!l1.slope_exist) && l2.slope_exist)
			{
				double x = l1.b;
				double y = l2.k * x + l2.b;
				return (Point) { x, y };
			}
			else
				return (Point) { IMP, IMP };

}

inline double ComputeTriangleVectorArea(Point p1, Point p2, Point p3)
{
	return (double)0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));   
}

inline double Com(Point p1, Point p2, Point p3)
{
	return (double)((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));   
}

inline double ComputeAns(Polygon PointSet)
{
	if (PointSet.empty()) return 0.0;
	double area = 0.0;
	Point O;
	O.x = O.y = 0;
	for (register Polygon::iterator ii = PointSet.begin(); ii != PointSet.end() - 1; ++ii)
	{
		area += CTVA(O, (*ii), (*(ii + 1)));
	}
	area += CTVA(O,PointSet[PointSet.size() - 1], PointSet[0]);
	return abs(area);
}

inline bool CheckAns(Point aa, Point bb, Point cc, Point dd, Point res)
{
	if (aa.x > bb.x) swap(aa, bb);
	if (cc.x > dd.x) swap(cc, dd);
	bool res1 = (aa.x <= res.x && res.x <= bb.x && cc.x <= res.x && res.x <= dd.x);
	
	if (aa.y > bb.y) swap(aa, bb);
	if (cc.y > dd.y) swap(cc, dd);
	bool res2 = (aa.y <= res.y && res.y <= bb.y && cc.y <= res.y && res.y <= dd.y);
	return res1 & res2;
}

inline bool CheckAnsStrict(Point aa, Point bb, Point cc, Point dd, Point res)
{
	if (aa.x > bb.x) swap(aa, bb);
	if (cc.x > dd.x) swap(cc, dd);
	bool res1 = (aa.x < res.x && res.x < bb.x && cc.x < res.x && res.x < dd.x);
	if (aa.y > bb.y) swap(aa, bb);
	if (cc.y > dd.y) swap(cc, dd);
	bool res2 = (aa.y < res.y && res.y < bb.y && cc.y < res.y && res.y < dd.y);
	return res1 & res2;
}

inline bool Checked(Polygon PointSet, Point p)
{
	//if (p == (Point) { 0.0, 0.0 }) return false;
	bool flag = true;
	for (register Polygon::iterator i = PointSet.begin(); i != PointSet.end(); ++i)
	{
		if (p == *i)
		{
			flag = false;
			break;
		}
	}
	return flag;
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
			Point res;
			res.x = a.x, res.y = y;
			if (CheckAns(a, b, c, d, res))
				return (Point) { a.x, y };
			else
				return (Point) { IMP, IMP };
		}
	}
	else
		if (c.x == d.x)
		{
			if ((a.x <= c.x && c.x <= b.x) || (a.x >= c.x && c.x >= b.x))
			{
				line l = GetLineFromPoint(a, b);
				double y = l.k * c.x + l.b;
				Point res;
				res.x = c.x, res.y = y;
				if (CheckAns(a, b, c, d, res))
					return (Point) { a.x, y };
				else
					return (Point) { IMP, IMP };
			}
		}
		else
		{
			line l1 = GetLineFromPoint(a, b);
			line l2 = GetLineFromPoint(c, d);
			
			Point res = GetCrossPoint(l1, l2);
			if (CheckAns(a, b, c, d, res))
				return res;
			else
				return (Point) { IMP, IMP };
		}
}


Point center;
inline Point calc_center(Polygon G)
{
	double x = 0, y = 0;
	for (register Polygon::iterator i = G.begin(); i != G.end(); ++i)
	{
		x += (*i).x;
		y += (*i).y;
	}
	x /= G.size(), y /= G.size();
	return (Point) { x, y };
}
bool Cmpless(Point a, Point b)
{
    if (a.x - center.x >= 0 && b.x - center.x < 0)
        return true;
    if (a.x - center.x < 0 && b.x - center.x >= 0)
        return false;
    if (a.x - center.x == 0 && b.x - center.x == 0)
	{
        if (a.y - center.y >= 0 || b.y - center.y >= 0)
            return a.y > b.y;
        return b.y > a.y;
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    int det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
    if (det < 0)
        return true;
    if (det > 0)
        return false;
    
    // points a and b are on the same line from the center
    // check which point is closer to the center
    int d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
    int d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
    return d1 > d2;
}
inline void ClockwiseSortPoints(Polygon& G)
{
	center = calc_center(G);
	sort(G.begin(), G.end(), Cmpless);
}

inline bool Inpolygon(Point P, Polygon G)
{
	Point END;
	END.x = DOUBLE_MAX, END.y = DOUBLE_MAX - 1;
	int tot = 0;
	for (register Polygon::iterator i = G.begin(); i != G.end(); ++i)
	{
		Polygon::iterator Nexti;
		if (i == G.end() - 1) Nexti = G.begin();
		else Nexti = i + 1;
		Point CP = GetCross(P, END, *i, *Nexti);
		if (CP != (Point) { IMP, IMP } && CheckAnsStrict(P, END, *i, *Nexti, CP))
		{
			++tot;
		}
	}
	if (tot == 1) return true;
	else return false;
}

int main()
{
	freopen("area.in", "r", stdin);
	freopen("area.out", "w", stdout);
	ios::sync_with_stdio(false);
	
	Points.clear(), PointsM.clear(), PointsN.clear();
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
	
	for (register Polygon::iterator i = PointsN.begin(); i != PointsN.end(); ++i)
	{
		Polygon::iterator Nexti;
		if (i == PointsN.end() - 1) Nexti = PointsN.begin();
		else Nexti = i + 1;
		for (register Polygon::iterator j = PointsM.begin(); j != PointsM.end(); ++j)
		{
			Polygon::iterator Nextj;
			if (j == PointsM.end() - 1) Nextj = PointsM.begin();
			else Nextj = j + 1;
			if (GetCross(*i, *Nexti, *j, *Nextj) != (Point) { IMP, IMP })
			{
				Point P = GetCross(*i, *Nexti, *j, *Nextj);
				if (Checked(Points, P))
				{
//					cout << GetLineFromPoint(*i, *Nexti) << endl << GetLineFromPoint(*j, *Nextj) << endl;
					Points.push_back(P);
//					cout << P << endl;
				}
			}
		}
	}
	
//	cout << "_______________________________" << endl;
	for (register Polygon::iterator i = PointsN.begin(); i != PointsN.end(); ++i)
	{
		int tot = 0;
		if (Inpolygon(*i, PointsM))
			++tot;
		if (tot == 1)
			if (Checked(Points, *i))
				Points.push_back(*i);
	}

	for (register Polygon::iterator i = PointsM.begin(); i != PointsM.end(); ++i)
	{
		int tot = 0;
		if (Inpolygon(*i, PointsN))
			++tot;
		if (tot == 1)
			if (Checked(Points, *i))
				Points.push_back(*i);
	}
	
	if (Points.empty())
	{
		cout << "0.000" << endl;
		return 0;
	}
	ClockwiseSortPoints(Points);
//	for (register Polygon::iterator i = Points.begin(); i != Points.end(); ++i)
//	{
//		cout << *i << endl;
//	}
	printf("%0.3lf\n",ComputeAns(Points));
	return 0;
}
