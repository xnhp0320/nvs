#include "netdev.h"
#include "gtest/gtest.h"

TEST(netdev, netdev_open) {
  netdev::register_constructor("", netdev_linux::constructor);

  auto dev = std::static_pointer_cast<netdev_linux>(netdev::open("eth0"));
  EXPECT_EQ(dev.use_count(), 2);
  netdev::remove(dev);
  EXPECT_EQ(dev.use_count(), 1);
}

