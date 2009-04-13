//
// C++ Implementation: protocol
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "protocol.h"
#include "protocolsegment.h"

namespace PDS {

Protocol::Protocol() : ComponentContainer(ProtocolComponent::Protocol){

}


Protocol::~Protocol(){

}


}


/*!
    \fn PDS::Protocol::isValidType(PDS::ProtocolComponent* component) const
 */
bool PDS::Protocol::isValidType(PDS::ProtocolComponent* component) const{
	return component->type() == ProtocolComponent::ProtocolSegment;
}


/*!
    \fn PDS::Protocol::setBackPointer(PDS::ProtocolComponent* component)
 */
void PDS::Protocol::setBackPointer(PDS::ProtocolComponent* component){
	static_cast<PDS::ProtocolSegment*>(component)->protocol_ = this;
}

PDS::ProtocolExecutioner* PDS::Protocol::executioner() const{
	return executioner_;
}
