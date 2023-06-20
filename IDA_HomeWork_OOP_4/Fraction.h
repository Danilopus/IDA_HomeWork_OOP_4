#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Service functions.h"
//#include <windows.h>
#include <conio.h>
#include <cassert>
#include <map>

class Fraction
{
	//private:
	int _numerator{ 1 };
	int _denominator{ 1 };
	static std::vector<Fraction*>* static_pointer_Available_fractions;// = nullptr;
	int MaxCommonDivider(int a, int b);
	void Fraction_reduction();
public:
	static std::map <int, std::string> codes_of_operation;
	static void Set_static_pointer_Available_fractions(std::vector<Fraction*>& Available_fractions)
	{
		static_pointer_Available_fractions = &Available_fractions;
	}

	// Constructors // Destructors // Memory Clean -------------------------
	Fraction(int A1, int A2, std::vector<Fraction*>& Available_fractions);// : _numerator(A1), _denominator(A2){	Available_fractions.push_back(this); Fraction_reduction();	}
	Fraction(std::vector<Fraction*>& Available_fractions) { Available_fractions.push_back(this); }
	Fraction(int new_numerator, int new_denominator);
	Fraction() {}
	~Fraction()
	{
		std::cout << "\nDestructor at work\n";
		//_getch();

		/*for (int i =0; i < static_pointer_Available_fractions->size(); i++)
			if ((*static_pointer_Available_fractions)[i] == this)
				*static_pointer_Available_fractions->erase(static_pointer_Available_fractions->begin() + i);*/
		
		//delete this; //если объект был создан в динамической памяти надо ли его удалять?
		
	}
	static void Memory_Clean(const std::vector<Fraction*>& Available_fractions);

	// Setters // Getters --------------------------------------------------
	void Set_numerator(int numerator) { _numerator = numerator; }
	void Set_denominator(int denominator);
	int Get_numerator() { return _numerator; }
	int Get_denominator() { return _denominator; }

	// Shows ---------------------------------------------------------------
	void ShowValues() { std::cout << this->Get_numerator() << " / " << this->Get_denominator(); }
	static void ShowMethods();
	void ShowAvailableFractions(std::vector<Fraction*> Available_fractions);
	static void ShowAvailableFractions()
	{
		std::cout << "\nAvailable fractions:";
		for (int i = 0; i < (*static_pointer_Available_fractions).size(); i++)
		{
			//	std::cout << "\nFraction [" << i + 1 << "] -> " << Available_fractions[i]->Get_numerator() << " / " << Available_fractions[i]->Get_denominator();
			//	std::cout << "\nFraction [" << i + 1 << "] -> " << (*static_pointer_Available_fractions)[i]->ShowValues();
			std::cout << "\nFraction [" << i + 1 << "] -> " << *(*static_pointer_Available_fractions)[i];
		}
		std::cout << "\n";
	}
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Q1 Почему при передаче аргумента по константной ссылке перестают работать геттеры?
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::	

		// Inputs handle -------------------------------------------------------		
	static int UserChoiceHandle()
		// 	static void UserChoiceHandle(int keycode)

	{
		std::cout << "choose a method: ";
		int action = Get_Int_Positive(0, 9, "Please, focus your attention on methods amount -> [0..9] ");

		/*
		std::cout << "\nchoose operand 1:";
		int fraction_index_1 = Get_Int_Positive(0, static_pointer_Available_fractions->size(), "index out of range");
		fraction_index_1--;	//transform number to index

		if (action > 4) return; // if not binary

		std::cout << "choose operand 2: ";
		int fraction_index_2 = Get_Int_Positive(0, static_pointer_Available_fractions->size(), "index out of range");
		fraction_index_2--;

		Fraction Operand_1 = *Available_fractions[fraction_index_1];
		Fraction Operand_2 = *Available_fractions[fraction_index_2];
		*/


		return action;
	}
	static Fraction& Choose_Operand_Handle(int Operand_number)	{
		
		std::cout << "\nchoose operand " << Operand_number << ": ";
		int fraction_index = Get_Int_Positive(1, static_pointer_Available_fractions->size(), "index out of range");
		--fraction_index; //transform number to index

		return *(*static_pointer_Available_fractions)[fraction_index];
	}
	//static void Get_Operand(int operand_number);

	//Overload operators - reference returned -----------------------------------------

	/*
	const Fraction& operator+(const Fraction& another_Fraction)
	{
		std::cout << "\n" << "Using const& overload parameter" << "\n";
		int new_numerator = (this->_numerator) * (another_Fraction._denominator) + (another_Fraction._numerator) * (this->_denominator);
		int new_denominator = (this->_denominator) * (another_Fraction._denominator);
		Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
		return *result_fraction;
	}
	//*/

