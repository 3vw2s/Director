#ifndef DIRECTOR_EMAIL_H
#	define DIRECTOR_EMAIL_H
#	include <string>
#	include <map>
#	include <utility>

namespace Director {

	class EmailItem
	{
		template <typename T>
		class _ItemObj 
		{
		public:
			_ItemObj(T obj) { m_obj = obj; }
			T m_obj;
		};

		enum _Type {
			_char,
			_int,
			_float,
			_long,
			_longlong,
			_string,
		};
	private:
		_Type m_type;
		void* m_data;
	public:
		EmailItem(int obj);
		EmailItem(char obj);
		EmailItem(std::string obj);
		EmailItem(float obj);
		EmailItem(long obj);
		EmailItem(long long obj);

		inline int toIntger() {
			return m_data && m_type == _int ?
				*static_cast<int*> (m_data) : -123456789;
		}

		inline char toByte() {
			return m_data && m_type == _char ? 
				*static_cast<char*> (m_data) : -256;
		}

		inline float toFloat() {
			return m_data && m_type == _float ?
				*static_cast<char*> (m_data) : -123456789.0;
		}
		
		inline long toLong() {
			return m_data && m_type == _long ? 
				*static_cast<char*> (m_data) : -123456789;
		}

		long long toLongLong() {
			return m_data && m_type == _longlong ? 
				*static_cast<char*> (m_data) : -123456789;
		}

		std::string toString() {
			return m_data && m_type == _string ? 
				*static_cast<std::string*> (m_data) : "";
		}
	};

	class Email  
	{
	public:
		Email() {}
		~Email() {}
		EmailItem& operator [] (std::string KeyName);
		Email& operator= (char value);
		Email& operator= (int value);
		Email& operator= (std::string value);
		Email& operator= (float value);
		Email& operator= (long value);
		Email& operator= (long long value);

	protected:
		std::map<std::string, EmailItem> m_items;
	};
}


#endif