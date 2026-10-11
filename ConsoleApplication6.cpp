#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct Sclient {
	string AcountNumber;
	string pinCode;
	string ClientName;
	string Phone;
	double Balance;
	bool makefordelet = false;
};
string acount;
string pin;
Sclient client;

void Atmmainmenu();
enum enchoos { quikwithdraww = 1, normalwithdraw = 2, deposit = 3, balances = 4, logoutt = 5 };
enum enwithdraw { e20 = 1, e50 = 2, e100 = 3, e200 = 4, e400 = 5, e600 = 6, e800 = 7, e1000 = 8, exitt = 9 };
vector<Sclient> savedelet(vector<Sclient>& vclient);
void printshowwithdraw() {
	cout << "-------------------------------------------------------\n";
	cout << "-------------------------------------------------------\n";
	cout << "                            Quick Withdraw            \n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";
	cout << "            [1]20            [2]50\n";
	cout << "            [3]100           [4]200\n";
	cout << "            [5]400           [6]600\n";
	cout << "            [7]800          [8]1000\n";
	cout << "            [9]Exit     \n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";

}
vector<string>split(string s, string delim) {
	vector<string>vstring;
	int pos = 0;
	string word;
	while ((pos = s.find(delim)) != string::npos) {
		word = s.substr(0, pos);
		if (word != " ") {
			vstring.push_back(word);
		}
		s.erase(0, pos + delim.length());
	}
	if (s != " ") { vstring.push_back(s); }
	return vstring;
}
Sclient convertlinetorecord(string line, string delim) {
	vector<string>vclient = split(line, delim);
	Sclient client;
	client.AcountNumber = vclient[0];
	client.pinCode = vclient[1];
	client.ClientName = vclient[2];
	client.Phone = vclient[3];
	client.Balance = stod(vclient[4]);
	return client;
}

vector<Sclient>fillvector(string delim) {
	vector<Sclient>vclient;
	fstream myfile;
	Sclient client;
	myfile.open("client.txt", ios::in);
	if (myfile.is_open()) {
		string line;
		while (getline(myfile, line)) {
			client = convertlinetorecord(line, delim);
			vclient.push_back(client);
		}

		myfile.close();
	}
	return vclient;
}
bool search(string& acount, string& pin, Sclient& client) {
	vector<Sclient>readclient = fillvector("#//#");
	for (Sclient& clientt : readclient) {
		if (clientt.AcountNumber == acount && clientt.pinCode == pin) {

			client = clientt;
			return true;
		}
	}
	return false;
}
void updat(Sclient& client) {
	vector<Sclient>readv = fillvector("#//#");
	for (Sclient& c : readv) {
		if (c.AcountNumber == client.AcountNumber) {
			c.Balance = client.Balance;
			savedelet(readv);
			readv = fillvector("#//#");
		}
	}
}

void Normalwithdraw() {
	int amount;
	cout << "----------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------\n";
	cout << "                         Normal Withdraw Screen\n ";
	cout << "--------------------------------------------------------------------\n";
	cout << "--------------------------------------------------------------------\n";
	if (search(acount, pin, client)) {
		cout << "Enter an Amount multiply 5?\n";
		cin >> amount;
		while (amount % 5 != 0) {
			cout << "Enter an Amount multiply 5?\n";
			cin >> amount;
		}if (amount > client.Balance) {
			cout << "Amount Exceded your Balance ,make another choose\n";
		}
		else {
			char c;
			cout << "Are you sure you want this transaction?\n";
			cin >> c;
			if (toupper(c) == 'Y') {
				client.Balance -= amount;
				updat(client);
				cout << "\n\n Done Successfull, New Balance is:" << client.Balance << endl;

			}
		}
	}

}

void login() {

	bool log = false;

	do {
		system("cls");
		cout << "--------------------------------------------------\n";
		cout << "                   Login Screen                     \n";
		cout << "---------------------------------------------------\n";
		if (log) {
			cout << "Invalid Acountnumber/pin!\n";
		}
		cout << "Enter Acount Number?\n";
		cin >> acount;
		cout << "Enter pin?\n";
		cin >> pin;
		log = !search(acount, pin, client);

	} while (log);
	system("cls");
	Atmmainmenu();
}
string converttoline(Sclient  client, string delim) {
	string s = "";
	s += client.AcountNumber + delim;
	s += client.pinCode + delim;
	s += client.ClientName + delim;
	s += client.Phone + delim;
	s += to_string(client.Balance);
	return s;
}

