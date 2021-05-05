#include <iostream.h>
#include <conio.h>
#include <ctype.h>
#include <cmath.h>
#include<cstdio.h>
#include<fstream.h>
#include<stdlib.h>
#include<graphics.h>

/***FUNCTIONS***/
void mode();
void adminmenu();
void adminmode();
void home();
void line();




/***REQUIRED CLASS***/
struct question
{
char q[200];
char a[200],b[200],c[200],d[200];
};
struct answer
{
int a,b,c,d;
}ans[10];

class survey
{
public:
question ques[10];
int qno;
char name[200];
void fill();
void create();
void modify();
void display();
void deleteques();
void displayques();
}s;

/***FUNCTION TO DRAW A LINE***/

void line()
{
cout<<endl;
for (int i=0;i<80;i++)
cout<<"_";
cout<<endl;
}


void box()
{
clrscr();
int top, bottom , right, left , i;
top=8;
bottom=21;
right=65;
left=11;
textcolor(4);

for(i=left;i<=right;i++)
{
gotoxy(i,top);
putch(char(205));
gotoxy(i,bottom);
putch(char(205));
}

for(i=top;i<=bottom;i++)
{
gotoxy(left,i);
putch(char(186));
gotoxy(right,i);
putch(char(186));
}

gotoxy(left,top);
putch(char(201));
gotoxy(right,top);
putch(char(187));


gotoxy(left,bottom);
putch(char(200));
gotoxy(right,bottom);
putch(char(188));
gotoxy(1,1);
gotoxy(35,14);

textcolor(2);
cout<<"SURVEY";
gotoxy(33,15);
cout<<"MANAGEMENT";
getch();
clrscr();
}

int error()
{
clrscr();
survey temp;
fstream f;
f.open("Survey.DAT",ios::in);
f.read((char*)&temp,sizeof(temp));
if (temp.qno==0)
{
cout<<"\n\n";
line();
cout<<"\n\t\t\t\t  ERROR\n";
line();
cout<<"\n\n\n\t\t\tNo Questions Exist !\n";
cout<<"\n\n\t\t\tPress any key to go back !";
getch();
f.close();
clrscr();
return 0;
}
else
{
f.close();
clrscr();
return 1;
}
}
/***FUNCTION TO GUIDE THE ADMINISTRATOR***/


void adminmode()
{
clrscr();

textcolor(2);
cout<<"\n\n";
line();
cout<<"\n\t\t\t\t ADMINSTRATOR MODE\n";
line();
cout<<"\n\n";
cout<<"\t\tENTER THE PASSWORD:";
char ch[20];
gets(ch);
if (strcmpi(ch,"access")!=0)
{
cout<<"\n\t Wrong Password!\n\tAccess Denied !!! \n\n\n\t\tABORTING !";
for(int i=0;i<3;i++)
cout<<"\a";
mode();
}
else
cout<<"\n\t\tPassword Accepted !";
cout<<"\n\n\t\tLoading Admin Menu";
for(int i=0;i<1;i++)
cout<<"\a.";
clrscr();
adminmenu();
}
/***FUNCTION TO DISPLAY ADMINS'S MENU***/


