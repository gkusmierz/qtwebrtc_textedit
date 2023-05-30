#ifndef TESTWIDGET_H

#define TESTWIDGET_H

#include "talk/app/webrtc/peerconnectioninterface.h"
#include "ui_testwidget.h"
#include <QMainWindow>

class TestVideoCapturer;

class TestWidget : public QMainWindow, public Ui::TestWidget
{
	Q_OBJECT
public:
	TestWidget();
	~TestWidget();

	void setNewFrame(const QImage &img);
private slots:
	void onStartClicked();
	void onAnswerClicked();
	void onRemoteICEClicked();
	void onLocalSDPInfo(const QString &sdpText);
	void onLocalIceCandidate(const QString &iceCandidate);
private:
	cricket::VideoCapturer* OpenVideoCaptureDevice();
	TestVideoCapturer *m_pCapturer;

	talk_base::scoped_refptr<webrtc::PeerConnectionFactoryInterface> m_pcfIface;
	talk_base::scoped_refptr<webrtc::PeerConnectionInterface> m_peerConnection;
};

class TestSDObserver : public QObject, public talk_base::RefCountedObject<webrtc::CreateSessionDescriptionObserver>
{
	Q_OBJECT
public:
	TestSDObserver();
	~TestSDObserver();
	
	void OnSuccess(webrtc::SessionDescriptionInterface* desc);
 	void OnFailure(const std::string& error);
signals:
	void signalSDPText(const QString &sdp);
};


class TestConnectionObserver : public QObject, public webrtc::PeerConnectionObserver
{
	Q_OBJECT
public:
	TestConnectionObserver();
	~TestConnectionObserver();

	void OnError();
	void OnStateChange(webrtc::PeerConnectionObserver::StateType state_changed);
	void OnAddStream(webrtc::MediaStreamInterface* stream);
	void OnRemoveStream(webrtc::MediaStreamInterface* stream);
	void OnRenegotiationNeeded();
	void OnIceChange();
	void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
signals:
	void signalIceCandidate(const QString &iceCandidate);
};

#endif // TESTWIDGET_H
