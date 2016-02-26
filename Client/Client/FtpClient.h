#pragma once
#include "EXider.h"
namespace EXider {

	class FtpClient {

	public:
		FtpClient( const std::string& IP, const std::string& Login, const std::string& Password );
		bool connected() const;
		void reConnect();
		void disconnect();
		void upload( const std::string filePathToUpload, const std::string filePathToSave ) const;
		void download( const std::string filePathToDownload, const std::string filePathToSave ) const;
	};

}