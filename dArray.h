/************	cout << "flag1" << endl;
 * 
 * Deven Thiel
 * 
 * 05.11.2015
 *
 * v1.0 - addition of operator overloading
 *
 * Header file to declare a class that impliments a method for use of a 
 * 	dynamically sized array.
 * 
 ************/
#ifndef DARRAY_H
#define DARRAY_H

#include <iostream>

using namespace std;

template <class T>
class DArray
{
	public:
		//Default constructor
		DArray();
		
		//Constructor taking a variable length	 
		DArray(int);
	
		//copy constructor
		DArray(const DArray &);

		//Default destructor
		~DArray();
		
		void deleteElement();
	 
		void deleteElement(int);
		
		void addElement ();
		
		int getLength ();
		
		T& getElement (int);
	
		T& operator[] (int);
	
		DArray<T>& operator= (DArray<T> & other);

	private:
		int length;
		
		T *dataP;
};

#include "dArray.t"
 
#endif
