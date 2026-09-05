#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsDepositScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient Client)
	{
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

	}

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public: 
    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\tDeposit Screen");
		string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
			cout << "\nClient with Account Number (" << AccountNumber << ") is not found, choose another one.\n";
			AccountNumber = _ReadAccountNumber();
        }
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
        cout << "\nPlease Enter deposit amount : ";
        double Amount = clsInputValidate::ReadDblNumber();
		cout << "\nAre you sure you want to perform this deposit? (y/n) ";
		char Answer = 'n';
		cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            Client.Deposit(Amount);
            cout << "\nAmount Deposited Successfully.\n";
			cout << "\nNew Balance Is: " << Client.AccountBalance;
        }
        else
        {
			cout << "\nOperation was canceled.";
        }

    }


};

