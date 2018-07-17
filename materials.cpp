//materials.cpp
//Max Smiley
//CS202 - program 2

#include "materials.h"

using namespace std;

Mat::Mat(): name(NULL), completed(0)
{}

Mat::Mat(const Mat &to_copy): name(NULL), completed(to_copy.completed)
{
	name = new char[strlen(to_copy.name) +1];
	strcpy(name, to_copy.name);
}



Mat::~Mat()
{
	delete[] name;
	name = NULL;
}

Mat::Mat(char * in_name): name(NULL), completed(0)
{
	name = new char[strlen(in_name)+1];
	strcpy(name, in_name);
}

//this is called in all inherited class display functions.
void Mat::display()
{
	cout << name << '\n';
	if(completed)
	{
		cout << "***COMPLETE***\n";
	}
	else
	{
		cout << "  incomplete  \n";
	}
}

void Mat::complete()
{
	completed = 1;
}

bool Mat::isComplete()
{
	return completed;
}


//////////////////////////////////////////////////////////////////////////////////////////


Reading::Reading(): Mat(), author(NULL), chapter(0), page(0)
{}

Reading::Reading(const Reading &to_copy): Mat(to_copy), author(NULL), chapter(to_copy.chapter), page(to_copy.page)
{
	author = new char[strlen(to_copy.author)+1];
	strcpy(author, to_copy.author);
}

Reading::~Reading()
{
	delete[] author;
	author = NULL;
}

Reading::Reading(char * in_name, char * in_author, int in_chapter, int in_page): Mat(in_name), author(NULL), chapter(in_chapter), page(in_page)
{
	author = new char[strlen(in_author)+1];
	strcpy(author, in_author);
}

void Reading::display()
{
	cout << "Type: READING\n";
	cout << "Title: ";
	Mat::display();
	cout << "Author : " << author << '\n';
	cout << "Chapter: " << chapter << '\n';
	cout << "Page # : " << page << "\n\n";
}

void Reading::edit()
{
	cout << "####### EDITING #######\n";
	display();
	cout << "New chapter #: ";
	cin >> chapter;
	cin.ignore(100, '\n');
	cout << "\nNew Page #: ";
	cin >> page;
	cin.ignore(100, '\n');
	cout << "#### EDIT COMPLETE ####\n\n";
}


//////////////////////////////////////////////////////////////////////////////////////////

Exercise::Exercise(): Mat(), next(NULL)
{}

Exercise::Exercise(const Exercise &to_copy): Mat(to_copy), next(NULL)
{}

Exercise::~Exercise()
{}

Exercise::Exercise(char * in_name): Mat(in_name), next(NULL)
{}

void Exercise::setNext(Exercise * in_next)
{
	next = in_next;
}

Exercise * Exercise::getNext()
{
	return next;
}

void Exercise::edit()
{}

void Exercise::display()
{
	cout << name << '\n';
	if(completed)
	{
		cout << "\t\t***COMPLETE***\n";
	}
	else
	{
		cout << "\t\t  incomplete  \n";
	}
}	

///////////////////////////////////////////////////////////////////////////////////////////

Exercise_Set::Exercise_Set(): Mat(), head(NULL), size(0)
{}

Exercise_Set::Exercise_Set(const Exercise_Set &to_copy): Mat(to_copy), head(NULL), size(0)
{
	//make a head node for the new exercise set
	head = new Exercise(*to_copy.head);
	//where are we going to be copying from??
	Exercise * from = to_copy.head;
	//wher eare we going to be copying TO?
	Exercise * to = head;
	//while the next element in the "from stream" isn't its head...
	while(from->getNext() != to_copy.head)
	{
		//make a new exercise that is a copy of "from"
		Exercise * a = new Exercise(*from->getNext());
		//set that exercise as the next element in the "to list"
		to->setNext(a);
		//step forward in the "from stream"
		from = from->getNext();
		//"to" is now the Exercise we just created.
		to = to->getNext();
	}
	//this loop should terminate when "to" is the last element in the list, so all that
	//is left to do is to link the list together. 
	to->setNext(head);
}

Exercise_Set::~Exercise_Set()
{
	if(head)
	{
		recursive_delete(head);
	}
}

//will continue recursing until we're at the last node due to the if statement.
//will then delete every node consecutively, starting with the last.
void Exercise_Set::recursive_delete(Exercise * node)
{
	Exercise * next = node->getNext();
	if(next != head)
	{
		recursive_delete(next);
	}
	delete node;
	node = NULL;
}

Exercise_Set::Exercise_Set(char * in_name): Mat(in_name), head(NULL), size(0)
{}

//displays whole set
void Exercise_Set::display()
{
	cout << "Type: EXERCISE SET\n";
	cout << "Name of set: ";
	Mat::display();
	
	int count = 1;
	
	if(size == 0)
	{
		cout << "list empty.\n";
		return;
	}
	recursive_display(count, head); 
}

//used by above
void Exercise_Set::recursive_display(int count, Exercise * node)
{

	cout << "\texercise #" << count << ": ";
	node->display();
	cout << "\n";
	++count;
	if(node->getNext() != head)
	{
		recursive_display(count, node->getNext());
	}
}

