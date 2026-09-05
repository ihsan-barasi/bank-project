#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
class clsDeleteClientScreen : protected clsScreen
{
private:
	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card : \n";
		cout << "________________________\n";
		cout << "First Name      : " << Client.FirstName << endl;
		cout << "Last Name       : " << Client.LastName << endl;
		cout << "Email           : " << Client.Email << endl;
		cout << "Phone Number    : " << Client.Phone << endl;
		cout << "Account Number  : " << Client.AccountNumber() << endl;
		cout << "Password        : " << Client.PinCode << endl;
		cout << "Balance         : " << Client.AccountBalance << endl;
		cout << "________________________\n";

	}

public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("\tDelete Client");
		string AccountNumber;
		cout << "Enter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not Found , Choose Again : ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		char Again = 'y';
		cout << "\nAre you sure you want to delete this client y/n? ";
		cin >> Again;
		if (Again == 'y' || Again == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
	}

};

