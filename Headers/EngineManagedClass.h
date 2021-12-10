#pragma once
#include <memory>

namespace O3DCppEngine
{

	// base class for classes that can be managed by CppEngine (Factory)
	class EngineManagedClass
	{
	protected:
		unsigned int			mUID;
		static unsigned int		mUIDCounter;
	public:
		virtual void	init() = 0;
		virtual void	close() = 0;

		EngineManagedClass() : mUID(mUIDCounter++)
		{

		}

		// empty destructor
		virtual ~EngineManagedClass()
		{

		}

		unsigned int getUID()
		{
			return mUID;
		}
	};

	typedef std::shared_ptr<EngineManagedClass> (*createCppEngineClass)();

#define DECLARE_CLASS(classname) public:\
static std::shared_ptr<EngineManagedClass>	createInstance()\
{\
	std::shared_ptr<classname>	inst=std::make_shared<classname>();\
	return std::static_pointer_cast<EngineManagedClass>(inst);\
}

#define CREATION_FUNC(classname) &classname::createInstance

}