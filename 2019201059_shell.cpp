#define _XOPEN_SOURCE 700
#include<bits/stdc++.h>
#include<unistd.h>
#include  <cstdio>
#include <sys/types.h>
#include<cstring>
#include<stdlib.h>
#include<sys/wait.h>
#include <termios.h>
#include <time.h>
#include <fcntl.h>
#include<map>
#include<unordered_map>
#define MAX 100
#include<iostream>
using namespace std;
#define hasmap unordered_map<char,node *>
unordered_map<string,string> m;

char *remspa(char *s)
{
int l=0,r=0;
  while(s[r]!='\0')
  {
  if(s[l]!=' ')
  {
  s[l++]=s[r];
  }
r++;
}
s[l]='\0';
return s;
}

class node
{
public:
  char data;
  hasmap h;
  bool isTerminal;
  node(char d)
  {
    data = d;
    isTerminal = false;
  }
};

class Trie
{
node *root;

public:
  Trie()
  {

  root = new node('\0');
  }

void addWord(char *word)
{
  node *temp = root;
  
  for(int i=0;word[i]!='\0';i++)
  {
    char ch = word[i];
  if(temp->h.count(ch)==0)
  {
    node *child = new node(ch);
    temp->h[ch]=child;
    temp=child;
  }
  
  else
  {
    temp = temp->h[ch];
  }

  }
  temp->isTerminal = true;
}

void printWord(char *word, int wordLength, char *prefix)
{
    cout<<prefix;
    for(int i = 0; i < wordLength; i++)
        cout<<word[i];
}

void traverseTrie(node *root, char *wordSoFar, int wordLength, char *prefix)
{
    wordSoFar[wordLength++] = root -> data;
    if(root -> isTerminal)
    {
        printWord(wordSoFar, wordLength, prefix);
        cout<<endl;
    }
    auto it = (root -> h).begin();
    while(it != (root-> h).end())
    {
        traverseTrie(it -> second, wordSoFar, wordLength, prefix);
        it++;
    }
}

bool searchAll(char *word)
{


    node *temp = root;
    char arr[100];
    for(int i=0;word[i]!='\0';i++)
    {
        char ch = word[i];
        if(temp->h.count(ch))
        {
          temp=temp->h[ch];
        }
        else
        {
            return false;
        }
    }

    for(auto it = (temp -> h).begin(); it != (temp -> h).end(); it++)
    {
        char wordSoFar[MAX];
        int wordLength = 0;
        traverseTrie(it -> second, wordSoFar, wordLength, word);
    }

    return temp->isTerminal;

}

};


void insertion(string key,string val)
{
m.insert(make_pair(key,val));
//cout<<endl<<key<<endl;
//cout<<val<<endl;
}

void executeg_pipe(char **par,char *line)
{ 
  //cout<<endl;
  //cout<<par[0]<<endl;
  //cout<<par[1]<<endl;
  //cout<<line<<endl;
  int pipe1[2];
  int pipe2[2];
 //cout<<line;
  pipe(pipe1);
  pipe(pipe2);
 pid_t  pid;


     int status;
    for(int i=0;i<2;i++)
    { 
      char *token=new char[strlen(par[i])];
      char* aval[100];
      int cp=0;
      token = strtok(par[i]," ");
      while(token){
        aval[cp] = new char[strlen(token)];
        strcpy(aval[cp],token);
        token = strtok(NULL," ");
        //cout << "This is aa " << aa[pi];
        cp++;
      }
      aval[cp] = NULL;

     if ((pid = fork()) < 0) 
     {     
          printf("Fail to create fork child\n");
          exit(1);
     }
     
     else if (pid == 0) 
     {          
     
      if(i==0)
      {
        close(1);
        close(pipe1[0]);
        dup2(pipe1[1],1);
      }

      if(i==1)
      {
        close(0);
        close(pipe1[1]);
        dup2(pipe1[0],0);
      }
          if (execvp(aval[0], aval) < 0) 
          {     
               printf("Error in execution\n");
               exit(1);
          }
     }


     else 
     {                                
     int stat;  
         waitpid(pid,&stat,WUNTRACED);
         // while (wait(&status) != pid)       
               //;
     }
     if(i==0)
     close(pipe1[1]);
    if(i==1)
        close(pipe2[1]);

   }
 
} 


