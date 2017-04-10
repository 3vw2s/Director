#include "SocketComponent.h"
#include "ZeroMQ\zmq.h"
#include "ZeroMQ\zmq_utils.h"
#include <thread>

namespace Director {
	bool SocketComponent::_init(std::string ActorName, unsigned int port)
	{
		if (m_lpContext)
			return true;
		if (!port || port > 65535)
			COMP_ERROR_RETURN(InvalidPort, false);
		if (ActorName == "")
			COMP_ERROR_RETURN(InvalidActorName, false);

		m_lpContext = zmq_ctx_new();
		if (!(m_lpRequester = zmq_socket(m_lpContext, ZMQ_REQ)))
			COMP_ERROR_RETURN(RequesterCreateFailed, false);

		if (!(m_lpLocalResponder = zmq_socket(m_lpContext, ZMQ_REP)))
			COMP_ERROR_RETURN(LocalResponderCreateFailed, false);

		std::string localBind = "inporc://LocalSocket_" + ActorName;
		if (-1 == zmq_bind(m_lpLocalResponder, localBind.c_str()))
			COMP_ERROR_RETURN(LocalResponderBindFailed, false);

		if (!(m_lpRemoteResponder = zmq_socket(m_lpContext, ZMQ_REP)))
			COMP_ERROR_RETURN(RemoteResponderCreateFailed, false);

		std::string remoteBind = "tcp://*:" + std::to_string(port);
		if (-1 == zmq_bind(m_lpRemoteResponder, localBind.c_str()))
			COMP_ERROR_RETURN(RemoteResponderBindFailed, false);

		m_workingMutex.unlock();
		m_bInit = true;
		return 0;
	}

	bool SocketComponent::_start()
	{
		COMP_CHECK_INIT(false);
		if (m_bWorking)
			return true;
		std::thread pollThread([&]() {
			m_workingMutex.lock();
			m_bWorking = true;
			while (m_bWorking) {
				zmq_pollitem_t items[2] = {
					{ m_lpLocalResponder, 0, ZMQ_POLLIN },
					{ m_lpRemoteResponder, 0, ZMQ_POLLIN },
				};
				zmq_msg_t msg;
				int nRes = zmq_poll(items, 2, -1);
				int type = -1;
				int msgSize = 0;
				if (nRes == -1) {
					_SocketCOMP_DoPollSocketFailed();
					return;
				}

				if (items[0].revents & ZMQ_POLLIN) {	//local
					zmq_msg_init(&msg);
					if (zmq_msg_recv(&msg, items[0].socket, 0) != -1)
						type = 0;
				}
				else if (items[1].revents & ZMQ_POLLIN) { //remote
					zmq_msg_init(&msg);
					if (zmq_msg_recv(&msg, items[1].socket, 0) != -1)
						type = 1;
				}
				if (type != -1) {
					msgSize = zmq_msg_size(&msg);
					if (!msgSize) {
						zmq_msg_close(&msg);
						continue;
					}
					char* lpData = new char[msgSize];
					memcpy(lpData, zmq_msg_data(&msg), msgSize);
					_SocketCOMP_DoResponderPollIn(type, lpData);
					delete[] lpData;
					zmq_msg_close(&msg);
				}
			}
			m_workingMutex.unlock();
		});
		pollThread.detach();
		return true;
	}

	bool SocketComponent::_send(const std::string address, const unsigned int port,
		const char* lpSendData, const unsigned int DataLength)
	{
		COMP_CHECK_INIT(false);
		if (address == "")
			COMP_ERROR_RETURN(InvalidAddress, false);
		if (!port || port > 65535)
			COMP_ERROR_RETURN(InvalidPort, false);

		if (m_lastRequestAddress != "")
			zmq_disconnect(m_lpRequester, m_lastRequestAddress.c_str());
		m_lastRequestAddress = "tcp://" + address + ":" + std::to_string(port);
		if (-1 == zmq_connect(m_lpRequester, m_lastRequestAddress.c_str())) {
			m_lastRequestAddress = "";
			COMP_ERROR_RETURN(RequesterConnectFailed, false);
		}

		if (!lpSendData || !DataLength) {
			if (!zmq_send(m_lpRequester, nullptr, 0, 0))
				return true;
			COMP_ERROR_RETURN(RequesterSendFailed, false);
		}
		zmq_msg_t msg;
		zmq_msg_init_data(&msg, (void*)lpSendData, DataLength, nullptr, nullptr);
		if (!zmq_msg_send(&msg, m_lpRequester, 0))
			return true;
		COMP_ERROR_RETURN(RequesterSendFailed, false);
	}
}