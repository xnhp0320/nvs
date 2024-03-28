#include "netdev.h"

std::unordered_map<std::string, std::shared_ptr<netdev>> netdev::map;
std::mutex netdev::lock;
std::map<const std::string, netdev::Constructor> netdev::ctors;
