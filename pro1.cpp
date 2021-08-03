#include <iostream>
#include <string>
#include <fstream>
using namespace std;
	fstream pr("prim-index.txt",ios::in|ios::out|ios::binary);
	fstream se ("scnd-indx.txt",ios::in|ios::out|ios::binary);
	fstream emp ("Employees.txt",ios::in|ios::out|ios::binary);
	static int i=0,j=0;
struct primary
{
	char Serial[5];
	short offset;
};
struct secondry
{
	char Department[10], Serial[5];
};
struct employee
{
	char Serial[5],firstName[10],lastName[10],Department[10];
	short age;
	float Salary;
	
}; 
primary p[100]={0};
secondry s[100]={0};
void mainWindow()
{
	cout<<endl<<" \t \t Employee Management System "<<endl<<endl;
	cout<<" 1)  Add New Employee"<<endl;
	cout<<" 2)  Update an Employee"<<endl;
	cout<<" 3)  Delete an Employee"<<endl;
	cout<<" 4)  Display all Employees"<<endl;
	cout<<" 5)  Display all Employees in specific Department"<<endl;
	cout<<" 6)  Search Employee by Serial"<<endl;
	cout<<" 7)  Compress File"<<endl;
	cout<<" 8)  Exit"<<endl;	
	pr.seekg(0,ios::beg);
	se.seekg(0,ios::beg);
	while (!pr.eof())
	{
		if(pr.eof())
			break;
		else
		{
		pr.read(p[i].Serial,5);
		pr.read((char*)&p[i].offset,sizeof(short));
				i++;
		}

		
	}
	while (1)
	{
		if(se.eof())
			break;
		else
		{
			se.read(s[j].Department,10);
			se.read(s[j].Serial,5);
		j++;
		}
	}
	
}
void addNew()
	{
		
		employee e2;
		l:
	cout<<"Enter your serial : ";
	cin>>e2.Serial;
	//check serial
	for(int d=0;d<i;d++)
	{
		if(strcmp(e2.Serial,p[d].Serial) == 0)
		{cout<<"This Serial is already exist!! please enter other one "<<endl; goto l; break;}
	}
	cout<<"Enter your first name : ";
	cin>>e2.firstName;
	cout<<"Enter your last name : ";
	cin>>e2.lastName;
	cout<<"Enter your age : ";
	cin>>e2.age;
	cout<<"Enter your Department : ";
	cin>>e2.Department;
	cout<<"Enter your Salary : ";
	cin>>e2.Salary;

		short len,reLen,ndelete=0,l,off;

	len=(2+(2*6)+strlen(e2.Serial)+strlen(e2.firstName)+strlen(e2.lastName)+2+strlen(e2.Department)+4);
	
	short header=-1;	
	
	emp.seekg(0,ios::end);
	int size_of_fie=emp.tellg();
	if(size_of_fie==0)
		emp.write((char *)&header,2);
	emp.seekg(0,ios::beg);


	emp.read((char*)&header,sizeof(short));
	off=header;
	la2:
	if(header == -1 || ndelete == -1)
	{
		emp.seekg(0,ios::end);
		emp.write((char*)&len,sizeof(short));
		l=strlen(e2.Serial);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.Serial,l);
		l=strlen(e2.firstName);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.firstName,l);
		l=strlen(e2.lastName);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.lastName,l);
		l=2;
		emp.write((char*)&l,sizeof(short));
		emp.write((char*)&e2.age,l);
		l=strlen(e2.Department);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.Department,l);
		l=sizeof(float);
		emp.write((char*)&l,sizeof(short));
		emp.write((char*)&e2.Salary,l);
		p[i].offset=(emp.get()-len);strcpy(p[i].Serial,e2.Serial);
		strcpy(s[j].Department,e2.Department);strcpy(s[j].Serial,e2.Serial);
	}
	else
	{
	emp.seekg(header,ios::beg);
	la:
	emp.read((char*)&reLen,sizeof(short));
	if(len <= reLen)
	{
		emp.seekg(1,ios::cur);
		emp.read((char*)&ndelete,sizeof(short));
		emp.seekg(-5,ios::cur);
		emp.write((char*)&len,sizeof(short));
		l=strlen(e2.Serial);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.Serial,l);
		l=strlen(e2.firstName);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.firstName,l);
		l=strlen(e2.lastName);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.lastName,l);
		l=2;
		emp.write((char*)&l,sizeof(short));
		emp.write((char*)&e2.age,l);
		l=strlen(e2.Department);
		emp.write((char*)&l,sizeof(short));
		emp.write(e2.Department,l);
		l=sizeof(float);
		emp.write((char*)&l,sizeof(short));
		emp.write((char*)&e2.Salary,l);
		p[i].offset=off;strcpy(p[i].Serial,e2.Serial);
		strcpy(s[j].Department,e2.Department);strcpy(s[j].Serial,e2.Serial);
		if((reLen-len)<=54)
		{
			for(int r=0;r<(reLen-len);r++);
			emp.put(' ');
			header=ndelete;
			emp.seekg(0,ios::beg);
			emp.write((char*)&header,sizeof(short));

		}
		else
		{
			emp.write((char*)&len,sizeof(short));
			emp.put('*');
			emp.write((char*)&ndelete,sizeof(short));
			header=off+len;
			emp.write((char*)&header,sizeof(short));
		}
	}
	else
	{
	emp.seekg(1,ios::cur);
	emp.read((char*)&ndelete,sizeof(short));
	if(ndelete== -1 )
		goto la2;
	else
		{
	emp.seekg(ndelete,ios::beg);
	goto la;
		}
	}
	}
	}
