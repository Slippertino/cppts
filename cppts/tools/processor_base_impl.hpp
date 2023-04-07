#include "tools/processor_base.hpp"

namespace cppts {

template<class TCont>
IProcessorBase<TCont>::IProcessorBase() : _processor(this)
{ }

template<class TCont>
void IProcessorBase<TCont>::process() {
    _target_mutex.lock_shared();

    auto dir = Generator<uint16_t>::generate(0, 1);

    dir
        ? forward_processing()
        : reverse_processing();

    _target_mutex.unlock_shared();
}

template<class TCont>
void IProcessorBase<TCont>::forward_processing() {
    std::for_each(_target.begin(), _target.end(), _processor);
}

template<class TCont>
void IProcessorBase<TCont>::reverse_processing() {
    std::for_each(_target.rbegin(), _target.rend(), _processor);
}

} // namespace cppts