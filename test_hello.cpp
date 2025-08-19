#define BOOST_TEST_MODULE test_hello
#include <boost/test/unit_test.hpp>
#include <sstream>

#include "hello.h"

BOOST_AUTO_TEST_SUITE(test_hello)

BOOST_AUTO_TEST_CASE(HelloTestCase){
  std::stringstream ss;
  hello::greetings(ss);
  BOOST_CHECK("Hello, world" == ss.str());
}

BOOST_AUTO_TEST_SUITE_END()
