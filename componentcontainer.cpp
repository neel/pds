//
// C++ Implementation: componentcontainer
//
// Description: 
//
//
// Author: Neel Basu <neel.basu.z@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "componentcontainer.h"
#include "debug_helper.h"
#include <QDebug>
#include <QVariant>

namespace PDS {

ComponentContainer::ComponentContainer(ComponentType t) : ProtocolComponent(t), pause_(false){
	lastExecuted_ = -1;
	lastFinished_ = -1;
}


ComponentContainer::~ComponentContainer(){

}

}

void PDS::ComponentContainer::pause(bool flag){
	pause_ = flag;
}

bool PDS::ComponentContainer::isPaused() const{
	return pause_;
}

void PDS::ComponentContainer::resume(){
	if(isPaused()){
		pause_ = false;
		this->ComponentContainer::run();
	}
}

/*!
    \fn PDS::ComponentContainer::atEnd() const
 */
bool PDS::ComponentContainer::atEnd() const{
	return (lastExecuted_ >= components.count());
}


/*!
    \fn PDS::ComponentContainer::current() const
 */
PDS::ProtocolComponent* PDS::ComponentContainer::current() const{
	return last();
}


/*!
    \fn PDS::ComponentContainer::last() const
 */
PDS::ProtocolComponent* PDS::ComponentContainer::last() const{
	++lastExecuted_;
	if(atEnd())
		return 0x0;
	return components.at(lastExecuted_);
}


/*!
    \fn PDS::ComponentContainer::excute()
 */
void PDS::ComponentContainer::execute(){
	//qDebug() << " ---- " << componentName(type()) << "::execute()";
	execNew();
}


/*!
    \fn PDS::ComponentContainer::incrementLastFinished()
 */
void PDS::ComponentContainer::incrementLastFinished(){
	++lastFinished_;
}


/*!
    \fn PDS::ComponentContainer::run()
 */
void PDS::ComponentContainer::run(){
	//qDebug() << " --- " << componentName(type()) << "::run()";
	execute();
}


/*!
    \fn PDS::ComponentContainer::executeNew()
 */
void PDS::ComponentContainer::execNew(){
	if(isPaused())
		return;
	//qDebug() << " ---- " << componentName(type()) << "::execNew()";
	ProtocolComponent* c = current();
	if(atEnd()){
		//qDebug() << " ^:- "  << "atEnd  " << QString("lastExecuted_:(%1), components.size():(%3)").arg(lastExecuted_).arg(components.size());;
		emitExecuted();
		return;
	}
	if(c == 0x0){
		//qDebug() << " ^:- " << componentName(type()) << c << " atEnd():" << atEnd() << QString("lastExecuted_:(%1), components.size():(%3)").arg(lastExecuted_).arg(components.size());
		return;
	}

	//qDebug() << " ::: " << c << componentName(c->type());

	if(dynamic_cast<ComponentContainer*>(c) == 0x0){
		if(!waitingList.empty()){
			--lastExecuted_;//This One has not been executed so Decreament
			//qDebug() << "\tHas Item In Waiting List returning";
			return;
		}
	}
	if(c->isDelayed() && !(components.at(c->delayUntill())->isFinished())){//Execution of The Current Item should be delayed untill the c->delayUntill() Item Finishes
		//qDebug() << "\tItem " << lastExecuted_ << " delayed Untill " << c->delayUntill() ;
		waitingList.insert(c->delayUntill(), lastExecuted_);
	}else{
		processComponent(c, (lastExecuted_));
	}
	emit positionChanged(lastExecuted_);
	execNew();
}


/*!
    \fn PDS::ComponentContainer::somethingFinishedSlot()
 */
void PDS::ComponentContainer::somethingFinishedSlot(){
	incrementLastFinished();
	//qDebug() << " +^~, " << componentName(type()) << "Item " << lastFinished_ << "/" << components.count() << " Finished ";
	if(lastFinished_ >= components.count()-1){
		//qDebug() << " +^~, " << componentName(type()) << "::somethingFinishedSlot() " << "Finished ";
		emitFinished();
		return;
	}
	ProtocolComponent* finishedComponent = components.at(lastFinished_);
	disconnect(finishedComponent, SIGNAL(finished()), this, SLOT(somethingFinishedSlot()));
	//qDebug() << "\tItem Finished" << lastFinished_ << "Has Candidate in Waiting List : " << waitingList.contains(lastFinished_);
	if(waitingList.contains(lastFinished_)){
		//qDebug() << "\t\tExecuting Item Delayed for above" << waitingList.value(lastFinished_);
		ProtocolComponent* c = components.at(waitingList.value(lastFinished_));
		if(components.at(waitingList.value(lastFinished_)-1)->isExecuted()){//Experimental
			processComponent(c, (lastFinished_));
		}
		waitingList.remove(lastFinished_);
		execNew();
	}
	emit finished(lastFinished_);
	finishedComponent->emitFinished();
	emit progressChanged(lastFinished_);
}


/*!
    \fn PDS::ComponentContainer::processComponent(ProtocolComponent* c, int l)
 */
void PDS::ComponentContainer::processComponent(ProtocolComponent* c, int l){
	//qDebug() << " ---- " << componentName(type()) << "::processComponent("<< componentName(c->type()) << "," << l <<")";
	emit beforeExecution(l);
	emit c->beforeExecution();
	emit c->beforeExecution(c);
	connect(c, SIGNAL(finished()), this, SLOT(somethingFinishedSlot()));
	c->run();
	emit executed(l);
	c->emitExecuted();
}

void PDS::ComponentContainer::append(ProtocolComponent* component){
	if(!appendable())return;
	if(isValidType(component)){
		setBackPointer(component);
		components.append(component);
	}
}

void PDS::ComponentContainer::append(const QList<ProtocolComponent*>& componentsList){
	if(!appendable())return;
	foreach(ProtocolComponent* c, componentsList){
		if(isValidType(c)){
			setBackPointer(c);
			components.append(c);
		}
	}
}

PDS::ProtocolComponent* PDS::ComponentContainer::at(int i) const{
	return components.at(i);
}

void PDS::ComponentContainer::clear(){
	components.clear();
}

bool PDS::ComponentContainer::empty() const{
	return components.empty();
}

void PDS::ComponentContainer::insert(int i, ProtocolComponent* value){
	if(!(appendable() && prependable()))return;
	components.insert(i, value);
}

int PDS::ComponentContainer::length() const{
	return components.count();
}

int PDS::ComponentContainer::size() const{
	return components.size();
}

int PDS::ComponentContainer::count() const{
	return components.count();
}

void PDS::ComponentContainer::move(int from, int to){
	components.move(from, to);
}

void PDS::ComponentContainer::prepend(ProtocolComponent* component){
	if(!prependable())return;
	if(isValidType(component)){
		setBackPointer(component);
		components.prepend(component);
	}
}

void PDS::ComponentContainer::removeAt(int i){
	components.removeAt(i);
}

bool PDS::ComponentContainer::hasHint(const QString& key) const{
	//qDebug() << componentName(type()) << ":hasHint() : " << "Searching for hint " << key;
	return hints_.contains(key);
}

QVariant PDS::ComponentContainer::hint(const QString& key) const{
	return hints_.value(key);
}

void PDS::ComponentContainer::addHint(const QString& key, const QVariant& val){
	hints_.insert(key, val);
	//qDebug() << componentName(type()) << "::addHint() : " << hints_.size();
}


PDS::ComponentContainer& PDS::ComponentContainer::operator<<(PDS::ProtocolComponent* component){
	append(component);
	return *this;
}