void readg3_cmd(char *line, char **argv)
{
int count=0; 
int i=0,j=0;
char *array[1024],*tok,*tok2;

char *temp = new char[strlen(line)];

char *final = new char[strlen(line)];

int p=0;
for(;p<strlen(line);p++)
{
    temp[p]=line[p];
}

tok = strtok(line,"|");
 tok2 = strtok(tok," "); 
  array[i++] = strdup(tok2);

for(int j=0;j<i;j++)
{
 argv[j] = array[j];
 argv[i] = NULL;
}

int l=0;
int size = strlen(temp)-1;
while(size>=0)
{
  if(temp[size]=='|')
    break;
  
  final[l]=temp[size];
  l++;
  size--;
}
final[l]='\0';
char *rev = new char[strlen(final)];
int size1 = strlen(final)-1;
int t=0;
//cout<<size1;
while(size1>=0)
{
//cout<<"kesari";
rev[size1]=final[t];
size1--;
t++;  
}
rev[t]='\0';

/*for(int k=0;k<strlen(rev);k++)
      cout<<rev[k];*/

argv[1]=rev;
//cout<<argv[0]<<" "<<argv[1];
executeg_pipe(argv,rev);
delete rev;
delete temp;
delete final;
}




void executeg2(char **par,char *line)
{ 
cout<<"Home";
cout<<line;
pid_t  pid;
int status;

if ((pid = fork()) < 0) 
{     
printf("Fail to create fork child\n");
exit(1);
}
     
else if (pid == 0) 
{          
int fd = open(line,O_RDONLY|O_APPEND|O_WRONLY,0777);
if(fd==-1)
{
  cout<<"unable to open";
  exit(1);
}
dup2(fd,1);
close(fd);
if (execvp(*par, par) < 0) 
{     
printf("Error in execution\n");
exit(1);
 }
     }


     else 
     {                                  
          while (wait(&status) != pid)       
               ;
     }
  //cout<<fd<<" "<<t; 
}

void readg2_cmd(char *line, char **argv)
{

int count=0; 
int i=0,j=0;
char *array[1024],*tok,*tok2;

char *temp = new char[strlen(line)];

char *final = new char[strlen(line)];

int p=0;
for(;p<strlen(line);p++)
{
    temp[p]=line[p];
}

tok = strtok(line,">>");
 tok2 = strtok(tok," "); 
  array[i++] = strdup(tok2);

for(int j=0;j<i;j++)
{
 argv[j] = array[j];
 argv[i] = NULL;
}

int l=0;
int size = strlen(temp)-1;
while(size>=0)
{
  if(temp[size]=='>')
    break;
  
  final[l]=temp[size];
  l++;
  size--;
}
final[l]='\0';
char *rev = new char[strlen(final)];
int size1 = strlen(final)-1;
int t=0;
//cout<<size1;
while(size1>=0)
{
//cout<<"kesari";
rev[size1]=final[t];
size1--;
t++;  
}
rev[t]='\0';

//cout<<"first"<<argv[0]<<endl;
//cout<<"second"<<rev<<endl;

executeg2(argv,rev);

}


void executeg(char **par,char *line)
{
  
  cout<<line;
 pid_t  pid;
 

     int status;
     
     if ((pid = fork()) < 0) 
     {     
          printf("Fail to create fork child\n");
          exit(1);
     }
     
     else if (pid == 0) 
     {          
      int fd = open(line,O_RDONLY|O_CREAT|O_WRONLY,0777);
      dup2(fd,1);
      close(fd);
          if (execvp(*par, par) < 0) 
          {     
               printf("Error in execution\n");
               exit(1);
          }
     }


     else 
     {                                  
          while (wait(&status) != pid)       
               ;
     }
  //cout<<fd<<" "<<t; 
}



