#pragma once

#include <mutex>

namespace cppts {

class IUnitProcessable {
public:
	void process();

	virtual bool is_active() const = 0;

	virtual ~IUnitProcessable() = default;

protected:
	virtual void process_base() = 0;

private:
	std::mutex _processing_sync;
};

} // namespace cppts