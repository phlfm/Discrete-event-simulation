#include <iostream>
#include <functional>
#include <string>

class Base {
public:
	void Base::Choose() {
		UserFunction("Base Choose Run");
	}

	virtual void Base::setUserFunction() = 0;

protected:
	std::function<void(Base::*)(std::string)> UserFunction;
};

class Derived : public Base {
public:
	virtual void Derived::setUserFunction() {
		UserFunction = &myFunction;
	}

private:
	void myFunction(std::string Msg) {
		std::cout << Msg << std::endl;
	}
};

int Scrap_DerivedClassFunctionPointers() {
	Derived D;
	D.setUserFunction();

	D.Choose();
	return 0;
}