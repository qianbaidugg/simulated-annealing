#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Position                             //����
{
	double x;
	double y;
};

struct City									//������Ϣ
{
	string cityname;
	int index;
	Position pos;
};

class tuihuo								//�˻���Ķ���
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