	/*
	const Fraction& operator+(Fraction& another_Fraction)
	{
		std::cout << "\n" << "Using & overload parameter" << "\n";
		int new_numerator = this->_numerator * another_Fraction.Get_denominator() + another_Fraction.Get_numerator() * this->_denominator;
		int new_denominator = this->_denominator * another_Fraction.Get_denominator();
		Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
		return *result_fraction;
	}
	//*/

	/*
	friend const Fraction& operator+(const Fraction& Fraction_Operand_1, const Fraction& Fraction_Operand_2)
	{
		std::cout << "\n" << "Using friend const& overload parameter, return reference" << "\n";

		int new_numerator = (Fraction_Operand_1._numerator) * (Fraction_Operand_2._denominator) + (Fraction_Operand_2._numerator) * (Fraction_Operand_1._denominator);
		int new_denominator = (Fraction_Operand_1._denominator) * (Fraction_Operand_2._denominator);
		Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
		return *result_fraction;
	}
	//*/

	//Overload operators - pointer returned -----------------------------------------

	// перегрузка оператора через friend не может принять только указатели на операнды (нужны объекты или ссылки):
	//		friend Fraction* operator+(Fraction* Fraction_Operand_1, Fraction* Fraction_Operand_2) - такое только через глобальную перегрузку видимо???

	//*
	friend Fraction* operator+(const Fraction& Fraction_Operand_1, const Fraction& Fraction_Operand_2);
	//*/

	// Выводы:

	//1 у компилятора в приоритете использование перегрузки через функции-члены
	//2 только потом пытается  использовать friend, причем это проихсодит даже если friend подходит, а member нет!
	//3 также компилятор предпочитает использовать варианты перегрузок с параметрами с простой ссылкой вместо const&
	//4* при попытке выноса определения у friend функции VS пытается вынести его рядом с main (вместо classes.cpp)

	Fraction* operator+(const Fraction& another_Fraction);

	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Q4 ??? при объявлении Fraction* operator+(Fraction& another_Fraction) в .h все было нормально, при переносе в .cpp вдруг давай ругаться ???
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
	//Fraction* operator+(Fraction& another_Fraction);

	Fraction* operator+(Fraction& another_Fraction)
	{
		std::cout << "\n" << "var3 Using member-function & overload parameter, pointer return" << "\n";
		int new_numerator = (this->_numerator) * (another_Fraction._denominator) + (another_Fraction._numerator) * (this->_denominator);
		int new_denominator = (this->_denominator) * (another_Fraction._denominator);
		Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
		return result_fraction;
	}

	/*
	Fraction* operator+(const Fraction* another_Fraction)
	{
		std::cout << "\n" << "Using friend pointer overload parameter" << "\n";
		int new_numerator = (this->_numerator) * (another_Fraction->_denominator) + (another_Fraction->_numerator) * (this->_denominator);
		int new_denominator = (this->_denominator) * (another_Fraction->_denominator);
		//вариант с сокращением дроби в момент создания через вызов Fraction_reduction в конструкторе
		Fraction* result_fraction = new Fraction(new_numerator, new_denominator);
		//return result_fraction;
		return result_fraction;
	}
	*/

	Fraction* Add(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Subtract(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Multiply(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);
	Fraction* Divide(Fraction& another_Fraction, std::vector<Fraction*>& Available_fractions);

	Fraction* operator-(const Fraction& another_Fraction);
	Fraction* operator*(const Fraction& another_Fraction);
	Fraction* operator/(const Fraction& another_Fraction);

	Fraction* operator++() //prefix
	{
		_numerator++;
		return this;
	}
	Fraction* operator++(int) //postfix
	{
		//Fraction& tmp_obj(*this);
		Fraction* tmp_obj = new Fraction(*this);		
		_numerator++;
		//return &tmp_obj;
		return tmp_obj;
	}
	Fraction* operator--() //prefix
	{
		_numerator--;
		return this;
	}
	Fraction* operator--(int) //postfix
	{
		//Fraction& tmp_obj(*this);
		Fraction* tmp_obj = new Fraction(*this);
		_numerator--;
		//return &tmp_obj;
		return tmp_obj;
	}

	Fraction* operator+() 
	{
		return this;
	}
	Fraction* operator-()
	{
		_numerator = -_numerator;
		return this;
	}


	friend std::ostream& operator << (std::ostream& out, Fraction& just_a_fraction)
	{
		//just_a_fraction.ShowValues();

		out << just_a_fraction._numerator << "/" << just_a_fraction._denominator;

		return out;
	}
};
