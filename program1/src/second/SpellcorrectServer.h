
#ifndef __MYSP_SPELLCORRECTSERVER_H__
#define __MYSP_SPELLCORRECTSERVER_H__

#include "Configuration.h"
#include "Server.h"

namespace mysp
{

class SpellcorrectServer
: public Server{

	public:
		SpellcorrectServer(const Configuration &);
		void start();

	private:
		void onConnection(const TcpConnectionPtr &);
		void onMessage(const TcpConnectionPtr &);
		void onClose(const TcpConnectionPtr &);

};

}

#endif