//adds a node to head, and then correctly connects last pointer to point to head
void Exercise_Set::add(Exercise * in_ex)
{
	if(!head)
	{
		head = in_ex;
		head->setNext(head);
	}

	else
	{
		Exercise * node = head;
		Exercise * oldHead = head;
		head = in_ex;
		head->setNext(node);

		while(node->getNext() != oldHead)
		{
			node = node->getNext();
		}
	
		node->setNext(head);
	}	
	++size;
}

//this should have been in main with a dynamic_cast. ran out of time. 
void Exercise_Set::edit()
{
	cout << "******* EDITING *******\n";
	display();
	
	char ch = 'x';
	cout << "\nwould you like to (A)dd, (C)omplete, or (R)emove?  ";
	cin >> ch;
	cin.ignore(100, '\n');
	cout << "\n\n";
	ch = toupper(ch);

	switch(ch)
	{
		case 'R':
		{
			int to_remove;
			cout << "Which exercise would you like to remove?\n";
			cout << "press '0' to quit.\n";
			cout << "exercise #";
			cin >> to_remove;
			cin.ignore(100, '\n');
			if(to_remove < 1 || to_remove > size)
			{
				cout << "\n***** EDIT ABORTED *****\n";
				return;
			}
			int count = 1;
			recursive_edit(1, to_remove, count, head);
			cout << "\n**** EDIT FINISHED ****\n";
			break;
		}
		case 'A':
		{
			char * exname = new char[256];
			cout << "What is the new question? \n";
			cin.getline(exname, 256);
			Exercise * e = new Exercise(exname);
			add(e);
			break;
		}
		//this will correctly move head to the next incomplete exercise, and if all exercies are completed it will mark the set itself as complete. 
		case 'C':
		{
			int to_complete;
			cout << "Which exercise have you completed?\n";
			cout << "press '0' to quit. \n";
			cout << "exercise #";
			cin >> to_complete;
			cin.ignore(100, '\n');
			cout << "\n\n";
			if(to_complete < 1 || to_complete > size)
			{
				cout << "\n*** COMPLETION ABORTED ***\n";
				return;
			}
			int count = 1;
			recursive_edit(0, to_complete, count, head);

			Exercise * oldHead = head;
			while(head->isComplete())
			{
				head = head->getNext();
				if(head == oldHead)
				{
					complete();
					break;
				}
			}
			break;

		}		
	}
}


//deletes if bool is true, completes if bool is false.

//for delete, looks at next, sees if it should be deleted, then links the circular list correctly.
//untested for deleting last element in a list. probably doesn't work. 
void Exercise_Set::recursive_edit(bool b, int to_edit, int count, Exercise * node)
{
	++count;
	if(count > to_edit)
	{
		count -= size;
		head = head->getNext();
	}
	
	if(count == to_edit)
	{
		if(b)
		{
			Exercise * to_del = node->getNext();
			Exercise * next = to_del->getNext();
			node->setNext(next);
			to_del->setNext(NULL);
			delete to_del;
		}
		else
		{
			Exercise * next = node->getNext();
			next->complete();
		}
	}
	else
	{
		recursive_edit(b, to_edit, count, node->getNext());
	}
}

//////////////////////////////////////////////////////////////////////////////////////

Lecture::Lecture(): Mat(), presenter(NULL), medium(NULL), numSlides(0)
{}

Lecture::Lecture(const Lecture &to_copy): Mat(to_copy), presenter(NULL), medium(NULL), numSlides(to_copy.numSlides)
{
	presenter = new char[strlen(to_copy.presenter)+1];
	strcpy(presenter, to_copy.presenter);
	medium = new char[strlen(to_copy.medium) + 1];
	strcpy(medium, to_copy.medium);
}

Lecture::~Lecture()
{
	delete[] presenter;
	delete[] medium;
}

Lecture::Lecture(char * in_name, char * in_presenter, const char * in_medium, int in_numSlides): Mat(in_name), presenter(NULL), medium(NULL), numSlides(in_numSlides)
{
	presenter = new char[strlen(in_presenter)+1];
	strcpy(presenter, in_presenter);
	medium = new char[strlen(in_medium)+1];
	strcpy(medium, in_medium);
}

void Lecture::display()
{
	cout << "Type: LECTURE\n";
	cout << "  Title      : ";
	Mat::display();
	cout <<   "Presenter  : " << presenter;
	cout << "\nMedium     : " << medium;
	cout << "\n# of slides: " << numSlides << "\n\n";
}

void Lecture::edit()
{
	char * newPresenter = new char[256];
	display();
	cout << "New presenter name: ";
	cin.getline(newPresenter, 256);
	delete[] presenter;
	presenter = new char[strlen(newPresenter)+1];
	strcpy(presenter, newPresenter);
	delete[] newPresenter;
	cout << "\nNew # of slides: ";
	cin >> numSlides;
	cin.ignore(100, '\n');
	cout << "\n\nEdit completed.\n\n";
}

 
