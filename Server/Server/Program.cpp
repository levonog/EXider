#include "EXider.h"
namespace EXider {
	Program::Program( const std::string& m_fileName, const std::string& m_path, const std::string& m_arguments ):
	m_fileName(m_fileName), m_path(m_path), m_arguments(m_arguments){

	}
	Program::Program( const std::string& m_fileName, const std::string& m_path ):Program(m_fileName,m_path,"") {

	}
	Program::Program( const std::string& fullPathWithArguments ) { // TODO
	 
	}
	const std::string Program::getFileName() const {
		return m_fileName;
	}
	const std::string Program::getPath() const {
		return m_path;

	}
	const std::string Program::getArguments() const {
		return m_arguments;

	}
	const std::string Program::getFullPath() const {
		return m_path + m_fileName;

	}
	const std::string Program::getFullPathWithArguments() const	{
		return m_path + m_fileName + " " + m_arguments;

	}
}