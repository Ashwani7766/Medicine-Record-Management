#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
class med
{
    char name[30];
    int price;
    int dose;
    int quantity;
    int code;
public:
    void invoice(int q)
    {

        if(q<=quantity)
        {
            cout<<"\nTotal price to be paid "<<q*price;
            quantity=quantity-q;
        }
        else
        {
            cout<<"\nStock not available ";
            cout<<"\nStock available is "<<quantity;
        }
    }
    void get()
    {
        cout<<"\n Enter the name of Medicine ::";
        cin>>name;
        cout<<"\nEnter the code of the medicine ::";
        cin>>code;
        cout<<"\n Enter the dose of Medicine ::";
        cin>>dose;
        cout<<"\n Enter the price of Medicine ::";
        cin>>price;
        cout<<"\nEnter the quantity ::";
        cin>>quantity;
    }
    void put()
    {

        cout<<"\t"<<name<<"\t";
        cout<<"\t"<<code<<"\t";
        cout<<"\t"<<dose<<"\t";
        cout<<"\t"<<price<<"\t";
        cout<<"\t"<<quantity<<"\t";
    }
    int rcode()
    {
        return code;
    }

}m;
void stockinfo();
void add();
void findmed();
void del();
void bill();
int main()
{
    first:

    cout<<"\n\n\n\n \t\t\t\tMedicine Record Management System ";
    cout<<"\nEnter the option below ::";
    cout<<"\n1.Stock Info\n2.Add med.\n3.Find med\n4.Delete\n5.Customer Invoice\n6.Exit";
    int n;
    cin>>n;
    switch(n)
    {
      case 1:stockinfo();
             system("pause");
             system("cls");
             goto first;
             break;
      case 2:add();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 3:findmed();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 4:del();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 5:bill();
      system("pause");
                   system("cls");
             goto first;
      default: cout<<"\nWrong choice entered !!";
    }
}
void stockinfo()
{
    system("cls");
    fstream f;
    f.open("record.dat",ios::in|ios::binary);
    if(!f)
    {
        cout<<"\n Error File Opening ";
    }
    cout<<"\n Currently Available ::"<<endl;
    cout<<"\n\tNAME:\t\tCODE:\t\tDOSE:\t\tPRICE:\t\tQUANTITY";
    while(f)
    {
        f.read((char*)&m,sizeof(m));
        if(f.eof())
        {
            break;
        }
        else
        {
        cout<<"\n";
        m.put();
        }
    }

}
void add()
{
    char ch;
    string s("ashwani");
    string s1;
    system("cls");
    cout<<"\n Enter password ";
    cin>>s1;
    if(s==s1)
    {

    int x;
   fstream h;
   h.open("record.dat",ios::out|ios::app|ios::binary);
   start:
   cout<<"\n Enter the number of medicines to add :";
   cin>>x;
   int i=0;
   while(x>0)
   {
   cout<<"\n"<<i+1<<" Record : ";
       m.get();
       h.write((char*)&m,sizeof(m));
       ++i;
       --x;
   }
   cout<<"\n Want to add again ?";
   cin>>ch;
   if(ch=='y'||ch=='Y')
   {
       goto start;
   }
   h.close();
    }
    else
        cout<<"\n Access denied ";



}
void findmed()
{
    system("cls");
    int b;
    cout<<"\nEnter the code of the medicine to be searched ::";
    cin>>b;
    fstream f;
    int p=0;
    f.open("record.dat",ios::in|ios::binary);
    while(f)
    {
        if(f.eof())
        {
            break;
        }
        f.read((char*)&m,sizeof(m));
        if(b==m.rcode())
        {
           p++;
           break;
        }

    }
    if(p>0)
    {
        cout<<"\nRecord found ";
        m.put();
    }
    else
        cout<<"\nRecord not found";
    f.close();
}
void del()
{
	fstream file,file2;
    string s("ashwani");
    string s1;
    system("cls");
    cout<<"\n Enter password ";
    cin>>s1;
    if(s==s1)
    {

   system("cls");
   int x;
   cout<<"\nEnter the code of medicine to delete ::";
   cin>>x;
   
   file.open("record.dat",ios::in|ios::binary);
   file2.open("r.dat",ios::out|ios::binary);

   while(!file.eof())
   {
       if(file.eof())
       {
           break;
       }
       file.read((char*)&m,sizeof(m));
       if(x!=m.rcode())
       {
           file2.write((char*)&m,sizeof(m));
       }
       else
        cout<<"\nDeleted successfully ";

    }
    }
    else
        cout<<"\n Access denied ";
    file.close();
    file2.close();
    remove("record.dat");
    rename("r.dat","record.dat");

}
void display()
{
    fstream f;
    cout<<"\n\n\tName\t\tCode\t\tDose\t\tPrice\t\tQuantity ";
    f.open("record.dat",ios::in|ios::binary);
    while(f)
    {
        f.read((char*)&m,sizeof(m));
        if(f.eof())
        {
            break;
        }
        else
            {
                cout<<"\n";m.put();
            }
    }
}
void bill()
{
    system("cls");
    fstream file;
    int b,x,p=0;
    long pos=0;
    file.open("record.dat",ios::in|ios::out|ios::binary);
    display();
    cout<<"\n\n\tEnter the code of medicine ";
    cin>>b;
    cout<<"\n\tEnter the quantity ";
    cin>>x;
    while(!file.eof())
    {
        pos=file.tellp();
        file.read((char*)&m,sizeof(m));
        if(m.rcode()==b)
        {
            m.invoice(x);
            file.seekp(pos);
            file.write((char*)&m,sizeof(m));
            p++;
            break;
        }


    }          if(p==0)
               {
                 cout<<"\nMedicine Not Found !!";
               }

    file.close();
}

