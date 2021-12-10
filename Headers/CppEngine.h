#pragma once

namespace O3DCppEngine
{
	// forward declarations
	class Factory;
}

class CppEngine
{
protected:

	O3DCppEngine::Factory* mFactory;

public:
	CppEngine();
	~CppEngine();

	O3DCppEngine::Factory& getFactory()
	{
		return *mFactory;
	}
};
