#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;
class clsTransferScreen : protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card : \n";
		cout << "________________________\n";
		cout << "Full Name       : " << Client.FullName() << endl;
		cout << "Account Number  : " << Client.AccountNumber() << endl;
		cout << "Balance         : " << Client.AccountBalance << endl;
		cout << "________________________\n";
	}
	static string _ReadAccountNumber(string Word)
	{
		cout << "\nPlease Enter Account Number to Transfer" << Word << ": ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nPlease Enter valid Account Number to Transfer" << Word << ": ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

	static double _ReadTransferAmount(clsBankClient FromClient)
	{
		double Amount;
		cout << "\nEnter Amount to Transfer: ";
		Amount = clsInputValidate::ReadDblNumber();
		while (Amount > FromClient.AccountBalance)
		{
			cout << "\nAmount Exceeds the Balance, Enter Amount to Transfer: ";
			Amount = clsInputValidate::ReadDblNumber();
		}
		
		return Amount;

	}
public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t Transfer Screen ");
		string FromAccountNumber, ToAccountNumber;
		FromAccountNumber = _ReadAccountNumber("From");
		clsBankClient FromClient = clsBankClient::Find(FromAccountNumber);
		_PrintClientCard(FromClient);
		ToAccountNumber = _ReadAccountNumber("To");
		clsBankClient ToClient = clsBankClient::Find(ToAccountNumber);
		_PrintClientCard(ToClient);
		double TransferAmount = _ReadTransferAmount(FromClient);
		cout << "\nAre you sure you want to perform this operation? y/n? ";
		char Answer = 'n';
		cin >> Answer;
		if (Answer == 'Y' || Answer == 'y')
		{
			if (FromClient.Transfer(TransferAmount, ToClient))
			{
				cout << "\nTransfer done successfully\n";
			}
			else
			{
				cout << "\nTransfer Failed \n";
			}
		}
		_PrintClientCard(FromClient);
		cout << endl;
		_PrintClientCard(ToClient);
		
	}
};

