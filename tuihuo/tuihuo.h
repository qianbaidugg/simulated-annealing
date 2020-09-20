/*
模拟退火算法
制作者：薛成刚
*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <ctime>
using namespace std;
struct Position                     /////////////////////坐标
{
	double x;
	double y;
};

struct City			///////////////////////////城市信息
{
	string cityname;
	int index;
	Position pos;
};

class tuihuo		//////////////////////////退火类的定义
{
public:
	vector<City> cvec;
	vector<string> route;
	double StartTmp;
	double EndTmp;
	double NowTmp;
	double Fordown;
	int count;

public:
	tuihuo(double a,double b,double c,int d);
	bool ReadFile(char *c); 
	double Distance();
	vector<City> NewRoute();
	bool IsShorter(double dist1,double dist2);
	bool IsPossible(double dist1,double dist2);
	bool IsInnerjmpOver();
	bool IsOuterjmpOver();

	void Process();
};