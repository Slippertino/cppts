#pragma once

#include <functional>
#include <sstream>

namespace cppts {

class DataStream final {
public:
	using data_record_handler = std::function<void(const std::string&)>;

public:
	DataStream() = delete;
	DataStream(data_record_handler handler);

	template<class TArg>
	DataStream& operator<<(const TArg& arg) {
		_stream << arg;
		return *this;
	}

	~DataStream();

private:
	data_record_handler _indirect_handler;
	std::ostringstream _stream;
};

} // namespace cppts
