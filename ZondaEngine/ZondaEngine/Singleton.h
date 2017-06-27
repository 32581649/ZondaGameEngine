#ifndef SINGLETON_H
#define SINGLETON_H

// reference: https://www.codeproject.com/Articles/1921/Singleton-Pattern-its-implementation-with-C
template <class T>
class Singleton{
public:
	static T* Instance(){
		if (!instance_flag){
			ret = new T();
			instance_flag = true;
			return ret;
		}
		else{
			return ret;
		}
	};

private:
	Singleton();
	~Singleton(){ instance_flag = false; };
	Singleton(Singleton const&);
	Singleton& operator = (Singleton const&);

	static bool instance_flag;
	static T* ret;
};

template <class T>
bool Singleton<T>::instance_flag = false;

template <class T>
T* Singleton<T>::ret = 0;

#endif