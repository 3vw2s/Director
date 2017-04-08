#ifndef DIRECTOR_COMPONENT_SOCKET
#	define DIRECTOR_COMPONENT_SOCKET

class SocketComponent
{
public:
	SocketComponent();
	virtual ~SocketComponent() {}

protected:
	void* m_context;
};
#endif