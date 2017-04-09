#ifndef DIRECTOR_COMPONENT_SOCKET
#	define DIRECTOR_COMPONENT_SOCKET
#	include <string>
#	include <mutex>
#	include "Component.h"

class SocketComponent : public Component
{
public:
	enum SocketComponentError {
		InvalidActorName = 100,
		InvalidPort,
		InvalidAddress,
		RequesterCreateFailed,
		RequesterConnectFailed,
		RequesterSendFailed,
		LocalResponderCreateFailed,
		LocalResponderBindFailed,
		RemoteResponderCreateFailed,
		RemoteResponderBindFailed,
	};

protected:
	void* m_lpContext;
	void* m_lpRequester;
	void* m_lpLocalResponder, *m_lpRemoteResponder;
	bool m_bWorking;
	std::mutex m_workingMutex;
	std::string m_lastRequestAddress;
public:
	SocketComponent():
		m_lpContext(nullptr),
		m_lpRequester(nullptr),
		m_lpLocalResponder(nullptr),
		m_lpRemoteResponder(nullptr),
		m_bWorking(false) {}
	virtual ~SocketComponent() {}

protected:
	bool _init(std::string ActorName, unsigned int port);
	bool _start();

	inline void _shutdown() {
		m_bWorking = false;
	}
	bool _send(const std::string address, const unsigned int port,
		const char* lpSendData, const unsigned int DataLength);

	virtual void _SocketCOMP_DoPollSocketFailed() = 0;
	virtual void _SocketCOMP_DoResponderPollIn(int ResponderType, char* lpRecvedData) = 0;
};
#endif