void readg_cmd(char *line, char **argv)
{

int count=0; 
int i=0,j=0;
char *array[1024],*tok,*tok2;

char *temp = new char[strlen(line)];

char *final = new char[strlen(line)];

int p=0;
for(;p<strlen(line);p++)
{
    temp[p]=line[p];
}

tok = strtok(line,">");
 tok2 = strtok(tok," "); 
  array[i++] = strdup(tok2);

for(int j=0;j<i;j++)
{
 argv[j] = array[j];
 argv[i] = NULL;
}

int l=0;
int size = strlen(temp)-1;
while(size>=0)
{
  if(temp[size]=='>')
    break;
  
  final[l]=temp[size];
  l++;
  size--;
}
final[l]='\0';
char *rev = new char[strlen(final)];
int size1 = strlen(final)-1;
int t=0;
//cout<<size1;
while(size1>=0)
{
//cout<<"kesari";
rev[size1]=final[t];
size1--;
t++;  
}
rev[t]='\0';

/*for(int k=0;k<strlen(rev);k++)
      cout<<rev[k];*/

executeg(argv,rev);
delete rev;
delete temp;
delete final;
}



int getkey() {
    int character;
    struct termios orig_term_attr;
    struct termios new_term_attr;
    tcgetattr(fileno(stdin), &orig_term_attr);
    memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
    new_term_attr.c_lflag &= ~(ECHO|ICANON);
    new_term_attr.c_cc[VTIME] = 0;
    new_term_attr.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);
  
    while((character=fgetc(stdin))==-1);

    tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);

    return character;
}

/*int getval() 
{
    int character;
    struct termios prev_att;
    struct termios next_att;
    tcgetattr(fileno(stdin), &prev_att);
    memcpy(&next_att, &prev_att, sizeof(struct termios));
    next_att.c_lflag &= ~(ECHO|ICANON);
    next_att.c_cc[VTIME] = 0;
    next_att.c_cc[VMIN] = 0;
    tcsetattr(fileno(stdin), TCSANOW, &next_att);
  
    while((character=fgetc(stdin))==-1);

    tcsetattr(fileno(stdin), TCSANOW, &prev_att);

    return character;
}*/




void prompt_function(char p)
{
char cwd[PATH_MAX];

char* prompt_val = getcwd(cwd,sizeof(cwd));
//cout<<prompt_val<<endl;
   if (prompt_val!= NULL) 
   {
       cout<<prompt_val<<p;
       //cout<<sizeof(cwd);
   } 
   else 
   {
       perror("getcwd() error");
   }
  
}

     
void  execute(char **par)
{
     pid_t  pid;
     int    status;
     
     if ((pid = fork()) < 0) 
     {     
          printf("Fail to create fork child\n");
          exit(1);
     }
     
     else if (pid == 0) 
     {          
          if (execvp(*par, par) < 0) 
          {     
               printf("Error in execution\n");
               exit(1);
          }
     }


     else 
     {                                  
          while (wait(&status) != pid)       
               ;
     }

}



