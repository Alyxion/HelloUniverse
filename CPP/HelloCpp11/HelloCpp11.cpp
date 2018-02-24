/** @file

 ----.........____ C++ sandbox ____.........----

 This file contains a sandbox for several common used functions of C and C++ and of the possibilities
 the "new" C++ 11 standard introduced. 
 
 Copyright (c) 2018 by Michael Ikemann */

// ----------------------------------------------------------------------------

#include "stdafx.h"
#include "conio.h"
#include <stdio.h>
#include <string>
#include <iostream>

// ----------------------------------------------------------------------------
// Hello world

/** @brief Hello world string experiments */
class HelloWorld
{
public:
	//! Executes the hello world experiments
	void Run()
	{
		// --- Some string fun with hello world ----

		std::cout << "\n--- Strings ---\n\n";

		std::cout << "Hello world, how are you doing?\n";

		std::cout << "What's your name?\n";

		std::string name;
		std::getline(std::cin, name);

		std::cout << ("Your name is " + name + "\n");

		std::string search = "you ";
		std::string tooLarge = "Hello you world";
		std::cout << tooLarge << std::endl;
		tooLarge.erase(tooLarge.find(search), search.length());
		std::cout << tooLarge << std::endl;
	}
};

// ----------------------------------------------------------------------------
// Vectors and maps

#include <vector>  // for vector lists
#include <sstream> // for string stream
#include <iterator>
#include <map>

/** More strings, vectors and a map */
class VectorsHashMapsEtc
{
public:
	//! Executes the examples
	void Run()
	{
		std::cout << "\n--- Vectors and maps ---\n\n";

		char text[] = "42 The Answer to the Ultimate Question of Life The Universe and Everything";

		std::vector<std::string> words;

		std::stringstream ss(text);
		std::string item;
		while (std::getline(ss, item, ' ')) 
		{
			words.push_back(item);
		}

		// iterating
		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			std::cout << *iter << std::endl;
		}

		// dictionaries
		std::map<std::string,int> mapIt;

		// fill dictionary
		int index = 0;
		for (auto iter = words.begin(); iter != words.end(); iter++, index++)
		{
			mapIt[*iter] = index;
		}

		// access dictionary
		int questionValue = mapIt["Question"];
		char buff[100];
		snprintf(buff, sizeof(buff), "\nIndex of question is %i\n", questionValue);

		std::cout << buff;

		if (mapIt.find("43") == mapIt.end())
		{
			std::cout << "43 not found!\n";
		}
	}
};

// ----------------------------------------------------------------------------
// C++ 11 functionality is making the life a lot more comfortable

#include <functional> // for std::function

/** @brief Another class providing a callback function */
class AnotherClassProvidingACallback
{
public:
	int miVar1 = 123, ///< Finally
		miVar2 = 345, ///< Declaring Initial Values
		miVar3 = 456; ///< Is Possible

	char* mlpSomeHugeDataPointer = nullptr; ///< Far safer to always keep it initialized here
	int miDataSize = 0;	///< Data size

	//! Constructor
	AnotherClassProvidingACallback()
	{
		// doing some common stuff
	}

	//! Inherited constructor, calling shared one, not possible before, just via a solution such as void Init()
	AnotherClassProvidingACallback(const int Val1, const int Val2, const int Val3) :
		AnotherClassProvidingACallback()
	{
		miVar1 = Val1;
		miVar2 = Val2;
		miVar3 = Val3;
	}

	//! Copy constructor
	/** @param [in] Original The object to be copied */
	AnotherClassProvidingACallback(const AnotherClassProvidingACallback &Original)
	{
		*this = Original;
	}

	//! Movement constructor.
	// This function is called if the compiler can foresee that the original of a copy constructed object is anyway
	// going to die. In that case it looks for movement functions which can then use an optimized version of
	// assignment which is able to steal data pointers as long as they are not pointing at pre-reserved memory of the object itself.
	// In difference to a typical copy constructor the passed object is not constant, so we are able to nullify stoled references.
	/** @param [in] DieingOriginal The object of which the compiler foresees it will not be required anymore after the construction */
	AnotherClassProvidingACallback(AnotherClassProvidingACallback &&DieingOriginal)
	{
		*this = DieingOriginal;
	}

	//! Destructor
	~AnotherClassProvidingACallback()
	{
		if (mlpSomeHugeDataPointer)
		{
			delete[] mlpSomeHugeDataPointer;
		}
	}

	//! Movement assignment. See above.
	/** @param [in] DieingOriginal The object of which the compiler foresees it will not be required anymore after the assignment 
	  * @return Reference to this */
	AnotherClassProvidingACallback& operator = (AnotherClassProvidingACallback &&DieingOriginal)
	{
		// release own data pointer if required
		if (mlpSomeHugeDataPointer)
		{
			delete[] mlpSomeHugeDataPointer;
		}

		this->miVar1 = DieingOriginal.miVar1;
		this->miVar2 = DieingOriginal.miVar2;
		this->miVar3 = DieingOriginal.miVar3;
		
		// steal the other's pointer, it won't need it anymore
		mlpSomeHugeDataPointer = DieingOriginal.mlpSomeHugeDataPointer;
		miDataSize = DieingOriginal.miDataSize;

		// inform the other object that it doesn't own a datapointer anymore
		DieingOriginal.mlpSomeHugeDataPointer = nullptr;

		return *this;
	}

