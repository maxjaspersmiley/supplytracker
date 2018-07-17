//materials.h
//Max Smiley
//CS202 - program 2

#ifndef _MATERIALS_H
#define _MATERIALS_H

//this file describes the different materials the user can create. 
//mat is an abstract class describing a material. It has 4 children, one 
//of which is Exercise, which is stored in another called Exercise_set.
//It would be possible for a user to put a single exercise into a 
//list object, given more time I would have prevented this possibility. 
//Currently the list is set up to contain reading, lecture, and 
//exercise_set data. 

#include <iostream>
#include <cstring>
#include <cassert>

class Mat
{
	public:
		//have-to-haves
		Mat();
		Mat(const Mat &to_copy);
		virtual ~Mat();

		//the constructor invoked by all child classes
		Mat(char * in_name);
	
		//display and complete functions used with dynamic
		//binding by child classes.
		virtual void display();
		virtual void complete();

		//allows correct behavior by exercise_set
		bool isComplete();

		//making the class abstract.
		virtual void edit() = 0;

	protected:
		char * name;
		bool completed;
};

class Reading: public Mat
{
	public:
		//have-to-haves
		Reading();
		Reading(const Reading &to_copy);
		~Reading();

		//the constructor that is actually used.
		Reading(char * in_name, char * in_author, int in_chapter, int in_page);

		//correct display and edit functions for dynamic binding.
		void display();
		void edit();

	protected:
		char * author;
		int chapter;
		int page;
};

class Exercise: public Mat
{
	public:
		//have-to-haves
		Exercise();
		Exercise(const Exercise &to_copy);
		~Exercise();

		//the constructor that is actually used (calls parent)
		Exercise(char * in_name);

		//correct display for dynamic binding
		void display();

		//for circular list traversal. 
		Exercise * getNext();	
		void setNext(Exercise * in_next);

		//so we can create instances of exercise.
		void edit();

	protected: 
		Exercise * next;
};


class Exercise_Set: public Mat
{
	public:
		//have-to-haves
		Exercise_Set();
		Exercise_Set(const Exercise_Set &to_copy);
		~Exercise_Set();
	
		//the constructor that is actually used.
		Exercise_Set(char * in_name);
	
		//adds an exercise pointer to the list. 
		//this should have been overloaded to take
		//a reference, but currently that behavior is undefined.
		void add(Exercise * in_ex);

		//correct display and edit functions. 
		void display();
		void edit();

	protected:
		//recursive functions for list operations.
		void recursive_delete(Exercise * node);
		void recursive_display(int count, Exercise * node);
		void recursive_edit(bool, int, int, Exercise * node);

		Exercise * head;
		int size;
};



class Lecture: public Mat
{
	public:
		//have-to-haves
		Lecture();
		Lecture(const Lecture &to_copy);
		~Lecture();

		//constructor that is actually used
		Lecture(char *, char *, const char *, int);

		//correct display and edit functions
		void display();
		void edit();
	
	protected:
		char * presenter;
		char * medium;
		int numSlides;
};

#endif
