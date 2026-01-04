#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>


using namespace std;


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};


const string ClientsFileName = "Clients.txt";
sClient CurrentClient;



enum enMainMenueOptions {
	eQucikWithdraw = 1, eNormalWithDraw = 2, eDeposit = 3,
	eCheckBalance = 4, eExit = 5
};




vector<string> SplitString(string S1, string Delim)
{

	vector<string>vString;
	short pos = 0;
	string sWord = "";
	
	
	while (S1.find(Delim) != string::npos)
	{
		pos = S1.find(Delim);
		sWord = S1.substr(0, pos);

		vString.push_back(sWord);

		S1.erase(0, pos + Delim.length());

	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}


	return vString;
}




sClient  ConvertLineToRecord(string Line, string Seperator = "#//#")
{

	sClient Client;
	vector<string> vClientsData = SplitString(Line, Seperator);

	Client.AccountNumber = vClientsData[0];
	Client.PinCode = vClientsData[1];
	Client.Name = vClientsData[2];
	Client.Phone = vClientsData[3];
	Client.AccountBalance = stod(vClientsData[4]);


	return Client;
}



vector<sClient> LoadCleintsDataFromFile(string FileName)
{
	vector<sClient> vClients;

	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{

		string Line;
		sClient Client;


		while (getline(MyFile, Line))
		{

			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}



bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
	
	vector<sClient>vClients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClient C : vClients)
	{


		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{

			Client = C;

			return true;

		}

	}

	return false;

}



bool LoadClientInfo(string AccountNumber, string PinCode)
{

	return FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient);
}


void Login()
{

	bool LoginFaild = false;

	string AccountNumber, PinCode;

	
	do
	{

		system("cls");


		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";


		if (LoginFaild)
		{
			cout << "Invalid Account Number / PinCode!\n";
		}
		cout << "Enter Account Number? ";
		cin >> AccountNumber;

		
		cout << "Enter Pin? ";
		cin >> PinCode;

		LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFaild);

	//ShowMainMenue();

}




void ShowMainMenue()
{


	system("cls");

	
	cout << "===========================================\n";
	cout << "\t\tATM Main Menue Screen\n";
	cout << "===========================================\n";

	
	cout << "\t[1] Quick Withdraw.\n";      
	cout << "\t[2] Normal Withdraw.\n";     
	cout << "\t[3] Deposit\n";            
	cout << "\t[4] Check Balance.\n";       // خيار معرفة الرصيد
	cout << "\t[5] Logout.\n";              // خيار تسجيل الخروج
	cout << "===========================================\n";


	PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}




short ReadMainMenueOption()
{

	cout << "Choose what do you want to do? [1 to 5]? ";

	short Choice = 0;
	cin >> Choice;

	return Choice;

}


void PerfromMainMenueOption(enMainMenueOptions Option)
{

	switch (Option)
	{
	case enMainMenueOptions::eQucikWithdraw:
	{
		ShowQuickWithdrawScreen();
		break;
	}
	case enMainMenueOptions::eNormalWithDraw:
	{

		break;
	}
	case enMainMenueOptions::eDeposit:
	{

		break;
	}
	case enMainMenueOptions::eCheckBalance:
	{
		break;
	}
	case enMainMenueOptions::eExit:
	{

		Login();
		break;
	}
	default:
		cout << "Invalid Option!\n";
		break;

	}
}



void ShowQuickWithdrawScreen()
{

	system("cls");

	cout << "===========================================\n";
	cout << "\t\tQuick Withdraw Screen\n";
	cout << "===========================================\n";


	cout << "\t[1] 20\n";
	cout << "\t[2] 50\n";
	cout << "\t[3] 100\n";
	cout << "\t[4] 200\n";
	cout << "\t[5] 400\n";
	cout << "\t[6] 600\n";
	cout << "\t[7] 800\n";
	cout << "\t[8] 1000\n";
	cout << "\t[9] Exit\n"; // للخروج من شاشة السحب السريع

	cout << "===========================================\n";

	// هذا السطر يطلب من المستخدم اختيار مبلغ من القائمة
	cout << "Choose what do you want to withdraw? [1 to 9]? ";

	// هذا المتغير سيحمل رقم الاختيار
	short Choice = 0;
	cin >> Choice;

	// إذا اختار المستخدم رقم 9 فهذا يعني أنه يريد الخروج بدون سحب
	if (Choice == 9)
	{
		// العودة للقائمة الرئيسية
		ShowMainMenue();
		return;
	}


	int  WithdrawAmount = (Choice * 20);

	if (WithdrawAmount > 1000)
	{
		cout << "Invalid choice!\n";
		return;
	}
	if (CurrentClient.AccountBalance < WithdrawAmount)
	{
		cout << "\n\nYou do not have enough balance!\n";
		return;
	}


	CurrentClient.AccountBalance -= WithdrawAmount;


	cout << "\n\nWithdraw completed successfully.\n";
	cout << "Your new balance is: " << CurrentClient.AccountBalance << "\n";

	// الانتقال إلى القائمة الرئيسية مرة أخرى
	cout << "\nPress Enter to return to Main Menue...";
	system("pause>0");
	ShowMainMenue();


}



























int main()
{



	Login();








}