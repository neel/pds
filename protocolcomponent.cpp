//
// C++ Implementation: protocolcomponent
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "protocolcomponent.h"
#include <QVariant>

namespace PDS {

	ProtocolComponent::ProtocolComponent(QObject *parent) : QObject(parent), type_(ProtocolComponent::InvalidType){
	delay_ = -1;
	executed_ = false;
	finished_ = false;
}

ProtocolComponent::ProtocolComponent(ComponentType t) : QObject(0x0), type_(t){
	delay_ = -1;
	executed_ = false;
	finished_ = false;
}


ProtocolComponent::~ProtocolComponent(){

}


}


/*!
    \fn PDS::ProtocolComponent::executed() const
 */
bool PDS::ProtocolComponent::isExecuted() const{
	return executed_;
}


/*!
    \fn PDS::ProtocolComponent::type() const
 */
PDS::ProtocolComponent::ComponentType PDS::ProtocolComponent::type() const{
	return type_;
}


/*!
    \fn PDS::ProtocolComponent::finished() const
 */
bool PDS::ProtocolComponent::isFinished() const{
	return finished_;
}


/*!
    \fn PDS::ProtocolComponent::isDelayed() const
 */
bool PDS::ProtocolComponent::isDelayed() const{
	return delay_ > -1;
}

void PDS::ProtocolComponent::setDelay(int d){
	delay_ = d;
}

/*!
    \fn PDS::ProtocolComponent::delay() const
 */
int PDS::ProtocolComponent::delayUntill() const{
	return delay_;
}

const QDateTime& PDS::ProtocolComponent::executedAt() const{
	return executionTime;
}

const QDateTime& PDS::ProtocolComponent::finishedAt() const{
	return finishTime;
}

/*!
    \fn PDS::ProtocolComponent::emitFinished()
 */
void PDS::ProtocolComponent::emitFinished(){
	finished_ = true;
	finishTime = QDateTime::currentDateTime();
	emit finished();
	emit finished(this);
}


/*!
    \fn PDS::ProtocolComponent::emitExecuted()
 */
void PDS::ProtocolComponent::emitExecuted(){
	executed_ = true;
	executionTime = QDateTime::currentDateTime();
	emit executed();
	emit executed(this);
}
