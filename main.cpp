#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<string.h>
using namespace std;

string keyword[32]={"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if",
"int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void","volatile","while" };

int total_num=0;
int switch_num=0;
int case_num[100];
int else_num;
int num=0;
int ifelse_num=0;
int if_elseif_else_num=0;
int stack[100];

int level;
string file_name;
string str;
int main()
{
	int i=0,j=0,tap=0;
    cin>>file_name;
    cin>>level;
    ifstream file(file_name.c_str());//���ļ�
	while(getline(file,str))
	{
	    istringstream is(str);     
        string s;
		while (is>>s)
		{
		    if(s[0]==';'&&s[1]=='/'&&(s[2]=='*'||s[2]=='/')) break;//�ж��Ƿ���ע�� ,�����ע�ͣ�������һ�� 
			char str1[100],str2[100];
			int s1,s2;
	        for(i=0;i<32;i++)			
	        {
			    s1=s.size(),s2=keyword[i].size();
	            memset(str1,0,sizeof(str1));
	            memset(str2,0,sizeof(str2));
	            
	            for(j=0;j<s1;j++) if(s[j]!='{'&&s[j]!='}'&&s[j]!='('&&s[j]!=')'&&s[j]!=':'&&s[j]!=';') str1[j]=s[j];//�������ŵȷ��ŶԶ�ȡ��Ӱ�� 
	            for(j=0;j<s2;j++) str2[j]=keyword[i][j];
		        if(strcmp(str1,str2)==0)
		        {
			        if(strcmp(str1,"switch")==0) switch_num++;
		    	    if(strcmp(str1,"case")==0) case_num[switch_num]++;
			        total_num++;
		        	break;
		        }
	        }	
		}//�ؼ��ʼ��+switch��case��� 
		
     	if(str.find("else if")!=string::npos)
    	{
		    if(stack[tap]!=2)//�������������else-if����ϲ�������ʱ��Ϊһ��if-elseif-else�ṹ 
			{
				tap++;
    		    stack[tap]=2;
			}	
    	}
		else
		{
			if(str.find("if")!=string::npos)
			{
				tap++;
				stack[tap]=1;
			}
			else
			{
				if(str.find("else")!=string::npos)
				{
					if(stack[tap]==1)
					{
						ifelse_num++;
						tap--;
					}//���else֮ǰ�����һ����if������һ��if-else�ṹ��ifelse-num+1������ 
					else	
					{
						if(stack[tap]==2)
						{
							if_elseif_else_num++;
							tap-=2;
						}
					}//���else֮ǰ�����һ����else-if�����ж�Ϊif-elseif-else�ṹ��if-elseif-else-num+1������ 
				}
			}
		}
	}//if��else�ṹ��� 
	

    if(level>=1) 
	{
		cout<<"total num: "<<total_num<<endl;
	}//�ȼ�һ	
	if(level>=2)
	{
		cout<<"switch num: "<<switch_num<<endl;
		cout<<"case num: ";
		for(i=1;i<=switch_num;i++) 
		{
		    cout<<" "<<case_num[i];
		} 
		cout<<endl;
	}//�ȼ��� 
	if(level>=3)
	{
		cout<<"if-else num: "<<ifelse_num<<endl;
	}//�ȼ��� 
	if(level>=4)
	{
		cout<<"if-elseif-else num: "<<if_elseif_else_num;
	}//�ȼ��� 
}
