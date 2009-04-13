//
// C++ Implementation: protocolsegment
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "protocolsegment.h"
#include "conversation.h"
#include "debug_helper.h"
#include "helper.h"
#include <QTcpSocket>
#include <QSslSocket>

namespace PDS {

ProtocolSegment::ProtocolSegment(bool useSSL) : ComponentContainer(ProtocolComponent::ProtocolSegment), socket_(0x0), ssl_(useSSL), stateLess_(false), stateLessBuffer(&stateLessBufferArray){

}

ProtocolSegment::ProtocolSegment(QAbstractSocket* s, bool useSSL): ComponentContainer(ProtocolComponent::ProtocolSegment), ssl_(useSSL), stateLess_(false), stateLessBuffer(&stateLessBufferArray){
	socket_ = s;
}

ProtocolSegment::~ProtocolSegment(){
	QList<PDS::Conversation*>::iterator i = pool.begin();
	for(;i != pool.end();++i){
		delete *i;
	}
}


}

PDS::Conversation* PDS::ProtocolSegment::newConversation(){
	PDS::Conversation* c = new PDS::Conversation;
	pool << c;
	return c;
}

PDS::Conversation* PDS::ProtocolSegment::newConversation(const QString& requestString){
	PDS::Conversation* c = newConversation();
	c->request().setHintedMessage(requestString);
	return c;
}

PDS::Conversation* PDS::ProtocolSegment::newConversation(const QString& requestString, const QRegExp& ticketExtractorRegExp, const QStringList& ticketKeys){
	PDS::Conversation* c = newConversation(requestString);
	c->response().setTicketCounter(ticketExtractorRegExp, ticketKeys);
	return c;
}

QHttpRequestHeader& PDS::ProtocolSegment::httpRequestHeader(){
	//if not stateLess_ ERROR
		Q_ASSERT_X(stateLess_, "PDS::ProtocolSegment::httpRequestHeader()", "Extraction as HTTP Header is not allowed in Stateful Protocols");
	//if size != 1 ERROR (QList assert Failure)
		Q_ASSERT_X(size() == 1, "PDS::ProtocolSegment::httpRequestHeader()", QString("Expected only 1 Conversation but %1 exists").arg(size()).toLatin1());
	return static_cast<QHttpRequestHeader&>(at(0)->request().asHttpHeader());
}

const QHttpRequestHeader& PDS::ProtocolSegment::httpRequestHeader() const{
	//if not stateLess_ ERROR
		Q_ASSERT_X(stateLess_, "PDS::ProtocolSegment::httpRequestHeader() const", "Extraction as HTTP Header is not allowed in Stateful Protocols");
	//if size != 1 ERROR (QList assert Failure)
		Q_ASSERT_X(size() == 1, "PDS::ProtocolSegment::httpRequestHeader() const", QString("Expected only 1 Conversation but %1 exists").arg(size()).toLatin1());
	return static_cast<const QHttpRequestHeader&>(at(0)->request().asHttpHeader());
}

QHttpResponseHeader& PDS::ProtocolSegment::httpResponseHeader(){
	//if not stateLess_ ERROR
		Q_ASSERT_X(stateLess_, "PDS::ProtocolSegment::httpResponseHeader()", "Extraction as HTTP Header is not allowed in Stateful Protocols");
	//if size != 1 ERROR (QList assert Failure)
		Q_ASSERT_X(size() == 1, "PDS::ProtocolSegment::httpResponseHeader()", QString("Expected only 1 Conversation but %1 exists").arg(size()).toLatin1());
	return static_cast<QHttpResponseHeader&>(at(0)->response().asHttpHeader());
}

const QHttpResponseHeader& PDS::ProtocolSegment::httpResponseHeader() const{
	//if not stateLess_ ERROR
		Q_ASSERT_X(stateLess_, "PDS::ProtocolSegment::httpResponseHeader() const", "Extraction as HTTP Header is not allowed in Stateful Protocols");
	//if size != 1 ERROR (QList assert Failure)
		Q_ASSERT_X(size() == 1, "PDS::ProtocolSegment::httpResponseHeader() const", QString("Expected only 1 Conversation but %1 exists").arg(size()).toLatin1());
	return static_cast<const QHttpResponseHeader&>(at(0)->response().asHttpHeader());
}

QList<QNetworkCookie> PDS::ProtocolSegment::extractCookies() const{
	//if not stateLess_ ERROR
		Q_ASSERT_X(stateLess_, "PDS::ProtocolSegment::extractCookies() const", "Cookie Extraction is not allowed in Stateful Protocols");
	//if size != 1 ERROR (QList assert Failure)
		Q_ASSERT_X(size() == 1, "PDS::ProtocolSegment::extractCookies() const", QString("Expected only 1 Conversation but %1 exists").arg(size()).toLatin1());
	return at(0)->response().cookieList();
}

bool PDS::ProtocolSegment::canBeTreatedAsHTTP() const{
	return (stateLess_ && size()==1);
}

PDS::Conversation* PDS::ProtocolSegment::at(int i) const{
	return static_cast<PDS::Conversation*>(ComponentContainer::at(i));
}

/*!
    \fn PDS::ProtocolSegment::isValidType(PDS::ProtocolComponent* component) const
 */
bool PDS::ProtocolSegment::isValidType(PDS::ProtocolComponent* component) const{
	return component->type() == ProtocolComponent::Conversation;
}


/*!
    \fn PDS::ProtocolSegment::setBackPointer(PDS::ProtocolComponent* component)
 */
void PDS::ProtocolSegment::setBackPointer(PDS::ProtocolComponent* component){
	static_cast<PDS::Conversation*>(component)->protocolSegment_ = this;
}

