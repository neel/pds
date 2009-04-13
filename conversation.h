//
// C++ Interface: conversation
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSCONVERSATION_H
#define PDSCONVERSATION_H

#include <protocolcomponent.h>
#include "socketmessage.h"

namespace PDS{
	class ProtocolSegment;
}

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class Conversation : public ProtocolComponent{
	friend class ProtocolSegment;
	Q_OBJECT
	private:
		PDS::ProtocolSegment* protocolSegment_;
		PDS::SocketMessage request_;
    PDS::SocketMessage response_;
	public:
    Conversation();
		Conversation(const QString& msg);
		Conversation(const QString& msg, int delay);
    ~Conversation();
	public:
    void run();
	public:
		const PDS::SocketMessage& request() const;
		const PDS::SocketMessage& response() const;
		PDS::SocketMessage& request();
		PDS::SocketMessage& response();
		PDS::ProtocolSegment* protocolSegment() const;
	public:
		bool sent();
		bool recieved();
};

}

#endif
