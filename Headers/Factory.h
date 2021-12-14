#pragma once
#include <map>
#include <string>
#include <memory>
#include "EngineManagedClass.h"

namespace O3DCppEngine
{

	class Factory
	{
	private:
		// only the CppEngine can create and destroy the Factory
		Factory();
		~Factory();

		// map classname => static creation method
		std::map<std::string, createCppEngineClass>					mClassCreationMap;
		// map classname => singleton instance
		std::map<std::string, std::shared_ptr<EngineManagedClass>>	mSingletonMap;

		// generic getInstance is protected so the user always use the template method
		std::shared_ptr<EngineManagedClass>		genericGetInstance(const std::string& name) const;

		// generic getSingleton is protected so the user always use the template method
		std::shared_ptr<EngineManagedClass>		genericGetSingleton(const std::string& name);
	public:

		// register a new class using a generic class name and a static creation method
		void									registerClass(const std::string& name,createCppEngineClass func);
		// retrieve an instance of the class given its generic name
		template<typename T= EngineManagedClass>
		std::shared_ptr<T>		getInstance(const std::string& name) const
		{
			return std::static_pointer_cast<T>(genericGetInstance(name));
		}
		// retrieve a singleton instance given its generic name
		template<typename T = EngineManagedClass>
		std::shared_ptr<T>		getSingleton(const std::string& name)
		{
			return std::static_pointer_cast<T>(genericGetSingleton(name));
		}
		

		// CppEngine is a friend class so that it can create and destroy Factory
		friend class CppEngine;
	};
}