void update()
{
	employee e3;
	char uSerial[5];
	cout<<"Enter employee Serial who you want to update : ";
	cin>>uSerial;
	for(int q=0;q<i;q++)
	{
		if(strcmp(uSerial,p[q].Serial) == 0)
		{
		cout<<"Enter your first name : ";
		cin>>e3.firstName;
		cout<<"Enter your last name : ";
		cin>>e3.lastName;
		cout<<"Enter your age : ";
		cin>>e3.age;
		cout<<"Enter your Department : ";
		cin>>e3.Department;
		cout<<"Enter your Salary : ";
		cin>>e3.Salary;

			short len,rL,l;
		len=(2+(2*6)+strlen(e3.Serial)+strlen(e3.firstName)+strlen(e3.lastName)+2+strlen(e3.Department)+4);
		emp.seekg(p[q].offset,ios::beg);
		emp.read((char*)&rL,sizeof(short));
		if(len <= rL)
			{
				emp.seekg(-2,ios::cur);
				emp.write((char*)&len,sizeof(short));
				l=strlen(uSerial);
				emp.write((char*)&l,sizeof(short));
				emp.write(uSerial,l);
				l=strlen(e3.firstName);
				emp.write((char*)&l,sizeof(short));
				emp.write(e3.firstName,l);
				l=strlen(e3.lastName);
				emp.write((char*)&l,sizeof(short));
				emp.write(e3.lastName,l);
				l=2;
				emp.write((char*)&l,sizeof(short));
				emp.write((char*)&e3.age,l);
				l=strlen(e3.Department);
				emp.write((char*)&l,sizeof(short));
				emp.write(e3.Department,l);
				l=sizeof(float);
				emp.write((char*)&l,sizeof(short));
				emp.write((char*)&e3.Salary,l);
			
		}
		else
			cout<<"Erorr!! Cann't fit "<<endl;
		break;
		}
	}

}
void deleteEmp()
{
	char uSer[5];
	cout<<"Enter employee Serial who you want to update : ";
	cin>>uSer;
	short of,k=i;
	primary temp;
	for(int h=0;h<i;h++)
	{
		if(strcmp(uSer,p[h].Serial) == 0)
		{
			emp.seekg(0,ios::beg);
			emp.read((char*)&of,sizeof(short));
			emp.seekg(p[h].offset,ios::beg);
			emp .seekg(2,ios::cur);
			emp.put('*');
			emp.write((char*)&of,sizeof(short));
			emp.seekg(0,ios::beg);
			emp.write((char*)&p[h].offset,sizeof(short));
			while(k>h)
			{
			temp=p[k];
			p[k]=p[k+1];
			p[k-1]=temp;
			k--;
			}
		break;
		}
			else
			{cout<<"This Serial did'n found"<<endl;}
	}
	--i;
}
void displayAll()
	{
			employee e1;
				short c=0,re,f;
				cout<<endl<<"Serial \t First Name \t Last Name \t Age \t Department \t Salary"<<endl;
		for(int c=0;c<i-1;c++)
		{
			
			
			emp.seekg(p[c].offset,ios::beg);
			emp.read((char*)&re,sizeof(short));
			emp.read((char*)&f,sizeof(short));
			emp.read(e1.Serial,f);
			e1.Serial[f]='\0';
			emp.read((char*)&f,sizeof(short));
			emp.read(e1.firstName,f);
			e1.firstName[f]='\0';
			emp.read((char*)&f,sizeof(short));
			emp.read(e1.lastName,f);
			e1.lastName[f]='\0';
			emp.read((char*)&f,sizeof(short));
			emp.read((char*)&e1.age,f);
			emp.read((char*)&f,sizeof(short));
			emp.read(e1.Department,f);
			e1.Department[f]='\0';
			emp.read((char*)&f,sizeof(short));
			emp.read((char*)&e1.Salary,f);
		
			cout<<' '<<e1.Serial<<" \t   "<<e1.firstName<<" \t   "<<e1.lastName<<" \t "<<e1.age<<" \t    "<<e1.Department<<" \t \t "<<e1.Salary<<endl;	
			

		}
	}
