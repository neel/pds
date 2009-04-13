#include "debug_helper.h"
#include <QDebug>
#include "protocolcomponent.h"

QString componentName(int t){
	switch(t){
		case PDS::ProtocolComponent::SocketMessage:
			return "SocketMessage";
			break;
		case PDS::ProtocolComponent::Conversation:
			return "Conversation";
			break;
		case PDS::ProtocolComponent::ProtocolSegment:
			return "ProtocolSegment";
			break;
		case PDS::ProtocolComponent::Protocol:
			return "Protocol";
			break;
		case PDS::ProtocolComponent::ProtocolExecutioner:
			return "ProtocolExecutioner";
			break;
		default:
			return "InValid";
	}
}
