//
// C++ Interface: protocolsegment
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSPROTOCOLSEGMENT_H
#define PDSPROTOCOLSEGMENT_H

#include <QAbstractSocket>
#include <componentcontainer.h>
#include <QString>
#include <QVariant>
#include <QTcpSocket>
#include <QTextStream>
#include <QHttpRequestHeader>
#include <QHttpResponseHeader>
#include <QNetworkCookie>
#include "conversation.h"

namespace PDS{
	class ProtocolComponent;
	class Protocol;
	class Conversaton;
}

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class ProtocolSegment : public ComponentContainer{
	Q_OBJECT
	friend class PDS::Protocol;
	friend class PDS::SocketMessage;
	private:
		QString          host_;
		quint16          port_;
		QAbstractSocket* socket_;
		bool             connected_;
		PDS::Protocol*   protocol_;
		bool ssl_;
		bool stateLess_;
		QString  stateLessBufferArray;
		QTextStream stateLessBuffer;
	private:
    QList<PDS::Conversation*>   talks;///Conversations to be executed Serially
		QList<PDS::Conversation*>   pool;///Conversations Created By ProtocolSegment itself. Meant to be deleted by destructor
	  QMap<QString, QVariant>  tickets;///tickets resolved by Ticket Extractor RegExp from various Conversation's SocketMessage (Key Pair) [[ticketKey1 => ticketValue1], [ticketKey2 => ticketVal2]]
	public:
		ProtocolSegment(bool useSSL=false);
		ProtocolSegment(QAbstractSocket* s, bool useSSL=false);
    ~ProtocolSegment();
	public:
    bool isValidType(PDS::ProtocolComponent* component) const;
    void setBackPointer(PDS::ProtocolComponent* component);
	public:
		PDS::Conversation* newConversation();
		PDS::Conversation* newConversation(const QString& requestString);
		PDS::Conversation* newConversation(const QString& requestString, const QRegExp& ticketExtractorRegExp, const QStringList& ticketKeys);
		QHttpRequestHeader& httpRequestHeader();
		const QHttpRequestHeader& httpRequestHeader() const;
		QHttpResponseHeader& httpResponseHeader();
		const QHttpResponseHeader& httpResponseHeader() const;
		QList<QNetworkCookie> extractCookies() const;
		bool canBeTreatedAsHTTP() const;
		PDS::Conversation* at(int i) const;
	public:
		const QAbstractSocket* socket() const;
		QAbstractSocket* socket();
		void useSSL(bool flag=true);
		bool ssl() const;
		void setHost(const QString& addr);
		void setPort(quint16 p);
		const QString& host() const;
		quint16 port() const;
		PDS::Protocol* protocol() const;
		bool isStateLess() const;
		void setStateLess(bool flag=true);
	public:
    QVariant ticket(const QString& key) const;
		QStringList ticketKeys() const;
	public:
    void addTicket(const QString& key, const QVariant& value);
	public:
		void run();
	signals:
		void beforeConnecting();
		void socketConnected();
		void socketDisconnected();
		void hostFound();
		void connectionError(QAbstractSocket::SocketError);
		void socketStateChanged(QAbstractSocket::SocketState);
		void readChannelFinished(ProtocolSegment*);
		void hintNotFound(QString&);
	private slots:
		void connectedSlot();
		void encryptedSlot();
		void dataReceived();
		void readChannelFinishedSlot();
		void socketStateChangedSlot(QAbstractSocket::SocketState s);
		void disconnectedSlot();
	public:
		using ComponentContainer::operator<<;
	public:
		PDS::ProtocolSegment& operator<<(const QString& msg);
	public:
		bool appendable() const;
		bool prependable() const;
};

}

#endif
