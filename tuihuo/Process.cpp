#include "tuihuo.h"
/*
�˻��๹�캯��
ָ����ʼ�¶ȣ������¶�
�˻�ϵ�����ͼ������ĳ�ʼ��
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
���ļ����������ļ��еĳ�����Ϣ�洢��
���ж���ĳ���������
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


//����·������������ÿ��·���ľ���

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
//����2-opt�����õ��µ�·��

vector<City> tuihuo::NewRoute()
{
	int x = rand()%10;
	int y = rand()%10;
	if( x !=0&& y!=0)/////// ��TSP�����У���һ�������ǲ��ܸı�ģ��˾��Ǳ�֤��һ�����в��䡣
	{
		City temp;
		temp = cvec[x];
		cvec[x] = cvec[y];
		cvec[y] =temp;
	}
	
	return cvec;
}

/*
�ж��µ�·���Ƿ��ԭ·���̵ĺ���
*/
bool tuihuo::IsShorter(double dist1,double dist2)
{
	if( dist1 < dist2 )
		return true;
	else
		return false;
}

/*
�ж��µ�·���Ƿ���һ�����ʽϴ��·��
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
�ж���ѭ���Ƿ����
*/
bool tuihuo::IsInnerjmpOver()
{
	if (count > 1000)
		return true;
	else
		return false;
}

/*
�ж���ѭ���Ƿ����
*/
bool tuihuo::IsOuterjmpOver()
{
	if( NowTmp < EndTmp)
		return true;
	else 
		return false;
}

/*
ģ���˻��㷨�ĺ��ĺ���
���ѭ��1000����ѭ��������
ÿ����ѭ����һ�������洢��ʼ��·��
�����·�����������������µ�·��
��������ԭ����·��
������ڵ��¶�С�ڹ涨�Ľ����¶�
����ѭ��Ҳ������������ֹ
*/
void tuihuo::Process()
{
//	tuihuo(200,1,0.95,0);
	char *c = "������Ϣ.txt";
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