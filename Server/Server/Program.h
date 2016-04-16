#pragma once
#include "EXider.h"
namespace EXider {
	class Program {
		std::string m_fileName;
		std::string m_path;
		std::string m_arguments;
		void deleteWhitespaces(std::string & str);
	public:
		Program( const std::string& m_fileName, const std::string& m_path, const std::string& m_arguments );
		Program( const std::string& m_fileName, const std::string& m_path );
		Program( const std::string& fullPathWithArguments );
		const std::string getFileName() const;
		const std::string getPath() const;
		const std::string getArguments() const;
		const std::string getFullPath() const;
		const std::string getFullPathWithArguments() const;
	};
}