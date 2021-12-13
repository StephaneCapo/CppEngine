#include "Factory.h"

using namespace O3DCppEngine;

Factory::Factory()
{

}
Factory::~Factory()
{
	mSingletonMap.clear();
}

// register an new class in the Factory
void Factory::registerClass(const std::string& name, createCppEngineClass func)
{
	mClassCreationMap[name] = func;
}

std::shared_ptr<EngineManagedClass> Factory::getInstance(const std::string& name)
{
	// search class in map
	auto	 found = mClassCreationMap.find(name);
	// if class was found
	if (found != mClassCreationMap.end())
	{
		// call class creation
		return ((*found).second)();
	}
	return nullptr;
}

std::shared_ptr<EngineManagedClass> Factory::getSingleton(const std::string& name)
{
	// search if singleton already there
	auto found = mSingletonMap.find(name);
	// if class was found
	if (found != mSingletonMap.end())
	{
		// call class creation
		return (*found).second;
	}

	// else we need to create an instance and add it to the map
	std::shared_ptr<EngineManagedClass> inst = getInstance(name);
	if (inst)
	{
		mSingletonMap[name] = inst;
		return inst;
	}

	return nullptr;
}
