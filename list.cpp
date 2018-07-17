//list.cpp
//Max Smiley
//CS202 - program 2

#include "list.h"
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


Materials::Materials(): size(0), head(NULL), tail(NULL)
{}

Materials::Materials(const Materials& to_copy): size(to_copy.size), head(NULL), tail(NULL)
{

}

Materials::~Materials()
{
	while(head)
	{
		MatNode * newNode = head->getNext();
		delete head;
		head = newNode;
	}
}

//adds a material to the list. 
void Materials::add(Mat & to_add)
{
	if(!head)
	{
		head = new MatNode(NULL, to_add, NULL);
		tail = head;
	}
	else
	{
		MatNode * newNode = new MatNode(tail, to_add, NULL);
		tail->setNext(newNode);
		tail = newNode;
	}
	++size;
}

//this constructor is invoked above. 
MatNode::MatNode(MatNode * p, Mat & to_add, MatNode * n): mat(NULL), prev(NULL), next(NULL)
{
	prev = p;
	mat = &to_add;
	next = n;
}

//completes a specific material.
void Materials::complete(int index)
{
	int i = index;
	if(head)
	{
		head->recursive_complete(i);
	}
}

//used by above function.
void MatNode::recursive_complete(int &i)
{
	--i;
	if(i == 0)
	{
		mat->complete();
	}
	else if(i>0 || next)
	{
		next->recursive_complete(i);
	}
}


//removes all materials in the list. this function is not called in 
//my main, but I decided to leave it here.
void Materials::remove()
{
	if(!head)
	{
		return;
	}

	else if(head == tail)
	{
		head->setNext(NULL);

		delete head;
	
		head = NULL;
		tail = NULL;
	}

	else
	{
		MatNode * node = head;
		while(head != tail)
		{
			head = head->getNext();

//			node->setPrev(NULL);
//			node->setNext(NULL);
			delete node;
			node = head;
		}
//		node->setPrev(NULL);
//		node->setNext(NULL);
		delete node;
		head = NULL;
		tail = NULL;
	}
	size = 0;
}


//removes the material at a specific index, and 
//links the list back together correctly. 
//not recursive - hacked it together and ran out of time. 
void Materials::remove(int index)
{
	if(!head || (index > size))
	{
		return;
	}
	else if(head == tail)
	{
		head->setNext(NULL);
		delete head;
		head = NULL;
		tail = NULL;
	}

	else
	{
		MatNode * p = NULL;
		MatNode * node = head;
		MatNode * n = head->getNext();		

		for(int i = 1; i < index; i++)
		{
			p = node;
			node = node->getNext();
			n = node->getNext();
		}

//		node->setPrev(NULL);
//		node->setNext(NULL);
		delete node;
		node = NULL;

		if(!p)
		{
			head = n;
			n->setPrev(NULL);
		}
		else
		{
			p->setNext(n);
		}

		if(!n)
		{
			tail = p;
			p->setNext(NULL);
		}
		else
		{
			n->setPrev(p);
		}

	}

	--size;
}

//displays all materials	
void Materials::display()
{
	int n = 1;
	if(head)
	{
		head->recursive_display(n);
	}
}

//called by above
void MatNode::recursive_display(int & n)
{
	cout << "\n\n******* Node #" << n << " *******\n";
	++n;
	mat->display();
	if(next)
	{
		next->recursive_display(n);
	}
}

//displays specific material. not used in main, but decided to leave it. 
void Materials::display(int index)
{
	int i = index;
	int n = 1;
	if(head)
	{
		head->recursive_display(i, n);
	}
}

//called by above.
void MatNode::recursive_display(int &i, int & n)
{
	--i;
	if(i == 0)
	{
		cout << "\n******* Node #" << n << " *******\n";
		mat->display();
	}
	else if(i > 0 && next)
	{
		++n;
		next->recursive_display(i, n);
	}
}

//edits a specific material
void Materials::edit(int index)
{
	int i = index;
	int n = 1;
	if(head)
	{
		head->recursive_edit(i, n);
	}
}

//called by above
void MatNode::recursive_edit(int &i, int &n)
{
	--i;
	if(i == 0)
	{
		cout << "**** Node #" << n << " ****\n";
		mat->edit();
	}
	else if(i > 0 && next)
	{
		++n;
		next->recursive_edit(i, n);
	}
}

//returns size of list
int Materials::getSize()
{
	return size;
}
	

//getters and setters for list traversal
MatNode * MatNode::getPrev()
{
	return prev;
}
MatNode * MatNode::getNext()
{
	return next;
}
void MatNode::setPrev(MatNode * newPrev)
{
	prev = newPrev;
}
void MatNode::setNext(MatNode * newNext)
{
	next = newNext;
}



///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////


//matnode have-to-haves.
MatNode::MatNode(): mat(NULL), prev(NULL), next(NULL)
{}

MatNode::MatNode(const MatNode & to_copy): mat(NULL), prev(NULL), next(NULL)
{
	//mat = new Mat(*to_copy.mat);
}

//this might be broken if an object is passed by value/reference to the matnode constructor. 
MatNode::~MatNode()
{
	prev = NULL;
//		void complete();
	delete mat;
	mat = NULL;
	
}