void read_cmd(char *line, char **argv)
{
int count=0; 
int i=0,j=0;
//insertion("~","/home/hp/Documents/OS-Assignment");
char *array[1024],*tok;


tok = strtok(line," ");

while(tok!=NULL)
{
  array[i++] = strdup(tok);
  tok = strtok(NULL," ");
}

for(int j=0;j<i;j++)
{
 argv[j] = array[j];
 argv[i] = NULL;
}
if (strcmp(argv[0], "exit") == 0) 
               exit(0);            
else if(strcmp(argv[0],"cd")==0)
{    

if(strcmp(argv[1],"~")==0)
{
  chdir("/home/hp/Documents/OS-Assignment");
}
else
{
chdir(argv[1]);
}
}
/*else if(strcmp(argv[0],"/snap/bin/vlc")==0)
{
  execute_video(argv);
}*/
else
execute(argv);

}



     
int  main()
{
char buff[1024];           
char  *par[64];
char cmp[100]="alias";              
int tag=0;
int unique=0;
char word[162][100] ={"bash","cp","fusermount","loginctl","ntfs-3g","plymouth","sync","unicode_start","brlttycpio","getfacl","lowntfs-3g","ntfs-3g.probe","ps","systemctl","vdir","bunzip2","dash","grep","ls","ntfscat","pwd","systemd","wdctl"
"busybox","date","gunzip","lsblk","ntfscluster","rbash","systemd-ask-password","which","bzcat","dd","gzexe","lsmod","ntfscmp","readlink","systemd-escape","whiptail","bzcmp","df","gzip","mkdir","ntfsfallocate","red","systemd-hwdb","ypdomainname","bzdiff","dir","hciconfig","mknod","ntfsfix","rm","systemd-inhibit","zcat","bzegrep","dmesg","hostname","mktemp","ntfsinfo","rmdir","systemd-machine-id-setup","zcmp,bzexe","dnsdomainname","ip","more","ntfsls","rnano","systemd-notify","zdiff","bzfgrep","domainname","journalctl","mount","ntfsmove","run-parts","systemd-sysusers","zegrep","bzgrep","dumpkeys","kbd_mode","mountpoint","ntfsrecover","sed","systemd-tmpfiles","zfgrep","bzip2","echo","kill","mt","ntfssecaudit","setfacl","systemd-tty-ask-password-agent","zforce","bzip2recover","ed","kmod","mt-gnu","ntfstruncate","setfont","tar","zgrep","bzless","efibootdump","less","mv","ntfsusermap","setupcon","tempfile","zless","bzmore","efibootmgr","lessecho","nano","ntfswipe","sh","touch","zmore","cat","egrep","lessfile","nc","open","sh.distrib","true","znew","chacl","false","lesskey","nc.openbsd","openvt","sleep","udevadm","chgrp","fgconsole","lesspipe","netcat","pidof","ss","ulockmgr_server","chmod","fgrep","ln","netstat","ping","static-sh","umount","chown","findmnt","loadkeys","networkctl","ping4","stty","uname","chvt","fuser","login","nisdomainname","ping6","su","uncompress"};
Trie tuniq;
vector<string> v;
vector<int> p;
v.push_back("\0");
v.push_back("\0");
p.push_back(0);
p.push_back(0);
int count=1;
int temp=1;
int num =1 ;
int temp1=1;

for(int i=0;i<162;i++)
{
tuniq.addWord(word[i]);
}
while (1) 
{         
int deal=0;   
bool t=0;
bool t2=0;
buff[1024]='\0';
char *key_t;       
tag =0;
prompt_function('$');     

int key;
    char buff[1024];
    /* initialize the random number generator */
    srand(time(NULL));
    int i=0;
for (;;) 
{
key = getkey();
        
/*if(key==10)
break;*/

if(key==127 && i>0)
{
cout<<"\b";
buff[--i]=' ';
cout<<(char)buff[i];
cout<<"\b";
continue;
}

else if(key==127 && i==0)
  continue;

if(key==10)
  {
    break;
  }
if(key==9)
{
  int key_p=getkey();
  if(key_p==9)
  {
    buff[i]='\0';
    tuniq.searchAll(buff);
    deal=1;
    break;
  }

}


if(key==62)
    {
      buff[i]=(char)key;
      cout<<(char)buff[i];
      i++;
      int keyz=getkey();
      buff[i]=(char)key;
      cout<<(char)buff[i];
      i++;
      if(keyz==62)
       {  
        tag=2;
        continue;
      }
      else
     { 
      tag=1;
      continue;
    }
    }

if(key==27)
{
int key1 = getkey(); 
int key2 =getkey();
if(key1==91)
{
if(key2==65 && temp==0)
   { 
    
    if(t==1)
    {
     int dest = p[temp1--]; 
    while(dest>0)
    {
    cout<<"\b";
    cout<<" ";
    cout<<"\b";
    dest--; 
    }
    //cout<<'\0';
    t=0;
  }

    continue;
  }

else if(key2==65 && temp>0)
         { 
          t=1;
          int dest=p[temp1--];
        
          while(dest>0)
          {
            cout<<"\b";
            cout<<" ";
            cout<<"\b";
            dest--;
          }
          cout<<v[--temp];
            continue;
        }
if(key2==66 && temp==(count))
      {
      if(t2==1)
    {
     int dest = p[++temp1];
     //cout<<"dest"<<dest; 
    while(dest>0)
    {
    cout<<"\b";
    cout<<" ";
    cout<<"\b";
    dest--; 
    }
    //cout<<'\0';
    t2=0;

  }

      continue;
  }

else if(key2==66 && temp<(count))
{
int dest=p[++temp1];
while(dest>0)
{
cout<<"\b";
cout<<" ";
cout<<"\b";
dest--;
}

t2=1;
cout<<v[++temp];
continue;
 }
}

}
if(key==124)
{
  tag=3;
}


buff[i]=(char)key;
cout<<(char)buff[i];
i++; 
}

if(deal==1)
{
  continue;
}

buff[i]='\0';
//cout<<endl<<buff<<endl;
if(strncmp(buff,"alias",5)==0)
 {
//cout<<endl<<"alias insert mode"<<endl;
char *cpr = new char[strlen(buff)];
char *to = new char[strlen(buff)];
int out = strlen(buff);
strncpy(to,buff+6,out);
strcpy(cpr,buff);
//char *key=strtok(to,"=");
key_t=strtok(to,"=");
char *rev = new char[strlen(cpr)];
int j=0;
for(int i=(strlen(cpr)-1);cpr[i]!='=';i--)
{
  rev[j]=cpr[i];
  j++;
}

rev[j]='\0';


int len=strlen(rev);
char *frev = new char[strlen(rev)];
int t=strlen(rev)-1;
int i;
for(i=0;i<strlen(rev);i++)
{
  frev[i]=rev[t];
t--;
}
frev[i]='\0';

string k,vp;
int ko;
for(ko=0;ko<strlen(key_t);ko++)
{
  k+=key_t[ko];
}

k[ko]='\0';

int ki;
for(ki=0;ki<strlen(frev);ki++)
{
  vp+=frev[ki];
}
vp[ki]='\0';

 insertion(k,vp);
 delete frev;
 delete to;
 delete cpr;
 cout<<endl;
 continue;
}

string keyfin="";
//char buff[100]="l";
int tp;
for(tp=0;tp<strlen(buff);tp++)
{
keyfin+=buff[tp];

}
keyfin[tp]='\0';



if((keyfin.length())>0)
{
v.pop_back();
p.pop_back();
v.push_back(keyfin);
p.push_back(keyfin.length());
v.push_back("\0");
p.push_back(0);

count++;
num++;
temp=count;
temp1=num;
}




if(m.count(keyfin)==1)
{
  int tp=0;
//cout<<"I am in";
string tempo=m[keyfin];
char temp_buff[1000];
int tempy;
for(tempy=0;tempy<tempo.length();tempy++)
{
  temp_buff[tempy]=tempo[tempy];
}
temp_buff[tempy]='\0';
//cout<<"Virat"<<temp_buff;
for(int sea=0;sea<strlen(temp_buff);sea++)
  {   
     if(temp_buff[sea]=='>')
      {
        if(temp_buff[sea+1]=='>')
            {
              tp=2;
            }
        else
          {
            tp=1;
          }
      break;
      }
      tp=0;
      }
    
if(strlen(temp_buff)!=0 && tp==0)
{
  
  read_cmd(temp_buff,par);     


}
else if(strlen(temp_buff)!=0 && tp==1)
{ 
  //cout<<endl;
  //cout<<"execute2";
  readg_cmd(temp_buff,par);
}

else if(strlen(temp_buff)!=0 && tp==2)
{
  //cout<<endl;
  //cout<<"execute3";
  readg2_cmd(temp_buff,par);
}

//cout<<endl;
}

else
{
//cout<<"else part";
if(strlen(buff)!=0 && tag==0 && (strcmp(buff,"history")!=0))
read_cmd(buff,par);     

else if(strlen(buff)!=0 && tag==1)
{ 
  readg_cmd(buff,par);
}

else if(strlen(buff)!=0 && tag==2)
{
  readg2_cmd(buff,par);
}

else if(strlen(buff)!=0 && tag==3)
{
  readg3_cmd(buff,par);
}

else if(strcmp(buff,"history")==0)
{
cout<<endl;
  for(int cy=1;cy<(v.size()-1);cy++)
  {
    cout<<cy<<" "<<v[cy]<<endl;
  }
}



/*else if(strcmp(buff,"record start")==0)
{
  int fp = open("/home/hp/Documents/OS-Assignment",O_RDONLY|O_CREAT|O_WRONLY,0777);
 unique=1;
  while(strcmp(buff,"record stop")!=0)
  {
    cout<<endl<<scripting stops here
    break;
  }

}*/
cout<<endl;
}


}

return 0;

}

