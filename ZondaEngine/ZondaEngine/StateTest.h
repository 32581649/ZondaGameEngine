#ifndef STATETEST_H
#define STATETEST_H

class StateTest{
public:
	StateTest(){
		a = new int;
		*a = 0;
	};
	~StateTest(){
		if(a) delete a;
	};
	StateTest(StateTest const& new_obj){
		*(this->a) = *(new_obj.a);
	}


	int GetA(){
		return *(a);
	}

	void SetA(int const & new_val){
		*(this->a) = new_val;
	}

private:
	int* a;
};

#endif