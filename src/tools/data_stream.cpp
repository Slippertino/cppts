#include "tools/data_stream.hpp"

namespace cppts {

DataStream::DataStream(data_record_handler handler) : _indirect_handler(handler)
{ }

DataStream::~DataStream() {
    _indirect_handler(_stream.str());
}

} // namespace cppts
