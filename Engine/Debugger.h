#pragma once
#include <iostream>
#include <Windows.h>

class Debugger
{
private:

	Debugger();
	~Debugger();
	HANDLE hConsole;
	WORD m_color;

public:

	enum ConsoleColor : WORD
	{

		COLOR_GREEN = 10,
		COLOR_WHITE = 15,
		COLOR_RED = 12

	};

	static auto& Get()
	{
		static Debugger instance;
		return instance;
	}

	void SetColor(const ConsoleColor& color);
	void Print(const std::string& line);
	void Print(const std::string& line, const ConsoleColor& color);

};