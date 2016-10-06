#include<iostream>
#include<vector>
#include <deque>
#include<set>
#include<fstream>
using namespace std;

int findOdd(int *matrix, int row, int line);
vector<vector<pair<int, int> > > bianli(int *matrix, int row, int line, int startvertex);
//bool isConn(int (*matrix)[5], int count);

int main()
{
	ifstream in;
	in.open("..\\yibihua\\data.txt",ios::in);
	int vertex, lines;	//图的顶点个数和边数
	in >> vertex >> lines;
	int *matrix = new int[vertex*vertex];
	memset(matrix, 0, sizeof(int)*vertex*vertex);
	for (int i = 0; i < lines*2; i++)
	{
		int startv, endv;
		in >> startv >> endv;
		matrix[startv*vertex + endv] = 1;
	}

	int startvertex = findOdd(matrix,vertex,vertex);
	vector<vector<pair<int, int> > > res = bianli(matrix,vertex, vertex, startvertex);
	//cout << res.size() << endl;
	for (int i = 0; i < res.size(); i++)
	{
		if (res[i].size() == lines)
		{
			for (int j = 0; j < res[i].size(); j++)
			{
				cout << "(" << res[i][j].first << "," << res[i][j].second << ")";
			}
			cout << endl;
			break;
		}		
	}
	/*ofstream out;
	out.open("res.txt", ios::trunc);
	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
		{
			out << "(" << res[i][j].first << "," << res[i][j].second << ")";
		}
		out << endl;
	}*/

	return 0;
}

//第一步：寻找度为奇数的顶点
int findOdd(int *matrix,int row, int line)
{
	for (int i = 0; i < row; i++)
	{
		int odd = 0;
		for (int j = 0; j < line; j++)
		{
			if (matrix[i*row+j] == 1)
				odd++;
		}
		if (odd % 2 == 1)return i;
	}
	return 0;
}

vector<vector<pair<int, int> > > bianli(int *matrix,int row,int line, int startvertex)
{
	int *tmpmatrix=new int[row*line];
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < line; j++)
		{
			tmpmatrix[i*row+j] = matrix[i*row+j];
		}
	}
	vector<vector<pair<int, int> > > res;
	for (int i = 0; i < line; i++)
	{
		if (tmpmatrix[startvertex*row+i] == 1)
		{
			pair<int, int> mypair = make_pair(startvertex, i);
			tmpmatrix[startvertex*row+i] = 0;
			tmpmatrix[i*row+startvertex] = 0;
			vector<vector<pair<int, int> > > tmp = bianli(tmpmatrix,row, line, i);
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
			tmpmatrix[startvertex*row+i] = 1;
			tmpmatrix[i*row+startvertex] = 1;
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
