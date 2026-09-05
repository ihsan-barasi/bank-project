#pragma once
#include <iostream>
#include <vector>
#include<string>
#include<fstream>
#include "clsPerson.h"
#include "clsString.h"
using namespace std;
class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0,UpdateMode=1 ,AddNewMode=2};

	struct stTransferLog;

	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkedForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line)
	{
		vector <string> vClientData = clsString::Split(Line, "#//#");
		
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3],
			vClientData[4], vClientData[5], stof(vClientData[6]));
	}
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static string _ConvertObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance) + Seperator;

		return stClientRecord;

	}
	static vector <clsBankClient> _LoadClientDateFromFile()
	{
		fstream MyFile;
		vector <clsBankClient> vClients;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);

			}
			MyFile.close();
		}
		return vClients;
	}
	static void _SaveClientDateToFile(vector <clsBankClient> vClients)
	{
		string Record;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C.MarkedForDelete() == false)
				{
					Record = _ConvertObjectToLine(C);
					MyFile << Record << endl;
				}
			}
			MyFile.close();
		}
	}
	
	void _Update()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientDateFromFile();
		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDateToFile(vClients);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertObjectToLine(*this));
	}

	string _PrepareTransferRecord(clsBankClient ToClient, double Amount, string Separator = "#//#")
	{
		string TransferRecord = "";
		TransferRecord += clsDate::GetSystemDateTimeString() + Separator;
		TransferRecord += AccountNumber() + Separator;
		TransferRecord += ToClient.AccountNumber() + Separator;
		TransferRecord += to_string(Amount) + Separator;
		TransferRecord += to_string(AccountBalance) + Separator;
		TransferRecord += to_string(ToClient.AccountBalance) + Separator;
		TransferRecord += CurrentUser.UserName;
		return TransferRecord;
	}

	void _RegisterTransferLog(clsBankClient ToClient, double Amount)
	{
		string stDataLine = _PrepareTransferRecord(ToClient, Amount);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}

	static stTransferLog _ConvertLineToTransferLogStructure(string Line)
	{
		stTransferLog TransferLog;
		vector <string> vLine = clsString::Split(Line, "#//#");
		TransferLog.Date = vLine[0];
		TransferLog.SourceClientAccountNumber = vLine[1];
		TransferLog.DestinationClientAccountNumber = vLine[2];
		TransferLog.Amount = vLine[3];
		TransferLog.SourceClientBalance = vLine[4];
		TransferLog.DestinationClientBalance = vLine[5];
		TransferLog.UserName = vLine[6];
		return TransferLog;
	}

public :

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}


	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	
	bool MarkedForDelete()
	{
		return _MarkedForDelete;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;

	

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}
		return _GetEmptyClientObject();
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists =2};

	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFaildEmptyObject;
		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResult::svSucceeded;
		}
		case enMode::AddNewMode:
		{
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceeded;
			}
			break;
		}
		}
	}

	bool Delete()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientDateFromFile();
		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkedForDelete = true;
				break;
			}
		}
		_SaveClientDateToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		return (!Client.IsEmpty());
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "",AccountNumber, "", 0);
	}

	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientDateFromFile();
	}

	static double GetTotalBalance()
	{
		double TotalBalance=0;
		vector <clsBankClient> vClients = _LoadClientDateFromFile();
		for (clsBankClient Client : vClients)
		{
			TotalBalance += Client.AccountBalance;
		}
		return TotalBalance;
	}

	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
	}
	}

	bool Transfer(double Amount, clsBankClient &ToClient)
	{
		if (AccountBalance < Amount)
		{
			return false;
		}
		else
		{
			this->Withdraw(Amount);
			ToClient.Deposit(Amount);
			Save();
			_RegisterTransferLog(ToClient, Amount);
		}
		return true;
	}
	struct stTransferLog
	{
		string Date;
		string SourceClientAccountNumber;
		string DestinationClientAccountNumber;
		string Amount;
		string SourceClientBalance;
		string DestinationClientBalance;
		string UserName;
	};
	static vector <stTransferLog> GetTransferLog()
	{
		fstream MyFile;
		vector <stTransferLog> vTransferLog;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				stTransferLog TransferLog = _ConvertLineToTransferLogStructure(Line);
				vTransferLog.push_back(TransferLog);
			}
			MyFile.close();
		}
		return vTransferLog;
	}
};

