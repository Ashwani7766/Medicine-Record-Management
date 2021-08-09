#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;
class medicine
{
    char mname[30];
    int price;
    int dose;
    int quant;
    int medicinecode;
public:
    void billing(int q)
    {

        if(q<=quant)
        {
            cout<<"\nAmt to be paid: "<<q*price;
            quant=quant-q;
        }
        else
        {
            cout<<"\nUnavailable ";
            cout<<"\nAvailable : "<<quant;
        }
    }
    void getdata()
    {
        cout<<"\n Med Name ::";
        cin>>mname;
        cout<<"\nMcode ::";
        cin>>medicinecode;
        cout<<"\n Dose ::";
        cin>>dose;
        cout<<"\n  MRP ::";
        cin>>price;
        cout<<"\nEnter quant ::";
        cin>>quant;
    }
    void putdata()
    {

        cout<<"\t"<<mname<<"\t";
        cout<<"\t"<<medicinecode<<"\t";
        cout<<"\t"<<dose<<"\t";
        cout<<"\t"<<price<<"\t";
        cout<<"\t"<<quant<<"\t";
    }
    int rmedicinecode()
    {
        return medicinecode;
    }

}m;
void infoStock();
void addMedicine();
void findmedicine();
void Delete();
void bill();
int main()
{
    first:

    cout<<"\n\n\n\n \t\t\t\tMED RECORD ";
    cout<<"\nSelect Any Option ::";
    cout<<"\n1.Current Available \n2.New medicine.\n3. Search\n4.Delete\n5.Customer billing\n6.Exit";
    int n;
    cin>>n;
    switch(n)
    {
      case 1:infoStock();
             system("pause");
             system("cls");
             goto first;
             break;
      case 2:addMedicine();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 3:findmedicine();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 4:Delete();
      system("pause");
                   system("cls");
             goto first;
      break;
      case 5:bill();
      system("pause");
                   system("cls");
             goto first;
      default: cout<<"\nPlease enter a valid value !!";
    }
}
void infoStock()
{
    system("cls");
    fstream f;
    f.open("record.dat",ios::in|ios::binary);
    if(!f)
    {
        cout<<"\n Error opening ";
    }
    int size=f.tellp()/sizeof(m);
    cout<<"\n Currently Available ::"<<endl;
    while(f)
    {
        f.read((char*)&m,sizeof(m));
        if(f.eof())
        {
            break;
        }
        else
        {
        m.putdata();
        cout<<"\n";}
    }

}
void addMedicine()
{
    char ch;
    string s("Ashwani");
    string s1;
    system("cls"); 
    cout<<"\n Password ";
    cin>>s1;
    if(s==s1)
    {

    int x;
   fstream h;
   h.open("record.dat",ios::out|ios::app|ios::binary);
   start:
   cout<<"\n No of new med to add :";
   cin>>x;
   int i=0;
   while(x>0)
   {
   cout<<"\n"<<i+1<<" Record : ";
       m.getdata();
       h.write((char*)&m,sizeof(m));
       ++i;
       --x;
   }
   cout<<"\n Add more ?";
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
void findmedicine()
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
        if(b==m.rmedicinecode())
        {
           p++;
           break;
        }
 
    }
    if(p>0)
    {
        cout<<"\nRecord found ";
        m.putdata();
    }
    else
        cout<<"\nRecord not found";
    f.close();
}
void Delete()
{
    fstream file,file2;
    string s("Ashwani");
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
       if(x!=m.rmedicinecode())
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
void fdisplay()
{
    fstream f;
    cout<<"\n\n\t\t\tCode\t\tDose\t\tPrice\t\tQuantity ";
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
                cout<<"\n";m.putdata();
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
    fdisplay();
    cout<<"\n\n\tEnter the unique code of medicine ";
    cin>>b;
    cout<<"\n\tEnter the quantity ";
    cin>>x;
    while(!file.eof())
    {
        pos=file.tellp();
        file.read((char*)&m,sizeof(m));
        if(m.rmedicinecode()==b)
        {
            m.billing(x);
            file.seekp(pos);
            file.write((char*)&m,sizeof(m));
            p++;
            break;
        }


    }          if(p==0)
               {
                 cout<<"\nmedicine Not Found !!";
               }

    file.close();
}
