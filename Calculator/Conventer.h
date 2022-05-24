#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace System;

string& Convector_String_to_string(String^ s, std::string& os);

// ������� �� ���� "String" � "string"
std::string& Convector_String_to_string(String^ s, std::string& os)
{
	using namespace Runtime::InteropServices;
	const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
	return os;
}


class Converters {
private:
	//������ �������� �������� �����
	vector<int> a;
	//�������� ������� ���������
	int iriginal;
public:
	//�����������, �������� 2 ���������: ������ ��������� �����, �������� ������� ���������
	Converters(string str, int original) {
		this->iriginal = original;
		//������� ����� ��������� ����� � ������
		for (int i = 0; i < str.length(); i++) {
			this->a.push_back(charToInt(str[i]));
		}
	}
	//��������� ������ � �����, ������ ������������ �������� ���������� -1
	int charToInt(char c) {
		if (c >= '0' && c <= '9' && (c - '0') < this->iriginal) {
			return c - '0';
		}
		else {
			if (c >= 'A' && c <= 'Z' && (c - 'A') < this->iriginal) {
				return c - 'A' + 10;
			}
			else {
				return -1;
			}
		}
	}
	//��������� ����� � ������
	char intToChar(int c) {
		if (c >= 0 && c <= 9) {
			return c + '0';
		}
		else {
			return c + 'A' - 10;
		}
	}
	//�������� ��������� ����� ����� � ����� ������� ���������
	int nextNumber(int final) {
		int temp = 0;
		for (int i = 0; i < this->a.size(); i++) {
			temp = temp * this->iriginal + this->a[i];
			a[i] = temp / final;
			temp = temp % final;
		}
		return temp;
	}
	//���������� true - ���� ������ ������� �� ����� ����� � false � ��������� ������
	bool zero() {
		for (int i = 0; i < this->a.size(); i++) {
			if (a[i] != 0) {
				return false;
			}
		}
		return true;
	}
	//������������ �������� ����� � �������� ������� ���������
	string convertTo(int final) {
		vector<int> b;
		int size = 0;
		do {
			b.push_back(this->nextNumber(final));
			size++;
		} while (!this->zero());

		string sTemp = "";
		for (int i = b.size() - 1; i >= 0; i--) {
			sTemp += intToChar(b[i]);
		}
		return sTemp;
	}
};
// ������� ������� ��������� ������� ����� �� 10 �� � ����� ������.
string double_to_another_sys(double number, int sys, int iterationCount = 9)
{
	// iterationCount - �������� �������
	double integer;
	string result = "";
	for (int i = 0; i < iterationCount; i++)
	{
		number *= sys;
		number = modf(number, &integer);
		if (integer > sys)
		{
			result += "0";
			number = modf(number, &integer);
		}
		else
		{
			result += to_string((int)integer);
		}
	}
	return result;
}

// ������� ��� �������� ������� ����� �� ����� �� � ����������
double to_some_system(string number, int sys)
{
	double result = 0;
	number.erase(number.find('.'), 1);
	int len = number.length();

	for (int i = 0; i < len; i++)
	{
		int num = number[i] - 0x30; // 0x30 - ����������������� ��� ��� " 0 ".
		result += num * pow(sys, i * -1);
	}
	return result;
}