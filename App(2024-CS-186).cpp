#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<Windows.h>
using namespace std;

int printTitle();
void setColor(int color);
int login();
int signIn();
int createAccount();
char userWork();
char bills();
void billPayment(char billing);
int viewBalance();
int rechargeBalance();
int onlineTransaction();
char adminWork();
int seeRecord();
int deleteRecord();
int findRecord();
int collectTax();
void writeToFile();
void loadFromFile();
string getField(string record,int field);

string usernameArray[10];
string passwordArray[10];
double balanceArray[10];
int balanceIndex=0;
double balance=0;
bool checkadmin=false;

int main()
{
    char exit=' ';

    loadFromFile();

    while(exit!='q')
    {
        system("cls");
        setColor(2);
        printTitle();
        if(login())
        {
            break;
        }

        if((checkadmin))
        {   
            while(exit!='q')
            {
                system("cls");
                setColor(12);
                printTitle();

                char adminOption=adminWork();

                if(adminOption=='1')
                {
                    seeRecord();
                }
                else if(adminOption=='2')
                {
                    deleteRecord();
                }
                else if(adminOption=='3')
                {
                    findRecord();
                }
                else if(adminOption=='4')
                {
                    collectTax();
                }
                else if(adminOption=='b')
                {
                    checkadmin=false;
                    break;
                }

                cout<<"Press any key to continue! (q to exit) and (s to sign out): ";
                exit=getch();
                if(exit=='s')
                {
                    checkadmin=false;
                    break;
                }
            }
        }
        else
        {
            while(exit!='q')
            {
                system("cls");
                setColor(9);
                printTitle();

                char menu1=userWork();

                if(menu1=='1')
                {
                    char billing=bills();
                    if(billing=='b')
                    {
                        continue;
                    }
                    billPayment(billing);
                }
                else if(menu1=='2')
                {
                    viewBalance();
                }
                else if(menu1=='3')
                {
                    rechargeBalance();
                }
                else if(menu1=='4')
                {
                    onlineTransaction();
                }
                else if(menu1=='b')
                {
                    break;
                }
                balanceArray[balanceIndex]=balance;

                cout<<"Press any key to continue! (q to exit) and (s to sign out): ";
                exit=getch();
                if(exit=='s')
                {
                    break;
                }
            }
        }
    }
    writeToFile();
    system("cls");
    printTitle();
    cout<<"Thank You for using our app!"<<endl;

    return 0;
}

int printTitle()
{
    cout<<"##############################################################################"<<endl;
    cout<<"#                                                                            #"<<endl;
    cout<<"#    ########  ######   ######  ######    #####   ######    ######   ##  ##  #"<<endl;
    cout<<"#       ##    ##    ##     ##      ##    ##      ##    ##  ##    ##  ##  ##  #"<<endl;
    cout<<"#       ##    ########    ##      ##     ##      ########    ##      ######  #"<<endl;
    cout<<"#  ##   ##    ##    ##   ##      ##      ##      ##    ##      ##    ##  ##  #"<<endl;
    cout<<"#  ##   ##    ##    ##  ##      ##       ##      ##    ##  ##    ##  ##  ##  #"<<endl;
    cout<<"#   #####     ##    ##  ######  ######    #####  ##    ##   ######   ##  ##  #"<<endl;
    cout<<"#                                                                            #"<<endl;
    cout<<"##############################################################################"<<endl;

    return 0;
}

