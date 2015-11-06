#include<stdio.h>
#include <stdlib.h>
#define max 100
#define infinity 10000
float in[max][max],tmp[max][max],sig[max][max],form[max][max];
int size,energy[max];
char tmpq[max];
int ans[max];
//copy and clean tmp
int isdigit(char a)
{
	return (a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9');
}
void copy(float *a,float *b,int c)
{
	for(int i=0;i<c;i++)
	{
		b[i]=a[i];
		a[i]=0;
	}
}
void insert(float a,float b,float k)
{
	int *ptr=ans;
	if(k>=0)
	{
		if(*ptr<0)
		{
			ptr[0]=(int)a;
			ptr[1]=(int)k;
			ptr[2]=(int)b;
		}
		else
		{
			int *i=ans;
			while(*i>=0)i++;
			i--;
			while(!(*ptr==(int)a&&*(ptr+1)==(int)b))ptr++;
			while(i!=ptr)
			{
				*(i+1)=*i;
				i--;
			}
			*(ptr+1)=(int)k;
		}
		insert(a,k,form[(int)a][(int)k]);
		insert(k,b,form[(int)k][(int)b]);
	}
	else
	{
		if(*ptr<0)
		{
			ptr[0]=(int)a;
			ptr[1]=(int)b;	
		}
	}
}
void refresh(float s)
{
	for(int i=0;i<size;i++)
	{
		ans[i]=-1;
		for(int j=0;j<size;j++)
		{
			form[i][j]=-1;
			if(energy[i]==0||sig[i][j]<s)tmp[i][j]=-1;//0°T¯E¤]ºâ³á 
		
			else tmp[i][j]=in[i][j];
			//printf("(  %d)\n",(int)in[i][j]);
		}
	}
}
//find if it can do

int id(float *q)
{
	if(tmpq[1]<='9'&&tmpq[1]>='0')
	{
		char *ptr=tmpq;
		int i=0;
		while(*ptr&&i<3)
		{
			while(!(*ptr<='9'&&*ptr>='0')&&*ptr&&i<3)++ptr;
			if(*ptr)
			{
				q[i]=atof(ptr);
				i++;
				while((*ptr<='9'&&*ptr>='0')||*ptr=='.')ptr++;
			}
		}
		
		return 1;
	}
	return 0;
	
}
int printans(float a,float b)
{
/*	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size ;j++)
		{
			printf("%d ",(int)tmp[i][j]);
		}
		printf("\n");
	}*/
	int i=0;
	insert(a,b,form[(int)a][(int)b]);
	//printf("[%d]\n",(int)tmp[(int)a][(int)b]);
//	printf("the ans for%f,%f  [2][3]=%d energy:%d\n",a,b,(int)form[2][3],energy[(int)a]);
	if(energy[(int)a]==0)
	{
		printf("S%d has no energy\n",(int)(a+1));
		//getchar(); 
		int i=0;
		while(ans[i]>=0)
		{
			ans[i]=-1;
			i++;
		}
		return 0; 
	}
	if((int)tmp[(int)a][(int)b]==-1)
	{
		printf("no result!!\n");
		return 0;
	}
	while(ans[i]>=0)
	{
		
		if(ans[i+1]>=0)energy[ans[i]]--;
		printf("S%d",ans[i]+1);
		if(ans[i+1]>=0)printf("-"); 
		ans[i]=-1;
		i++;
	}
	printf("\n");
	return 0; 
}
void findans(float*q)
{
	refresh(q[2]);
	for(int k=0;k<size;k++)
	{
		for(int i=0;i<size;i++)
		{
			for(int j=0;j<size;j++)
			{
				//printf("[%d][%d][%d]  [%d][%d+%d]\n",i,k,j,(int)tmp[i][j],(int)tmp[i][k],(int)tmp[k][j]);
				if(tmp[i][k]>=0&&tmp[k][j]>=0)
				{
					//printf("[%d][%d][%d]  [%d][%d+%d]\n",i,k,j,(int)tmp[i][j],(int)tmp[i][k],(int)tmp[k][j]);
					if(tmp[i][j]>tmp[i][k]+tmp[k][j]||tmp[i][j]<0)
					{
						//printf("%d  [%d][%d]\n",(int)tmp[i][j],(int)tmp[i][k],(int)tmp[k][j]);
						
						tmp[i][j]=tmp[i][k]+tmp[k][j];
						form[i][j]=k;
					}
				}
			}
		}
	}
	/*for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			printf("%d ",(int)form[i][j]);
		}
		printf("\n");
	}*/
	printans(q[0]-1,q[1]-1);
}
int builddata(char*name,float a[][max])
{
	int msize=0,count=0;
	FILE*in;
	in=fopen(name,"r");
	char tmp[5*max];
	for(int r=0;r<5*max;r++){tmp[r]=0;}
	while(fgets(tmp,5*max,in))
	{
		
	//printf("[%s] \n",tmp);
		int i=0,tmpsize=0;
		float trow[max];
		
	//	printf("OK!");
		char *ptr=tmp;
			
		while(*ptr!='\0'&&*ptr!=0)
		{
			//printf("OK!");
			if(*(ptr)=='X'||*(ptr)=='x')trow[i]=infinity;
			else trow[i]=atof(ptr);
			//printf(" %f ",trow[i]);
			i++;
			
			if(msize==0)tmpsize++;
		
			while((*ptr>='0'&&*ptr<='9')||(*ptr=='.')||*(ptr)=='X'||*(ptr)=='x')
			{
				//	printf("(%c)",*ptr);
				ptr++;
				
				
			}
			++ptr;
			//printf("%c",*ptr);
		}
		if(tmpsize && msize==0)
		{
			msize=tmpsize;
			//printf("(%d OK!)\n",msize);
		}
	//	printf("\n");
		
		for(int i=0;i<msize;i++)
		{
			a[count][i]=trow[i];
			trow[i]=0;
		}
		count++;
		
		for(int r=0;r<5*max;r++){tmp[r]=0;}
	}
	return msize;
}
int main()
{
	FILE *input;
	input=fopen("input.txt","r");
	
	size=builddata("initial.txt",in);
	builddata("signal.txt",sig);
/*	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			printf("%d ",(int)in[i][j]);
		}
		printf("\n");
	}*/
	for(int i=0;i<size;i++)
	{
		energy[i]=10;
	}
	while(fgets(tmpq,max,input))
	{
		//printf("[%s]",tmpq);
		if(!isdigit(*tmpq))
		{
			//printf("[%s]\n",tmpq);
			//printf("in!!\n");
			continue;
		}
		float q[3];
			
		if(id(q))
		{
			
			findans(q);
		}
		else 
		{
		
			char *ptr=tmpq;
			while(*ptr)ptr++;
			//printf("[%d][%d][%d]\n",*ptr,*(ptr-1),*(ptr-2));
			if(!isdigit(*(ptr-1)))
			{
				
				*(ptr-1)=0;	
			}
			//printf("[%s]\n",tmpq);
			builddata(tmpq,sig);
				
		}
	
		for(int i=0;i<max;i++)
		{
			tmpq[i]=0;
		}
		
	}
	
	//getchar(); 
	system("pause");
	
	
	
}
