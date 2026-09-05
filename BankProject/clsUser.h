#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsDate.h"
#include "clsString.h"
#include "clsPerson.h"
#include "clsUtil.h"
class clsUser : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions;
	bool _MarkedForDelete = false;

	struct stLoginRegister;
	string _PrepareLogInRecord(string Separator = "#//#")
	{
		string LoginRecord = "";
		LoginRecord += clsDate::GetSystemDateTimeString() + Separator;
		LoginRecord += UserName + Separator;
		LoginRecord += clsUtil::EncryptText(Password)+Separator;
		LoginRecord += to_string(Permissions);
		return LoginRecord;
	}

	static stLoginRegister _ConvertLineToLoginRegisterStructure(string Line)
	{
		stLoginRegister LoginRegister;
		vector <string> vLine = clsString::Split(Line, "#//#");
		LoginRegister.DateTime = vLine[0];
		LoginRegister.UserName = vLine[1];
		LoginRegister.Password = clsUtil::DecryptText(vLine[2]);
		LoginRegister.Permissions = stoi(vLine[3]);
		return LoginRegister;
	}
	static vector <stLoginRegister> _LoadLoginRegisterDataFromFile()
	{
		fstream MyFile;
		vector <stLoginRegister> vLoginRegisters;
		MyFile.open("LoginRegister.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				stLoginRegister LoginRegister = _ConvertLineToLoginRegisterStructure(Line);
				vLoginRegisters.push_back(LoginRegister);
			}
			MyFile.close();
		}
		return vLoginRegisters;
	}

	

	static clsUser _ConvertLineToUserObject(string Line)
	{
		vector <string> vUserData = clsString::Split(Line, "#//#");
		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3],
			vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
	}
	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}
	static string _ConvertObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string stUserRecord = "";
		stUserRecord += User.FirstName + Seperator;
		stUserRecord += User.LastName + Seperator;
		stUserRecord += User.Email + Seperator;
		stUserRecord += User.Phone + Seperator;
		stUserRecord += User.UserName + Seperator;
		stUserRecord += clsUtil::EncryptText(User.Password) + Seperator;
		stUserRecord += to_string(User.Permissions) + Seperator;
		return stUserRecord;
	}
	static vector <clsUser> _LoadUserDataFromFile()
	{
		fstream MyFile;
		vector <clsUser> vUsers;
		MyFile.open("Users.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				vUsers.push_back(User);
			}
			MyFile.close();
		}
		return vUsers;
	}
	static void _SaveUserDataToFile(vector <clsUser> vUsers)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsUser User : vUsers)
			{
				if (User.IsMarkedForDelete() == false)
				{
					string Record = _ConvertObjectToLine(User);
					MyFile << Record << endl;
				}
			}
			MyFile.close();
		}
	}
	void _Update()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUserDataFromFile();
		for (clsUser& U : vUsers)
		{
			if (U.UserName == _UserName)
			{
				U = *this;
				break;
			}
		}
		_SaveUserDataToFile(vUsers);
	}

	void _AddDataLineToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);
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

public:
	struct stLoginRegister
	{
		string DateTime;
		string UserName;
		string Password;
		int Permissions;
	};
	enum enPermissions { eAll = -1 , pListClients = 1 , pAddNewClient =2 , pDeleteClient = 4
						,pUpdateClients = 8 , pFindClient = 16  , pTransactions = 32 , pManageUsers = 64 , pLoginRegister = 128 , pCurrencyExchange = 256 };

	clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;
	}
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	bool IsMarkedForDelete()
	{
		return _MarkedForDelete;
	}
	
	void SetUserName(string UserName)
	{
		_UserName = UserName;
	}
	string GetUserName()
	{
		return _UserName;
	}
	__declspec(property(get = GetUserName, put = SetUserName)) string UserName;
	
	void SetPassword(string Password)
	{
		_Password = Password;
	}
	string GetPassword()
	{
		return _Password;
	}
	__declspec(property(get = GetPassword, put = SetPassword)) string Password;

	void SetPermissions(int Permissions)
	{
		_Permissions = Permissions;
	}
	int GetPermissions()
	{
		return _Permissions;
	}
	__declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

	static clsUser Find(string UserName)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}

			MyFile.close();

		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string UserName, string Password)
	{

		fstream MyFile;
		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}

			}

			MyFile.close();

		}
		return _GetEmptyUserObject();
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResults Save()
	{

		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return enSaveResults::svFaildEmptyObject;
			}
		}

		case enMode::UpdateMode:
		{
			_Update();
			return enSaveResults::svSucceeded;

			break;
		}

		case enMode::AddNewMode:
		{
			if (clsUser::IsUserExist(_UserName))
			{
				return enSaveResults::svFaildUserExists;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svSucceeded;
			}

			break;
		}
		}

	}

	static bool IsUserExist(string UserName)
	{

		clsUser User = clsUser::Find(UserName);
		return (!User.IsEmpty());
	}

	bool Delete()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUserDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.UserName == _UserName)
			{
				U._MarkedForDelete = true;
				break;
			}

		}

		_SaveUserDataToFile(_vUsers);

		*this = _GetEmptyUserObject();

		return true;

	}

	static clsUser GetAddNewUserObject(string UserName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	static vector <clsUser> GetUsersList()
	{
		return _LoadUserDataFromFile();
	}
	
	bool CheckAccessPermissions(enPermissions Permission)
	{
		if (this->Permissions == enPermissions::eAll)
		{
			return true;
		}
		if((this->Permissions & Permission) == Permission)
		{
			return true ;
		}
		else
		{
			return false;
		}
	}
	
	void RegisterLogIn()
	{

		string stDataLine = _PrepareLogInRecord();

		fstream MyFile;
		MyFile.open("LoginRegister.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	
	
	static vector <stLoginRegister> GetLoginRegisterList()
	{
		return _LoadLoginRegisterDataFromFile();
	}
	
	
};

