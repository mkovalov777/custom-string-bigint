#define _CRT_SECURE_NO_WARNINGS 
#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

class String
{
protected:
	char* str;
	int maxLength;
public:
	String() {} // default constructor
	String(const String &from) //copy constructor
	{
		maxLength = from.maxLength;
		delete[] str; // для випадку коли рядок уже заданий.
		str = new char[strlen(from.str) + 1];
		strcpy(str, from.str);
	} 
	String(char* s, int maximumLength) //custom constructor
	{
		maxLength = maximumLength;
		if (strlen(s) <= maxLength) 
		{
			str = new char[strlen(s) + 1];
			strcpy(str,s);
		}
		else // maximum length limit
		{
			str = new char[maxLength];
			for (int i = 0; i < maxLength; i++)
				str[i] = s[i];
			str[maxLength] = '\0';
		}
	}
	virtual void testOfLateBinding() // just function to test late binding
	{
		cout << "It's String class function" << endl;
	}
	void SetData(char* s, int maxLen) //analogy to custom constructor
	{
		maxLength = maxLen;
		if (strlen(s) <= maxLength) 
		{
			str = new char[strlen(s) + 1];
			strcpy(str, s);
		}
		else
		{
			str = new char[maxLength];
			for (int i = 0; i < maxLength; i++)
				str[i] = s[i];
			str[maxLength] = '\0';
		}

	}
	char* GetStr() // get string
	{
		return str;
	}
	int getMaxLength() //get max length
	{
		return maxLength;
	}
	friend ostream& operator<<(ostream& os,String& obj) // overloaded output operator
	{
		os << obj.str;
		return os;
	}
	friend istream& operator>>(istream& is,String& obj) // overloaded input operator
	{
		char tmp[50];
		cin >> tmp;
		tmp[strlen(tmp)] = '\0';
		delete[] obj.str;
		obj.str = new char[strlen(tmp) + 1];
		strcpy(obj.str, tmp);
		obj.maxLength = strlen(obj.str);
		return is;
	}
	String& operator=(const String& obj) // overloaded "=" operator
	{
		maxLength = obj.maxLength;
		delete[] str;
		str = new char[strlen(obj.str)+1];
		strcpy(str, obj.str);
		return *this;
	}
	virtual void operator+ (const String& obj) // overloaded "+" operator for concatenation
	{
		String tmp;
		tmp.maxLength = maxLength + obj.maxLength;
		tmp.str = new char[strlen(str) + strlen(obj.str)+1];
		strcpy(tmp.str, str);
		strcat(tmp.str, obj.str);
		cout << str << " + " << obj.str << " = " << tmp << endl;
		*this = tmp;
	}
	void operator- (const String& obj) // overloaded operator "-" for deleting substring
	{
		char* tmp;
		tmp = strstr(str, obj.str);
		if (tmp != nullptr)
		{
			// just output of how does it work
			cout << str << " - " << obj.str << " = "; 
			strcpy(tmp, tmp + strlen(obj.str));
			cout << str << endl; 
		}
		else cout << "Error" << endl;
	}
	void operator* (const String& obj) // overloaded "*" operator for searching substring
	{
		char* tmp;
		tmp = strstr(str, obj.str);
		cout << "Searching " << obj.str << " in " << str << endl;
		// just showing how does it work
		if (tmp!=nullptr)
		{
			cout << "There is " << obj.str << " in " << str << endl << endl;
		}
		else
			cout << "There is no " << obj.str << " in " << str << endl << endl;
	}
	virtual ~String() { delete[] str; } // віртуальний деструктор
};
class HugeIntegers :public String // our bigintegers is implemented from our custom string class
{
public:
	HugeIntegers() {} // default constructor
	HugeIntegers(char* s, int maximumLength) //custom constructor
	{
		maxLength = maximumLength;
		if (strlen(s) <= maxLength)
		{
			str = new char[strlen(s) + 1];
			strcpy(str, s);
		}
		else // max length limit
		{
			str = new char[maxLength];
			for (int i = 0; i < maxLength; i++)
				str[i] = s[i];
			str[maxLength] = '\0';
		}
	}
	HugeIntegers(const HugeIntegers &from) //copy constructor
	{
		maxLength = from.maxLength;
		delete[] str; // для випадку коли рядок уже заданий.
		str = new char[strlen(from.str) + 1];
		strcpy(str, from.str);
	}
	void testOfLateBinding() // late binding test
	{
		cout << "It's HugeIntegers class function" << endl;
	} 
	virtual void operator + (HugeIntegers &obj) // overloaded "+" for addition of numbers
	{
		char* result;
		int rest = 0, number1 = 0, number2 = 0, resultNumber = 0;
		if (strlen(str) > strlen(obj.str)) // у випадку якщо перший операнд
		{
			int lengthDifference = strlen(str) - strlen(obj.str);
			char* tmp = new char[strlen(str) + 1];
			tmp[strlen(str)] = '\0';
			for (int i = 0; i < strlen(tmp); i++)
			{
				if (i >= lengthDifference) tmp[i] = obj.str[i - lengthDifference];
				else tmp[i] = '0';
			}
			result = new char[strlen(str) + 2];
			result[strlen(str)+1] = '\0';
			result[0] = '0';
			for (int i = strlen(str) - 1 ; i >= 0; i--)
			{
				number1 = str[i] - '0';
				number2 = tmp[i] - '0';
				resultNumber = number1 + number2 + rest;
				rest = 0;
				if (resultNumber >= 10)
				{
					rest = 1;
					resultNumber %= 10;
				}
				result[i+1] = resultNumber + '0';
			}
			if (rest != 0)
				result[0] = '1';
			else
				result++;
			cout << str << " + " << obj.str << " = " << result << endl;
			str = result;
		}
		if (strlen(str) == strlen(obj.str))
		{
			result = new char[strlen(str) + 2];
			result[strlen(str) + 1] = '\0';
			result[0] = '0';
			for (int i = strlen(str) - 1; i >= 0; i--)
			{
				number1 = str[i] - '0';
				number2 = obj.str[i] - '0';
				resultNumber = number1 + number2 + rest;
				rest = 0;
				if (resultNumber >= 10)
				{
					rest = 1;
					resultNumber %= 10;
				}
				result[i + 1] = resultNumber + '0';
			}
			if (rest != 0)
				result[0] = '1';
			else
				result++;
			cout << str << " + " << obj.str << " = " << result << endl;
			str = result;
		}
		if (strlen(str) < strlen(obj.str))
		{
			int lengthDifference = strlen(obj.str)-strlen(str);
			char* tmp = new char[strlen(obj.str) + 1];
			tmp[strlen(obj.str)] = '\0';
			for (int i = 0; i < strlen(tmp); i++)
			{
				if (i >= lengthDifference) tmp[i] = str[i - lengthDifference];
				else tmp[i] = '0';
			}
			result = new char[strlen(obj.str) + 2];
			result[strlen(obj.str) + 1] = '\0';
			result[0] = '0';
			for (int i = strlen(obj.str) - 1; i >= 0; i--)
			{
				number1 = tmp[i] - '0';
				number2 = obj.str[i] - '0';
				resultNumber = number1 + number2 + rest;
				rest = 0;
				if (resultNumber >= 10)
				{
					rest = 1;
					resultNumber %= 10;
				}
				result[i + 1] = resultNumber + '0';
			}
			if (rest != 0)
				result[0] = '1';
			else
				result++;
			cout << str << " + " << obj.str << " = " << result << endl;
			str = result;

		}
	}

