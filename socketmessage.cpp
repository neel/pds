//
// C++ Implementation: socketmessage
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "socketmessage.h"
#include "protocolsegment.h"
#include "debug_helper.h"
#include "protocol.h"
#include "protocolexecutioner.h"
#include <QHttpHeader>

namespace PDS {

SocketMessage::SocketMessage() : ProtocolComponent(ProtocolComponent::SocketMessage){
	executed_ = false;
	hasTickets = false;
	useHints = false;
	header = 0x0;
}

SocketMessage::SocketMessage(PDS::Conversation* c) : ProtocolComponent(ProtocolComponent::SocketMessage), conversation_(c){
	executed_ = false;
	hasTickets = false;
	useHints = false;
	header = 0x0;
}

SocketMessage::SocketMessage(const QString& data) : ProtocolComponent(), msg(data){

}

SocketMessage::~SocketMessage(){

}


}

PDS::ComponentContainer*  PDS::SocketMessage::targetComponent(const QString& hintPath) const{
	QString targetPath = hintPath.split(':').at(0);
	QRegExp r("(\\d+)$");
	PDS::ComponentContainer* target = 0x0;
	int i = r.indexIn(targetPath);//i might be -1 if not found else it would be +ve
	if(i >= 0){
		int index = QVariant(r.cap(1)).toInt();//might be 0 if \d is not there in the targetPath
		if(i == 0)//No ../ Is Present There
			target = conversation()->protocolSegment()->protocol();
		else{
			int backCount = targetPath.mid(0, i).count("../");
			if(backCount > 1)
				backCount = 1;
			switch(backCount){
				case 0:
					target = conversation()->protocolSegment()->protocol();
					break;
				case 1:
					target = conversation()->protocolSegment()->protocol()->executioner();
					break;
			}
		}
		return static_cast<PDS::ComponentContainer*>(target->at(index));
	}else{//Its only ../ There
		int backCount = targetPath.count("../");
		if(backCount > 2)
			backCount = 2;
		switch(backCount){
			case 0:
				target = conversation()->protocolSegment();
				break;
			case 1:
				target = conversation()->protocolSegment()->protocol();
				break;
			case 2:
				target = conversation()->protocolSegment()->protocol()->executioner();
				break;
		}
		return target;
	}
}

QString PDS::SocketMessage::hintKey(const QString& hintPath) const{
	QStringList hintPathParts = hintPath.split(':');
	QString ret;
	if(hintPathParts.size() > 2)
		return QString();
	else if(hintPathParts.size() == 1){
		//qDebug() << componentName(type()) << ":hintKey() : " << hintPath.left(hintPath.length()-1);
		ret = hintPath;
	}else{
		//qDebug() << componentName(type()) << ":hintKey() : " << hintPathParts.at(1).left(hintPathParts.at(1).length()-1);
		ret = hintPathParts.at(1);
	}
	if(ret.endsWith('$'))
		ret = ret.left(ret.length()-1);
	if(ret.startsWith('$'))
		ret = ret.right(ret.length()-1);
	return ret;
}

bool PDS::SocketMessage::hintExists(const QString& hintPath) const{
	return targetComponent(hintPath)->hasHint(hintKey(hintPath));
}

QVariant PDS::SocketMessage::getHint(const QString& hintPath) const{
	return targetComponent(hintPath)->hint(hintKey(hintPath));
}

void PDS::SocketMessage::setMessage(const QString& data){
	msg = data;
}

void PDS::SocketMessage::setHintedMessage(const QString& data){
	setMessage(data);
	QString c = data.simplified();
	int i=0;
	QRegExp hintsExtractor("(\\$[^\\$]+\\$)");
	while(i >= 0 && i < c.length()){
		i = c.indexOf(hintsExtractor, i);
		//qDebug() << i << c << hintsExtractor.capturedTexts();
		if(hintsExtractor.numCaptures() >= 1){
			QString key = hintsExtractor.cap(1);
			i+=hintsExtractor.cap(0).length();
			if(key.length() > 0 && !hints.contains(key))
				hints << key;
		}else
			return;
	}
	useHints = hints.size() > 0;
}

/*const*/ QString/*&*/ PDS::SocketMessage::message() const{
	//qDebug() << "useHints : " << useHints;
	QString r = msg;
	if(header != 0x0){
		r = header->toString();
		r += "\r\n";
	}
	if(!useHints)
		return r;
	else{
		QString /*&*/ data = r;
		foreach(const QString& d, hints){
			//qDebug() << " ^:- Hint => " << d;
			if(hintExists(d)){
				data.replace(d, getHint(d).toString());
			}else{
				qDebug() << " ^:- Hint not available for " << d;
				QString change = d;
				emit conversation()->protocolSegment()->hintNotFound(change);
				if(d != change)
					data.replace(d, change);
			}
		}
		return data;
	}
}

PDS::Conversation* PDS::SocketMessage::conversation() const{
	return conversation_;
}

bool PDS::SocketMessage::isValid() const{
	return ticketExtractorRegexp.isEmpty() || msg.indexOf(ticketExtractorRegexp) >= 0;
}

void PDS::SocketMessage::setTicketCounter(const QRegExp& r, QStringList t){
	ticketExtractorRegexp = r;
	tickets = t;
	hasTickets = true;
}

void PDS::SocketMessage::extractTickets() /*const*/{
	if(hasTickets){
		//qDebug() << " --- " << componentName(type()) << "::extractTickets()";
		QString data = msg;
		data.replace(QRegExp("\\r\\n"), "  ");
		ticketExtractorRegexp.indexIn(data);
		QStringList matches = const_cast<QRegExp&>(ticketExtractorRegexp).capturedTexts();
		matches.takeFirst();
		//qDebug() << " --- " << componentName(type()) << "::extractTickets() Matches:  " << matches.count();
		for(int i=0;i<tickets.size();++i){
			conversation()->protocolSegment()->addTicket(tickets.at(i), (i<matches.count()) ? matches.at(i) : "");
		}
	}
}

QHttpHeader& PDS::SocketMessage::asHttpHeader() const{
	QString data = message();
	int i = data.indexOf("\r\n\r\n");
	data = i >= 0 ? data.mid(0, i) : "";
	header = (type_ == Request) ? dynamic_cast<QHttpHeader*>(new QHttpRequestHeader(data)) : dynamic_cast<QHttpHeader*>(new QHttpResponseHeader(data));
	return *header;
}

QList<QNetworkCookie> PDS::SocketMessage::cookieList() const{
	QHttpHeader& headers = asHttpHeader();
	//qDebug() << headers.keys();
	if(headers.keys().count("Set-Cookie") <= 0 )
		return QList<QNetworkCookie>();
	QString cookieString;
	typedef QPair<QString, QString> StringPairT;
	foreach(StringPairT p, headers.values()){
		if(p.first.trimmed() == "Set-Cookie")
			cookieString += QString("Set-Cookie: %1\r\n").arg(p.second.trimmed());
	}
	//qDebug() << "::: " << cookieString;
	qDebug() << "::: " << QNetworkCookie::parseCookies(cookieString.toLatin1()).size();
	return QNetworkCookie::parseCookies(cookieString.toLatin1());
}

void PDS::SocketMessage::run(){}
