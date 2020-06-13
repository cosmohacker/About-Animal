// About_Animal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h> 
#include <vector>
#include <string>

using namespace std;

class Utils {
public:
	vector<float> _brainSize, _shouldCalories, _takeCalories, _wingSize, _expectedLifeMammal, _expectedLifeBird;
	float brainSize, shouldCalories, takeCalories, wingSize, expectedLifeTime;
	int _operationSelection, _speciesSelection, _inputCounter = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	vector<string> _name, _diet, _exit;
	string name, diet, exit;
};

class Animal : Utils
{
public:

	virtual void calculateExpectedLifeTime(float size, float calorie, float multiplier) {
		expectedLifeTime = size * multiplier / calorie;
	}

	virtual void display() {
	}
};

class Mammal : Animal
{
public:

	float expectedLifeTime;

	void calculateExpectedLifeTime(float brainSize, float dailyCalorie)
	{
		float multiplier = 20.0;

		expectedLifeTime = brainSize * multiplier / dailyCalorie;
	}

	void display() override {
	}
};

class Bird : Animal {
public:

	float expectedLifeTime;

	void calculateExpectedLifeTime(float wingSize, float dailyCalorie)
	{
		float multiplier = 10.0;

		expectedLifeTime = wingSize * multiplier / dailyCalorie;
	}

	void display() override {
	}
};

class Events : public Utils {

public:

	Mammal _mammal;
	Bird _bird;

	virtual void switchEvent() {

		SetConsoleTextAttribute(handle, 15);
		cout << "What do you want to do ? (1 for add an animal, 2 for remove last added animal, 3 display all): ";
		cin >> _operationSelection;
		switch (_operationSelection)
		{
		case 1:
			operationOne();
			break;

		case 2:
			operationTwo();
			break;

		case 3:
			operationThree();
			break;

		default:
			charError();
		}

		if (_operationSelection > 3)
		{
			cout << "\n";
			switchEvent();
		}

		if (_speciesSelection > 2)
		{
			cout << "\n";
			switchEvent();
		}
	}

	void operationOne() {

		cout << "Which species do you want to add? (1 for mammals, 2 for birds): ";
		cin >> _speciesSelection;

		if (_speciesSelection == 1)
		{
			cout << "Enter its name: ";
			cin >> name;
			_name.push_back(name);
			cout << endl;

			cout << "Enter its diet: ";
			cin >> diet;
			_diet.push_back(diet);
			cout << endl;

			cout << "Enter its brain size: ";
			cin >> brainSize;
			_brainSize.push_back(brainSize);
			_wingSize.push_back(0);
			cout << endl;

			cout << "Enter the daily calories it should take: ";
			cin >> shouldCalories;
			_shouldCalories.push_back(shouldCalories);
			cout << endl;

			cout << "Enter the daily calories it takes: ";
			cin >> takeCalories;
			_takeCalories.push_back(takeCalories);
			_mammal.calculateExpectedLifeTime(brainSize, takeCalories);
			_expectedLifeMammal.push_back(_mammal.expectedLifeTime);
			_expectedLifeBird.push_back(0);
			cout << endl;

			cout << "Enter e for exit: ";
			cin >> exit;
			_inputCounter++;
			cout << endl;
			switchEvent();
		}
		else if (_speciesSelection == 2)
		{
			cout << "Enter its name: ";
			cin >> name;
			_name.push_back(name);
			cout << endl;

			cout << "Enter its diet: ";
			cin >> diet;
			_diet.push_back(diet);
			cout << endl;

			cout << "Enter its wing size: ";
			cin >> wingSize;
			_wingSize.push_back(wingSize);
			_brainSize.push_back(0);
			cout << endl;

			cout << "Enter the daily calories it should take: ";
			cin >> shouldCalories;
			_shouldCalories.push_back(shouldCalories);
			cout << endl;

			cout << "Enter the daily calories it takes: ";
			cin >> takeCalories;
			_takeCalories.push_back(takeCalories);
			_bird.calculateExpectedLifeTime(wingSize, takeCalories);
			_expectedLifeBird.push_back(_bird.expectedLifeTime);
			_expectedLifeMammal.push_back(0);
			cout << endl;

			cout << "Enter e for exit: ";
			cin >> exit;
			cout << endl;
			_inputCounter++;
			switchEvent();
		}
	}

	void operationTwo() {
		cout << "Removed Animal: " << endl;

		cout << "Name: " << _name.back() << endl;
		cout << "Diet: " << _diet.back() << endl;
		cout << "Wing Size: " << _wingSize.back() << endl;
		cout << "Brain Size: " << _brainSize.back() << endl;

		_name.pop_back();
		_diet.pop_back();
		_wingSize.pop_back();
		_brainSize.pop_back();
		_takeCalories.pop_back();
		_shouldCalories.pop_back();
		_expectedLifeBird.pop_back();
		_expectedLifeMammal.pop_back();
		_inputCounter--;


		switchEvent();
	}

	void operationThree() {

		cout << "All animal(s) in stack :" << endl;
		for (int i = 0; i < _inputCounter; i++)
		{
			cout << i << ". Animal:" << endl;

			cout << "Name: " << _name.at(i) << endl;
			cout << "Diet: " << _diet.at(i) << endl;

			if (_wingSize.size() > i)
			{
				cout << "Wing Size: " << _wingSize.at(i) << endl;
				_bird.calculateExpectedLifeTime(_wingSize.at(i), _takeCalories.at(i));
				cout << "Expected Life Time: " << _expectedLifeBird.at(i) << endl;
			}

			if (_brainSize.size() > i)
			{
				cout << "Brain Size: " << _brainSize.at(i) << endl;
				_mammal.calculateExpectedLifeTime(_brainSize.at(i), _takeCalories.at(i));
				cout << "Expected Life Time: " << _expectedLifeMammal.at(i) << endl;
			}
		}
		switchEvent();
	}

	void charError() {
		SetConsoleTextAttribute(handle, 4);
		cout << "Please enter the specified characters";
	}
};

int main()
{
	Events _events;

	_events.switchEvent();
}	