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



enum enMainMenuOptions {
	eQuickWithdraw = 1, eNormalWithDraw = 2, eDeposit = 3,
	eCheckBalance = 4, eExit = 5
};





void ShowQuickWithdrawScreen();
short ReadMainMenuOption();
void PerformMainMenueOption(enMainMenuOptions Option);
void ShowMainMenu();
void PerformNormalWithdrawOption();
void PerformDepositOption();




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



sClient ConvertLineToRecord(string Line, string Seperator = "#//#")
{
	sClient Client;

	vector<string> vClientsData = SplitString(Line, Seperator);

	if (vClientsData.size() < 5)
		return Client;

	Client.AccountNumber = vClientsData[0];
	Client.PinCode = vClientsData[1];
	Client.Name = vClientsData[2];
	Client.Phone = vClientsData[3];
	Client.AccountBalance = stod(vClientsData[4]);

	return Client;
}









string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
	return

		Client.AccountNumber + Seperator +
		Client.PinCode + Seperator +
		Client.Name + Seperator + 
		Client.Phone + Seperator + 
		to_string(Client.AccountBalance);
}




vector<sClient> LoadClientsDataFromFile(string FileName)
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
			if (Line == "")
				continue;

			Client = ConvertLineToRecord(Line);


			if (Client.AccountNumber == "")
				continue;

			vClients.push_back(Client);

		}

		MyFile.close();
	}

	return vClients;
}







void SaveClientsDataToFile(string FileName, vector<sClient> vClient)
{

	fstream MyFile;

	MyFile.open(FileName, ios::out);


	if (MyFile.is_open())
	{

		for (sClient C : vClient)
		{
			MyFile << ConvertRecordToLine(C) << endl;
		}


		MyFile.close();

	}
}




void UpdateClientBalance()
{

	vector<sClient> vClients = LoadClientsDataFromFile(ClientsFileName);


	for (sClient& C : vClients)
	{

		if (C.AccountNumber == CurrentClient.AccountNumber)
		{

			C.AccountBalance = CurrentClient.AccountBalance;
			break;
		}
	}

	SaveClientsDataToFile(ClientsFileName, vClients);
}





bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{

	vector<sClient>vClients = LoadClientsDataFromFile(ClientsFileName);

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


}






void ShowMainMenu()
{
	while (true)
	{

		system("cls");

		cout << "===========================================\n";
		cout << "\t\tATM Main Menu Screen\n";
		cout << "===========================================\n";


		cout << "\t[1] Quick Withdraw.\n";
		cout << "\t[2] Normal Withdraw.\n";
		cout << "\t[3] Deposit\n";
		cout << "\t[4] Check Balance.\n";
		cout << "\t[5] Logout.\n";
		cout << "===========================================\n";



		enMainMenuOptions Option = (enMainMenuOptions)ReadMainMenuOption();

		if (Option == enMainMenuOptions::eExit)
			return;


		PerformMainMenueOption(Option);

	}
}




short ReadMainMenuOption()
{

	cout << "Choose what do you want to do? [1 to 5]? ";

	short Choice = 0;
	cin >> Choice;

	return Choice;

}




void ShowNormalWithdrawScreen()
{

	system("cls");

	cout << "===========================================\n";
	cout << "\t\tNormal Withdraw Screen\n";
	cout << "===========================================\n";
	PerformNormalWithdrawOption();
}




bool ConfirmTransaction()
{

	char Answer = 'n';

	cout << "\nAre you sure you want to perform this transaction? y/n ?";

	cin >> Answer;


	if (Answer == 'y' || Answer == 'Y')
		return true;


	return false;
}





int ReadWithdrawAmount()
{

	int Amount;

	cout << "Enter an amount multiple of 5's ? ";
	cin >> Amount;


	while (Amount % 5 != 0)
	{

		cout << "Enter an amount multiple of 5's ? ";
		cin >> Amount;
	}

	return Amount;
}





void PerformNormalWithdrawOption()
{

	int WithDrawAmount = ReadWithdrawAmount();


	if (CurrentClient.AccountBalance < WithDrawAmount)
	{
		cout << "\n\nYou do not have enough balance!\n";
		system("pause>0");
		return;
	}
	if (!ConfirmTransaction())
		return;


	CurrentClient.AccountBalance -= WithDrawAmount;
	UpdateClientBalance();


	cout << "\n\nWithDraw completed successfully.\n";
	cout << "Your new balance is: " << CurrentClient.AccountBalance << "\n";

	system("pause>0");
}





void ShowDepositScreen()
{

	system("cls");
	cout << "===========================================\n";
	cout << "\t\tDeposit Screen\n";
	cout << "===========================================\n";
	PerformDepositOption();

}



double ReadDepositAmount()
{
	double Amount;

	cout << "Enter a positive deposit amount: ";
	cin >> Amount;


	while (Amount <= 0)
	{
		cout << "Enter a positive deposit amount: ";
		cin >> Amount;
	}

	return Amount;
}






void PerformDepositOption()
{

	double DepositAmount = ReadDepositAmount();

	if (!ConfirmTransaction())

		return;

	CurrentClient.AccountBalance += DepositAmount;
	UpdateClientBalance();


	cout << "\n\nDeposit completed successfully.\n";
	cout << "Your new balance is: " << CurrentClient.AccountBalance << "\n";
	system("pause>0");

}





void ShowCheckBalanceScreen()
{

	system("cls");

	cout << "===========================================\n";
	cout << "\t\tCheck Balance Screen\n";
	cout << "===========================================\n";

	cout << "Your Balance is: " << CurrentClient.AccountBalance << "\n";
	system("pause>0");
}




void PerformMainMenueOption(enMainMenuOptions Option)
{

	switch (Option)
	{
	case enMainMenuOptions::eQuickWithdraw:
	{
		ShowQuickWithdrawScreen();
		break;
	}
	case enMainMenuOptions::eNormalWithDraw:
	{
		ShowNormalWithdrawScreen();
		break;
	}
	case enMainMenuOptions::eDeposit:
	{
		ShowDepositScreen();
		break;
	}
	case enMainMenuOptions::eCheckBalance:
	{
		ShowCheckBalanceScreen();
		break;
	}
	case enMainMenuOptions::eExit:
	{
	
		return;
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
	cout << "\t[9] Exit\n";
	cout << "===========================================\n";



	cout << "Choose what do you want to withdraw? [1 to 9]? ";


	short Choice = 0;
	cin >> Choice;

	if (Choice == 9)
	{

		return;
	}


	int WithdrawAmount = 0;


	switch (Choice)
	{
		case 1: WithdrawAmount = 20; break;
		case 2: WithdrawAmount = 50; break;
		case 3: WithdrawAmount = 100; break;
		case 4: WithdrawAmount = 200; break;
		case 5: WithdrawAmount = 400; break;
		case 6: WithdrawAmount = 600; break;
		case 7: WithdrawAmount = 800; break;
		case 8: WithdrawAmount = 1000; break;
		default:

		cout << "Invalid choice!\n";
		system("pause>0");
		return;
	}


	if (CurrentClient.AccountBalance < WithdrawAmount)
	{
		cout << "\n\nYou do not have enough balance!\n";
		system("pause>0");
		return;
	}


	CurrentClient.AccountBalance -= WithdrawAmount;
	UpdateClientBalance();


	cout << "\n\nWithdraw completed successfully.\n";
	cout << "Your new balance is: " << CurrentClient.AccountBalance << "\n";


	cout << "\nPress Enter to return to Main Menue...";
	system("pause>0");

}





int main()
{
	while (true)
	{
		Login();
		ShowMainMenu();
	}
	return 0;
}
