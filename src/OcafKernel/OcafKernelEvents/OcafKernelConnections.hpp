#ifndef OcafKernelConnections_hpp
#define OcafKernelConnections_hpp

#include "OcafKernelEventTypes.hpp"
#include "SignalSubscription.hpp"
#include <map>

using OcafKernelConnections = std::map<OcafKernelEventTypes, SignalSubscription>;

#endif