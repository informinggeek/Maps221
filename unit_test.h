#ifndef _UNIT_TEST_H_
#define _UNIT_TEST_H_

#include <iostream>
#include <string>

////////////////////////////////////////////////////////////////////////////////
/// @brief Test class for unit test framework
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class test_class {
  public:
    /// @brief Constructor
    test_class() {}
    /// @brief Destructor
    virtual ~test_class() {}
    /// @brief Run Unit test's setup, test, and teardown functions
    /// @return Passed test or not
    bool run() {
      setup();
      test();
      tear_down();
      return all_tests_passed();
    }

  protected:
    /// @brief Setup data to be tested
    virtual void setup() {};
    /// @brief Test data
    virtual void test() = 0;
    /// @brief Teardown data which was tested
    virtual void tear_down() {};

    /// @return All asserts have passed
    bool all_tests_passed() const {return !fail;}

    /// @brief Assert a unit test passes
    /// @param b Conditional for assert
    /// @param msg Message on fail
    void assert_msg(bool b, std::string msg) {
      if(!b) {
        std::cerr << msg << std::endl;
        fail = true;
      }
    }

  private:
    bool fail = false; ///< Stores if any test case has failed
};

#endif
