#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
using namespace std;
class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "\nEnter First Name :";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter Last Name :";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email :";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone :";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Pin Code :";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter Account Balance :";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();

	}


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
public :
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}
		clsScreen::_DrawScreenHeader("\tUpdate Client");
		string AccountNumber;
		cout << "\nEnter Account Number : ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number is not Found , Choose Again : ";
			AccountNumber = clsInputValidate::ReadString();

		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		Client.Print();
		cout << "\nUpdate Client Info : ";
		_ReadClientInfo(Client);
		clsBankClient::enSaveResult SaveResult;
		SaveResult = Client.Save();
		switch (SaveResult)
		{
		case clsBankClient::enSaveResult::svSucceeded:
		{
			cout << "\nAccount Updated Successfully :-)";
			_PrintClient(Client);
			break;
		}
		case clsBankClient::enSaveResult::svFaildEmptyObject:
		{
			cout << "\nError account was not saved because it's Empty";
			break;
		}
		}
	}
};