void adminmenu()
{
int choice;
restart:
clrscr();

textcolor(2);
line();
cout<<"\n\t\t\t ADMINISTRATOR MAIN MENU"<<endl;
line();
cout<<"\t 1.CREATE SURVEY"<<endl;
cout<<"\t 2.MODIFY SURVEY"<<endl;
cout<<"\t 3.DISPLAY RESULTS"<<endl;
cout<<"\t 4.DELETE QUESTION"<<endl;
cout<<"\t 5.DISPLAY QUESTIONS"<<endl;
cout<<"\t 6.BACK TO MAIN MENU"<<endl;
retry:cout<<"\n\n\n\t\tENTER YOUR CHOICE:";
cin>>choice;
switch(choice)
{
case 1://CREATE
fstream f1;
f1.open("Survey.DAT",ios::out||ios::binary);
remove("Answer.DAT");
for(int k=0;k<s.qno;k++)
{
ans[k].a=0;
ans[k].b=0;
ans[k].c=0;
ans[k].d=0;
}
s.create();
f1.write((char*)&s,sizeof(s));
f1.close();
goto restart;
break;
case 2://MODIFY
int x=error();
if(x!=0)
{
fstream f4,f9;
f4.open("Survey.DAT",ios::in||ios::out||ios::binary);
f9.open("Answer.DAT",ios::in||ios::out||ios::binary);
f4.seekg(0,ios::beg);
f9.seekg(0,ios::beg);
f4.read((char*)&s,sizeof(s));
f9.read((char*)&ans,sizeof(ans));
s.modify();
f4.seekg(0,ios::beg);
f4.write((char*)&s,sizeof(s));
clrscr();
cout<<"\n\n\n";
line();
cout<<"\n\t\tQuestion has been successfully modified.\n\n";
line();

cout<<"\n\n\n\n\t\t\tPress any key to continue.";
getch();
f4.close();
getch();
}

goto restart;

break;

case 3://DISPLAY
int y=error();
if(y!=0)
{
fstream f3,f2;

f3.open("Survey.DAT",ios::in||ios::binary);
f2.open("Answer.DAT",ios::in||ios::binary);
f3.seekg(0,ios::beg);
f2.seekg(0,ios::beg);

f3.read((char*)&s,sizeof(s));
f2.read((char*)&ans,sizeof(ans));
s.display();
f3.close();
f2.close();
}
goto restart;
break;
case 4://DELETE QUESTION
int z=error();
if(z!=0)
{
fstream f5,f6;
f5.open("Survey.DAT",ios::in||ios::out||ios::binary);
f6.open("Answer.DAT",ios::in||ios::out||ios::binary);
f5.seekg(0,ios::beg);
f6.seekg(0,ios::beg);
f5.read((char*)&s,sizeof(s));
f6.read((char*)&ans,sizeof(ans));
s.deleteques();
f5.seekp(0,ios::beg);
f6.seekp(0,ios::beg);
f5.write((char*)&s,sizeof(s));
f6.write((char*)&ans,sizeof(ans));
}
clrscr();

cout<<"\n\n\n";
line();
cout<<"\n\t\tQuestion has been successfully deleted.\n\n";
line();
cout<<"\n\n\n\t\t\tPress any key to continue.";
getch();
goto restart;

break;

case 5://DISPLAY QUESTIONs
int p=error();
if(p!=0)
{
fstream f7;
f7.open("Survey.DAT",ios::in||ios::binary);
f7.seekg(0,ios::beg);
f7.read((char*)&s,sizeof(s));
s.displayques();
}
goto restart;
break;
case 6:
mode();
break;
default:
cout<<"\n\nInvalid Choice. Please try again !";
goto retry;

}
}
/*FUNCTION TO SELECT ADMIN/USER MODE
 */
void mode()
{
restart:
clrscr();
line();
char modech;

cout<<"\n\t\t\t SELECT THE OPERATOR MODE"<<endl;
line();
cout<<"\n\t\t\t1.USER MODE - To fill survey form"<<endl;
cout<<"\n\t\t\t2.ADMIN MODE - To manage survey"<<endl;

cout<<"\n\t\t\t3.EXIT"<<endl;
cout<<"\n\n\n\t\tENTER YOUR CHOICE:";
cin>>modech;
if(modech=='1')
{
int a;
a=error();
if(a!=0)
{
fstream f1,f2;
f1.open("Survey.DAT",ios::out||ios::in||ios::binary);
f1.seekg(0);
f1.read((char*)&s,sizeof(s));
f2.open("Answer.DAT",ios::out||ios::in||ios::binary);
f2.seekg(0,ios::beg);
f2.read((char*)&ans,sizeof(ans));
s.fill();
f2.seekp(0,ios::beg);
f2.write((char*)&ans,sizeof(ans));
f1.close();
f2.close();
}
goto restart;
}
else

if(modech=='2')
adminmode();
else if (modech=='3')
exit(0);
else
cout<<"INVALID CHOICE"<<endl;
}




void survey::create()
{
clrscr();
line();
cout<<"\n\t\t\t\tNEW SURVEY\n";
line();
cout<<"Enter the name of the survey :";
gets(name);
cout<<"\n\tHow many questions do you wish to include in the survey ?\n\n\t\t";
cin>>qno;
for(int i=0;i<qno;i++)
{
clrscr();
line();
cout<<"\n\n\t\t\t\t"<<name<<"\n\n";
line();
cout<<"\n\n";
cout<<"\t\tEnter question number "<<i+1<<endl;
gets(ques[i].q);
cout<<"\tEnter Option A : ";
gets(ques[i].a);
cout<<"\tEnter Option B : ";
gets(ques[i].b);
cout<<"\tEnter Option C : ";
gets(ques[i].c);
cout<<"\tEnter Option D : ";
gets(ques[i].d);
cout<<"\n\n";
line();
}
}








void survey::fill()
{
clrscr();
char x;
restart:
for(int i=0;i<qno;i++)
{
clrscr();
cout<<"\n\n\n";
line();
cout<<"\t\t\t\t"<<name;
line();
cout<<"\n\n\tQ: "<<i+1<<"."<<ques[i].q;
cout<<"\n\tOption A: "<<ques[i].a;
cout<<"\n\tOption B: "<<ques[i].b;
cout<<"\n\tOption C: "<<ques[i].c;
cout<<"\n\tOption D: "<<ques[i].d;
retry:cout<<"\n\n\tEnter your choice (A/B/C/D): ";
cin>>x;
switch(x)
{
 case '1':
 case 'a':
 case 'A':++ans[i].a;
 break;

 case '2':
 case 'b':
 case 'B':++ans[i].b;
 break;

 case '3':
 case 'c':
 case 'C':++ans[i].c;
 break;

 case '4':
 case 'd':
 case 'D':++ans[i].d;
 break;

 default:cout<<"\n\nInvalid Choice. Please try again\n";
 goto retry;
}
}
reenter:
cout<<"\n\n\t'1':Submit survey form\n\t'2':Restart\n";
cout<<"\t\tEnter your choice(1/2):";
char ch;
cin>>ch;
switch(ch)
{
case '1':
clrscr();
cout<<"\n\n\n\n\n\n\t\t";
cout<<"Thank you for filling the survey form.\n";
cout<<"\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\tEnter any key to continue.";
getch();
break;
case '2':
goto restart;
default:
cout<<"Invalid Choice.Please enter again.";
goto reenter;
}
}







