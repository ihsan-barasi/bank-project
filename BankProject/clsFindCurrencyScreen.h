#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "_____________________________\n";
		cout << "\nCountry    : " << Currency.Country();
		cout << "\nCode       : " << Currency.CurrencyCode();
		cout << "\nName       : " << Currency.CurrencyName();
		cout << "\nRate(1$) = : " << Currency.Rate();

		cout << "\n_____________________________\n";

	}
	
	static void _ShowResults(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");
		
		cout << "Find By: [1] Code or [2] Country ? ";
		short Choice = clsInputValidate::ReadShortNumberBetween(1, 2);
		if (Choice == 1)
		{
			cout << "\n\nPlease Enter Currency Code : ";
			string CurrencyCode = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
			_ShowResults(Currency);
			
		}
		else if (Choice == 2)
		{
			cout << "\n\nPlease Enter Country Name : ";
			string CountryName = clsInputValidate::ReadString();
			clsCurrency Currency = clsCurrency::FindByCountry(CountryName);
			_ShowResults(Currency);
			
		}
	}
};


