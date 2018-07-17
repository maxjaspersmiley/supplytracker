//main.cpp
//Max Smiley
//CS202 - program 2

//this main function acts as a client of my materials classes and data structures.
//its purpose is to demonstrate how all the functions in these classes work.
//I would have liked to add functionality to read/write from a file, so a persistent
//list could be maintained, but ran out of time. 

//most of the i/o for the program is done in Main, with the exception of specific display
//functions and, glaringly, the Exercise_Set::edit() function, which takes user input to 
//add/remove/complete different elements of the circular linked list contained therein. 
//in hindsight, i should have implemented that functionality here in main, with a dynamic cast, 
//but I had already coded it and ran out of time. 

//keep in mind, input is very weakly guarded. A char input into an int will cause an infinite loop.
//I planned on fixing this as well, but I focused more on cleaning up numerous segmentation
//faults and memory leaks. 

#include "materials.h"
#include "list.h"


using namespace std;

void getUserInput(Materials & materials);
void modifyList(Materials & materials);

int main()
{
	Materials materials;
	getUserInput(materials);
	modifyList(materials);


	materials.display();
	cout << "Thank you for using my list manager!\n\n";
return 0;
}
void modifyList(Materials & materials)
{
	char chinput = 'x';
	int input = -1;

	while (input != 0)
	{
		cout << "\nWould you like to add more material, or modify?\n";
		cout << "M: Modify.\n";
		cout << "A: Add.\n";
		cout << "Q: Quit. \n";
		cin >> chinput;
		cin.ignore(100, '\n');
		cout << "\n\n";
		chinput = toupper(chinput);
		switch(chinput)
		{
			case 'Q':
				input = 0;
				break;
			case 'A':
				getUserInput(materials);
				break;
			case 'M':
			{
				while(chinput != 'Q')
				{
					cout << "Which material would you like to modify? (enter '0' to quit)  ";
					cin >> input;
					cin.ignore(100, '\n');
			
					while(input <= 0 || input > materials.getSize())
					{
						if(input == 0)
						{
							break;;
						}
						cout << "\nINVALID INPUT, TRY AGAIN!   ";
						cin >> input;
						cin.ignore(100, '\n');					
					}
					if(input == 0)
					{
						break;
					}
		
					cout << "\n\nOkay, element #" << input << ", what would you like to do?\n";
					cout << "E: EDIT\n";
					cout << "R: REMOVE\n";
					cout << "C: COMPLETE\n";
					cout << "Q: QUIT\n";
					cout << "CHOICE: ";
					cin >> chinput;
					cin.ignore(100, '\n');
					cout << "\n\n";

					chinput = toupper(chinput);
	
					switch(chinput)
					{
						case 'Q':
							cout << "Done modifying. \n\n";
							break;
						case 'R':
							materials.remove(input);
							break;
						case 'E':
							materials.edit(input);
							break;
						case 'C':
							materials.complete(input);
							break;
					}
				materials.display();
				input = -1;
				}
			}
		}
	}
}

void getUserInput(Materials & materials)
{
	int arrlength = 256;
	char input = 'e';

	while(input != 'Q')
	{
		cout << "\nAdding a material. Which type of material to add?\n";
		cout << "R: Reading.\n";
		cout << "E: Excercise set.\n";
		cout << "L: Lecture.\n";
		cout << "Q: Quit adding.\n";
		cout << "CHOICE: ";
		cin >> input;
		cin.ignore(100, '\n');
		cout << "\n";
	
		input = toupper(input);

		switch(input)
		{
			case 'Q':
				cout << "Done adding. \n\n";
				break;
			case 'R':
			{
				char * name = new char[arrlength];
				char * author = new char[arrlength];
				int chapter, page;
				cout << "Adding reading.\n";
				cout << "What is the name of the reading material?  ";
				cin.getline(name, arrlength);
				cout << "\nWhat is the name of the author?  ";
				cin.getline(author, arrlength);
				cout << "\nWhat is the chapter number?  ";
				cin >> chapter;
				cin.ignore(100, '\n');
				cout << "\nWhat is the page number?  ";
				cin >> page;
				cin.ignore(100, '\n');
	
				Reading * r = new Reading(name, author, chapter, page);
	
				materials.add(*r);

				delete[] name;
				delete[] author;

				break;
			}	
			case 'E':
			{
				char * setname = new char[arrlength];
				int length;
				cout << "Adding an exercise set.\n";
				cout << "What is the name of the set?  ";
				cin.getline(setname, arrlength);
				cout << "\nWhat is the length of the set?  ";
				cin >> length;
				cin.ignore(100, '\n');
				cout << "\n\n";
				Exercise_Set * ex = new Exercise_Set(setname);
				for(int i = 1; i <= length; ++i)
				{
					char * exname = new char[arrlength];
					cout << "What is question #" << i << "?  ";
					cin.getline(exname, arrlength);
					Exercise * e = new Exercise(exname);
					ex->add(e);
					delete[] exname;
				}
				
				materials.add(*ex);
				
				delete[] setname;

				break;	
			}
			case 'L':
			{
				char * name = new char[arrlength];
				char * presenter = new char[arrlength];
				const char * medium;
				int numSlides;
				char ch = 'x';

				cout << "Adding lecture.\n";
				cout << "What is the title of the lecture?  ";
				cin.getline(name, arrlength);
				cout << "\nWho will be presenting the lecture?  ";
				cin.getline(presenter, arrlength);
				cout << "\nWill the lecture be presented";
				cout << "\n(O)nline, or in (C)lass?     ";
				cin >> ch;
				cin.ignore(100, '\n');
				ch = toupper(ch);
//need ways to remove elements, and complete elements:

/*
void modifyList(Materials & materials)
{
	char chinput = 'x';
	int input = -1;

	while (input != 0)
	{
		while(chinput != 'Q')
		{
			cout << "Lets change some materials. What is the index\n";
			cout << "of the list element you'd like to modify?\n";
			cout << "enter '0' to exit this loop.        ";
			cin >> input;
			cin.ignore(100, '\n');
	
			if(input == 0)
			{
				break;
			}
	
			while(input < 0 || input > materials.getSize())
			{
				cout << "\nINVALID INPUT, TRY AGAIN!   ";
				cin >> input;
				cin.ignore(100, '\n');
			}
		
			cout << "\n\nOkay, element #" << input << ", what would you like to do?\n";
			cout << "E: EDIT\n";
			cout << "R: REMOVE\n";
			cout << "Q: QUIT\n";
			cout << "CHOICE: ";
			cin >> chinput;
			cin.ignore(100, '\n');
			cout << "\n\n";

			chinput = toupper(chinput);

			switch(chinput)
			{
				case 'Q':
					cout << "Done modifying. \n\n";
					break;
				case 'R':
					materials.remove(input);
					break;
				case 'E':
					materials.edit(input);
					break;
			}
		}
	}
	materials.display();
}
*/
				switch(ch)
				{
					case 'O':
						medium = "online";
						break;
					case 'C':
						medium = "class";
						break;
					default:
						medium = "unspecified";
						break;
				}
				cout << "\nHow many slides in the lecture?  ";
				cin >> numSlides;
				cin.ignore(100, '\n');
	
				Lecture * l = new Lecture(name, presenter, medium, numSlides);

				materials.add(*l);
			
				delete[] name;
				delete[] presenter;
			}
		}
	}
	materials.display();
}
