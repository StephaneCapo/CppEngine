#pragma once
#include <memory>

namespace O3DCppEngine
{
	// forward declarations
	class Factory;
}

// the main class used to manage everything in the engine
class CppEngine
{
protected:

	// Factory is not directly accessible
	// use getFactory to access factory methods
	O3DCppEngine::Factory* mFactory=nullptr;

public:
	// constructor, init Engine 
	CppEngine();
	// destructor
	~CppEngine();

	// return the Factory singleton
	O3DCppEngine::Factory& getFactory() const
	{
		return *mFactory;
	}
};

template<typename T>
using sp=std::shared_ptr<T>;