	//! Common assignment operator
	/** @param [in] Original The original 
	  * return Reference to this */
	AnotherClassProvidingACallback& operator = (const AnotherClassProvidingACallback &Original)
	{
		// release own data pointer if required
		if (mlpSomeHugeDataPointer)
		{
			delete[] mlpSomeHugeDataPointer;
		}

		this->miVar1 = Original.miVar1;
		this->miVar2 = Original.miVar2;
		this->miVar3 = Original.miVar3;

		// steal the other's pointer, it won't need it anymore
		mlpSomeHugeDataPointer = new char[Original.miDataSize];
		memcpy(mlpSomeHugeDataPointer, Original.mlpSomeHugeDataPointer, Original.miDataSize);
		miDataSize = Original.miDataSize;

		return *this;
	}

	// This function will be called via the new delegates in C++ 11 which allows it (finally) to
	// also set object functions as callbacks, not just global ones
	void SomeFunctionToBeCalled()
	{
		std::cout << "Current values: " << miVar1 << " " << miVar2 << " " << miVar3 << std::endl;
	}

	// This function will be called via the new delegates in C++ 11 which allows it (finally) to
	// also set object functions as callbacks, not just global ones
	int SomeFuncWithMatchingParameters(int A, int B)
	{
		std::cout << "Current values scaled: " << miVar1  * A << " " << miVar2 * B << " " << miVar3 << std::endl;
	}
};

// ..................................................................

//! Function type used to demonstrate how to set C++ 11 callbacks and how to use C++ 11 lambda
typedef int (CallBackWithTwoParamters)(int a, int b);
typedef std::function<CallBackWithTwoParamters> Cpp11CallbackType;

// ..................................................................

/** @brief Several nice improvements introduced by C++ 11 */
class NextLevelWithCpp11
{
public:
	int miVariable = 123;	///< Some local variable

	///< It's now also possible to call constructors using curly brackets
	AnotherClassProvidingACallback mObject = { 1, 2, 3 }; 
	
	// As well it's possible to pass data arrays to classes such as vector if they implement the new initializer list constructor:
	std::vector<std::string> mVector = { "Hello", "world", "how", "are", "you" };


	//! Runs the examples
	void Run()
	{
		std::cout << "\n--- C++ 11 ---\n\n";

		// Mightiest new feature first. With help of the new std::function class it's now possible
		// to easily customize behavior of objects in C++ likely already for a long time standard
		// in languages such as C#. You can for example now inline define a behavior like this:
		// Button* button = new Button();
		// Button->OnClick = [this]() { Application.Quit(); }
		//
		// or of course also with parameters like here to sot a list of strings, 1 means greater, -1 smaller, 0 equal:
		//
		// QuickSort(List, [](String &A, String &B) 
		// { 
		//    return A>B ? 1 : A<B ? -1 : 0; 
	    // });	
		//

		// We want to call an event function with two parameters, A and B

		Cpp11CallbackType eventFunction;

		// we define the function directly inline like in Java
		eventFunction = [](int A, int B)
		{
			std::cout << "The parameters are " << A << " and " << B << std::endl;
			return 0;
		};

		// and call the function
		eventFunction(33, 44);

		AnotherClassProvidingACallback cb; // just some object to show it's now possible to use member functions as delegate

		// we pass a local object (could also be this) to the lambda and let it be called directly.
		// we need to wrap the other object's function into a lambda if the parameters to mismatch
		eventFunction = [&cb](int A, int B) {  cb.SomeFunctionToBeCalled(); return 0; };
		eventFunction(33, 44);

		// ----------------- initializer lists, auto and foreach -----------------
		
		// we can now directly initialize variables with lists of data if they provide a constructor for std::initializer_list
		std::vector<std::string> list = { "This", "demonstrates", "the", "new", "initializer", "list", "feature" };

		// we know finally have a typical for each loop and we also do not need to know the type anymore but can use auto instead
		for (const auto &cur : list)
		{
			std::cout << cur << std::endl;
		}

		// of course we can also use auto directly
		auto someInt = 123;
		auto someFloat = 23.4f;

		// works for arrays too
		int values[] = { 1,2,3,4,5 };

		for (auto cv : values)
		{
			std::cout << cv << std::endl;
		}

	}
};

// ----------------------------------------------------------------------------

//! Main entry point
int main()
{
	// hello world	
	HelloWorld helloWorld;
	helloWorld.Run();
	_getch();

	// vectors etc.
	VectorsHashMapsEtc vhm;
	vhm.Run();
	_getch();

	// c++ 11
	NextLevelWithCpp11 cpp11;
	cpp11.Run();
	_getch();

    return 0;
}

