#include "EXider.h"
namespace EXider {
	Program::Program( const std::string& m_fileName, const std::string& m_path, const std::string& m_arguments ) :
		m_fileName( m_fileName ), m_path( m_path ), m_arguments( m_arguments ) {
		deleteWhitespaces( this->m_fileName );
		deleteWhitespaces( this->m_path );
		deleteWhitespaces( this->m_arguments );
	}
	Program::Program( const std::string& m_fileName, const std::string& m_path ) : Program( m_fileName, m_path, "" ) {

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
	const std::string Program::getFullPathWithArguments() const {
		return m_path + m_fileName + " " + m_arguments;

	}
	void Program::deleteWhitespaces( std::string & str ) {
		str = str.substr( str.find_first_not_of( ' ' ));
	}
}