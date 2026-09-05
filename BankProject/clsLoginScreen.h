#pragma once
#include <iostream>
#include <fstream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsInputValidate.h"
#include "Global.h"

class clsLoginScreen : protected clsScreen
{
private:
	
	static bool _Login()
	{
		
		bool LoginFailed = false;
		string UserName, Password;
		short FailedLoginCount = 0;
		do
		{
			if(LoginFailed)
			{
				FailedLoginCount++;
				cout << "\nInvalid Username/Password!\n\n";
				cout << "You have " << 3-FailedLoginCount << " attempts left.\n";
			}
			if (FailedLoginCount == 3)
			{
				cout << "\nYou have exceeded the maximum number of attempts.\n\n";
				return false;
			}
			cout << "\nPlease Enter UserName: ";
			UserName = clsInputValidate::ReadString();
			cout << "\nPlease Enter Password: ";
			Password = clsInputValidate::ReadString();
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFailed = CurrentUser.IsEmpty();
			
		} while (LoginFailed);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenu();
		return true;
	}
public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t Login Screen ");
		return _Login();
	}
};

