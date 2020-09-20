#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Position                             //坐标
{
	double x;
	double y;
};

struct City									//城市信息
{
	string cityname;
	int index;
	Position pos;
};

class tuihuo								//退火类的定义
{
private:
	vector<City> cvec;
	vector<string> route;
	static double StartTmp;
	static double EndTmp;
	double NowTmp;
	double Fordown;
	int count;

public:
	tuihuo(double a,double b,double c);
	void ReadFile(char *c); 
	double Distance();
	vector<City> NewRoute();
	bool IsShorter(double dist1,double dist2);
	bool IsPossible(double dist1,double dist2);
	bool IsInnerjmpOver();
	bool IsOuterjmpOver();

	void Process();
};