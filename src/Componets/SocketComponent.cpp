#include "SocketComponent.h"
#include "ZeroMQ\zmq.h"
#include "ZeroMQ\zmq_utils.h"
#include <thread>

SocketComponent::SocketComponent():m_context(nullptr)
{

}