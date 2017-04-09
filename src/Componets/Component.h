#ifndef DIRECTOR_COMPONENT_H
#	define DIRECTOR_COMPONENT_H
#	define COMP_ERROR_RETURN(x,y) { m_error=x; return y;}
#	define COMP_CHECK_INIT(y)  if (!__super::m_bInit)	{		\
				__super::m_error = ComponentError::NotInited;	\
				return y; }										\

class Component
{
public:
	enum ComponentError {
		NotInited = 0,
	};
protected:
	int m_error;
	bool m_bInit;
public:
	Component():
		m_error(0),
		m_bInit(false) {}
	virtual ~Component() {}

	inline int getError() {
		return m_error;
	}
};

#endif