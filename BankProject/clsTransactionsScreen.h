#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLog.h"
#include "clsScreen.h"

using namespace std;
class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenuOptions
    {
        Deposit =1 , Withdraw=2 , TotalBalances = 3 ,Transfer=4 ,TransferLog=5,MainMenu = 6
    };
    
    static void _ShowDepositScreen()
    {
        clsDepositScreen::ShowDepositScreen();
    }
    
    static void _ShowWithdrawScreen()
    {
		clsWithdrawScreen::ShowWithdrawScreen();
    }
    
    static void _ShowTotalBalancesScreen()
    {
		clsTotalBalancesScreen::ShowTotalBalancesScreen();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLog::ShowTransferLogScreen();
    }
    static void _GoBackToTransactionsMenu()
    {
        cout << "\n\nPress any key to go back to Transactions Menu...";
        system("pause>0");
        ShowTransactionsMenu();
    }

    static void _PerformTransactionsMenu(enTransactionsMenuOptions TransactionsMenuOption)
    {
        switch (TransactionsMenuOption)
        {
        case enTransactionsMenuOptions::Deposit:
        {
            system("cls");
            _ShowDepositScreen();
            _GoBackToTransactionsMenu();
        }
        case enTransactionsMenuOptions::Withdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionsMenu();
        }
        case enTransactionsMenuOptions::TotalBalances:
        {
            system("cls");
            _ShowTotalBalancesScreen();
            _GoBackToTransactionsMenu();
        }
        case enTransactionsMenuOptions::Transfer:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionsMenu();

        }
        case enTransactionsMenuOptions::TransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionsMenu();
        }

        case enTransactionsMenuOptions::MainMenu:
        {
            //Do nothing..
        }
        }
    }

    static short _ReadTransactionMenuOptions()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

public :
	static void ShowTransactionsMenu()
	{
        system("cls");
        if (!CheckAccessRights(clsUser::enPermissions::pTransactions))
        {
            return;
        }
		_DrawScreenHeader("\t Transactions Screen");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menu.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformTransactionsMenu((enTransactionsMenuOptions)_ReadTransactionMenuOptions());
	}
};

