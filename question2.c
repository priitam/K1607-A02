

#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

int a[100],b[50],c[50];
int n; 
int l,h;
int m;
void *divide();
void *h1();
void *h2();
void *join();
pthread_mutex_t l1;
int main()
{
printf("Enter the number of element u want in array : ");
scanf("%d",&n);
m=n/2;
l=0;
h=n;
int x;
for(x=0;x<n;x++)
{
printf("\n Enter the %d  element : ",x+1);
scanf("%d",&a[x]);
}
pthread_mutex_init(&l1,NULL);
pthread_t  th1;
printf("\n original array\n");
for(int i=0;i<n;i++)
printf("%d , ",a[i]);
pthread_create(&th1,NULL,divide,NULL);
pthread_join(th1,NULL);
int i;
printf("\n-------------------------------------------------------------------------\n\t\t\tFINAL SORTED ARRAY IS :\n");
for (i=0;i<n;i++)
printf(" %d , ",a[i]);
printf("\n\n------------------------------------------------------------------------------------------------------\n\n");
}

void *divide()
{
pthread_t th2,th3, th4;

pthread_create(&th2,NULL,h1,NULL);
sleep(1);
pthread_create(&th3,NULL,h2,NULL);
sleep(1);
pthread_create(&th4,NULL,join,NULL);
pthread_join(th2,NULL);
pthread_join(th3,NULL);
pthread_join(th4,NULL);
printf("\n------------------------------------------------------------------------------\n\t\tMERGING SORT THREAD 1 AND SORT THREAD 2\n ");
}
void *h1()
{
pthread_mutex_lock(&l1);
 int i,j,t;
for(i=0;i<m;i++)
b[i]=a[i];
printf("\n------------------------------------------------------------------------------\n\t\t\tSORTING THREAD 1 :\n ");
for(i=0;i<m;i++)
printf("%d , ",b[i]);
for (i=0;i<m-1;i++)
for(j=0;j<m-i-1;j++)
{
if(b[j]>b[j+1])
{
t=b[j];
b[j]=b[j+1];
b[j+1]=t;
}
pthread_mutex_unlock(&l1);
}
printf("\n\n\t\t\tSORTING DONE IN THREAD 1 : \n");
for(i=0;i<m;i++)
printf("%d , ",b[i]);
}

void *h2()

{
pthread_mutex_lock(&l1);
 int i,j,t;
for(i=0,j=m;j<n;j++,i++)
c[i]=a[j];
printf("\n------------------------------------------------------------------------------------\n\t\t\tSORTING THREAD 2 :\n");
for(i=0;i<n-m;i++)
printf("%d , ",c[i]);
for (i=0;i<n-m-1;i++)
for(j=0;j<n-m-i-1;j++)
{
if(c[j]>c[j+1])
{
t=c[j];
c[j]=c[j+1];
c[j+1]=t;
}
}
printf("\n\n\t\t\tSORTING DONE IN THREAD 2 :  \n");
for(i=0;i<n-m;i++)
printf("%d , ",c[i]);
pthread_mutex_unlock(&l1);
}

void *join()
{
pthread_mutex_lock(&l1);
int i=0,j=0,k=0;
while(i<m && j<n-m)
{
if(b[i]<c[j])
{
a[k]=b[i];
i++;
}
else
{
a[k]=c[j];
j++;
}
k++;
}
if(i>=n-m)
while(j<n-m)
{
a[k]=c[j];
j++;k++;
}
if(j>=m)
while(i<m)
{
a[k]=b[i];
i++;k++;
}
pthread_mutex_unlock(&l1);
}