void displayInSpecificD()
{
	char de[10];
	short l,c=0;
	employee e;
	cout<<"Enter Department to Display : ";
	cin>>de;
	cout<<endl<<"Serial \t First Name \t Last Name \t Age \t Department \t Salary"<<endl;
	for(int m=0;m<j;m++)
	{
		if(strcmp(de,s[m].Department) == 0)
		{
			for(int n=0;n<i;n++)
			{
				if(strcmp(s[m].Serial,p[n].Serial)==0)
				{
					emp.seekg(p[n].offset,ios::beg);
					emp.seekg(2,ios::cur);
					emp.read((char*)&l,sizeof(short));
					emp.read(e.Serial,l);
					e.Serial[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read(e.firstName,l);
					e.firstName[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read(e.lastName,l);
					e.lastName[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read((char*)&e.age,l);
					emp.read((char*)&l,sizeof(short));
					emp.read(e.Department,l);
					e.Department[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read((char*)&e.Salary,l);
		
				cout<<' '<<e.Serial<<" \t   "<<e.firstName<<" \t   "<<e.lastName<<" \t "<<e.age<<" \t    "<<e.Department<<" \t \t "<<e.Salary<<endl;
				c++;
				}	
			}
		}
	}
	if(c==0)
		cout<<"Department not found !"<<endl;
}
void search()
{
	employee e;
	char ser[5];
	short l,c=0;
	cout<<"Enter Serial: ";
	cin>>ser;
	for(int y=0;y<i;y++)
	{
		if(strcmp(ser,p[y].Serial)==0)
		{
			emp.seekg(p[y].offset,ios::beg);
			emp.seekg(2,ios::cur);
			emp.read((char*)&l,sizeof(short));
					emp.read(e.Serial,l);
					e.Serial[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read(e.firstName,l);
					e.firstName[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read(e.lastName,l);
					e.lastName[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read((char*)&e.age,l);
					emp.read((char*)&l,sizeof(short));
					emp.read(e.Department,l);
					e.Department[l]='\0';
					emp.read((char*)&l,sizeof(short));
					emp.read((char*)&e.Salary,l);
		
				cout<<' '<<e.Serial<<" \t   "<<e.firstName<<" \t   "<<e.lastName<<" \t "<<e.age<<" \t    "<<e.Department<<" \t \t "<<e.Salary<<endl;
				c++;
		}
	}
	if(c==0)
		cout<<"Not Found!!"<<endl;
}
void compress()
{
	short head=-1;
	fstream temp("temp.txt",ios::in|ios::out|ios::binary);
	employee e2;
	temp.write((char*)&head,sizeof(short));
	for(int o=0;o<i-1;o++)
	{
		emp.seekg(p[o].offset,ios::beg);
		short reLen,l;
		emp.read((char*)&reLen,sizeof(short));
		temp.write((char*)&reLen,sizeof(short));
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read(e2.Serial,l);
		e2.Serial[l]='\0';
		temp.write(e2.Serial,l);
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read(e2.firstName,l);
		e2.firstName[l]='\0';
		temp.write(e2.firstName,l);
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read(e2.lastName,l);
		e2.lastName[l]='\0';
		temp.write(e2.lastName,l);
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read((char*)&e2.age,l);
		temp.write((char*)&e2.age,l);
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read(e2.Department,l);
		e2.Department[l]='\0';
		temp.write(e2.Department,l);
		emp.read((char*)&l,sizeof(short));
		temp.write((char*)&l,sizeof(short));
		emp.read((char *)&e2.Salary,l);
		temp.write((char *)&e2.Salary,l);
	}
}
void Exit(fstream&pr)
{
//	pr.open("prim-index.txt",ios::out);
	if(pr.fail())
		cout<<"error";
	pr.seekg(0,ios::beg);
	cout<<p[i].Serial<<endl;
	cout<<p[i].offset<<endl;
	pr.write(p[i].Serial,5);
	pr.write((char*)&p[i].offset,sizeof(short));
	pr.close();
	se.seekg(0,ios::end);
	se.write(s[j].Department,10);
	se.write(s[j].Serial,5);
}
int main()
{	
	/*int x=-1;
	emp.seekg(0,ios::beg);
	emp.write((char*)&x,2);*/
	fstream pr("prim-index.txt",ios::in|ios::out|ios::binary);
		int choose;
	mainWindow();
	cin>>choose;
	if(choose==1)
	
		addNew();
	else if(choose==2)
			update();
	else if(choose ==3)
		deleteEmp();
	else if(choose ==4)
		displayAll();
	else if(choose ==5)
		displayInSpecificD();
	else if(choose ==6)
		search();
		else if(choose==7)
		{compress();}
	else if(choose==8)
		{return 0;}
	Exit(pr);
}