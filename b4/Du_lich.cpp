#include <fstream>
#include <iostream>
using namespace std;

struct Node
{
	int index;  // so thu tu
	int g;      // khoang cach tu dinh ban dau den dinh hien ta
	int f;      // f = h + g;
	int h;      // duong di ngan nhat
	int color;  // danh dau dinh di qua
	int parent;    // dinh cha
};

int a[100][100];
Node p[100];
Node Open[100];
Node Close[100];

void ReadInputFile1(int *b, int &n)
{
	fstream fs1("Input1.txt");

	if (!fs1.is_open())
	{
		cout << "Khong the mo duoc file!";
	}
	else
	{
		fs1 >> n;

		for (int i = 0; i < n; i++)
		{
			fs1 >> b[i];
		}
	}
    fs1.close();
}

void ReadInputFile2(int a[100][100], int &n, int &start, int &finsh)
{
	fstream fs2("Input2.txt");

	if (!fs2.is_open())
	{
		cout << "Khong the mo duoc file!";
	}
	else
	{
		fs2 >> n >> start >> finsh;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
				fs2 >> a[i][j];
		}
	}
	fs2.close();
}

void RhowMatrix(int a[100][100], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << a[i][j] << "\t";
		}
		cout << "\n";
	}
}

int Count(int n, Node *Open)
{
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].color == 1)
			count++;
	}
	return count;
}

int Find(int n, Node *Open)
{

	for (int i = 0; i < n; i++)
		if (Open[i].color == 1)
			return i;
    return -1;
}

int FindMin(int n, Node *Open)
{
	int minIndex = Find(n, Open);
	int min = Open[minIndex].f;
	for (int i = 0; i < n; i++)
	{
		if (Open[i].f < min && Open[i].color == 1)
		{
			minIndex = i;
			min = Open[i].f;
		}
	}
	return minIndex;
}

void Init(int n, int *b)
{
	for (int i = 0; i < n; i++)
	{
		p[i].index = i;
		p[i].color = 0;
		p[i].g = b[i];
		p[i].parent = 0;
		p[i].f = p[i].g;
		p[i].h = 0;
	}
}

int FindPoint(int n, Node *q, int o)
{
	for (int i = 0; i < n; i++)
		if (q[i].index == o)
			return  i;
    return -1;
}

void AStar(int a[100][100], int n, int start, int finsh, int b[])
{
	int l = 0;
	Open[l] = p[start];
	Open[l].color = 1;
	Open[l].f = Open[l].h + Open[l].g;
	l++;
	int w = 0;

	while (Count(l, Open) != 0) // kiem tra xem tap Open co con phan tu nao khong
	{
		int k = FindMin(n, Open); // tim vi tri nho nhat trong Open
		Open[k].color = 2; // cho diem tim duoc vao Close
		Close[w] = Open[k];
		Close[w].color = 2;
		w++;
		p[FindPoint(n, p, Open[k].index)].color = 2;
		if (FindPoint(n, p, Open[k].index) == finsh)
		{
			cout << "Duong di qua  la" << endl;
			cout << finsh << "\t";
			int y = FindPoint(w, Close, finsh);
			int u = Close[y].parent;
			while (u != start)
			{
				y = FindPoint(w, Close, u);
				u = Close[y].parent;
				cout << u << "\t";
			}
			break;
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				if (a[FindPoint(n, p, Open[k].index)][i] != 0 && p[i].color == 0) // neu chua co trong Open va Close
				{
					Open[l] = p[i];
					Open[l].color = 1;
					Open[l].h = a[FindPoint(n, p, Open[k].index)][i] + Open[k].h; // tinh h khoang cach ngan nhat tu dinh bat dau den dinh hien tai 
					Open[l].f = Open[l].g + Open[l].h;
					Open[l].parent = FindPoint(n, p, Open[k].index);
					p[i].color = 1;
					l++;
				}
				if (a[FindPoint(n, p, Open[k].index)][i] != 0 && p[i].color == 1) // neu dinh da co trong Open
				{
					int h = FindPoint(l, Open, p[i].index);
					Node tempNode = p[i];
					tempNode.color = 1;
					tempNode.h = a[FindPoint(n, p, Open[k].index)][i] + Open[k].h;
					tempNode.parent = k;
					tempNode.f = tempNode.h + tempNode.g;
					if (tempNode.f < Open[h].f) // neu f trang thai hien tai be hon trang thai cap nhat truoc do			
						Open[h] = tempNode;
				}
				if (a[FindPoint(n, p, Open[k].index)][i] != 0 && p[i].color == 2) // neu dinh da co trong Close
				{
					int h = FindPoint(l, Close, p[i].index);
					Node tempNode = p[i];
					tempNode.color = 1;
					tempNode.h = a[FindPoint(n, p, Open[k].index)][i] + Open[k].h;
					tempNode.parent = k;
					tempNode.f = tempNode.h + tempNode.g;
					if (tempNode.f < Close[h].f) // neu f trang thai hien tai be hon trang thai truoc do	
					{
						Open[l] = tempNode; // them vao Open
						Close[h].color = 1; // danh dau dinh do thuoc Open						
						l++;
					}
				}
			}
		}
	}
}

int main()
{
	int n;	
	int start;
	int finish;
	int b[100];

	ReadInputFile1(b, n);
	ReadInputFile2(a, n, start, finish);

	Init(n, b);
	cout << "Dinh bat dau" << endl;
	cout << start << endl;
	cout << "Dinh ket thuc" << endl;
	cout << finish << endl;
	
	AStar(a, n, start, finish, b);
	return 0;
	
	
}