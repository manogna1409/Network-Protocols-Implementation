#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<fstream>
#include<fcntl.h>
#include<stdlib.h>

#define N strlen(g)

using namespace std;



int main()
{

int sz=32;

char msg[sz+9];
char rem[9],g[]="100000111";
char t[sz+9];
cout<<"size of crc8"<<N<<endl;

int sockfd;
struct sockaddr_in my_addr;
sockfd=socket(PF_INET,SOCK_STREAM,0);  //Creating the socket

if(sockfd<0)
{
cout<<"socket creation error"<<endl;
}

my_addr.sin_family=AF_INET;
my_addr.sin_port=htons(6000);
//  my_addr.sin_addr.s_addr=inet_addr("192.168.2.120");
my_addr.sin_addr.s_addr=INADDR_ANY;
// memset(my_addr.sin_zero, '\0', sizeof(my_addr.sin_zero));

int tmp=bind(sockfd, (struct sockaddr *)&my_addr, (sizeof my_addr)); //Binding the socket to the address

if(tmp==-1)
{
cout << "bind error" << endl;
return -1;
} 
else
{
cout << "binded" << endl;
}


int d=listen(sockfd,10);
if(d==-1)
{
cout<<"listen_error"<<endl;
return -1;
}
else
{
cout<<"Listening"<<endl;
}


struct sockaddr_in client_addr;
socklen_t client_size=sizeof client_addr;
int client_fd=accept(sockfd,(struct sockaddr*)&client_addr, &client_size);
if(client_fd==-1)
{
cout << "Accepted connection " << client_fd << endl;
}
else
{
cout<<"connection accepted"<<endl;
} 


//ifstream fil;
ifstream fil("data.txt",ios::binary);
fil.seekg(0,ios::end);
long siz=fil.tellg();
cout<<siz<<endl;
fil.seekg(0);
int b=send(client_fd,&siz,sizeof siz,0);
//int sz=32;
char rbuf[sz];
int p;
p=0;
int k=0;
int recv1_buf=0;
while(k<siz)
{
if(p==2)
p=0;

for(int i=0;i<sz;i++)
{
rbuf[i]='0';
}
fil.read(rbuf,sizeof(rbuf));
cout<<"after reading"<<endl;
for(int i=0;i<sz;i++)
{
cout<<rbuf[i];
}
int temp[4];
int a,e,c;

for(int i=0;i<sz;i++)
msg[i]=rbuf[i];

for(int i=0;i<sz;i++)
cout<<msg[i];
cout<<endl;

a=sz;
cout<<"size of the message "<<a<<endl;

char t[a+N+1];
for(int i=0;i<a;i++)
t[i]=msg[i];


for(int i=0;i<a;i++)
cout<<t[i];
cout<<endl;

for(e=a;e<a+N-1;e++) 
t[e]='0';


cout<<"\n Message after appending is :";
for(int i=0;i<a+N;i++)
cout<<t[i];

cout<<endl;


//crc computation
for(e=0;e<N;e++) 
rem[e]=t[e];
 do 
{
if(rem[0]=='1') 
//xorr
for(int c=1;c<N;c++)
rem[c]=((rem[c]==g[c])?'0':'1');

for(c=0;c<N-1;c++) rem[c]=rem[c+1];
rem[c]=t[e++];
}while(e<=a+N-1);
 
cout<<"\nRemainder is : ";
for(int i=0;i<N;i++)
cout<<rem[i];
cout<<endl;



 
 for(e=a;e<a+N;e++)
{ 
t[e]=rem[e-a];
}

srand(time(NULL));


cout<<"\nAfter crc :";
for(int i=0;i<a+N;i++)
cout<<t[i];
cout<<endl;

int man= rand() % 4 +1;
cout<<"man is "<<man<<endl;
if(man==1)
{
cout<<"Frame drops"<<endl;
sleep(3);
continue;
}

int pr=rand()% 3 + 1;
cout<<"\nDo u want to corrupt?? 0(yes) 1(no) ?  ";
//e=pr;
cin>>e;
if(e==1)
cout<<"Bits are corrupted"<<endl;
else
cout<<"bits are not corrupted"<<endl;

if(e==1) {


int num=rand() %14+ 6;
cout<<"number of bits corrupted"<<num<<endl;

for(int i=0;i<num;i++)
{

int x= rand() % (sz+N)+0;
//cout<<"corrupted bit is \n"<<x<<endl;
t[x]=(t[x]=='0')?'1':'0';
}
//cout<<"Enter position where error is to inserted : ";
//cin>>e;
 

cout<<"Data to be transmitted   :";
for(int i=0;i<a+N;i++)
cout<<t[i];
cout<<endl;
}
t[a+N]=p;
cout<<"Seq num  "<<p<<endl;
 int m;
m=send(client_fd,t,sizeof t,0);



if(m<0)
{
cout<<"error in sending"<<endl;
}
else
{
cout<<"message sent"<<endl;
}



int recv_buf;
int check;

//int check = rand() % 3 +0;
//cout<<"check is  "<<check<<endl;
sleep(3);
int mad=recv(client_fd,&recv_buf,sizeof recv_buf,MSG_DONTWAIT);
//cout<<"recv value " << mad;
if(mad<0)
{
cout<<"timeout"<<endl;
sleep(1);
int kav=recv(client_fd,&recv_buf,sizeof recv_buf,MSG_DONTWAIT);
if(kav>0)
{

cout<<"delayed"<< recv_buf<< endl;
continue;
}

}

/*if(check>500000)
{
recv1_buf=0;
usleep(400000);
cout<<"Timeout"<<endl;
continue;

//cout<<recv_buf<<endl;


}

else if(check>400000 && check<500000)
{
usleep(400000);
cout<<"Time out"<<endl;
//for(int i=0;i<5;i++)
recv1_buf=recv_buf;
continue;
}*/



else
{
cout<<"Recieved is  "<<recv_buf<<endl;
if(recv_buf==10 || recv_buf==11)
{

recv1_buf=0;
p++;

k=k+32;

}
}
}



fil.close();
return 0;
}
