#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"
#include "Global.h"
class clsCurrencyMainScreen : protected clsScreen
{
private:
	enum enCurrencyMainMenuOptions {
		eListCurrencies = 1, eFindCurrency = 2, eUpdateCurrencyRate = 3,eCurrencyCalculator ,eExit = 5
	};

	static void _GoBackToCurrencyMenuScreen()
	{
		cout << "\n\nPress any key to go back to Currency Menu...";
		system("pause>0");
		ShowCurrencyMainMenuScreen();
	}
	
	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}
	
	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateCurrencyRateScreen()
	{
		clsUpdateCurrencyRateScreen::ShowUpdateCurrencyRateScreen();
	}

	static void _ShowCurrencyCalculatorScreen()
	{
		clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
	}

	static short _ReadCurrencyMenuOptions()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}

	static void _PerformCurrencyMenu(enCurrencyMainMenuOptions CurrencyMenuOption)
	{
		switch (CurrencyMenuOption)
		{
		case enCurrencyMainMenuOptions::eListCurrencies:
		{
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMenuScreen();
		}
		case enCurrencyMainMenuOptions::eFindCurrency:
		{
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMenuScreen();
		}
		case enCurrencyMainMenuOptions::eUpdateCurrencyRate:
		{
			system("cls");
			_ShowUpdateCurrencyRateScreen();
			_GoBackToCurrencyMenuScreen();
		}
		case enCurrencyMainMenuOptions::eCurrencyCalculator:
		{
			system("cls");
			_ShowCurrencyCalculatorScreen();
			_GoBackToCurrencyMenuScreen();
		}
		
		}
	}
public:
	static void ShowCurrencyMainMenuScreen()
	{
		system("cls");
		if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
		{
			return;
		}
		_DrawScreenHeader("\t Currency Main Menu ");
		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << "\t\t Currency Menu\n";
		cout << setw(37) << left << "" << "=====================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency\n";
		cout << setw(37) << left << "" << "\t[3] Update Date\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculator\n";
		cout << setw(37) << left << "" << "\t[5] Main Menu\n";
		cout << setw(37) << left << "" << "=====================================\n";
		_PerformCurrencyMenu((enCurrencyMainMenuOptions)_ReadCurrencyMenuOptions());
	}
};

