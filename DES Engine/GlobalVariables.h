#pragma once
#include <boost/any.hpp>
#include <string>
#include <unordered_map>

class GlobalVariables
{

public:
	GlobalVariables();
	~GlobalVariables();

	void ClearAllVariables();

	void				  VarSet(const std::string Key, const boost::any Value);
	boost::any		const VarGet(const std::string Key, const boost::any DefaultNotFound = 0);

	// DANGEROUS - I don't know what happens when you edit the contents of this pointer that is a boost::any
	void*			const VarGet_ptr(const std::string Key);

	std::string		const VarGet_Type	(const std::string Key);

	char			const VarGet_Char	(const std::string Key);
	std::string		const VarGet_String	(const std::string Key);
	int				const VarGet_Int	(const std::string Key);
	unsigned int	const VarGet_uInt	(const std::string Key);
	long			const VarGet_Long	(const std::string Key);
	unsigned long	const VarGet_uLong	(const std::string Key);
	float			const VarGet_Float	(const std::string Key);
	double			const VarGet_Double	(const std::string Key);


private: 

	std::unordered_map<std::string, boost::any> VarMap;
};

