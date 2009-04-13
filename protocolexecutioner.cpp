//
// C++ Implementation: protocolexecutioner
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "protocolexecutioner.h"
#include "protocolsegment.h"
#include "conversation.h"
#include "protocol.h"
#include <QDebug>

namespace PDS {

ProtocolExecutioner::ProtocolExecutioner() : ComponentContainer(ProtocolComponent::ProtocolExecutioner){

}


ProtocolExecutioner::~ProtocolExecutioner(){

}


}


/*!
    \fn PDS::ProtocolExecutioner::isValidType(PDS::ProtocolComponent* component) const
 */
bool PDS::ProtocolExecutioner::isValidType(PDS::ProtocolComponent* component) const{
	return component->type() == ProtocolComponent::Protocol;
}


/*!
    \fn PDS::ProtocolExecutioner::setBackPointer(PDS::ProtocolComponent* component)
 */
void PDS::ProtocolExecutioner::setBackPointer(PDS::ProtocolComponent* component){
	static_cast<PDS::Protocol*>(component)->executioner_ = this;
}

void PDS::ProtocolExecutioner::report() const{
	qDebug() << "\n------------ Reporting ----------------\n";
	for(int i=0;i<size();++i){
		PDS::ComponentContainer* p = static_cast<PDS::ComponentContainer*>(at(i));
		qDebug().nospace() << QString("Protocol @ %1").arg(i) << p;
		for(int j=0;j<p->size();++j){
			PDS::ProtocolSegment* s = static_cast<PDS::ProtocolSegment*>(p->at(j));
			qDebug().nospace() << QString(" ProtocolSegment @ %1").arg(j) << s;
			for(int k=0;k<s->size();++k){
				PDS::Conversation* c = static_cast<PDS::Conversation*>(s->at(k));
				//qDebug().nospace() << QString("   Conversatin @ %1").arg(k) << c;
				qDebug().nospace() << ">> " << c->request().message().trimmed()  << " @ " << c->executedAt().toString("MMMM dd yyyy hh:mm:ss.zzz") << " " << c->isDelayed() << "/" << c->delayUntill();
				qDebug().nospace() << "<< " << c->response().message().trimmed() << " @ " << c->finishedAt().toString("MMMM dd yyyy hh:mm:ss.zzz");
			}
			qDebug() << "----- Tickets Collected -----";
			QStringList ticketKeys = s->ticketKeys();
			QStringList::const_iterator it = ticketKeys.constBegin();
			for(;it!=ticketKeys.constEnd();++it){
				qDebug().nospace() << *it << " : " << s->ticket(*it).toString();
			}
		}
		qDebug() << "\n";
	}
}
