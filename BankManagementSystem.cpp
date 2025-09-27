#include<iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;

class account_query
{
	//private :
	char account_number[10];
	char account_type[10];
	char first_name[10];
	char last_name[10];
	float total_balance;

	public :
	void read_data();
	void show_data();
	void write_rec();
	void read_rec();
	void search_rec();
	void edit_rec();
	void delete_rec();
};

void account_query::read_data()
{
	bool num;
	//cout<<"--------------------------------"<< endl;
	cout<<" Enter First Name : ";
	cin>>first_name;
	cout<<" Enter Last Name  : ";
	cin>>last_name;
	cout<<" Select Acc Type(Current(0) or Saving(1): ";
	cin>>num;

	if(num==0)
		strcpy(account_type,"Current");
	else if(num==1)
		strcpy(account_type,"Saving");

	cout<<" Enter Account Number : ";
	cin>>account_number;
	cout<<" Enter Balance : Rs.";
	cin>>total_balance;
	cout<<"--------------------------------"<< endl;
}

void account_query::show_data()
{
	//cout<<"--------------------------------"<< endl;
	cout<<"   First Name       ->  "<<first_name	<<endl;
	cout<<"   Last Name        ->  "<<last_name	<<endl;
	cout<<"   Account Number   ->  "<<account_number<<endl;
	cout<<"   Account Type     ->  "<<account_type	<<endl;
	cout<<"   Current Bal Rs.  ->  "<<total_balance	<<endl;
	cout<<"--------------------------------"<< endl;
}

void account_query::write_rec()
{
	ofstream outfile;
	outfile.open("record.bank",ios::binary | ios::app);
	read_data();
	outfile.write(reinterpret_cast<char*>(this),sizeof(*this));
	outfile.close();
}

/*void account_query::read_rec()
  {
  ifstream infile;
  infile.open("record.bank", ios::binary);
  if(!infile)
  {
  cout<<"Error in Opening! File Not Found!!"<<endl;
  return;
  }
  infile.seekg(0,ios::end);
  int count = infile.tellg()/sizeof(*this);
  if(count==0)
  {
  cout<<"No Record Available in Bank System\n";
  }
  else
  {
  cout<<"There are "<<count<<" records in the file\n";
  cout<<" ---------Data From File--------"<<endl;
  while(!infile.eof())
  {
  infile.read(reinterpret_cast<char*>(this),sizeof(*this));
  show_data();
  }
  }
  infile.close();
  }*/

void account_query::read_rec() 
{
	ifstream infile("record.bank", ios::binary);

	if (!infile) 
	{
		cout << "Error in Opening! File Not Found!!" << endl;
		return;
	}

	infile.seekg(0, ios::end);
	int count = infile.tellg() / sizeof(*this);

	if (count == 0) 
	{
		cout << "Records Not Available.!\n";
		cout<<"--------------------------------"<< endl;
		return ;
	}	 

	cout << "There are " << count << " records in the file\n";
	cout<<"--------------------------------"<< endl;
	cout << "---------Data From File--------" << endl;
	cout << endl;

	infile.seekg(0, ios::beg); // Reset file position to beginning

	while (infile.read(reinterpret_cast<char*>(this), sizeof(*this))) {
		show_data();
	}

	infile.close();
}

void account_query::search_rec()
{
	int n;
	ifstream infile;
	infile.open("record.bank", ios::binary);
	if(!infile)
	{
		cout<<"Error in Opening! File Not Found!!"<<endl;
		return;
	}
	infile.seekg(0,ios::end);
	int count = infile.tellg()/sizeof(*this);
	if(count==0)
	{
		cout<<"No Record Available.!"<< endl;
		cout<<"--------------------------------"<< endl;
		return ;
	}

	cout<<"There are "<<count<<" records in the file\n";
	cout<<"--------------------------------"<< endl;
	cout<<"Enter Record Number to Search : ";
	cin>>n;
	cout<<"--------------------------------"<< endl;
	if(n<=count && n!=0)
	{
		infile.seekg((n-1)*sizeof(*this));
		infile.read(reinterpret_cast<char*>(this),sizeof(*this));
		show_data();
	}
	else
	{
		cout<<"Enter Correct Record Number\n",search_rec();
	}
}


int main()
{
	account_query A;
	int choice;
	cout<<"-----Bank Management System-----"<< endl;
	cout<<"--------------------------------"<< endl;

	while(true)
	{
		cout<<"\t1-->Create Record \n\t2-->Display Records \n\t3-->Search Record \n\t4-->Update Record \n\t5-->Delete Record \n\t6-->Exit"<< endl;
		cout<<"--------------------------------"<< endl;
		cout<<"Enter option : ";
		cin>>choice;
		cout<<"--------------------------------"<< endl;
		switch(choice)
		{
			case 1:
				A.write_rec();
				break;
			case 2:
				A.read_rec();
				break;
			case 3:
				A.search_rec();
				break;
			case 4:
				A.edit_rec();
				break;
			case 5:
				A.delete_rec();
				break;
			case 6:
				exit(0);
				break;
			default : 
				cout<<"wrong option.!"<< endl;
		}
	}
	//system("pause");
	return 0;
}