void setColor(int color)
{ 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int login()
{
    char loginMenu='1';
    do{
        system("cls");
        printTitle();
        if(loginMenu!='1' && loginMenu!='2' && loginMenu!='q')
        {
            cout<<"Invalid input! Enter 1 or 2!"<<endl;
        }
        cout<<"1.Sign In!"<<endl;
        cout<<"2.Create Account!"<<endl;
        cout<<"q to exit!"<<endl;
        cin>>loginMenu;
    
    }while(loginMenu!='1' && loginMenu!='2' && loginMenu!='q');
    if(loginMenu=='1')
    {
        return signIn();
    }
    else if(loginMenu=='2')
    {
        return createAccount();
    }
    else if(loginMenu=='q')
    {
        return 1;
    }
}

int signIn()
{

    string username;
    string password;

    int test=0;

    while(test==0)
    {
        cout<<"SIGN IN"<<endl;
        cout<<"Enter username:";
        cin>>username;
        cout<<"Enter password:";
        cin>>password;

        if(username=="admin" && password=="admin123")
        {
            checkadmin=true;
            return 0;
        }

        for(int i=0;i<10;i++)
        {
            if(username==usernameArray[i] && password==passwordArray[i])
            {
                balanceIndex=i;
                balance=balanceArray[balanceIndex];
                test++;
                break;
            }
        }
        if(test==0)
        {
            char acc=' ';
            cout<<"Wrong username or password!"<<endl;
            cout<<"If no account? (press 'a' to make account) or (press any key to try again)"<<endl;
            acc=getch();
            if(acc=='a')
            {
                cout<<"No Account found"<<endl;
                createAccount();
                return 0;
            }
        }
    }
    return 0;
}

int createAccount()
{
    string username;
    string password;
    int usernameExist=0;

    while(true)
    {
        usernameExist=0;

        system("cls");
        printTitle();
        cout<<"CREATE ACCOUNT"<<endl;

        cout<<"Enter username:";
        cin>>username;
        cout<<"Enter password:";
        cin>>password;

        //checks for gmail
        int x=username.size()-1;  //-1 for removing '\0'
        string id="";
        for(int j=x;j>x-10;j--)
        {
            id=id+username[j];
        }
        //check for already email
        for(int i=0;i<10;i++)
        {
            if(username==usernameArray[i])
            {
                cout<<"Username Already Exists!"<<endl;
                cout<<"Press any key to continue!"<<endl;
                usernameExist++;
            }
        }
        if(usernameExist!=0)
        {
            getch();
            continue;
        }

        if(id!="moc.liamg@")
        {
            cout<<"Invalid username! Use gmail account!"<<endl;
        }
        else if(id=="moc.liamg@")
        {
            for(int i=0;i<10;i++)
            {
                balance=0;
                if(usernameArray[i]=="" && passwordArray[i]=="")
                {
                    usernameArray[i]=username;
                    passwordArray[i]=password;
                    balanceArray[i]=balance;
                    return login();
                }
            }
        }
    }   
}

char userWork()
{
    char menu1='1';
    do{
        system("cls");
        printTitle();
        if(menu1!='1' && menu1!='2' && menu1!='3' && menu1!='4' && menu1!='b')
        {
            cout<<"Invalid Input! Enter value between 1 and 4!"<<endl;
        }
        cout<<"Select the following options:"<<endl;
        cout<<"1.Pay bills!"<<endl;
        cout<<"2.View Balance!"<<endl;
        cout<<"3.Recharge account!"<<endl;
        cout<<"4.Online Transaction!"<<endl;
        cout<<"Press b to go back!"<<endl;

        cin>>menu1;
    }while(menu1!='1' && menu1!='2' && menu1!='3' && menu1!='4' && menu1!='b');

    return menu1;
}

char bills()
{
    char billing='1';
    do{
        system("cls");
        printTitle();
        if(billing!='1' && billing!='2' && billing!='3' && billing!='b')
        {
            cout<<"Invalid input! Enter value between 1 and 3!"<<endl;
        }  
        cout<<"Select the folowing option:"<<endl;
        cout<<"1.Electricity bill!"<<endl;
        cout<<"2.Gas bill!"<<endl;
        cout<<"3.Water bill!"<<endl;
        cout<<"Press b to go back!"<<endl; 
        cin>>billing; 
        
    }while(billing!='1' && billing!='2' && billing!='3' && billing!='b');
    
    return billing;
}
void billPayment(char billing)
{
    string billName;
    double billAmount;
    if(billing=='1')
    {
        billName="Electricity";
    }
    else if(billing=='2')
    {
        billName="Gas";
    }
    else if(billing=='3')
    {
        billName="Water";
    }
    
    cout<<"Enter "<<billName<<" bill: Rs.";
        cin>>billAmount;
        if(balance>=billAmount)
        {
            cout<<billName<<" Bill of Rs."<<billAmount<<" is paid!"<<endl;
            balance=balance-billAmount;
            cout<<"Remaining balance: Rs."<<balance<<endl;
        }
        else
        {
            cout<<"Not enough amount!"<<endl;
            cout<<"Balance: Rs."<<balance<<endl;
        }
}

int viewBalance()
{
    cout<<"Your Balance is: Rs."<<balance<<endl;
    return 0;
}

int rechargeBalance()
{
    double reload; 
    do{
        cout<<"Your Balance is: Rs."<<balance<<endl;
        cout<<"Enter Amount to recharge:";
        cin>>reload;
    }while(reload<0);

    balance=balance+reload;
    cout<<"Your Balance after recharge is: Rs."<<balance<<endl;
    return 0;
}

int onlineTransaction()
{
    double transaction;
    string username;
    int otherAccIndex=0;

    int check=0;

    cout<<"Enter username:";
    cin>>username;

    for(int i=0;i<10;i++)
    {
        if(usernameArray[i]==username)
        {
            otherAccIndex=i;
            check++;
            break;
        }
    }
    if(check==0)
    {
        cout<<"No such Record exists!"<<endl;
        return 0;
    }

    do{
        cout<<"Enter amount to transfer:";
        cin>>transaction;
    }while(transaction<0);

    if(balance>=transaction)
    {
        balance=balance-transaction;
        cout<<"Money has been transfered successfully!"<<endl;
        cout<<"Remaining Balance: Rs."<<balance<<endl;
        balanceArray[otherAccIndex]=balanceArray[otherAccIndex]+transaction;
    }
    else
    {
        cout<<"Not enough balance!"<<endl;
        cout<<"Your balance: Rs."<<balance<<endl;
    }
    return 0;
}

char adminWork()
{
    char adminOption='1';

    do{
        system("cls");
        printTitle();
        if(adminOption!='1' && adminOption!='2' && adminOption!='3' && adminOption!='4' && adminOption!='b')
        {
            cout<<"Invalid input! Enter value between 1 and 4!"<<endl;
        }
        cout<<"Select following option!"<<endl;
        cout<<"1.See All Records!"<<endl;
        cout<<"2.Delete Record!"<<endl;
        cout<<"3.Find Record!"<<endl;
        cout<<"4.Collect Taxes!"<<endl;
        cout<<"b to go back!"<<endl;
        cin>>adminOption;
    
    }while(adminOption!='1' && adminOption!='2' && adminOption!='3' && adminOption!='4' && adminOption!='b');

    return adminOption;   
}

int seeRecord()
{
    cout<<"Username\t\tPassword\tBalance"<<endl;

    for(int i=0;i<10;i++)
    {
        if(usernameArray[i]!="")
        {
            cout<<usernameArray[i]<<"\t\t"<<passwordArray[i]<<"\t\t"<<balanceArray[i]<<endl;
        }
    }
    return 0;
}

int deleteRecord()
{
    string username;
    string password;

    int check=0;

    cout<<"Enter username:";
    cin>>username;
    cout<<"Enter password:";
    cin>>password;

    for(int i=0;i<10;i++)
    {
        if(usernameArray[i]==username && passwordArray[i]==password)
        {
            usernameArray[i]="";
            passwordArray[i]="";
            balanceArray[i]=0;
            check++;
            break;
        }
    }
    if(check==0)
    {
        cout<<"No such Record exists!"<<endl;
    }
    else
    {
        cout<<"Record has been deleted!"<<endl;
    }
    return 0;
}

int findRecord()
{
    string username;
    string password;

    int check=0;

    cout<<"Enter username:";
    cin>>username;
    cout<<"Enter password:";
    cin>>password;

    for(int i=0;i<10;i++)
    {
        if(usernameArray[i]==username && passwordArray[i]==password)
        {
            cout<<"Username: "<<usernameArray[i]<<endl;
            cout<<"Password: "<<passwordArray[i]<<endl;
            cout<<"Balance:  "<<balanceArray[i]<<endl;
            check++;
            break;
        }
    }
    if(check==0)
    {
        cout<<"No such Record exists!"<<endl;
    }
    return 0;
}

int collectTax()
{
    double taxPercent=0.0;

    do{
        if(taxPercent<0 || taxPercent>20)
        {
            cout<<"Enter value between 0 and 20"<<endl;
        }
        cout<<"Enter Tax percentage (Between 1 and 20):";
        cin>>taxPercent;
    }while(taxPercent<0 || taxPercent>20);

    for(int i=0;i<10;i++)
    {
        balanceArray[i]=balanceArray[i]-(balanceArray[i]*(taxPercent)/100.0);
    }
    cout<<"Taxes have been deducted!"<<endl;

    return 0;
}

void writeToFile()
{
    fstream file;
    file.open("data.txt",ios::out);

    for(int i=0;i<10;i++)
    {
        if(usernameArray[i]!="")
        {
            file<<usernameArray[i]<<',';
            file<<passwordArray[i]<<',';
            file<<balanceArray[i];
            file<<endl;
        }
    }
}

void loadFromFile()
{
    string line;

    fstream file;
    file.open("data.txt",ios::in);

    while(getline(file,line))
    { 
        usernameArray[balanceIndex]=getField(line,1);
        passwordArray[balanceIndex]=getField(line,2);
        balanceArray[balanceIndex]=stoi(getField(line,3));
        balanceIndex++;
    }
}

string getField(string record,int field)
{
    int commaCount=1;
    string answer="";

    for(int i=0;i<record.size();i++)
    {
        if(record[i]==',')
        {
            commaCount++;
        }
        else if(commaCount==field)
        {
            answer=answer+record[i];
        }
    }
    return answer;
}