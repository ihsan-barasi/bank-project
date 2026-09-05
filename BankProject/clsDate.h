#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <ctime>
#include <iomanip>
#include<string>
#include<vector>
#include "clsString.h"
using namespace std;
class clsDate
{
	int _Year;
	short _Month;
	short _Day;
public:
	clsDate()
	{
		time_t t = time(0);
		tm* now = localtime(&t);
		_Day = now->tm_mday;
		_Month = now->tm_mon + 1;
		_Year = now->tm_year + 1900;
	}
	clsDate(string Date)
	{
		vector <string> vDate;
		vDate = clsString::Split(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, int Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(int Days, int Year)
	{
		clsDate Date = GetDateFromNumberOfDays(Days, Year);
		_Day = Date.Day;
		_Month = Date.Month;
		_Year = Date.Year;
	}
	static string GetSystemDateTimeString()
	{
		time_t t = time(0);
		tm* now = localtime(&t);

		short Day, Month, Year, Hour, Minute, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minute = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year) + " - "
			+ to_string(Hour) + ":" + to_string(Minute)
			+ ":" + to_string(Second));

	}

	void SetYear(int Year)
	{
		_Year = Year;
	}
	int GetYear()
	{
		return _Year;
	}
	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}
	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}
	__declspec(property(get = GetYear, put = SetYear))int Year;
	__declspec(property(get = GetMonth, put = SetMonth))short Month;
	__declspec(property(get = GetDay, put = SetDay))short Day;

	static string DateToString(clsDate Date)
	{
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}

	string DateToString()
	{
		return  DateToString(*this);
	}



	static bool IsLeapYear(int Year)
	{
		return(Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
	}
	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}

	static short NumberOfDayInMonth(int Year, short Month)
	{

		short DaysInMonth[] = { 31,0,31,30,31,30,31,31,30,31,30,31 };

		return Month < 1 || Month > 12 ? 0 : Month == 2 ? IsLeapYear(Year) ? 29 : 28 : DaysInMonth[Month - 1];
	}
	short NumberOfDayInMonth()
	{
		return NumberOfDayInMonth(_Year, _Month);
	}

	static short NameDayInWeek(int Year, short Month, short Day)
	{
		short A, Y, M, D;
		A = (14 - Month) / 12;
		Y = Year - A;
		M = Month + (12 * A) - 2;
		D = (Day + Y + (Y / 4) - (Y / 100) + (Y / 400) + ((31 * M) / 12)) % 7;
		return D;
	}
	short NameDayInWeek()
	{
		return NameDayInWeek(_Year, _Month, _Day);
	}

	static string MonthName(short Month)
	{
		string MonthName[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return MonthName[Month - 1];
	}
	string MonthName()
	{
		return MonthName(_Month);
	}

	static string DayName(short DayOrder)
	{
		string DayName[7] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		return DayName[DayOrder];
	}
	string DayName()
	{
		return DayName(NameDayInWeek());
	}

	static void CalendarMonth(int Year, short Month)
	{
		cout << "\n_________________" << MonthName(Month) << "_________________\n" << endl;
		cout << setw(5) << "Sun" << setw(5) << "Mon" << setw(5) << "Tue" << setw(5) << "Wed" << setw(5) << "Thu" << setw(5) << "Fri" << setw(5) << "Sat" << endl;
		short FirstDayName = NameDayInWeek(Year, Month, 1);
		for (short i = 0; i < FirstDayName; i++)
		{
			cout << setw(5) << " ";
		}
		for (short Day = 1; Day <= NumberOfDayInMonth(Year, Month); Day++)
		{
			cout << setw(5) << Day;
			if (NameDayInWeek(Year, Month, Day) == 6)
				cout << endl;


		}
		cout << "\n_________________________________________________________";
	}
	void CalendarMonth()
	{
		return CalendarMonth(_Year, _Month);
	}

	static void CalendarYear(int Year)
	{
		cout << "\n_________________" << Year << "_________________\n" << endl;
		for (short Month = 1; Month <= 12; Month++)
		{
			CalendarMonth(Year, Month);
			cout << endl;
		}
		cout << "\n_________________________________________________________";
	}
	void CalendarYear()
	{
		CalendarYear(_Year);
	}

	static int SumOfDaysFromBeginningOfYear(int Day, int Month, int Year)
	{

		int Sum = 0;
		for (short i = 1; i < Month; i++)
		{
			Sum += NumberOfDayInMonth(Year, i);
		}
		Sum += Day;
		return Sum;

	}
	int SumOfDaysFromBeginningOfYear()
	{
		return SumOfDaysFromBeginningOfYear(_Day, _Month, _Year);
	}

	static clsDate GetDateFromNumberOfDays(int Day, int Year)
	{
		clsDate Date;
		short Month = 1;
		while (Day > NumberOfDayInMonth(Year, Month))
		{
			Day -= NumberOfDayInMonth(Year, Month);
			Month++;
		}
		Date._Day = Day;
		Date._Month = Month;
		Date._Year = Year;
		return Date;
	}
	clsDate GetDateFromNumberOfDays()
	{
		return GetDateFromNumberOfDays(_Day, _Year);
	}

	static void AddDaysToDate(clsDate &Date, int DaysToAdd)
	{
		int Sum = SumOfDaysFromBeginningOfYear(Date.Day, Date.Month, Date.Year) + DaysToAdd;
		Date = GetDateFromNumberOfDays(Sum, Date.Year);
	}
	void AddDaysToDate(int DaysToAdd)
	{
		 AddDaysToDate(*this, DaysToAdd);
	}

	static bool IsDate1BeforeDate2(clsDate Data1, clsDate Data2)
	{
		if (Data1.Year < Data2.Year)
			return true;
		else if (Data1.Year == Data2.Year && Data1.Month < Data2.Month)
			return true;
		else if (Data1.Year == Data2.Year && Data1.Month == Data2.Month && Data1.Day < Data2.Day)
			return true;
		else
			return false;
	}
	bool IsDate1BeforeDate2(clsDate Date2)
	{
		return IsDate1BeforeDate2(*this, Date2);
	}

	static bool IsDate1EqualDate2(clsDate Date1, clsDate Date2)
	{
		return Date1.Year == Date2.Year ? (Date1.Month == Date2.Month ? (Date1.Day == Date2.Day ? true : false) : false) : false;
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeDate2(Date1, Date2) &&
			!IsDate1EqualDate2(Date1, Date2));
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(int Day, short Month, int Year)
	{
		return Day == NumberOfDayInMonth(Year, Month);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(_Day, _Month, _Year);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return Month == 12;
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}

	static clsDate AddOneDay(clsDate &Date)
	{
		if (IsLastDayInMonth(Date.Day, Date.Month, Date.Year))
		{
			Date.Day = 1;
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Year++;
			}
			else
				Date.Month++;
		}
		else
			Date.Day++;
		return Date;
	}
	void AddOneDay()
	{
		 *this = AddOneDay(*this);
	}

	

	static clsDate AddXDays(clsDate &Date, int NumberOfDay)
	{
		for (int i = 0; i < NumberOfDay; i++)
		{
			Date = AddOneDay(Date);
		}

		return Date;
	}
	void AddXDays(int NumberofDay)
	{
		 AddXDays(*this, NumberofDay);
	}

	static clsDate AddoneWeek(clsDate &Date)
	{
		return AddXDays(Date, 7);
	}
	void AddoneWeek()
	{
		 AddoneWeek(*this);
	}

	static clsDate AddXWeeks(clsDate &Date, int NumberOfWeeks)
	{
		return AddXDays(Date, NumberOfWeeks * 7);
	}
	void AddXWeeks(int NumberOfWeeks)
	{
		 AddXWeeks(*this, NumberOfWeeks);
	}

	static clsDate AddoneMonth(clsDate &Date)
	{
		if (IsLastMonthInYear(Date.Month))
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
			Date.Month++;
		if (Date.Day > NumberOfDayInMonth(Date.Year, Date.Month))
			Date.Day = NumberOfDayInMonth(Date.Year, Date.Month);
		return Date;
	}
	void AddoneMonth()
	{
		 AddoneMonth(*this);
	}

	static clsDate AddXMonths(clsDate &Date, int NumberOfMonths)
	{
		for (int i = 0; i < NumberOfMonths; i++)
		{
			Date = AddoneMonth(Date);
		}
		return Date;
	}
	void AddXMonths(int NumberOfMonths)
	{
		 AddXMonths(*this, NumberOfMonths);
	}

	static clsDate AddoneYear(clsDate &Date)
	{
		Date.Year++;
		return Date;
	}
	void AddoneYear()
	{
		 AddoneYear(*this);
	}


	static clsDate AddXYears(clsDate &Date, int NumberOfYears)
	{
		Date.Year += NumberOfYears;
		return 	Date;

	}
	void AddXYears(int NumberOfYears)
	{
		 AddXYears(*this, NumberOfYears);
	}

	static clsDate AddOneDecade(clsDate &Date)
	{
		Date.Year += 10;
		return Date;
	}
	void AddOneDecade()
	{
		 AddOneDecade(*this);
	}

	static clsDate AddXDecades(clsDate &Date, int NumberOfDecades)
	{
		Date.Year += NumberOfDecades * 10;
		return	Date;
	}
	void AddXDecades(int NumberOfDecades)
	{
		 AddXDecades(*this, NumberOfDecades);
	}

	static clsDate AddOneCentury(clsDate &Date)
	{
		return AddXYears(Date, 100);
	}
	void AddOneCentury()
	{
		 AddOneCentury(*this);
	}

	static clsDate AddOneMillennium(clsDate &Date)
	{
		return AddXYears(Date, 1000);
	}
	void AddOneMillennium()
	{
		 AddOneMillennium(*this);
	}

	static void Print(clsDate Date)
	{
		cout << Date.Day << "/" << Date.Month << "/" << Date.Year;
	}
	void Print()
	{
		Print(*this);
	}



	static clsDate DecreaseDateByOneDay(clsDate &Date)
	{
		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Month = 12;
				Date.Year--;
				Date.Day = 31;

			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDayInMonth(Date.Year, Date.Month);
			}
		}
		else
			Date.Day--;

		return Date;

	}
	void DecreaseDateByOneDay()
	{
		 DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDays(clsDate &Date, short Days)
	{
		for (short i = 0; i < Days; i++)
			Date = DecreaseDateByOneDay(Date);
		return Date;
	}
	void DecreaseDateByXDays(int Days)
	{
		 DecreaseDateByXDays(*this, Days);
	}

	static clsDate DecreaseDateByOneWeek(clsDate &Date)
	{
		return DecreaseDateByXDays(Date, 7);
	}
	void DecreaseDateByOneWeek()
	{
		 DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeeks(clsDate &Date, short Weeks)
	{
		for (short i = 0; i < Weeks; i++)
			Date = DecreaseDateByOneWeek(Date);
		return Date;
	}
	void DecreaseDateByXWeeks(short Weeks)
	{
		 DecreaseDateByXWeeks(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate &Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
			Date.Month--;
		if (Date.Day > NumberOfDayInMonth(Date.Year, Date.Month))
			Date.Day = NumberOfDayInMonth(Date.Year, Date.Month);

		return Date;

	}
	void DecreaseDateByOneMonth()
	{
		 DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonths(clsDate &Date, short Months)
	{
		for (short i = 0; i < Months; i++)
			Date = DecreaseDateByOneMonth(Date);
		return Date;
	}
	void DecreaseDateByXMonths(short Months)
	{
		 DecreaseDateByXMonths(*this, Months);
	}

	static clsDate DecreaseDateByOneYear(clsDate &Date)
	{
		Date.Year--;
		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year))
			Date.Day = 28;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		 DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYears(clsDate &Date, short Years)
	{
		Date.Year -= Years;
		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year))
			Date.Day = 28;
		return Date;
	}
	void DecreaseDateByXYears(short Years)
	{
		 DecreaseDateByXYears(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate &Date)
	{
		return DecreaseDateByXYears(Date, 10);
	}
	void DecreaseDateByOneDecade()
	{
		 DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecades(clsDate &Date, short Decades)
	{
		Date.Year -= Decades * 10;
		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year))
			Date.Day = 28;
		return Date;
	}
	void DecreaseDateByXDecades(short Decades)
	{
		 DecreaseDateByXDecades(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate &Date)
	{
		return DecreaseDateByXDecades(Date, 10);
	}
	void DecreaseDateByOneCentury()
	{
		 DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate &Date)
	{
		Date.Year -= 1000;
		if (Date.Month == 2 && Date.Day == 29 && !IsLeapYear(Date.Year))
			Date.Day = 28;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		 DecreaseDateByOneMillennium(*this);
	}

	static void SwapDate(clsDate& Data1, clsDate& Data2)
	{
		clsDate Temp;
		Temp.Day = Data1.Day;
		Temp.Month = Data1.Month;
		Temp.Year = Data1.Year;

		Data1.Day = Data2.Day;
		Data1.Month = Data2.Month;
		Data1.Year = Data2.Year;

		Data2.Day = Temp.Day;
		Data2.Month = Temp.Month;
		Data2.Year = Temp.Year;

	}
	void SwapDate(clsDate &Date2)
	{
		SwapDate(*this, Date2);
	}

	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;
		short flag = 1;
		if (!IsDate1BeforeDate2(Date1, Date2))
		{
			SwapDate(Date1, Date2);
			flag = -1;
		}
		while (Date1.Day != Date2.Day || Date1.Month != Date2.Month || Date1.Year != Date2.Year)
		{
			Date1 = AddOneDay(Date1);
			Days++;
		}
		return IncludeEndDay ? ++Days * flag : Days * flag;

	}
	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false)
	{
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}

	static bool IsEndOfWeek(clsDate Date)
	{
		return NameDayInWeek(Date.Year,Date.Month,Date.Day) == 5;
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}
	
	static bool IsaWeekEnd(clsDate Date)
	{
		short DayIndex =-NameDayInWeek(Date.Year, Date.Month, Date.Day);
		return (DayIndex == 0 || DayIndex == 6);
	}
	bool IsaWeekEnd()
	{
		return IsaWeekEnd(*this);
	}
	
	static bool IsBusinessDay(clsDate Date)
	{
		return !IsaWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return !IsaWeekEnd(*this);
	}
	
	static short DayUntilTheEndOfWeek(clsDate Date)
	{
		short Counter = 0;
		short DayOrder = NameDayInWeek(Date.Year, Date.Month, Date.Day);
		for (DayOrder; DayOrder < 7; DayOrder++)
		{
			if (IsEndOfWeek(Date))
				return Counter;
			Counter++;
			if (DayOrder == 6)
				DayOrder = -1;

		}
	}
	short DayUntilTheEndOfWeek()
	{
		return DayUntilTheEndOfWeek(*this);
	}
	
	static short DayUntilTheEndOfMonth(clsDate Date)
	{
		short Counter = 0;
		Counter = NumberOfDayInMonth(Date.Year, Date.Month) - Date.Day;
		return Counter;
	}
	short DayUntilTheEndOfMonth()
	{
		return DayUntilTheEndOfMonth(*this);
	}

	static int DayUntilTheEndOfYear(clsDate Date)
	{
		int Counter = 0;
		for (short Month = Date.Month; Month <= 12; Month++)
		{
			Counter += NumberOfDayInMonth(Date.Year, Month);
		}
		Counter -= Date.Day;
		return Counter;
	}
	int DayUntilTheEndOfYear()
	{
		return DayUntilTheEndOfYear(*this);
	}

	static int ActualVacationDays(clsDate StartDate, clsDate EndDate)
	{
		int Days = GetDifferenceInDays(StartDate, EndDate);
		int WeekEnds = 0;
		for (int i = 0; i < Days; i++)
		{
			if (IsaWeekEnd(StartDate))
				WeekEnds++;
			StartDate = AddOneDay(StartDate);
		}
		return Days - WeekEnds;
	}
	int ActualVacationDays(clsDate EndDate)
	{
		return ActualVacationDays(*this, EndDate);
	}

	static clsDate VacationReturnDate(clsDate StartDate, short VacationDays)
	{
		int DaysCount = 0;
		for (short i = 0; i < VacationDays; i++)
		{
			if (IsaWeekEnd(StartDate))
			{
				i--;
			}
			StartDate = AddOneDay(StartDate);
		}
		return StartDate;
	}
	clsDate VacationReturnDate(short VacationDays)
	{
		return VacationReturnDate(*this, VacationDays);
	}

	static bool IsValidDate(clsDate Date)
	{
		if (Date.Year < 1 || Date.Month < 1 || Date.Month > 12 || Date.Day < 1)
			return false;
		if (Date.Day > NumberOfDayInMonth(Date.Year, Date.Month))
			return false;
		return true;
	}
	bool IsValidDate()
	{
		return IsValidDate(*this);
	}
	enum enDateCompare { Before = -1, Equal = 0, After = 1 };

	static enDateCompare CompareDates(clsDate Date1, clsDate Date2)
	{
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;

		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;

		
		return enDateCompare::After;

	}

	enDateCompare CompareDates(clsDate Date2)
	{
		return CompareDates(*this, Date2);
	}

	static clsDate GetSystemDate()
	{
		clsDate Date;
		time_t t = time(0);
		tm* Now = localtime(&t);
		Date.Year = Now->tm_year + 1900;
		Date.Month = Now->tm_mon + 1;
		Date.Day = Now->tm_mday;
		return Date;
	}

};