	// compare operators
	bool operator > (const HugeIntegers& obj) 
	{
		if (strlen(str) > strlen(obj.str)) return true;
		else 
			if (strlen(str) == strlen(obj.str))
			{
				int number1 = 0, number2 = 0;
				for (int i = 0; i < strlen(str); i++)
				{
					number1 = str[i] - '0';
					number2 = obj.str[i] - '0';
					if (number1 > number2) return true;
				}
			}
			else return false;
	} 
	bool operator >= (const HugeIntegers& obj) 
	{
		if (strlen(str) > strlen(obj.str)) return true;
		else
			if (strlen(str) == strlen(obj.str))
			{
				int number1 = 0, number2 = 0, count = 0;
				for (int i = 0; i < strlen(str); i++)
				{
					number1 = str[i] - '0';
					number2 = obj.str[i] - '0';
					if (number1 > number2) return true;
					if (number1 == number2) count++;
				}
				if (count == strlen(str)) return true;
			}
			else return false;
	}
	bool operator < (const HugeIntegers& obj) 
	{
		if (strlen(str) < strlen(obj.str)) return true;
		else
			if (strlen(str) == strlen(obj.str))
			{
				int number1 = 0, number2 = 0;
				for (int i = 0; i < strlen(str); i++)
				{
					number1 = str[i] - '0';
					number2 = obj.str[i] - '0';
					if (number1 < number2) return true;
				}
			}
			else return false;
	}
	bool operator <= (const HugeIntegers& obj) 
	{

		if (strlen(str) < strlen(obj.str)) return true;
		else
			if (strlen(str) == strlen(obj.str))
			{
				int number1 = 0, number2 = 0, count = 0;
				for (int i = 0; i < strlen(str); i++)
				{
					number1 = str[i] - '0';
					number2 = obj.str[i] - '0';
					if (number1 < number2) return true;
					if (number1 == number2) count++;
				}
				if (count == strlen(str)) return true;
			}
			else return false;
	}
	
