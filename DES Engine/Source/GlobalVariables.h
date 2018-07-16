// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2018
// C++ Core "Standard" by Bjarne Stroustrup: https://goo.gl/4bziNu

#ifndef H_GLOBALVARIABLES
#define H_GLOBALVARIABLES
#pragma once

#include <typeinfo> // Where is this being used?
#include <string>
#include <unordered_map>
#include <boost/any.hpp> //C++17: Update to std::any

namespace DESE {
	class GlobalVariables
	{

	public:
		void ClearAllVariables();

		void	VarSet(const std::string Key, const boost::any Value);
		void	VarDel(const std::string Key);
		bool	VarExists(const std::string Key) const;

		template <typename T>
		T				VarGet_casted(const std::string Key) const;
		boost::any		VarGet(const std::string Key) const;
		std::string		VarGet_String(const std::string Key) const;
		std::string		VarGet_Type(const std::string Key) const;

	protected:
		
		std::unordered_map<std::string, boost::any> VarMap;

	}; //class GlobalVariables

	// Template Definition
	template<typename T>
	T GlobalVariables::VarGet_casted(const std::string Key) const
	{
		return boost::any_cast<T>(VarMap.at(Key));
	}

} // namespace DESE
#endif //H_GLOBALVARIABLES
