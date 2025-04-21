#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


struct Invoice
{
	char Seller[6];
	char Buyer[6];
	char Amount[100];
	unsigned int Year;
	unsigned int Month;
	unsigned int Day;
};

Invoice ReadFromFile(char* filename, int n)
{
	vector <Invoice> Records;
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Не удалось открыть файл. " << filename << endl;
	}
	for (int i = 0; i < n; i++)
	{
		file.getline(Records[i].Seller, 6);
		file.getline(Records[i].Buyer, 6);
		file.getline(Records[i].Amount, 100);
	}

}


int main()
{
	
}
