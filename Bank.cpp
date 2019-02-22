#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct PERSON 
{
    char  Name[20];
    float Balance; 
};

void Display(PERSON* a, int N)
{
	cout<<setprecision(2)<<fixed;
	cout<<"Name\tBalance"<<endl; 
  	cout<<"------------"<<endl; 
  	for(int i = 0; i < N; i++)
  	{
  		cout<<a[i].Name<<" "<<a[i].Balance<<endl;
  	}
}

void FindRichest(PERSON* a, int N)
{ 
	int max = 0; 
	for(int i = 0; i < N; i++)
	{
    	if(a[max].Balance < a[i].Balance)
    	{
    		max = i; 
    	}
    }
    cout<<endl;
  	cout<<"The customer with maximum balance is: "<<a[max].Name<<endl; 
}

void Deposit(char customerName[], PERSON* a, int N)
{
  	int wrong = -1; 
  	for(int i = 0; i < N; i++) 
  	{
    	if (strcmp(customerName, a[i].Name) == 0)
    	{
    		wrong = i;
    		break;
    	}
  	}
  	
  	if(wrong == -1)
  	{
  		cout<<"Wrong username. "<<endl;
  	}
  	
  	else
  	{
  		double amount;
    	cout<<customerName<<", how much would you like to deposit? "; 
    	cin>>amount; 
    	a[wrong].Balance += amount;
    	cout<<"Now your new balance is "<<a[wrong].Balance<<endl; 
  	}
}

void NewCopy(string firstName, PERSON* a, int N)
{
	ofstream out;
    out.open(firstName.c_str());

    for (int i = 0; i < N; i++) 
    {
        out<<a[i].Name<<" "<<a[i].Balance<<endl;
    }

    out.close();
}

int main()
{ 
	int N = 0;
	ifstream file;
	file.open("data.txt");
	if (file.fail())
	{
		cout<<"Cannot open the requested file"<<endl;
		return 0;
	}
	
	string line;
	while (getline(file, line)) {N++;}
	
	file.clear();
	file.seekg(0, ios::beg);
	
	PERSON* a = new PERSON[N];
	
	string firstName;
	string lastName;
	int i = 0;
	
	while(file>>firstName)
	{
		file>>lastName>>a[i].Balance;
		strcpy(a[i].Name, (firstName + " " + lastName).c_str());
		i++;
	}
	
	Display(a, N);
	FindRichest(a, N);
	char customerName[20];
	
	cout<<endl;
	cout<<"Enter your full name to deposit money: ";
	cin.getline(customerName, 20);
	
	Deposit(customerName, a, N);
	NewCopy("data.txt", a, N);
	
	cin.get();
	return 0;
}