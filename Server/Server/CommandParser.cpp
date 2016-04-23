#include "EXider.h"
using namespace EXider;
CommandParser::CommandParser( const std::string & command ) {
    parseCommand( command );
}

CommandParser::CommandParser() {

}

void CommandParser::parseCommand( const std::string & command ) {
    m_arguments.clear();
    m_command.clear();
    EXiderArgument temp;
    std::string temp_param = "";

    std::istringstream is( command );
    char k;

    is >> k;
    if ( k != '-' ) {
        is.putback( k );
        is >> m_command;
    }
    else
        is.putback( k );
    bool quotStarted = false, canBeArg = true;
    while ( is.get( k ) ) {
        if ( quotStarted && k != '"' ) {
            temp_param += k;
        }
        else if ( quotStarted ) {
            quotStarted = false;
            canBeArg = true;
            temp.parameters.push_back( temp_param );
            temp_param.clear();
        }
        else if ( k == '"' ) {
            quotStarted = true;
            canBeArg = false;
        }
        else if ( k == ' ' || k == '\t' ) {
            if ( !temp_param.empty() ) {
                temp.parameters.push_back( temp_param );
                temp_param.clear();
            }
            canBeArg = true;
        }
        else if ( k == '-' && canBeArg ) {
            if ( !temp.argument.empty() || !temp.parameters.empty() ) {
                m_arguments.push_back( temp );
                temp.argument.clear();
                temp.parameters.clear();
            }
            is >> temp.argument;
        }
        else {
            temp_param += k;
            canBeArg = false;
        }

    }
    if ( !temp_param.empty() )
        temp.parameters.push_back( temp_param );
    if ( !temp.argument.empty() || !temp.parameters.empty() )
        m_arguments.push_back( temp );
}

const std::string& CommandParser::command() const {
    return m_command;
}

const argList& CommandParser::arguments() const {
    return m_arguments;
}
