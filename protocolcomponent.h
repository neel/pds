//
// C++ Interface: protocolcomponent
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSPROTOCOLCOMPONENT_H
#define PDSPROTOCOLCOMPONENT_H

#include <QObject>
#include <QDateTime>
#include <QMap>

namespace PDS{
	class ComponentContainer;
}

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class ProtocolComponent : public QObject{
	Q_OBJECT
	friend class ComponentContainer;
	public:
		enum ComponentType{
			SocketMessage,
			Conversation,
			ProtocolSegment,
			Protocol,
			ProtocolExecutioner,
			InvalidType
		};
	protected:
		ComponentType type_;
		bool executed_;
		bool finished_;
    int delay_;
		QDateTime executionTime;
		QDateTime finishTime;
	public:
    PDS::ProtocolComponent::ComponentType type() const;
    bool isExecuted() const;
		bool isFinished() const;
		const QDateTime& executedAt() const;
		const QDateTime& finishedAt() const;
	public:
    ProtocolComponent(QObject *parent = 0);
		ProtocolComponent(ComponentType t);
    virtual ~ProtocolComponent();
    bool isDelayed() const;
    int delayUntill() const;
		void setDelay(int d);
	public:
		virtual void run() = 0;
	signals:
    void beforeExecution(ProtocolComponent*);
		void beforeExecution();
    void executed();
    void executed(ProtocolComponent*);
    void finished();
    void finished(ProtocolComponent*);
	protected:
    void emitExecuted();
    void emitFinished();
};

}

#endif