void PDS::ProtocolSegment::connectedSlot(){
	qDebug() << " ~~~ " << "Socket Connected";
	if(!ssl_)execute();
}

void PDS::ProtocolSegment::encryptedSlot(){
	qDebug() << " ~~~ " << "Socket Encrypted";
	execute();
}

void PDS::ProtocolSegment::dataReceived(){
	//qDebug() << lastFinished_+1;
	QString rcvdMsg = socket_->readAll();
	if(!stateLess_){
		qDebug() << "<< " << rcvdMsg.trimmed();
		if(lastFinished_+1 >= components.size()){
			qDebug() << " ^:- " << lastFinished_+1 << components.size() << rcvdMsg;
			QList<PDS::ProtocolComponent*>::iterator it = components.begin();
			for(;it!=components.end();++it){
				PDS::Conversation* cnvr = static_cast<PDS::Conversation*>(*it);
				qDebug() << " >>>> " << cnvr->request().message();
				qDebug() << " <<<< " << cnvr->response().message();
			}
		}
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->response_.msg = rcvdMsg;
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->response_.extractTickets();
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->emitFinished();
	}else{
		//qDebug() << "<<< " << rcvdMsg.trimmed();
		stateLessBuffer << rcvdMsg;
	}

}

void PDS::ProtocolSegment::disconnectedSlot(){
	//qDebug() << " ^:_ " << host_ << ":" << port_ << "disconnectedSlot()";
	if(stateLess_){
		QString rcvdMsg = stateLessBuffer.readAll();
		qDebug() << "<< " << rcvdMsg.trimmed();
		stateLessBuffer.flush();
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->response_.msg = rcvdMsg;
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->response_.extractTickets();
		static_cast<PDS::Conversation*>(components.at(lastFinished_+1))->emitFinished();
	}
	socket_->disconnectFromHost();//Is it Correct ??
}

void PDS::ProtocolSegment::readChannelFinishedSlot(){
	//qDebug() << " ^:_ " << host_ << ":" << port_ << "readChannelFinishedSlot()";
	if(!stateLess_){

	}
	socket_->disconnectFromHost();//Is it Correct ??bool
}

void PDS::ProtocolSegment::socketStateChangedSlot(QAbstractSocket::SocketState s){
	//qDebug() << host_ << ":" << port_ << "Socket State Changed To " << s;
}

void PDS::ProtocolSegment::addTicket(const QString& key, const QVariant& value){
	tickets.insert(key, value);
}

const QString& PDS::ProtocolSegment::host() const{
	return host_;
}

const QAbstractSocket* PDS::ProtocolSegment::socket() const{
	return socket_;
}

QAbstractSocket* PDS::ProtocolSegment::socket(){
	return socket_;
}

void PDS::ProtocolSegment::useSSL(bool flag){
	ssl_ = flag;
}
bool PDS::ProtocolSegment::ssl() const{
	return ssl_;
}

void PDS::ProtocolSegment::setHost(const QString& addr){
	host_ = addr;
}

void PDS::ProtocolSegment::setPort(quint16 p){
	port_ = p;
}

quint16 PDS::ProtocolSegment::port() const{
	return port_;
}

PDS::Protocol* PDS::ProtocolSegment::protocol() const{
	return protocol_;
}

bool PDS::ProtocolSegment::isStateLess() const{
	return stateLess_;
}

void PDS::ProtocolSegment::setStateLess(bool flag){
	stateLess_ = flag;
}

QVariant PDS::ProtocolSegment::ticket(const QString& key) const{
	return tickets.value(key);
}

QStringList PDS::ProtocolSegment::ticketKeys() const{
	return tickets.keys();
}

void PDS::ProtocolSegment::run(){
	//qDebug() << " --- " << componentName(type()) << "::run()";
	if(!socket_){
		if(ssl_)
			socket_ = new QSslSocket;
		else
			socket_ = new QTcpSocket;
	}
	connect(socket_, SIGNAL(connected()), this, SLOT(connectedSlot()));
	if(ssl_)connect(static_cast<QSslSocket*>(socket_), SIGNAL(encrypted()), this, SLOT(encryptedSlot()));
	connect(socket_, SIGNAL(connected()), this, SIGNAL(socketConnected()));
	connect(socket_, SIGNAL(disconnected()), this, SIGNAL(socketDisconnected()));
	connect(socket_, SIGNAL(hostFound()), this, SIGNAL(hostFound()));
	connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(connectionError(QAbstractSocket::SocketError)));
	connect(socket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(socketStateChanged(QAbstractSocket::SocketState)));
	connect(socket_, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socketStateChangedSlot(QAbstractSocket::SocketState)));
	connect(socket_, SIGNAL(readyRead()), this, SLOT(dataReceived()));
	connect(socket_, SIGNAL(readChannelFinished()), this, SLOT(readChannelFinishedSlot()));
	connect(socket_, SIGNAL(disconnected()), this, SLOT(disconnectedSlot()));

	emit beforeConnecting();
	qDebug().nospace() << "Connecting to " << host_ << ":" << port_;
	if(!ssl_)
		socket_->connectToHost(host_, port_);
	else
		static_cast<QSslSocket*>(socket_)->connectToHostEncrypted(host_, port_);
}

PDS::ProtocolSegment& PDS::ProtocolSegment::operator<<(const QString& msg){
	PDS::Conversation* c = newConversation();
	if(msg.indexOf('$') >= 0)
		c->request().setHintedMessage(msg);
	else
		c->request().setMessage(msg);
	append(c);
	return *this;
}


bool PDS::ProtocolSegment::appendable() const{
	return (!stateLess_ || size() < 1);
}

bool PDS::ProtocolSegment::prependable() const{
	return (!stateLess_ || size() < 1);
}
