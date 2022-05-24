#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace System;

string& Convector_String_to_string(String^ s, std::string& os);

// Перевод из типа "String" в "string"
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
	//Вектор содержит исходное число
	vector<int> a;
	//Исходная система счисления
	int iriginal;
public:
	//Конструктор, содержит 2 параметра: строка исходного числа, исходная система счисления
	Converters(string str, int original) {
		this->iriginal = original;
		//Заносит числа исходного числа в вектор
		for (int i = 0; i < str.length(); i++) {
			this->a.push_back(charToInt(str[i]));
		}
	}
	//Переводит символ в число, вместо некорректных символов возвращает -1
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
	//Переводит число в символ
	char intToChar(int c) {
		if (c >= 0 && c <= 9) {
			return c + '0';
		}
		else {
			return c + 'A' - 10;
		}
	}
	//Получает следующую цифру числа в новой системе счисления
	int nextNumber(int final) {
		int temp = 0;
		for (int i = 0; i < this->a.size(); i++) {
			temp = temp * this->iriginal + this->a[i];
			a[i] = temp / final;
			temp = temp % final;
		}
		return temp;
	}
	//Возвращает true - если массив состоит из одних нулей и false в противном случае
	bool zero() {
		for (int i = 0; i < this->a.size(); i++) {
			if (a[i] != 0) {
				return false;
			}
		}
		return true;
	}
	//Конвертирует исходное число в заданную систему счисления
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
// Функция которая переводит дробную часть из 10 СС в любую другую.
string double_to_another_sys(double number, int sys, int iterationCount = 9)
{
	// iterationCount - точность расчёта
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

// Функция для перевода дробной части из любой СС в десятичную
double to_some_system(string number, int sys)
{
	double result = 0;
	number.erase(number.find('.'), 1);
	int len = number.length();

	for (int i = 0; i < len; i++)
	{
		int num = number[i] - 0x30; // 0x30 - Шестнадцатеричный код для " 0 ".
		result += num * pow(sys, i * -1);
	}
	return result;
}
