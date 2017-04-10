#ifndef DIRECTOR_ACTOR_H
#	define DIRECTOR_ACTOR_H
#	include <string>
#	include "../Componets/SocketComponent.h"

namespace Director {
	class Actor :
		public SocketComponent
	{
	protected:
		std::string m_name;

	public:
		Actor() {}
		virtual ~Actor() {}
	};
}
#endif