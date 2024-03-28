#ifndef NETDEV_H_
#define NETDEV_H_
#include <memory>
#include <unordered_map>
#include <string>
#include <mutex>
#include <iostream>
#include <map>
#include <cassert>


struct netdev : public std::enable_shared_from_this<netdev> {
  netdev(const std::string& name) : name(name) {}
  ~netdev() { std::cout << "byte" <<std::endl; }

  std::string name;

  using Ptr = std::shared_ptr<netdev>;
  using Constructor = std::function<Ptr(const std::string& name)>;

  static std::unordered_map<std::string, Ptr> map;
  static std::mutex lock; 
  static std::map<const std::string, Constructor> ctors;

  static void register_constructor(const std::string& type, Constructor ctor) {
    ctors[type] = ctor;
  }

  static auto open(const std::string& name, const std::string& type = "") {
    std::lock_guard<std::mutex> g(lock);
    auto it = map.find(name);
    if (it == map.end()) {
      auto ctor = ctors.find(type);

      assert(ctor != ctors.end());
      auto dev = ctor->second(name);
      map[name] = dev;
      return dev;
    }
    return it->second;
  }

  static void remove(std::shared_ptr<netdev> dev) {
    std::lock_guard<std::mutex> g(lock);
    auto it = map.find(dev->name);
    if (it == map.end())
      return;
    map.erase(it);
  }

  auto ref() {
    return shared_from_this();
  }
};

struct netdev_linux : public netdev {
  netdev_linux(const std::string& name) : netdev{name} {}
  ~netdev_linux() { std::cout << "byebye linux" << std::endl; }

  static std::shared_ptr<netdev> constructor(const std::string& name) {
    return std::make_shared<netdev_linux>(name);
  }
};


#endif
