#include "tuihuo.h"
/*
退火类构造函数
指定起始温度，结束温度
退火系数，和计数器的初始化
*/
tuihuo::tuihuo(double a,double b,double c,int d)		
{
	StartTmp = a;
	EndTmp = b;
	Fordown = c;
	count = d;	
	NowTmp = StartTmp;
};

/*
读文件函数，将文件中的城市信息存储到
类中定义的城市容器中
*/
bool tuihuo::ReadFile(char *c)
{
	ifstream infile(c);
	if(!infile)
		return false;
	int num;
	infile>>num;
	
	string name;
	int index;
	double x;
	double y;
	for(int i=0;i<num;i++)
	{
		City city;
		
		infile>>name;
		city.cityname = name;
		
		infile>>index;
		city.index = index;
		
		infile>>x;
		city.pos.x = x;
		
		infile>>y;
		city.pos.y = y;

		cvec.push_back(city);
	}

	infile.close();
	return true;
};


//计算路径函数，计算每次路径的距离

double tuihuo::Distance()
{
	double distance = 0;
	double x,y;
	for(int i=0;i<cvec.size()-1;i++)
	{
		x = cvec[i].pos.x - cvec[i+1].pos.x;
		y = cvec[i].pos.y - cvec[i+1].pos.y;
		distance += sqrt( (x*x) + (y*y) );
	}

	return distance;
}
//利用2-opt方法得到新的路径

vector<City> tuihuo::NewRoute()
{
	int x = rand()%10;
	int y = rand()%10;
	if( x !=0&& y!=0)/////// 在TSP问题中，第一个城市是不能改变的，此就是保证第一个城市不变。
	{
		City temp;
		temp = cvec[x];
		cvec[x] = cvec[y];
		cvec[y] =temp;
	}
	
	return cvec;
}

/*
判断新的路径是否比原路径短的函数
*/
bool tuihuo::IsShorter(double dist1,double dist2)
{
	if( dist1 < dist2 )
		return true;
	else
		return false;
}

/*
判断新的路径是否是一个概率较大的路径
*/
bool tuihuo::IsPossible(double dist1,double dist2)
{
	double f = dist1 - dist2;
	double ft = -f/NowTmp;
	double rand1 = rand() / (double)(RAND_MAX);
	
	if( exp(ft) >  rand1 )
		return true;
	else
		return false;
}

/*
判断内循环是否结束
*/
bool tuihuo::IsInnerjmpOver()
{
	if (count > 1000)
		return true;
	else
		return false;
}

/*
判断外循环是否结束
*/
bool tuihuo::IsOuterjmpOver()
{
	if( NowTmp < EndTmp)
		return true;
	else 
		return false;
}

/*
模拟退火算法的核心函数
如果循环1000次内循环结束，
每次内循环用一个容器存储初始的路径
如果新路径满足条件，就用新的路径
否则还是用原来的路径
如果现在的温度小于规定的结束温度
则外循环也结束，程序终止
*/
void tuihuo::Process()
{
//	tuihuo(200,1,0.95,0);
	char *c = "城市信息.txt";
	ReadFile(c);
	while(1)
	{
		while(1)
		{
			vector<City> precity = cvec;
			double predist = Distance();
			NewRoute();
			double nowdist = Distance();
			if(!IsShorter(nowdist,predist))
			{
				if(!IsPossible(nowdist,predist))
				{
					cvec = precity;
				}
			}
			for(int i=0;i<cvec.size();i++)
			{
				cout<<cvec[i].cityname<<" ";
			}
			cout<<Distance()<<endl;
			count++;
			if(IsInnerjmpOver())
				break;
		}		 
		if(IsOuterjmpOver())
			break;
		else
			NowTmp = NowTmp * Fordown;	
	}
}

void main()
{
	tuihuo fire(400,0.0001,0.95,0);
	fire.Process();

}