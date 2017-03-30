//Milan Singh 
#include <iostream>

template <class T> class DynamicArrayIterator;
template <class T> class  DynamicArray{
	private:
		T *backArray;
		int capacity;
		int current;
	public:
		DynamicArray();
		~DynamicArray();


		void add(T item);
		T remove(int i);
		int size();

		T &operator[](int index){return backArray[index];};

		DynamicArrayIterator<T> begin();
		DynamicArrayIterator<T> end();
		DynamicArrayIterator<T> r_begin();
		DynamicArrayIterator<T> r_end();
	
};

template <class T> 
DynamicArray<T>::DynamicArray(){
	backArray = new T[10];
	capacity = 10;
	current = 0;
}

template <class T> 
DynamicArray<T>::~DynamicArray(){
	delete [] backArray;
}

template <class T> 
void DynamicArray<T>::add(T item){
	if (current>=capacity){
		capacity*=2;
		int *newArray = new int[capacity];
		for (int i = 0; i < capacity/2; i++){
			newArray[i] = backArray[i];
		}
		delete [] backArray;
		backArray = newArray;
	}
		
	backArray[current] = item; //Add item at current fre spot
	current++;	//Update current
}
 
template <class T> 
T DynamicArray<T>::remove(int i){
	T temp;
	temp = backArray[i];
	for (i; i<=current; i++){
		backArray[i] = backArray[i+1]; //SHift each down one (overwrite first one)
	}
	current--; // Update current to reflect shorter array
	return temp;
}

template <class T>
int DynamicArray<T>::size(){
	return current +1; //Return first index available + 1 (account for backArray[0])
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::begin(){
	return DynamicArrayIterator<T>(this,0,1);
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::end(){
	return DynamicArrayIterator<T>(this,current,1);
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::r_begin(){
	return DynamicArrayIterator<T>(this,current-1,-1);
}

template <class T>
DynamicArrayIterator<T> DynamicArray<T>::r_end(){
	return DynamicArrayIterator<T>(this,-1,-1);
}

template <class T> class DynamicArrayIterator{
	private:
		int currentPosition;
		DynamicArray<T>* array;
		int direction;
	public:
		DynamicArrayIterator(DynamicArray<T> *A, int iniCurr, int dir);
		DynamicArray<T>* getArray();
		int getPos();
		int getDir();

		void operator++(){currentPosition+=direction;};
		T & operator*(){return (*array)[currentPosition];};

		bool operator==(DynamicArrayIterator rhs){if ((array==rhs.getArray())&(currentPosition==rhs.getPos())&(direction==rhs.getDir())){return true;} else {return false;}};
		bool operator!=(DynamicArrayIterator rhs){if ((array==rhs.getArray())&(currentPosition==rhs.getPos())&(direction==rhs.getDir())){return false;} else {return true;}};
};

template <class T> 
DynamicArrayIterator<T>::DynamicArrayIterator(DynamicArray<T> *A, int iniCurr, int dir){
	currentPosition = iniCurr;
	direction = dir;
	array = A;
}

template <class T> 
DynamicArray<T>* DynamicArrayIterator<T>::getArray(){
	return array;
}

template <class T> 
int DynamicArrayIterator<T>::getPos(){
	return this->currentPosition;
}

template <class T> 
int DynamicArrayIterator<T>::getDir(){
	return this->direction;
}

int main() {
	DynamicArray<int> foo;
	foo.add(3);
	foo.add(2);
	std::cout << foo[1] << std::endl;
	foo[1] = 10;
	std::cout << foo[1] << std::endl;
	for(DynamicArrayIterator<int> a = foo.begin(); a != foo.end(); ++a) {
		std::cout << *a << std::endl;
		}
	for(DynamicArrayIterator<int> a = foo.r_begin(); a != foo.r_end(); ++a) {
		std::cout << *a << std::endl;
		}
}