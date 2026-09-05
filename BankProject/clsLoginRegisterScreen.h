#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
using namespace std;
class clsLoginRegisterScreen : protected clsScreen
{
private:
	static void _PrintLoginRegisterRecordLine(clsUser::stLoginRegister LoginRegister)
	{
		cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegister.DateTime;
		cout << "| " << setw(20) << left << LoginRegister.UserName;
		cout << "| " << setw(20) << left << LoginRegister.Password;
		cout << "| " << setw(10) << left << LoginRegister.Permissions;

	}
public:
	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
		{
			return;
		}
		vector <clsUser::stLoginRegister> vLoginRegisters = clsUser::GetLoginRegisterList();
		string Title = "\t Login Register Screen ";
		string SubTitle = "\t    (" + to_string(vLoginRegisters.size()) + ") Login(s).";
		_DrawScreenHeader(Title, SubTitle);
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		cout << setw(8) << left << "" << "| " << left << setw(20) << "Date/Time";
		cout << "| " << left << setw(15) << "User Name";
		cout << "| " << left << setw(15) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
		if (vLoginRegisters.size() == 0)
		{
			cout << "There's No Logins Available\n";
		}
		else
		{
			for (clsUser::stLoginRegister LoginRegister : vLoginRegisters)
			{
				_PrintLoginRegisterRecordLine(LoginRegister);
				cout << endl;
			}
		}
	}
};

