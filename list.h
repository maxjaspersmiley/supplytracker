//list.h
//Max Smiley
//CS202 - program 2

#ifndef _LIST_H
#define _LIST_H


//this file describes the behavior of the Materials class, which is
//a doubly linked list of materials. Materials are contained in this
//list inside MatNodes, which are nodes with next and previous pointers
//and a pointer to a Mat data. This uses dynamic binding to store 
//different types of material in the same list, and call the proper
//functions on each data. 

//note that MatNode is only ever used by Materials and should never be 
//instantiated by the client. (i tried to make the class exclusive to 
//materials, but wasn't able to do so).

#include "materials.h"

class MatNode
{
	public: 
		//have-to-haves
		MatNode();
		MatNode(const MatNode & to_copy);
		~MatNode();

		//this is the way we will create new materials.
		MatNode(MatNode * p, Mat &to_add, MatNode * n);

		//getters and setters for list traversal
		MatNode * getPrev();
		MatNode * getNext();
		void setPrev(MatNode * newPrev);
		void setNext(MatNode * newNext);
		
		//recursive functions called by Materials
		void recursive_complete(int &i);
		void recursive_display(int &n);
		void recursive_display(int &i, int &n);
		void recursive_edit(int &i, int&n);
	protected:
		Mat * mat;
		MatNode * prev;
		MatNode * next;		
};


class Materials
{

	public:
		//have-to-haves
		Materials();
		Materials(const Materials &to_copy);
		~Materials();

		//adds a new material to the linked list
		//should this take a POINTER or a REFERENCE
		void add(Mat & to_add);

		//allows us to mark a material as completed
		void complete(int index);

		//removes ALL materials from list
		void remove();
		//removes a single material from list
		void remove(int index);
		//displays ALL materials from list
		void display();
		//displays a single material from list
		void display(int index);
		//allows the user to edit a specific material
		void edit(int index);

		int getSize();
		
	protected:

		int size;
		MatNode * head;
		MatNode * tail;
};

#endif
