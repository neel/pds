//
// C++ Interface: socketmessage
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSSOCKETMESSAGE_H
#define PDSSOCKETMESSAGE_H

#include "protocolcomponent.h"
#include <QDateTime>
#include <QRegExp>
#include <QStringList>
#include <QString>
#include <QNetworkCookie>

class QHttpHeader;

namespace PDS{
	class Conversation;
	class ProtocolSegment;
}

namespace PDS{

/**
	@author Neel Basu <neel.basu.z@gmail.com>
	@internal Is it really required to Inherit from ProtocolComponent
*/
class SocketMessage : public ProtocolComponent{
	Q_OBJECT
	friend class PDS::Conversation;
	friend class PDS::ProtocolSegment;
	private:
		QString hintKey(const QString& hintPath) const;
		PDS::ComponentContainer* targetComponent(const QString& hintPath) const;
		bool hintExists(const QString& hintPath) const;
		QVariant getHint(const QString& hintPath) const;
	private:
		enum MessageType{
			Request,
			Response
		};
	private:
		MessageType type_;
		mutable QHttpHeader* header;
		QString msg;
		QRegExp ticketExtractorRegexp;
		PDS::Conversation* conversation_;
		bool useHints;
		bool hasTickets;
		QStringList hints;//mailBox [$Hint1$, $Hint2$]
		QStringList tickets;//[ticketKey1, ticketKey2]
	public:
    SocketMessage();
		SocketMessage(PDS::Conversation* c);
		SocketMessage(const QString& data);
    ~SocketMessage();
	public:
		void setMessage(const QString& data);
		void setHintedMessage(const QString& data);
		QString message() const;
		inline PDS::Conversation* conversation() const;
		bool isValid() const;
		void setTicketCounter(const QRegExp& r, QStringList t);
		void extractTickets() /*const*/;
		QHttpHeader& asHttpHeader() const;
		QList<QNetworkCookie> cookieList() const;//Not Working
	private:
		inline bool isDelayed() const{return false;}
		inline int delayUntill() const{return -1;}
		inline void setDelay(int /*d*/){}
	public:
		void run();
};

}

#endif
