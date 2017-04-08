#include<fstream>
#include<cstdio>
#include<iostream>
#include<cstring>
#include<iomanip>
#include<windows.h>
#include<string>
#include<time.h>
using namespace std;
class entry
{
protected:
	char Un[10];
	char dest[50];
	char pcode[20];
	int wt;
	int days;
	char type;
public:
    char ch;
    char date[20];
	void create_entry()
	{
	    cout<<"\n================================================================================================================================================================\n";
		cout<<"\n\t\t\tEntry Details...\n";
		cout<<"\n================================================================================================================================================================\n";
		cout<<"\nEnter the date: ";fflush(stdin);
		gets(date);
		cout<<"\n\nEnter Pin Code: ";
		gets(pcode);
		cout<<"\n\nEnter Unique Number: ";
		gets(Un);
		cout<<"\n\nEnter Destination: ";
		gets(dest);
		cout<<"\n\nEnter Weight: ";
		cin>>wt;
		cout<<"\nEnter type\n  N for Normal and O for Other\t";
		cin>>type;
		if(type=='O' ||type =='o')
        {
            cout<<"Enter number of days\n";
            cin>>days;
        }
		ch='S';
		cout<<"\n\n\n\t\t\tEntry Completed..\n";
	}
	virtual void show_entry()=0;//pure virtual function
	virtual void modify_entry()=0;//pure virtual function
	char* retcn()
	{
		return Un;
	}
	char* retdate()
	{
	    return date;
	}
};
//class deliver
class deliver: public entry
{
public:
    float fncalc(float,char);
    void show_entry()
	{
		//cout<<"\nEnter Unique Number : ";
		//gets(Un);
		cout<<"\nDate : ";
		puts(date);
		cout<<"\nPin Code : ";
		puts(pcode);
		cout<<"\nDestination : ";
		puts(dest);
		cout<<"\nWeight : "<<wt;
		cout<<"\n\nStatus : ";
		if(ch=='S')
        {
            cout<<"STARTED";
        }
        if(ch=='T')
        {
            cout<<"PACKED";
        }
        if(ch=='U')
        {
            cout<<"ON THE WAY";
        }
        if(ch=='V')
        {
            cout<<"DELIVERED";
        }
		cout<<"\n\nType : \t";
		if(type=='N'||type=='n')
		{
		    cout<<"Normal\n";
		}
		else
        {
            cout<<"Others\n";
        }
        cout<<endl;
		system("pause");

	}
	void modify_entry()
	{
		cout<<"\nEnter Unique Number : \t ";fflush(stdin);
		gets(Un);
		cout<<"\nModify Pin Code : \t";
		gets(pcode);
		cout<<"\nModify Destination : \t";
		gets(dest);
		cout<<"\nModify Date : \t";
		gets(date);
		cout<<"\nModify Weight : \t";
		cin>>wt;
		cout<<"\nEnter the type \t";
		cin>>type;
	}

	char* fncheckd()
    {

        if(ch=='s' || ch=='S')
        {
            return("Started");
        }
        if(ch=='t' || ch=='T')
        {
            return("Packed");
        }
        if(ch=='u' || ch=='U')
        {
            return("On the way");
        }
        if(ch=='v' || ch=='V')
        {
            return("Delivered");
        }
    }

void report()
	{
	    cout<<setw(5)<<Un<<setw(18)<<date<<setw(11)<<pcode<<setw(12)<<dest<<setw(12)<<wt<<setw(12)<<fncheckd()<<setw(8)<<type<<endl;
    }

};

