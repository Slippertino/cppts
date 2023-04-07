#pragma once

#include <algorithm>
#include <shared_mutex>
#include "generator.hpp"

namespace cppts {

template<class TCont>
class IProcessorBase {

    template<class TCont>
    class ProcessingFunctor {
    public:
        ProcessingFunctor() = delete;
        ProcessingFunctor(IProcessorBase<TCont>* obj) : _obj(obj)
        { }

        void operator()(typename TCont::value_type& sub) {
            _obj->process_base(sub);
        }

    private:
        IProcessorBase<TCont>* _obj;
    };

    friend class ProcessingFunctor<TCont>;

public:
    IProcessorBase();

    void process();

    virtual ~IProcessorBase() = default;

protected:
    virtual void process_base(std::add_lvalue_reference_t<typename TCont::value_type> sub) = 0;

private:
    void forward_processing();
    void reverse_processing();

protected:
    TCont _target;
    std::shared_mutex _target_mutex;

private:
    ProcessingFunctor<TCont> _processor;
};

} // namespace cppts

#include "processor_base_impl.hpp"