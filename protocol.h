//
// C++ Interface: protocol
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSPROTOCOL_H
#define PDSPROTOCOL_H

#include <componentcontainer.h>

namespace PDS{
	class ProtocolComponent;
	class ProtocolExecutioner;
}

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class Protocol : public ComponentContainer{
	friend class PDS::ProtocolExecutioner;
	Q_OBJECT
	private:
		PDS::ProtocolExecutioner* executioner_;
	public:
    Protocol();
    ~Protocol();
	public:
    bool isValidType(PDS::ProtocolComponent* component) const;
    void setBackPointer(PDS::ProtocolComponent* component);
	public:
		PDS::ProtocolExecutioner* executioner() const;
};

}

#endif