fstream fp,fp1;
deliver dt;// global object
void updatest()
    {
        int i,flag=0;
        char date2[10];
        char cid[10];
        cout<<"Enter today's date\n";
        for(i=0;i<10;i++)
        {
            cin>>date2[i];
        }
        date2[i]='\0';//make it as a string
        fstream fp2;
        fp2.open("entry",ios::in|ios::out);
        int pos=-1*sizeof(dt);
        //i=fp2.tellg();
        fp2.seekg(pos,ios::end);//to go back to last entered date
        fp2.read((char*) &dt,sizeof(deliver));//read it
        if(strcmpi(dt.retdate(),date2)==0)//comparing last enter date and today's date
        {
           cout<<"Every thing is Updated \n";
           system("pause");
        }
        else
        {
             //cout<<dt.retdate();
             cout<<"Enter the Unique id To update\t";
             cin>>cid;
             cout<<"================================================================================================================================================================\n";
             cout<<"\nUnique No."<<setw(10)<<"Date"<<setw(15)<<"Pin Code"<<setw(15)<<"Destination"<<setw(10)<<"Weight"<<setw(10)<<"status"<<setw(8)<<"type"<<"\n";
             cout<<"================================================================================================================================================================\n";
              try
              {
                  fp2.seekg(0,ios::beg);
                  while(fp2.read((char*) &dt,sizeof(deliver)))
                {
                    if(strcmpi(dt.retcn(),cid)==0)
                    {
                       if((int(dt.date[1]-date2[1])<-3) ||(int(dt.date[1]-date2[1])>-1))
                      {
                          throw -1;
                      }
                      if(int(dt.date[1])-date2[1]==-1)
                      {
                          dt.ch='T';
                      }
                      if(int(dt.date[1]-date2[1])==-2)
                      {
                         dt.ch='U';
                      }
                      if(int(dt.date[1]-date2[1])==-3)
                      {
                         dt.ch='V';
                      }

                      int pos=-1*sizeof(dt);
                      fp2.seekg(pos,ios::cur);//repositioning the cursor
                      fp2.write((char*) &dt,sizeof(deliver));//write it
                      dt.report();
                      flag=1;
                    }
                }
                if(flag==0)
                {
                    cout<<"Please Enter a valid Unique id\n";
                }//print it
            }
            catch(int i)
            {
               cout<<"\n\n"<<setw(90)<<"THE STATUS CAN'T BE UPDATED AFTER THREE DAYS\n";
            }
           system("pause");

        //fp5.open("Deliver",ios::in|ios::out);
      fp2.close();
    }
}
void write_entry()
{
	char ch;
	fp.open("entry",ios::out|ios::app);
	do
	{
        dt.create_entry();
		fp.write((char*)&dt,sizeof(entry));
		cout<<"\n\nDo you want to add more record..(y/n?)\t";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
	fp.close();
	system("pause");
}
void display_spb(char n[])
{
    cout<<"\n=====================================================================================================================================================\n";
	cout<<setw(80)<<"\tENTRY DETAILS\n";
	cout<<"\n=====================================================================================================================================================\n";
	int flag=0;
	fp.open("entry",ios::in);
	while(fp.read((char*)&dt,sizeof(entry)))
	{
		if(strcmpi(dt.retcn(),n)==0)//compare unique id
		{
			dt.show_entry();
			flag=1;
		}
	}

	fp.close();
	if(flag==0)
		cout<<"\n\nEntry does not exist\n";
		cout<<endl;
    //system("pause");
}

void modify_entry()
{
	char n[10];
	int found=0;
	cout<<"===========================================================================================================================================================\n";
	cout<<"\n\n"<<setw(80)<<"\t\tMODIFY Entry REOCORD\n ";
	cout<<"===========================================================================================================================================================\n";
	cout<<"\n\n\tEnter The Unique no. of The entry : ";
	cin>>n;
	fp.open("entry",ios::in|ios::out);
	while(fp.read((char*)&dt,sizeof(entry)) && found==0)
	{
		if(strcmpi(dt.retcn(),n)==0)
		{
			dt.show_entry();
			cout<<"\n\n\n";
            cout<<setw(80)<<"\tEnter The New Details of Unique no\n"<<endl;
			dt.modify_entry();
			int pos=-1*sizeof(dt);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&dt,sizeof(entry));
			cout<<"\n\n\t Record Updated\n";
			found=1;
		}
	}

	fp.close();
	if(found==0)
		cout<<"\n\n Record Not Found \n";
		system("pause");
}
void delete_entry()
{
	char n[10];
	cout<<"===========================================================================================================================================================\n";
	cout<<"\n\n\n"<<setw(80)<<"\t\tDELETE Entry ";
	cout<<"===========================================================================================================================================================\n";
	cout<<"\n\nEnter The Unique no. of the Entry You Want To Delete : ";
	cin>>n;
	fp.open("entry",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&dt,sizeof(entry)))
	{
		if(strcmpi(dt.retcn(),n)!=0)
		{
			fp2.write((char*)&dt,sizeof(entry));
		}
	}

	fp2.close();
	fp.close();
	remove("entry");
	rename("Temp","entry");
	cout<<"\n\n\tRecord Deleted ..";
}
void display_allb()
{
	fp.open("entry",ios::in);
	if(!fp)
	{
		cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
		return;
	}

	cout<<"\n\n"<<setw(80)<<"\t\tEntry LIST\n\n";
	cout<<"==================================================================================================================================================================\n";
	cout<<"\nUnique No."<<setw(10)<<"Date"<<setw(15)<<"Pin Code"<<setw(15)<<"Destination"<<setw(10)<<"Weight"<<setw(10)<<"status"<<setw(8)<<"type"<<"\n";
	cout<<"==================================================================================================================================================================\n";

	while(fp.read((char*)&dt,sizeof(entry)))
	{
		dt.report();//reading a line of data from file and printing
	}
	fp.close();
	system("pause");

}
float deliver::fncalc(float weight,char type)
{
    float price=0.0;
    int day,base_price=50;
    if(type=='N' || type=='n')
    {
      price=weight*base_price;//for general charges on weight
      price+=price/day;//for general charges on day
    }
    else if(type=='O'||type=='o')
    {
        cout<<"\nENTER NUMBER OF DAYS FOR DELIVERY \t Give 1 or 2\n";fflush(stdin);
        cin>>day;//regular charges
        price=(weight*base_price)+(price/day);//regular charges
        price+=price*0.10;//for fast delivery
    }
    return price;
}

