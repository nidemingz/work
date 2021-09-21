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
    ifstream file(file_name.c_str());//读文件
	while(getline(file,str))
	{
	    istringstream is(str);     
        string s;
		while (is>>s)
		{
		    if(s[0]==';'&&s[1]=='/'&&(s[2]=='*'||s[2]=='/')) break;//判断是否是注释 ,如果是注释，跳到下一行 
			char str1[100],str2[100];
			int s1,s2;
	        for(i=0;i<32;i++)			
	        {
			    s1=s.size(),s2=keyword[i].size();
	            memset(str1,0,sizeof(str1));
	            memset(str2,0,sizeof(str2));
	            
	            for(j=0;j<s1;j++) if(s[j]!='{'&&s[j]!='}'&&s[j]!='('&&s[j]!=')'&&s[j]!=':'&&s[j]!=';') str1[j]=s[j];//消除括号等符号对读取的影响 
	            for(j=0;j<s2;j++) str2[j]=keyword[i][j];
		        if(strcmp(str1,str2)==0)
		        {
			        if(strcmp(str1,"switch")==0) switch_num++;
		    	    if(strcmp(str1,"case")==0) case_num[switch_num]++;
			        total_num++;
		        	break;
		        }
	        }	
		}//关键词检查+switch、case检查 
		
     	if(str.find("else if")!=string::npos)
    	{
		    if(stack[tap]!=2)//如果是连着两个else-if，则合并，结算时视为一个if-elseif-else结构 
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
					}//如果else之前最近的一个是if，则有一个if-else结构，ifelse-num+1，忽略 
					else	
					{
						if(stack[tap]==2)
						{
							if_elseif_else_num++;
							tap-=2;
						}
					}//如果else之前最近的一个是else-if，则判断为if-elseif-else结构，if-elseif-else-num+1，忽略 
				}
			}
		}
	}//if—else结构检查 
	

    if(level>=1) 
	{
		cout<<"total num: "<<total_num<<endl;
	}//等级一	
	if(level>=2)
	{
		cout<<"switch num: "<<switch_num<<endl;
		cout<<"case num: ";
		for(i=1;i<=switch_num;i++) 
		{
		    cout<<" "<<case_num[i];
		} 
		cout<<endl;
	}//等级二 
	if(level>=3)
	{
		cout<<"if-else num: "<<ifelse_num<<endl;
	}//等级三 
	if(level>=4)
	{
		cout<<"if-elseif-else num: "<<if_elseif_else_num;
	}//等级四 
}
