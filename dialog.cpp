#include "dialog.h"
#include "ui_dialog.h"

#include "protocolexecutioner.h"
#include "protocol.h"
#include "protocolsegment.h"
#include "conversation.h"
#include "socketmessage.h"

#include <QSslSocket>
#include <QUrl>
#include <QHttpResponseHeader>
#include <QNetworkCookie>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::DialogClass){
	ui->setupUi(this);

	executioner = new PDS::ProtocolExecutioner;

	msnProtocol = new PDS::Protocol;
		msnProtocol->addHint("email", "labrat__@hotmail.com");

	initSegment = new PDS::ProtocolSegment;
		initSegment->setHost("messenger.hotmail.com");
		initSegment->setPort(1863);

	twnSegment  = new PDS::ProtocolSegment;
		twnSegment->setDelay(0);
		connect(twnSegment, SIGNAL(beforeExecution()), this, SLOT(twnSlot()));

	nexusSegment= new PDS::ProtocolSegment;
		nexusSegment->setHost("nexus.passport.com");
		nexusSegment->setPort(443);
		nexusSegment->useSSL(true);
		nexusSegment->setStateLess(true);
		nexusSegment->setDelay(1);

	nexusAuthSegment = new PDS::ProtocolSegment();
		nexusAuthSegment->addHint("email", QUrl::toPercentEncoding("labrat__@hotmail.com"));
		nexusAuthSegment->addHint("pwd", QUrl::toPercentEncoding("123456"));
		nexusAuthSegment->useSSL(true);
		nexusAuthSegment->setStateLess(true);
		nexusAuthSegment->setPort(443);
		nexusAuthSegment->setDelay(2);
		connect(nexusAuthSegment, SIGNAL(beforeExecution()), this, SLOT(nexusSetupSlot()));
		connect(nexusAuthSegment, SIGNAL(finished()), this, SLOT(nexusAuthFinishedSlot()));

	*msnProtocol << initSegment << twnSegment << nexusSegment << nexusAuthSegment;
	*executioner << msnProtocol;

	*initSegment << "VER 1 MSNP11 CVR0\r\n" << "CVR 2 0x0409 win 4.10 i386 MSNMSGR 5.0.0544 MSMSGS $../:email$\r\n"
							 << initSegment->newConversation("USR 3 TWN I $../:email$\r\n", QRegExp("XFR \\d+ NS (.+)\\:(\\d+) 0 (.+)\\:(\\d+)"), QStringList() << "nsIp" << "nsPort" << "currentIp" << "currentPort");

	*twnSegment  << "VER 1 MSNP11 CVR0\r\n" << "CVR 2 0x0409 win 4.10 i386 MSNMSGR 5.0.0544 MSMSGS $../:email$\r\n"
							 << twnSegment->newConversation("USR 3 TWN I $../:email$\r\n", QRegExp("USR \\d+ TWN S .+,\\s*(lc\\=.+)$"), QStringList() << "Challenge");

	*nexusSegment     << nexusSegment->newConversation("GET /rdr/pprdr.asp HTTP/1.0\r\n\r\n", QRegExp("DALogin\\=([^\\,\\/]+)\\/([^\\,]+)\\,"), QStringList() << "DALoginHost" << "DALoginPath");

	*nexusAuthSegment << nexusAuthSegment->newConversation();
}

Dialog::~Dialog(){
	delete ui;
}

void Dialog::startSlot(){
	executioner->run();
}

void Dialog::reportSlot(){
	executioner->report();
}

void Dialog::nexusSetupSlot(){
	nexusAuthSegment->setHost(nexusSegment->ticket("DALoginHost").toString());
	static_cast<PDS::Conversation*>(nexusAuthSegment->at(0))->request().setHintedMessage((QString("GET /%1 HTTP/1.1\r\nAuthorization: Passport1.4 OrgVerb=GET,OrgURL=http%3A%2F%2Fmessenger%2Emsn%2Ecom").arg(nexusSegment->ticket("DALoginPath").toString()))+(QString(",sign-in=$3:email$,pwd=$pwd$,%1\r\nHost: login.passport.com\r\n\r\n").arg(twnSegment->ticket("Challenge").toString().trimmed())));
}

void Dialog::twnSlot(){
	twnSegment->setHost(initSegment->ticket("nsIp").toString());
	twnSegment->setPort(QVariant(initSegment->ticket("nsPort")).toInt());
}

void Dialog::nexusAuthFinishedSlot(){
	qDebug() << "\n\n-----------------\n\n" << nexusAuthSegment->httpResponseHeader().toString();
	if(nexusAuthSegment->httpResponseHeader().statusCode() == 200){
		QString authString = nexusAuthSegment->httpResponseHeader().value("Authentication-Info");
		QRegExp da_status("da-status\\=(success|failed)");
		if(da_status.indexIn(authString) != -1 && da_status.cap(1) == "success"){
			QRegExp t_extractor("from-PP\\='(.+)'");
			if(t_extractor.indexIn(authString) != -1){
				QString t = t_extractor.cap(1);
				*twnSegment << QString("USR 7 TWN S %1\r\n").arg(t);
				twnSegment->run();
				return;
			}
		}
	}
}