void survey::display()

{
int j;
char ch;
clrscr();
for(int i=0;i<qno;i++)
{
clrscr();
line();
cout<<"\t\t\t\tRESULTS\n:";
line();
cout<<"Q:"<<i+1<<" ";
cout<<ques[i].q<<endl;
cout<<"A:"<<ques[i].a<<endl;
cout<<"B:"<<ques[i].b<<endl;
cout<<"C:"<<ques[i].c<<endl;
cout<<"D:"<<ques[i].d<<endl;
line();
cout<<"\nOption A:"<<ans[i].a<<" | ";
for(j=0;j<ans[i].a;j++)
cout<<"*";
cout<<" |";
cout<<"\nOption B:"<<ans[i].b<<" | ";
for(j=0;j<ans[i].b;j++)
cout<<"*";
cout<<" |";
cout<<"\nOption C:"<<ans[i].c<<" | ";
for(j=0;j<ans[i].c;j++)
cout<<"*";
cout<<" |";
cout<<"\nOption D:"<<ans[i].d<<" | ";
for(j=0;j<ans[i].d;j++)
cout<<"*";
cout<<" |";
cout<<endl;
cout<<"\n\n\t\t\t\tPress any key to continue...";
getch();
}
adminmenu();
}


void survey::modify()
{
clrscr();
int i;
char x;
restart:
cout<<"\n\n\t\tDo you wish to view the questions ?(y/n):";
cin>>x;
switch(x)
{
case 'y':
case 'Y':
clrscr();
displayques();
break;
case 'n':
case 'N':
break;
default:
clrscr();
cout<<"\n\n\n\t\t\t\t\tInvalid Option.Please enter again.";
goto restart;
}

retry:
clrscr();
line();
cout<<"\n\nEnter the question number you want to modify:";
cin>>i;
line();
if(i>qno)
{
cout<<"\n\n\nQuestion does not exist.\n";
getch();
goto retry;
}
else
{

clrscr();
line();
cout<<"\n\n\nThe Question is :\t";
line();
cout<<ques[i-1].q;
cout<<"\n\n\tEnter the new question:";
gets(ques[i-1].q);
cout<<"\nEnter Option A:";
gets(ques[i-1].a);
cout<<"\nEnter Option B:";
gets(ques[i-1].b);
cout<<"\nEnter Option C:";
gets(ques[i-1].c);
cout<<"\nEnter Option D:";
gets(ques[i-1].d);
cout<<"\n\n";
ans[i-1].a=0;
ans[i-1].b=0;
ans[i-1].c=0;
ans[i-1].d=0;
}
}


void survey::deleteques()
{
int i,flag;
char x;
restart:
clrscr();
line();
cout<<"\n\n\t\tDo you wish to view the questions ?(y/n):";
cin>>x;
line();
switch(x)
{
case 'y':
case 'Y':
clrscr();
displayques();
break;
case 'n':
case 'N':
break;
default:
clrscr();
cout<<"\n\n\n\t\t\t\t\tInvalid Option.Please enter again.";
goto restart;
}

retry:
cout<<"\n\n\nWhich question do you want to delete:";
cin>>i;
if (i>qno)
{
clrscr();
cout<<"Question does not exist.\n";
getch();
goto retry;
}
else
{
for(int j=i=1;j<qno-1;j++)
{
strcpy(ques[j].q,ques[j+1].q);
strcpy(ques[j].a,ques[j+1].a);
strcpy(ques[j].b,ques[j+1].b);
strcpy(ques[j].c,ques[j+1].c);
strcpy(ques[j].d,ques[j+1].d);
ans[j].a=ans[j+1].a;
ans[j].b=ans[j+1].b;
ans[j].c=ans[j+1].c;
ans[j].d=ans[j+1].d;
}
qno=qno-1;
}
}

void survey::displayques()
{
clrscr();
char x;
line();
cout<<"\t\t\t\tQUESTIONS\n";
line();
cout<<"\n";
for(int a=0;a<qno;a++)
{
cout<<"\t"<<a+1<<"."<<ques[a].q<<"\n";
}
cout<<"\n\n\t\t\t\t\t\tPress any key to continue...\n";
getch();
}

/******
MAIN PROGRAM
***/

void main ()
{
clrscr ();
box();
mode();
getch();
}

