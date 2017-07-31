// Project for "PCS3216 - Programming Systems"
// Polytechnic School of the University of Sao Paulo
// Copyright Pedro Henrique Lage Furtado de Mendonca - 2017

#ifndef GLOBVAR
#define GLOBVAR


#pragma once
#include <typeinfo>
#include <string>
#include <unordered_map>
#include <boost/any.hpp>


class GlobalVariables
{

public:
	GlobalVariables();
	~GlobalVariables();

	void ClearAllVariables();

	void				  VarSet(const std::string Key, const boost::any Value);
	boost::any		const VarGet(const std::string Key, const boost::any DefaultNotFound = 0);
	void				  VarDel(const std::string Key);

	// DANGEROUS - I don't know what happens when you edit the contents of this pointer that is a boost::any
	boost::any*		const VarGet_ptr(const std::string Key);

	bool			const VarExists(const std::string Key);
	std::string		const VarGet_Type	(const std::string Key);

	char			const VarGet_Char	(const std::string Key, char			DefaultNotFound = 0		, char				DefaultBadCast = -1);
	std::string		const VarGet_String	(const std::string Key, std::string		DefaultNotFound = "NF"	, std::string		DefaultBadCast = "BC");
	int				const VarGet_Int	(const std::string Key, int				DefaultNotFound = 0		, int				DefaultBadCast = -1);
	unsigned int	const VarGet_uInt	(const std::string Key, unsigned int	DefaultNotFound = 0		, unsigned int		DefaultBadCast = -1);
	long			const VarGet_Long	(const std::string Key, long			DefaultNotFound = 0		, long				DefaultBadCast = -1);
	unsigned long	const VarGet_uLong	(const std::string Key, unsigned long	DefaultNotFound = 0		, unsigned long		DefaultBadCast = -1);
	float			const VarGet_Float	(const std::string Key, float			DefaultNotFound = 0.0	, float				DefaultBadCast = -0.1);
	double			const VarGet_Double	(const std::string Key, double			DefaultNotFound = 0.0	, double			DefaultBadCast = -0.1);


private: 

	std::unordered_map<std::string, boost::any> VarMap;
};

#endif