	virtual ~HugeIntegers(){ }
};
class HugeIntegersArray // just array of hugeIntegers numbers, was created for iterator class test
{
	HugeIntegers* array;
	HugeIntegers summ;
	int size;
public:
	class Iterator // клас ітератор
	{
	public:
		HugeIntegers* i;
		Iterator(HugeIntegers *i1 = 0) { i = i1; }
		Iterator& operator=(Iterator& i1) { i = i1.i; return *this; }
		Iterator& operator++() { ++i; return *this; }
		Iterator& operator++(int) { i++; return *this; }
		Iterator& operator--() { --i; return *this; }
		Iterator& operator--(int) { i--; return *this; }
		Iterator operator+(int n) { return Iterator(i + n); }
		Iterator operator-(int n) { return Iterator(i - n); }
		Iterator& operator+=(int n) { i += n; return *this; }
		Iterator& operator-=(int n) { i -= n; return *this; }
		bool operator==(Iterator& i1) { return i == i1.i; }
		bool operator!=(Iterator& i1) { return i != i1.i; }
		bool operator<(Iterator& i1) { return i < i1.i; }
		bool operator>(Iterator& i1) { return i > i1.i; }
		bool operator<=(Iterator& i1) { return i <= i1.i; }
		bool operator>=(Iterator& i1) { return i >= i1.i; }
	};
	Iterator end()
		{
			return Iterator(array+size-1);
		}
	Iterator begin()
		{
			return Iterator(array);
		}
	HugeIntegersArray(const int n) 
	{
		size = n;
		array = new HugeIntegers[n];
		summ.SetData("0", 125);
	}
	void input() // input of numbers
	{
		for (int i = 0; i < size; i++)
		{
			char tmp[50];
			cin >> tmp;
			tmp[strlen(tmp)] = '\0';
			array[i].SetData(tmp, strlen(tmp));
		}
	}
	void summOfArray() // summ of array
	{
		for (HugeIntegersArray::Iterator it = begin(); it != end(); it++)
			summ + *it.i;
		cout << "Summ of array=" << summ << endl;
	}

	virtual ~HugeIntegersArray() {} // віртуальний деструктор
};

int main()
{
	
	String str("STRING", 6);
	String str2("GNIRTS", 6);
	String str3;
	String str4=String(str);      // test of copy constructor
	cout << str4 << endl << endl;
	
	// i/o test
	cin >> str3;				  
	cout << str3 << endl << endl; 

	str2 + str;                   // "+" test (string)
	cout << str2 << endl << endl; 
	str2*str; // "*" test					  
	
	str2 - str;	 // "-" test (string)
	cout << str2 << endl << endl; 
	str2*str;                     
	
	
	HugeIntegers int1("9123451612396979123412356", 26);
	HugeIntegers int2("912394951924969619123999", 25);
	int1 + int2; // "+" test (hugeInt)
	HugeIntegers int3("912341234521231235123124", 25);
	HugeIntegers int4("912312312312312312312312", 25);
	int3 + int4; // "+" test (hugeInt)
	HugeIntegers int5("123123151241246123123", 22);
	HugeIntegers int6("31231231231246123123123", 24);
	// compare operators test
	cout << (int6 > int5) << endl;
	cout << (int5 > int6) << endl;
	cout << (int6 < int5) << endl;
	cout << (int5 < int6) << endl;
	HugeIntegers int7("11111111111111111111111", 24);
	HugeIntegers int8("11111111111111111111111", 24);
	cout << (int7 >= int8) << endl; 
	cout << (int7 <= int8) << endl;
	

	//late binding test
	HugeIntegers test;
	String &ref = test;
	ref.testOfLateBinding();

	//input and summ of hugeIntegers array
	HugeIntegersArray array1(5);
	array1.input();
	array1.summOfArray();
	system("pause");
	return 0;
}
