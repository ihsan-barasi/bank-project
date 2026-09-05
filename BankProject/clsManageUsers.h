#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"
using namespace std;
class clsManageUsers : protected clsScreen
{
	enum enManageUsersMenuOptions { eListUsers = 1, eAddNewUser = 2,  eDeleteUser= 3,
		eUpdateUser = 4, eFindUser = 5, eMainMenu = 6 };

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Manage Users Menu...";
		system("pause>0");
		ShowManageUsersScreen();
	}

	static short _ReadMangeUsersMenuOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
		return Choice;
	}

	static void _ShowListUsersScreen()
	{
		clsUsersListScreen::ShowUsersList();
	}
	
	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddUserScreen();
	}
	
	static void _ShowDeleteUserScreen()
	{
		clsDeleteUserScreen::ShowDeleteUserScreen();
	}
	
	static void _ShowUpdateUserScreen()
	{
		clsUpdateUserScreen::ShowUpdateUserScreen();
	}
	
	static void _ShowFindUserScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}
	
	static void _PerformMangeUsersMenu(enManageUsersMenuOptions ManageUsersMenuOption)
	{
		switch (ManageUsersMenuOption)
		{
		case enManageUsersMenuOptions::eListUsers:
		{
			system("cls");
			_ShowListUsersScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersMenuOptions::eAddNewUser:
		{
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersMenuOptions::eDeleteUser:
		{
			system("cls");
			_ShowDeleteUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersMenuOptions::eUpdateUser:
		{
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		case enManageUsersMenuOptions::eFindUser:
		{
			system("cls");
			_ShowFindUserScreen();
			_GoBackToManageUsersMenu();
			break;
		}
		}
	}
public:
	static void ShowManageUsersScreen()
	{
		system("cls");
		if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
		{
			return;
		}
		_DrawScreenHeader("Manage Users Screen");
		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << "\t\t Manage Users Menu\n";
		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << "\t[1] List Users\n";
		cout << setw(37) << left << "" << "\t[2] Add New User\n";
		cout << setw(37) << left << "" << "\t[3] Delete User\n";
		cout << setw(37) << left << "" << "\t[4] Update User\n";
		cout << setw(37) << left << "" << "\t[5] Find User\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu\n";
		cout << setw(37) << left << "" << "=====================================\n";
		_PerformMangeUsersMenu((enManageUsersMenuOptions)_ReadMangeUsersMenuOption());
		
	}

};

