#ifndef DIALOG_H
#define DIALOG_H

#include <QtGui/QDialog>
#include <QAbstractSocket>

namespace Ui{
	class DialogClass;
}

namespace PDS{
	class ProtocolExecutioner;
	class Protocol;
	class ProtocolSegment;
	class Conversation;
	class SocketMessage;
}

class QSslSocket;

using namespace PDS;

class Dialog : public QDialog{
	Q_OBJECT
	private:
		PDS::ProtocolExecutioner* executioner;
		PDS::Protocol*            msnProtocol;
		PDS::ProtocolSegment*     initSegment;
		PDS::ProtocolSegment*     twnSegment;
		PDS::ProtocolSegment*     nexusSegment;
		PDS::ProtocolSegment*     nexusAuthSegment;
	public:
		Dialog(QWidget *parent = 0);
		~Dialog();
	private:
		Ui::DialogClass *ui;
	public slots:
		void startSlot();
		void reportSlot();
		void twnSlot();
		void nexusSetupSlot();
		void nexusAuthFinishedSlot();
};

#endif // DIALOG_H