vector<Sclient> savedelet(vector<Sclient>& vclient) {

	Sclient c;
	fstream myfile;
	string line;
	vector<Sclient>fillclient;
	myfile.open("client.txt", ios::out);
	if (myfile.is_open()) {
		for (Sclient& client2 : vclient) {
			if (client2.makefordelet == false) {
				line = converttoline(client2, "#//#");
				myfile << line << endl;

			}
		}

		myfile.close();
	}
	return vclient;

}


void Quickwithdraw() {
	printshowwithdraw();
	int choose;
	search(acount, pin, client);
	cout << "Your Balance " << client.Balance << endl;
	cout << "choos Show withdraw from[1 to8]?\n ";
	cin >> choose;
	char c;
	int amount;

	switch (choose) {
	case enwithdraw::e20:
		amount = 20;
		break;
	case enwithdraw::e50:
		amount = 50;
		break;
	case enwithdraw::e100:
		amount = 100;
		break;
	case enwithdraw::e200:
		amount = 200;
		break;
	case enwithdraw::e400:
		amount = 400;
		break;
	case enwithdraw::e600:
		amount = 600;
		break;
	case enwithdraw::e800:
		amount = 800;
		break;
	case enwithdraw::e1000:
		amount = 1000;
		break;
	case enwithdraw::exitt:
		Atmmainmenu();
		break;
	}
	cout << "Are you sure you want this transaction?\n";
	cin >> c;
	if (toupper(c) == 'Y') {
		client.Balance -= amount;
		if (amount > client.Balance) {
			cout << "Amount Exceded your Balance ,make another choose\n";
			updat(client);
			cout << "\n\n Done Successfull, New Balance is:" << client.Balance << endl;
		}
	}
}
void Atmscreen() {
	cout << "----------------------------------------------------\n";
	cout << "-----------------------------------------------------\n";
	cout << "                Atm Main Menue Screen \n";
	cout << "-------------------------------------------------------\n";
	cout << "-------------------------------------------------------\n";
	cout << "                         [1]Quik Withdraw\n";
	cout << "                         [2]Normal Withdraw\n";
	cout << "                         [3]Deposit\n";
	cout << "                         [4]check Balance\n";
	cout << "                         [5]log out \n";
}
void balance() {
	cout << "-----------------------------------------------\n";
	cout << "-----------------------------------------------\n";
	cout << "                      Check Balance Screen\n";
	cout << "----------------------------------------------------------\n";
	cout << "----------------------------------------------------------\n";

	if (search(acount, pin, client)) {

		cout << "Your Balance is" << client.Balance << endl;

	}
}
void Deposit() {
	int amount;
	cout << "------------------------------------------------------------\n";
	cout << "------------------------------------------------------------\n";
	cout << "                            Deposit Screen      \n";
	cout << "------------------------------------------------------------\n";
	cout << "------------------------------------------------------------\n";
	cout << "Enter  apositive deposit amount ?\n";
	cin >> amount;
	char c;
	cout << "Are you sure you want this transaction ?\n";
	cin >> c;
	if (toupper(c) == 'Y') {
		client.Balance += amount;
		updat(client);
		cout << "Your Balance is" << client.Balance << endl;
		cout << "Done successfully ,Now Balance:" << client.Balance << endl;

	}
}


void logout() {
	login();
}
void gobackmain() {
	cout << "press any key to back main menue..\n";
	system("pause>0");
	system("cls");
	Atmmainmenu();
}

void Atmmainmenu() {
	Atmscreen();
	int v;
	cout << "Choose What do you want do [1 to 5]?\n";
	cin >> v;
	if (search(acount, pin, client)) {
		switch (v) {
		case enchoos::quikwithdraww:
			system("cls");
			Quickwithdraw();
			gobackmain();
			break;
		case enchoos::normalwithdraw:
			system("cls");
			Normalwithdraw();
			gobackmain();
			break;
		case enchoos::deposit:
			system("cls");
			Deposit();
			gobackmain();
			break;
		case enchoos::balances:
			system("cls");
			balance();
			gobackmain();
			break;
		case enchoos::logoutt:
			system("cls");
			logout();
			gobackmain();
			break;
		}
	}
}

int main() {

	login();
	system("pause>0");
	return 0;
}

