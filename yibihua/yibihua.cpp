#include<iostream>
#include<vector>
#include <deque>
#include<set>
#include<fstream>
using namespace std;

int findOdd(int(*matrix)[13], int count);
vector<vector<pair<int, int> > > bianli(int(*matrix)[13], int length, int startvertex);
//bool isConn(int (*matrix)[5], int count);

int main()
{
	int matrix[13][13];
	memset(matrix, 0, sizeof(int)* 13 * 13);
	//matrix[0][1] = 1;
	//matrix[0][3] = 1;
	//matrix[0][4] = 1;
	//matrix[1][0] = 1;
	//matrix[1][2] = 1;
	//matrix[1][3] = 1;
	//matrix[2][1] = 1;
	//matrix[2][3] = 1;
	//matrix[3][0] = 1;
	//matrix[3][1] = 1;
	//matrix[3][2] = 1;
	//matrix[3][4] = 1;
	//matrix[4][0] = 1;
	//matrix[4][3] = 1;
	matrix[0][1] = 1;
	matrix[0][2] = 1;
	matrix[1][0] = 1;
	matrix[1][2] = 1;
	matrix[2][0] = 1;
	matrix[2][1] = 1;
	matrix[2][3] = 1;
	matrix[2][7] = 1;
	matrix[2][10] = 1;
	matrix[3][2] = 1;
	matrix[3][4] = 1;
	matrix[3][5] = 1;
	matrix[3][6] = 1;
	matrix[4][3] = 1;
	matrix[4][5] = 1;
	matrix[5][3] = 1;
	matrix[5][4] = 1;
	matrix[6][3] = 1;
	matrix[6][10] = 1;
	matrix[7][2] = 1;
	matrix[7][8] = 1;
	matrix[7][9] = 1;
	matrix[7][10] = 1;
	matrix[8][7] = 1;
	matrix[8][9] = 1;
	matrix[9][7] = 1;
	matrix[9][8] = 1;
	matrix[10][2] = 1;
	matrix[10][6] = 1;
	matrix[10][7] = 1;
	matrix[10][11] = 1;
	matrix[10][12] = 1;
	matrix[11][10] = 1;
	matrix[11][12] = 1;
	matrix[12][10] = 1;
	matrix[12][11] = 1;



	int startvertex = findOdd(matrix, 13);
	vector<vector<pair<int, int> > > res = bianli(matrix, 13, startvertex);
	cout << res.size() << endl;
	/*for (int i = 0; i < res.size(); i++)
	{
	for (int j = 0; j < res[i].size(); j++)
	{
	cout << "(" << res[i][j].first << "," << res[i][j].second << ")";
	}
	cout << endl;
	}*/
	ofstream out;
	out.open("res.txt", ios::trunc);
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
		{
			out << "(" << res[i][j].first << "," << res[i][j].second << ")";
		}
		out << endl;
	}

	return 0;
}

//第一步：寻找度为奇数的顶点
int findOdd(int(*matrix)[13], int count)
{
	for (int i = 0; i < count; i++)
	{
		int odd = 0;
		for (int j = 0; j < count; j++)
		{
			if (matrix[i][j] == 1)
				odd++;
		}
		if (odd % 2 == 1)return i;
	}
	return 0;
}

vector<vector<pair<int, int> > > bianli(int(*matrix)[13], int length, int startvertex)
{
	int tmpmatrix[13][13];
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			tmpmatrix[i][j] = matrix[i][j];
		}
	}
	vector<vector<pair<int, int> > > res;
	for (int i = 0; i < length; i++)
	{
		if (tmpmatrix[startvertex][i] == 1)
		{
			pair<int, int> mypair = make_pair(startvertex, i);
			tmpmatrix[startvertex][i] = 0;
			tmpmatrix[i][startvertex] = 0;
			vector<vector<pair<int, int> > > tmp = bianli(tmpmatrix, length, i);
			if (tmp.size() == 0)
			{
				vector<pair<int, int> > tmps;
				tmps.push_back(mypair);
				res.push_back(tmps);
			}
			for (int j = 0; j < tmp.size(); j++)
			{
				tmp[j].insert(tmp[j].begin(), mypair);
				res.push_back(tmp[j]);
			}
			tmpmatrix[startvertex][i] = 1;
			tmpmatrix[i][startvertex] = 1;
		}
	}
	return res;
}

//bool isConn(int (*matrix)[5], int count)
//{
//	set<int> vertexs;
//	deque<int> deques;
//	deques.push_back(0);
//	vertexs.insert(0);
//	int mycount = 1;
//	while (!deques.empty())
//	{
//		int num = deques.front();
//		deques.pop_front();
//		for (int i = 0; i < count; i++)
//		{
//			if (matrix[num][i] == 1 && vertexs.find(matrix[num][i]) != vertexs.end())
//			{
//				deques.push_back(matrix[num][i]);
//				mycount++;
//			}
//		}
//	}
//	if (mycount == count)
//		return true;
//	else
//		return false;
//}
