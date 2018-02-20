#pragma once
#include "..\\UserEvents.h"
#include <windows.h> // For colored console

class UserEvents_MVN : public UserEvents
{
public:
	UserEvents_MVN();
	~UserEvents_MVN();

protected:

	void UserEvents_MVN::Print(std::string Message, int OutputColor, int DefaultColor = 7, bool IsInstruction = false);
		 
	void UserEvents_MVN::InitMVN(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::FILE_INPUT(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::FILE_OUTPUT(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::MEMDUMP_LOAD(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::MEMDUMP(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::MEMPRINT(const std::vector<boost::any>& Parameters);
		 
	void UserEvents_MVN::PRINTREG(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::InstructionDecode(const std::vector<boost::any> &Parameters);
		 
	void UserEvents_MVN::Add(const std::vector<boost::any> &Parameters);

private:

	virtual void UserEvents_MVN::BuildUFPAliasMap();
};

