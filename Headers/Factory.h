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

		std::map<std::string, createCppEngineClass>					mClassCreationMap;
		std::map<std::string, std::shared_ptr<EngineManagedClass>>	mSingletonMap;

	public:

		void									registerClass(const std::string& name,createCppEngineClass func);
		std::shared_ptr<EngineManagedClass>		getInstance(const std::string& name);
		std::shared_ptr<EngineManagedClass>		getSingleton(const std::string& name);

		friend class CppEngine;
	};
}