void intro()
{
cout<<"\n========================================================================================================================================================================\n";
cout<<setw(100)<<"Welcome To AU Courier Service \n";
cout<<"\n========================================================================================================================================================================\n";
}
void admin_menu()
{
    system("cls");
	int ch2;
	cout<<"\n========================================================================================================================================================================\n";
	cout<<setw(90)<<"ADMINISTRATOR MENU\n";
	cout<<"\n========================================================================================================================================================================";
	cout<<"\n";
	cout<<setw(80)<<"1.ENTER DATA\n\n\n";
	cout<<setw(89)<<"2.DISPLAY ALL Entries\n\n\n";
	cout<<setw(92)<<"3.DISPLAY SPECIFIC Entry\n\n\n";
	cout<<setw(82)<<"4.MODIFY Entry\n\n\n";
	cout<<setw(82)<<"5.DELETE Entry\n\n\n";
	cout<<setw(83)<<"6.UPDATE STATUS\n\n\n";
	cout<<setw(87)<<"7.BACK TO MAIN MENU\n\n\n";
	cout<<setw(80)<<"Please Enter Your Choice (1-7)\n\n\n";
	cin>>setw(80)>>ch2;
	switch(ch2)
	{
        case 1: system("cls");
                write_entry();
                break;
		case 2: system("cls");
		        display_allb();
                break;
		case 3:{
                system("cls");
                char num[6];
                cout<<"\n\n\tPlease Enter The Unique Number ";
                cin>>num;
                display_spb(num);
                break;
                }
		case 4: system("cls");
		        modify_entry();
                break;
		case 5: system("cls");
		        delete_entry();
                break;
        case 6:system("cls");
               updatest();
        case 7://system("cls");
               return;

		default:cout<<"\a";
	}
	admin_menu();
}
istream &getpass(istream &stream)
{
   cout<<"\a";
   cout<<"Enter the password \n";
   return stream;
}
int main()
{
	char ch;
	//intro();
	while(1)
	{
	    system("cls");
	    intro();
	    cout <<setw(95)<< __TIMESTAMP__ << endl;//to print date and time

		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t1. ADMINISTRATOR MENU";
		cout<<"\n\n\t2. KNOW YOUR STATUS";
		cout<<"\n\n\t3. PRICE ESTIMATON";
		cout<<"\n\n\t4. CONTACT US ";
		cout<<"\n\n\t5. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-4) ";
		ch=getchar();
		switch(ch)
		{
			case '1':{
                      system("cls");
                      cout<<"\n====================================================================================================================================================================\n";
                      cout<<"\t\t\tSecurity Check\n";
                      cout<<"\n======================================================================================================================================================================\n";
                      string pw;
                      do{
                        cin>>getpass>>pw;
                      }while(pw!="password");
                      cout<<"Login Sucessfull";
			          admin_menu();
				      break;
			          }
			case '2':{
			          int flag=0;
			          char uid[10];
			          system("cls");
			          cout<<"\n=======================================================================================================================================================\n";
                      cout<<"\n\t\t\t\tCHECK YOUR CURRENT STATUS\n";
                      cout<<"\n=======================================================================================================================================================\n";
                      cout<<"\nEnter your Unique Id\n";
                      cin>>uid;
                      fstream fp;
                      fp.open("entry",ios::in|ios::out);
                      while(fp.read((char*)&dt,sizeof(entry)))
                      {
                          if(strcmpi(dt.retcn(),uid)==0)
                          {
                              flag=1;
                              cout<<"====================================================================================\n";
                              cout<<"\nUnique No."<<setw(10)<<"Date"<<setw(15)<<"Pin Code"<<setw(15)<<"Destination"<<setw(10)<<"Weight"<<setw(10)<<"status"<<setw(8)<<"type"<<"\n";
                              cout<<"====================================================================================\n";
                              dt.report();
                          }
                      }
                      if(flag==0)
                      {
                         cout<<"\nSorry please re enter the Unique id\n";
                      }
                       system("pause");
			             break;
                     }
            case '3':{
                        float weight,value;
                        char ty;
                        system("cls");
                        cout<<"\n===============================================================================================================================================================\n";
                        cout<<setw(90)<<"CALCULATE THE ESTIMATED PRICE\n";
                        cout<<"\n===============================================================================================================================================================\n";
                        cout<<"Enter you approx package weight :";
                        cin>>weight;
                        cout<<"\nEnter the type : (Type N for Normal and O for others)\n ";
                        cin>>ty;
                        value=dt.fncalc(weight,ty);
                        cout<<"\nYour estimated price is:\t";
                        cout<<value<<"\n\n\n\n\n";
                        system("pause");
                        break;
                     }

			case '4':{
                      char ch;
                      system("cls");
                      fstream fp8;
                      fp8.open("Helpline",ios::in|ios::out);
                      while(fp8.get(ch))
                      {
                         cout<<ch;
                      }
                      cout<<"\n\n\n\n\n\n";
                      system("pause");
                      fp8.close();
                      break;
                     }
			case '5':{
			           exit(1);
			          }
			default :cout<<"\a";
		}
	}
}

