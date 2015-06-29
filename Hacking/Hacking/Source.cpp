#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <random>
#include <time.h>
#include <sstream>
#include <algorithm>
using namespace std;

string IntToString(int num)
{
	stringstream ss;
	ss << num;
	string str;
	ss >> str;
	return str;
}

/* key info*/
int key[] = { 4, 3, 1, 2, 6, 5};
int keysize = 6;
string GetKey()
{
	string keystr = IntToString(key[0]);
	for (int i = 1; i < keysize; ++i)
		keystr += " " + IntToString(key[i]);
	//cout << keystr << endl;
	return keystr;
}

int find(int num, int arr[])
{
	int i = 0;
	for (; arr[i] != num || i > 100; ++i);
	return i;
}
string remove_spaces(string str)
{
	for (int i = 0; i < str.size(); ++i)
		if (str[i] == ' ')
		str.erase(i, 1);
	return str; 
}
string Encrypt(string str)
{
	// Columnar | Rail fence | Play fair 

	string org = str; 
	str = remove_spaces(str);
	string cipher;
	int Globi = 0; 
	for (int i = 0; i < keysize; i++)
	{
		int order = find(i+1 , key);
		for (int j = order; j < str.size(); j += keysize, Globi++)
		{
			if (org[Globi] == ' ')
			{
				cipher += " "; 
				j -= keysize;
			}
			else
			{
				cipher += str[j];
			}
		}
	}

	return cipher;
}
void deleteChars(int times)
{
	for (int j = 0; j < times; ++j)
		cout << "\b \b";
}
void typing(string person, int time)
{
	string type[] = { ".", "..", "...", "...." };
	string out = person + " is typing ";
	cout << out;
	for (int i = 0; i < time; ++i)
	{
		cout << type[i % 4];
		Sleep(1000);

		if (i != time - 1)
		{
			deleteChars(type[i % 4].size());
		}
	}
	deleteChars(out.size() + type[(time - 1) % 4].size());
}
void Chat()
{
	fstream chat1("C:\\Hacking\\Release\\Chat1.txt");
	fstream chat2("C:\\Hacking\\Release\\Chat2.txt");

	string str1, str2;
	if (!chat1.is_open())
		cout << "fail to open" << endl;
	while (getline(chat1, str1))
	{
		typing("Person1", rand() % 10 + 5);
		cout << "Person 1: " << Encrypt(str1) << endl;

		getline(chat2, str2);
		typing("Person2", rand() % 10 + 5);
		cout << "Person 2: " << str2 << endl;

		// remain todo
		// check if the system has been hacked to redirect the conversation to the hacker
	}

	chat1.close();
	chat2.close();

}
int Hack()
{
	string key;
	for (int i = 0; i < 3; ++i)
	{
		getline(cin, key);

		if (key == GetKey())
		{
			cout << "you have been logged in Successfully" << endl;
			string msg;
			getline(cin, msg);

			// remain todo
			// he should type the message here and send it to the chat window 
			// modify the text files

			cout << "Person 2: " << Encrypt("my password is PASSWORD") << endl;
			return 1;
		}
		else
			cout << "Access Denied" << endl;
	}
	return 0;
}
int SetFontSize(HANDLE windowHandle, COORD size)
{
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	font.dwFontSize = size;

	if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	return 1;
}
int main(int argc, char* argv[])
{
	HANDLE outcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD size;
	size.X = 10; size.Y = 18;

	SetFontSize(outcon, size);
	if (argc == 1)
	{
		HWND console = GetConsoleWindow();
		MoveWindow(console, 0, 0, 800, 600, TRUE);

		system("start \"Hacker\" C:\\Hacking\\Release\\Hacking.exe 1");
		cout << "chat will appear in this window ..." << endl;
		cout << "press enter when you are ready" << endl;
		getline(cin, string());
		Chat();
	}
	else
	{
		HWND console = GetConsoleWindow();
		MoveWindow(console, 400, 500, 600, 200, TRUE);

		cout << "write the key here ..." << endl;
		cout << "Key : ";
		Hack();
		system("pause");
	}
}