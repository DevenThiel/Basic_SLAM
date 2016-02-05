/************
 * 
 * Deven Thiel
 * 
 * 05.11.2015
 * 
 * v1.0 -ddition of operator overloading
 *
 * Template implimentation file to impliment templated portions of a
 * 	class providing functionality for a dynamically sized array.
 * 
 ************/

//default constructor
template <class T>
DArray<T>::DArray ()
{
	length = 0;
	dataP = 0;
}

//constructor taking length of array
template <class T>
DArray<T>::DArray (int inLength)
{
	length = inLength;
	dataP = new T[inLength];
}

//default destructor
template <class T>
DArray<T>::~DArray ()
{
	delete[] dataP;
}

//copy constructor
template <class T>
DArray<T>::DArray (const DArray<T> & other)
{
	length = other.getLength();
	
	delete[] dataP;
	
	dataP = &other[0];
}

//remove one element from array (length--)
template <class T>
void DArray<T>::deleteElement ()
{
	int inTarget = length - 1;
	length--;
	//create new array of correct size
	T *tempP = new T[length];
	//copy relevent parts of current array
	for (int i = 0; i <= length; i++)
	{
		if (i < inTarget)
		{
			tempP[i] = dataP[i];
		}
		else if (i > inTarget)
		{
			tempP[i-1] = dataP[i];
		}
	}
	//delete old array
	delete[] dataP;
	//move pointer
	dataP = tempP;
}

//remove one specific element from array (length--)
template <class T>
void DArray<T>::deleteElement (int inTarget)
{
	length--;
	//create new array of correct size
	T *tempP = new T[length];
	//copy relevent parts of current array
	for (int i = 0; i <= length; i++)
	{
		if (i < inTarget)
		{
			tempP[i] = dataP[i];
		}
		else if (i > inTarget)
		{
			tempP[i-1] = dataP[i];
		}
	}
	//delete old array
	delete[] dataP;
	//move pointer
	dataP = tempP;
}

//add one element to array (length++)
template <class T>
void DArray<T>::addElement ()
{
	length++;
	
	//create new array of correct size
	T *tempP;
	
	tempP = new T[length];
	
	//copy current array
	for (int i = 0; i < (length - 1); i++)
	{
		tempP[i] = dataP[i];
	}
	
	//move pointer
	dataP = tempP;
}

//return length
template <class T>
int DArray<T>::getLength ()
{
	return length;
}

//return address of element
template <class T>
T& DArray<T>::getElement (int inTarget)
{
	return dataP[inTarget];
}

//member access
template <class T>
T& DArray<T>::operator[](int num)
{
    return dataP[num];
}

//overload = operator
template <class T>
DArray<T>& DArray<T>::operator= (DArray<T> & other)
{
	length = other.getLength();
	
	delete[] dataP;
	
	dataP = &other[0];
	
	return *this;
}
