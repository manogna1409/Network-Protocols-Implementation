#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#define N strlen(g)

using namespace std;

int main()
{

int sockfd;
sockaddr_in client_addr;
sockfd=socket(PF_INET,SOCK_STREAM,0);
if(sockfd==-1)
{
cout<<"socket connectn error"<<endl;
}

client_addr.sin_family=AF_INET;
client_addr.sin_port=htons(6000);
client_addr.sin_addr.s_addr=INADDR_ANY;
//inet_aton("127.0.0.1",&(client_addr.sin_addr));
//memset(client_addr.sin_zero, '\0', sizeof client_addr.sin_zero);

int tep=connect(sockfd,(struct sockaddr*)&client_addr, sizeof(client_addr));
if(tep==-1)
{
cout << "Connection error" << endl;
return -1;
} 
else
{
cout << "connection established " << endl;
}

ofstream opt("dat.txt",ios::binary);
int siz;
tep=recv(sockfd,&siz,sizeof siz,0);
cout<<"received size is "<<siz<<endl;
for(int k=0;k<2;k=k+32)
{
for(int g=0;g<32;g++)
{

int a=32;
char recv_buf[a+9+1];
char msg[a+9];
char rem[9],g[]="100000111";
int e,c;
cout<<N;
tep=recv(sockfd,recv_buf,sizeof recv_buf,0);

cout<<"Message received:  ";

for(int i=0;i<a+N;i++)
{
msg[i]=recv_buf[i];
}

for(int i=0;i<a+N;i++)
cout<<msg[i];
cout<<endl;

if(tep<0)
{
cout<<"error in receiving data"<<endl;
}
else
{
cout<<"data received  "<<endl;
}

srand(time(NULL));
//int pr= rand()% 6 + 1;
//cout<<"Waiting time "<<pr<<endl;

int z=6;
int b=4;
if(k==0)
{
sleep(z);
}
if(k==1)
{
sleep(b);
}
//crc computation
  for(e=0;e<N;e++) 
rem[e]=msg[e];
 do 
{
    if(rem[0]=='1')
//xorr 
    for(c=1;c<N;c++)
 rem[c]=((rem[c]==g[c])?'0':'1');
  
  for(c=0;c<N-1;c++) rem[c]=rem[c+1];
    rem[c]=msg[e++];
  }while(e<=a+N-1);

 
cout<<"\nRemainder is : ";
for(int i=0;i<N;i++)
cout<<rem[i];

 




int sent_buf;
int count=0;
for(int k=0;k<8;k++)
{
if(rem[k]=='0')
{
count++;
}
}



cout<<"count is: "<<count<<endl;
if(count==8)
{
//cout<<"asci number is "<<sum<<endl;
cout<<"received is"<<endl;
for(int i=0;i<32;i++)
cout<<msg[i];
if(recv_buf[a+N]==0)
sent_buf= 11;
else
sent_buf = 10;


send(sockfd,&sent_buf,sizeof sent_buf,0);
cout<<endl;
//opt.write(m,sizeof m);
}
else
{
//cout<<"asci number is "<<sum<<endl;

cout<<"received is "<<msg<<endl;
cout<<"error in receiving"<<endl;
if(recv_buf[a+N] == 0)
sent_buf = 20;
else
sent_buf =21;
send(sockfd,&sent_buf,sizeof sent_buf,0);

}


}
}
close(sockfd);
return 0;
}









