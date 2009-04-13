//
// C++ Interface: protocolexecutioner
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSPROTOCOLEXECUTIONER_H
#define PDSPROTOCOLEXECUTIONER_H

#include <componentcontainer.h>

namespace PDS{
	class ProtocolComponent;
}

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class ProtocolExecutioner : public ComponentContainer{
	Q_OBJECT
	public:
    ProtocolExecutioner();
    ~ProtocolExecutioner();
	public:
    bool isValidType(PDS::ProtocolComponent* component) const;
    void setBackPointer(PDS::ProtocolComponent* component);
	public:
		void report() const;
};

}

#endif
