#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;
string keyword[32] = { "auto","break;","case","char","const","continue","default:","double","do","else","enum","extern","float","for",
					"goto","if","int","long","register","return","short","signed","sizeof","static","struct","switch","typedef",
					"union","unsigned","void","volatile","while" };
int num = 0;//��¼�ؼ������� 
int switchnum = 0;//ͳ��switch���� 
int casenum[100];//ͳ�Ƹ���switch��case�� 
int if_elseif_else_num = 0, ifelse_num = 0, top = 0;
int stack[100];
int main()
{
	int level;
	string file_name, line;
	cout << "�����ļ���·��:";
	cin >> file_name;
	cout << "������ɵĵȼ�:";//1Ϊ����4Ϊ�ռ� 
	cin >> level;
	ifstream myfile(file_name.c_str());	//���ļ� 
	void Level_12(string a);
	void Level_34(string c);
	while (getline(myfile, line))	//���ж�ȡ 
	{
		istringstream is(line);
		string sgl;
		if (level >= 3) Level_34(line);
		while (is >> sgl)//ȥ���ո�
		{
			if (level >= 1) Level_12(sgl);
		}
	}
	if (level >= 1) cout << "total num: " << num << endl;
	if (level >= 2)
	{
		cout << "switch num: " << switchnum << endl;
		cout << "case num: ";
		for (int a = 1; a <= switchnum; a++) cout << " " << casenum[a];
		cout << endl;
	}
	if (level >= 3)
	{
		cout << "if-else num: " << ifelse_num << endl;
	}
	if (level >= 4)
	{
		cout << "if-elseif-else num: " << if_elseif_else_num;
	}
}
void Level_12(string sige)
{
	char s1[100], s2[100];
	for (int i = 0; i < 32; i++)
	{
		int length1 = sige.length(), length2 = keyword[i].length();
		memset(s1, 0, sizeof(s1));
		memset(s2, 0, sizeof(s2));
		for (int j = 0; j < length1; j++) s1[j] = sige[j];
		for (int j = 0; j < length2; j++) s2[j] = keyword[i][j];
		if (strcmp(s1, s2) == 0)
		{
			if (strcmp(s2, "switch") == 0) switchnum++;
			if (strcmp(s2, "case") == 0) casenum[switchnum]++;
			num++;
			break;
		}
	}
}
void Level_34(string sige)
{
	if (sige.find("else if") != string::npos)
	{
		top++;
		stack[top] = 2;
	}
	else
	{
		if (sige.find("if") != string::npos)
		{
			top++;
			stack[top] = 1;
		}
		else
		{
			if (sige.find("else") != string::npos)
			{
				if (stack[top] == 1)
				{
					ifelse_num++;
					top--;
				}
				else
				{
					if (stack[top] == 2)
					{
						if_elseif_else_num++;
						top--;
					}
				}
			}
		}
	}
}









//C:\Users\ASUS\Desktop\�������\��һ��\text.txt
