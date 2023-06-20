// HomeWork template project v 4.0 // 20.06.2023 //

/*
Основы ООП на языке С++
Перегрузка унарных операторов
Задание
В реализованном ранее классе дробь реализовать перегрузку следующих унарных
поераторов :
инкримент "++"
декримент "--"
унарный минус "-"
унарный плюс "+"
Обратить внимание на конструкторы класса и те которые представляются нужными отметить
как explicit.выбор пояснить комментарием
Добавить в класс методы : -получения целой части от дроби - получения дробной части от
дроби - сокращение дроби(уменьшение знаменателя до возможного минимума) - получение
обратной дроби
``` задание сдаётся в виде ссылки на репозиторий либо подготовленным архивом проекта
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <time.h>
#include <algorithm>
#include <conio.h>
//#include <array>
//My own headers
#include "Service functions.h"
#include "MainMenu.h"
#include "Fraction.h"
#include "ComplexNumber.h"



// Homework OOP 4 ----------------------------------------------------	


// защита от нуля в знаменателе - assert

//Task 1 Fractions class demo with overloaded operators:\nBinary: + | - | / | * \nUnary: + | - | ++ | --
void Task_1(std::string name_of_task)
// Изначально реализовывал класс Fraction с внешним вектором и обработкой выбора пользователя не внутри класса (в дальнейшем делал все внутри)
// поэтому выглядит громоздко и необходимо часто передавать параметр с указателем на вектор (хотя может можно сделать константный статический указатель на вектор?)
// Переделывать сейчас слишком объемно кажется - буду тянуть с этим классом и дальше не удачную архитектуру в учебных целях
{
	//Вариант хранения объектов класса Fraction в векторе объектов вне класса (из точки вызова, с передачей указателя на этот вектор)
	std::vector<Fraction*> Available_fractions;

	// вот такой костыль родился на третьей итерации ДЗ про дроби, дабы избавиться от частой передачи указателя на вектор с объектами
	// старые функции переделывать не стал
	Fraction::Set_static_pointer_Available_fractions(Available_fractions);

	const int list_size = 5; //наполняем объектами память
	for (int i = 0; i < list_size; i++)	{ Fraction& new_fraction = *new Fraction(Get_Random(1,100), Get_Random(1, 100)); }
		
	do
	{	
		system("cls");
		std::cout << "***\t" << name_of_task << "\n";

		Fraction::ShowAvailableFractions();
		Fraction::ShowMethods();

		int action = Fraction::UserChoiceHandle();					
		if (action <= 4 && action>0)//разделеям бинарные и унарные операции
		{
			Fraction& Operand_1 = Fraction::Choose_Operand_Handle(1);
			Fraction& Operand_2 = Fraction::Choose_Operand_Handle(2);

			//switch (Fraction::UserChoiceHandle(_getch())))
			//switch (Fraction::UserChoiceHandle())
			switch (action)
			{
			case 1: Operand_1 + Operand_2; break;
				// Няглядная демонстрация упрощения кода от итерации к итерации ДЗ:
				//case 2: Available_fractions[fraction_index_1]->Subtract(*Available_fractions[fraction_index_2], Available_fractions); break;
				//case 2: Available_fractions.push_back(Operand_1 - Operand_2); break;		
			case 2: Operand_1 - Operand_2; break;
			case 3: Operand_1 * Operand_2; break;
			case 4: Operand_1 / Operand_2; break;
			}
			std::cout << std::endl << Operand_1 << Fraction::codes_of_operation[action] << Operand_2 << " = " << *Available_fractions[Available_fractions.size() - 1];

		}
		else
		{
			Fraction& Operand = Fraction::Choose_Operand_Handle(0);
			Fraction tmp(Operand); // Благодаря конструктору копирования этот временный объект не попадает в общий вектор объектов
			switch (action)
			{
			case 5: ++Operand; break;
			case 6: Operand++; break;
			case 7: --Operand; break;
			case 8: Operand--; break;
			case 9: +Operand; break;
			case 0: -Operand; break;
			}
			if (action == 8 || action == 6 )
			std::cout << std::endl << "(" << tmp << ")"<< Fraction::codes_of_operation[action] << " = " << Operand;
			else
				std::cout << std::endl << Fraction::codes_of_operation[action] <<"(" << tmp << ") = " << Operand;


		}

		std::cout << "\n\nEsc - for exit, any key to continue";
	} while (_getch() != 27);
	Fraction::Memory_Clean(Available_fractions);
	//сам вектор std::vector<Fraction*> Available_fractions вроде должен быть уничтожен автоматически, т.к. находится в стэке (мне так кажется)
}

//Task 2 ComplexNumber class through inheritance with overloaded operators: + | - | / | * demo
void Task_2()
//void Task_2(std::string name_of_work)
{
	//std::cout << "***\t ComplexNumber class through inheritance with overloaded operators: + | - | / | * demo\n";
	std::cout << "Enter provided_at_startup_complex_number_quantity -> ";
	int provided_at_startup_complex_number_quantity = Get_Int_Positive(0,10, "it's too much, reasonable limit is 10 -> ");
	ComplexNumber_class_through_inheritance::Initialisation(provided_at_startup_complex_number_quantity);

	do
	{
		system("cls");
		std::cout << "***\t ComplexNumber class through inheritance with overloaded operators: + | - | / | * demo\n";

		ComplexNumber_class_through_inheritance::Show_List_of_available_numbers();
		ComplexNumber_class_through_inheritance::ShowMethods();
		ComplexNumber_class_through_inheritance::User_Choice_Handle();

		std::cout << "\n\nEsc - for exit, any key to continue";
	} while (_getch() != 27);
	ComplexNumber_class_through_inheritance::MemoryClean();
}

//Task 3 ComplexNumber class through including with overloaded operators: + | - | / | * demo
void Task_3()
{
	std::cout << "Enter provided_at_startup_complex_number_quantity -> ";
	int provided_at_startup_complex_number_quantity = Get_Int_Positive(0, 10, "it's too much, reasonable limit is 10 -> ");
	ComplexNumber_class_through_including::Initialisation(provided_at_startup_complex_number_quantity);

	do
	{
		system("cls");
		std::cout << "***\t ComplexNumber class through inheritance with overloaded operators: + | - | / | * demo\n";

		ComplexNumber_class_through_including::Show_List_of_available_numbers();
		ComplexNumber_class_through_including::ShowMethods();
		ComplexNumber_class_through_including::User_Choice_Handle();

		std::cout << "\n\nEsc - for exit, any key to continue";
	} while (_getch() != 27);
	ComplexNumber_class_through_including::MemoryClean();
}

//Task 4
void Task_4() {}

// MAIN ------- MAIN ------- MAIN ------- MAIN ------- MAIN --------
int main()
{
	srand(time(NULL));
	//setlocale(LC_CTYPE, "Russian");
	//system("mode con cols=60 lines=40"); 
	Main_menu MainMenu;	
	MainMenu.AddElement("OOP Home Work 04: Classes. Operators overload Binary+Unary");	// Homework name
	MainMenu.AddElement("Fractions class demo with overloaded operators:\n\tBinary: + | - | / | * \n\tUnary: + | - | ++ | --");				// Menu element 1
	//MainMenu.AddElement("ComplexNumber class through inheritance with overloaded operators: + | - | / | * demo");		// Menu element 2
	//MainMenu.AddElement("ComplexNumber class through including with overloaded operators: + | - | / | * demo");		// Menu element 3
	//MainMenu.AddElement("XXX");
	do 
	{		
		MainMenu.Show_menu();
		if (!MainMenu.User_Choice_Handle(_getch()))	break;
	} while (true);
	return 0;
}

