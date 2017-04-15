#include "Email.h"

namespace Director {
	EmailItem::EmailItem(int obj) {
		m_data = new _ItemObj<int>(obj);
		m_type = _int;
	}

	EmailItem::EmailItem(char obj) {
		m_data = new _ItemObj<char>(obj);
		m_type = _char;
	}

	EmailItem::EmailItem(std::string obj) {
		m_data = new _ItemObj<std::string>(obj);
		m_type = _string;
	}

	EmailItem::EmailItem(float obj) {
		m_data = new _ItemObj<float>(obj);
		m_type = _float;
	}

	EmailItem::EmailItem(long obj) {
		m_data = new _ItemObj<float>(obj);
		m_type = _float;
	}

	EmailItem::EmailItem(long long  obj) {
		m_data = new _ItemObj<long long>(obj);
		m_type = _longlong;
	}
}