//
// C++ Implementation: conversation
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "conversation.h"
#include "protocolsegment.h"
#include "debug_helper.h"

namespace PDS {

Conversation::Conversation() : ProtocolComponent(ProtocolComponent::Conversation), request_(this), response_(this){
	request_.type_ = PDS::SocketMessage::Request;
	response_.type_ = PDS::SocketMessage::Response;
}

Conversation::Conversation(const QString& msg) : ProtocolComponent(ProtocolComponent::Conversation), request_(this), response_(this){
	if(msg.indexOf('$') >= 0)
		request_.setHintedMessage(msg);
	else
		request_.setMessage(msg);
}

Conversation::Conversation(const QString& msg, int delay) : ProtocolComponent(ProtocolComponent::Conversation), request_(this), response_(this){
	if(msg.indexOf('$') >= 0)
		request_.setHintedMessage(msg);
	else
		request_.setMessage(msg);
	setDelay(delay);
}

Conversation::~Conversation(){

}


}

const PDS::SocketMessage& PDS::Conversation::request() const{
	return request_;
}

const PDS::SocketMessage& PDS::Conversation::response() const{
	return response_;
}

PDS::SocketMessage& PDS::Conversation::request(){
	return request_;
}

PDS::SocketMessage& PDS::Conversation::response(){
	return response_;
}

PDS::ProtocolSegment* PDS::Conversation::protocolSegment() const{
	return protocolSegment_;
}


bool PDS::Conversation::sent(){
	return isExecuted();
}

bool PDS::Conversation::recieved(){
	return isFinished();
}

/*!
    \fn PDS::Conversation::run()
 */
void PDS::Conversation::run(){
	//qDebug() << " --- " << componentName(type()) << "::run()";
	qDebug() << ">> " << request().message().trimmed();
	protocolSegment()->socket()->write(request().message().toLatin1());
	request().extractTickets();
	emitExecuted();
}
