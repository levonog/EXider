#pragma once
#include "EXider.h"
namespace EXider {
	class Program {
		std::string m_fileName;
		std::string m_path;
		std::vector<std::string> m_arguments;
		void deleteWhitespaces(std::string & str);
        void parseArguments( const std::string& argv );
	public:
		Program( const std::string& fileName, const std::string& path, const std::string& arguments );
		Program( const std::string& fileName, const std::string& path );
		Program( const std::string& fullPathWithArguments );
		const std::string& getFileName() const;                     // Return name of executing file
		const std::string& getPath() const;                         // Return path of executing file 
		const std::vector<std::string >& getArguments() const;      // Return arguments (each parameter is alone)
        const std::string getArgumentsString() const;               // Return arguments like one line string
		const std::string getFullPath() const;                      // Return full path of executing file (Path + File name)
		const std::string getFullPathWithArguments() const;         // Return Path + File name + String of arguments
	};
}