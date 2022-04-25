#include <stdio.h>
#include <stdlib.h>

typedef struct n{
	int x;
	struct n *next;
};
typedef struct n mcnd;//Node1
typedef struct n mlpr;//Node2
typedef struct n res;//Node3

int a[600],b[600];
int l1,l2;

void Bastir(res *r)
{
	mcnd *mevcut=r;
	mcnd *onceki=NULL;
	mcnd *sonraki=NULL;
	
	while(mevcut!= NULL)
	{
		sonraki = mevcut->next;
		mevcut->next=onceki;
		
		onceki =mevcut;
		mevcut=sonraki;
	}
	r=onceki;
	int result[300];
	int i=0;
	FILE *outfile;
	outfile = fopen("output.txt","w");
	while(i<l1)
	{
		fprintf(outfile,"%d",a[i]);
		i++;
	}
	i=0;
	fprintf(outfile,"\n");
	while(i<l2)
	{
		fprintf(outfile,"%d",b[i]);
		i++;
	}
	i=0;
	fprintf(outfile,"\n");
	while(r!=NULL)
	{
	//	printf("%d",r->x);
		result[i]=r->x;
		fprintf(outfile,"%d",result[i]);
		r=r->next;
		i++;
	}
	fclose(outfile);
}
void Hesapla(mcnd *r1,mlpr *r2,int l1,int l2)
{	
	int carry=0;
	int i=0;
	int resNumber=0;
	
	res *resRoot;
	resRoot = (res *)malloc(sizeof(res));
	resRoot->next=NULL;
	resNumber=r1->x*r2->x;
	if(resNumber>9)
	{
		carry=resNumber/10;
		resNumber=resNumber-(carry*10);
		resRoot->x=resNumber;
	}
	else
	{
		resRoot->x=resNumber;
	}
	r1=r1->next;
	
		for(i=0;i<l1-1;i++)
		{
			resNumber=r1->x*r2->x;
			if(resNumber>9)
			{
				if(i==l1-2)
				{
					resNumber+=carry;
					ekleRes(resRoot,resNumber);
				}
				else
				{
					if(carry>0)
					{
						resNumber=resNumber+carry;
						carry=resNumber/10;
						resNumber=resNumber-(carry*10);
						ekleRes(resRoot,resNumber);
					}
					else
					{
						carry=resNumber/10;
						resNumber=resNumber-(carry*10);
						ekleRes(resRoot,resNumber);
					}
				}
			}
			else
			{
				if(i==l1-2)
				{
					resNumber+=carry;
					ekleRes(resRoot,resNumber);
				}
				else
				{
					if(resNumber+carry>9)
					{
						resNumber+=carry;
						carry=resNumber/10;
						resNumber-=(carry*10);
						ekleRes(resRoot,resNumber);
					}
					else
					{
						ekleRes(resRoot,(resNumber+carry));
						carry=0;
					}	
				}
			}
			resNumber=0;
			if(r1->next!=NULL)
			{
				r1=r1->next;
			}	
		}
	res *root;
	root =resRoot;
	Bastir(root);
}


void ekleRes(res *r,int data)
{
	while(r->next!=NULL)
	{
		r=r->next;
	}
	r->next=(mcnd *)malloc(sizeof(mcnd));
	r->next->x=data;

	r->next->next=NULL;
}
void ekle(mcnd *r,int data)
{
	while(r->next!=NULL)
	{
		r=r->next;
	}
	r->next=(mcnd *)malloc(sizeof(mcnd));
	r->next->x=data;
	r->next->next=NULL;
}
void ekle2(mlpr *r,int data)
{
	while(r->next!=NULL)
	{
		r=r->next;
	}
	r->next=(mlpr *)malloc(sizeof(mlpr));
	r->next->x=data;
	r->next->next=NULL;
}
void terscevir(mcnd *r,mlpr* r2,int l1,int l2)
{
	mcnd *mevcut=r;
	mcnd *onceki=NULL;
	mcnd *sonraki=NULL;
	
	while(mevcut!= NULL)
	{
		sonraki = mevcut->next;
		mevcut->next=onceki;
		
		onceki =mevcut;
		mevcut=sonraki;
	}
	r=onceki;
	
	mevcut=r2;
	onceki=NULL;
	sonraki=NULL;
	
	while(mevcut !=NULL)
	{
		sonraki = mevcut->next;
		mevcut->next=onceki;
		
		onceki =mevcut;
		mevcut=sonraki;
	}
	r2=onceki;
	Hesapla(r,r2,l1,l2);
}
int main()
{
	FILE *file=fopen("input.txt","r+");
	char s1[600],s2[600];
	fscanf(file,"%s %s",&s1,&s2);
	fclose(file);
	
	int ans[200];

	l1=strlen(s1);
	l2=strlen(s2);
	int i;
	for(i=0;i<l1;i++)
	{
		a[i]=s1[i]-'0';
	}	
	for(i=0;i<l2;i++)
	{
		b[i]=s2[i]-'0';
	}

	mcnd *root1;
	root1=(mcnd *)malloc(sizeof(mcnd));
	root1 ->next =NULL;
	root1 ->x=a[0];

	for(i=1;i<l1;i++)
	{
		ekle(root1,a[i]);
	}
	
	mlpr *root2;
	root2=(mlpr *)malloc(sizeof(mlpr));
	root2 ->next =NULL;
	root2 ->x=b[0];


	if(l2>1)
	{
		for(i=1;i<l2;i++)
		{
			ekle2(root2,b[i]);
		}
	}

	terscevir(root1,root2,l1,l2);


	return 0;
}
