//
// C++ Interface: componentcontainer
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef PDSCOMPONENTCONTAINER_H
#define PDSCOMPONENTCONTAINER_H

#include <protocolcomponent.h>
#include <QList>

namespace PDS {

/**
	@author Neel Basu <neel.basu.z@gmail.com>
*/
class ComponentContainer : public ProtocolComponent{
	Q_OBJECT
	protected:
    QMap<int, int> waitingList;
    mutable int lastExecuted_;
    mutable int lastFinished_;
    ProtocolComponent* currentComponent;
		QList<PDS::ProtocolComponent*> components;
		QMap<QString, QVariant> hints_;
	private:
		bool pause_;
	public:
		void pause(bool flag=true);
		bool isPaused() const;
		void resume();
	public:
		ComponentContainer(ComponentType t);
		virtual ~ComponentContainer();
    bool atEnd() const;
    PDS::ProtocolComponent* current() const;
    PDS::ProtocolComponent* last() const;
    virtual void execute();
    void incrementLastFinished();
    virtual void run();
		virtual bool isValidType(PDS::ProtocolComponent* component) const = 0;
		virtual void setBackPointer(PDS::ProtocolComponent* component) = 0;
	private:
    virtual void execNew();
	signals:
    void beforeExecution(int);
		void executed(int);
		void finished(int);
    void positionChanged(int);
    void progressChanged(int);
	private slots:
    void somethingFinishedSlot();
	protected:
    virtual void processComponent(ProtocolComponent* c, int l);
	public:
		void append(ProtocolComponent* component);
		void append(const QList<ProtocolComponent*>& components);
		virtual PDS::ProtocolComponent* at(int i) const;
		void clear();
		bool empty() const;
		void insert(int i, ProtocolComponent* value);
		int length() const;
		int size() const;
		int count() const;
		void move(int from, int to);
		void prepend(ProtocolComponent* component);
		void removeAt(int i);
	public:
		virtual bool appendable() const{return true;}
		virtual bool prependable() const{return true;}
	public:
		bool hasHint(const QString& key) const;
		QVariant hint(const QString& key) const;
		void addHint(const QString& key, const QVariant& val);
	public:
		PDS::ComponentContainer& operator<<(PDS::ProtocolComponent* component);
};

}

#endif
