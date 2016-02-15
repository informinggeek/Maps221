#include <algorithm>
#include <string>
#include <iostream>

#include "map.h"

#include "unit_test.h"

using std::all_of;
using std::string;
using std::pair;
using std::make_pair;
using mystl::map;

////////////////////////////////////////////////////////////////////////////////
/// @brief Testing of map
/// @ingroup Testing
////////////////////////////////////////////////////////////////////////////////
class map_test : public test_class {

  protected:

    void test() {
      test_default_constructor();

      test_element_access_operator_exists();

      test_element_access_operator_not_exists();

      test_element_access_at_exists();

      test_element_access_at_not_exists();

      test_find_exists();

      test_find_not_exists();

      test_count_exists();

      test_count_not_exists();

      test_insert_exists();

      test_insert_not_exists();

      test_erase_iterator();

      test_erase_key();

      test_copy_constructor();

      test_copy_assign();
    }

  private:

    /// @brief Setup map of integers to strings
    void setup_dummy_map(map<int, string>& m) {
      m[3] = "l";
      m[1] = "H";
      m[2] = "e";
      m[5] = "o";
      m[4] = "l";
    }

    /// @brief Test default constructor generates map of size 0
    void test_default_constructor() {
      map<int, string> m;

      assert_msg(m.size() == 0 && m.empty(),
          "Default construction failed.");
    }

    /// @brief Test element access operator when element exists
    void test_element_access_operator_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      string val = m[5];

      assert_msg(val == "o", "Element access operator exists failed");
    }

    /// @brief Test element access operator when element does not exist
    void test_element_access_operator_not_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      string val = m[7];

      assert_msg(val == "", "Element access operator not exists failed");
    }

    /// @brief Test element access at when element exists
    void test_element_access_at_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      string val = m.at(5);

      assert_msg(val == "o", "Element access at exists failed");
    }

    /// @brief Test element access at when element does not exist, ensure this
    ///        function will throw an error.
    void test_element_access_at_not_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      try {
        string val = m.at(7);
        assert_msg(false, "Element access at not exists failed");
      }
      catch(std::out_of_range) {
        //test success!
      }
      catch(...) {
        assert_msg(false, "Element access at not exists failed");
      }
    }

    /// @brief Test find when element exists
    void test_find_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      map<int, string>::iterator i = m.find(5);

      assert_msg(i->first == 5 && i->second == "o", "Find exists failed.");
    }

    /// @brief Test find when element does not exist
    void test_find_not_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      map<int, string>::iterator i = m.find(7);

      assert_msg(i == m.end(), "Find exists failed.");
    }

    /// @brief Test count when element exists
    void test_count_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      size_t i = m.count(5);

      assert_msg(i == 1, "Count exists failed.");
    }

    /// @brief Test count when element does not exist
    void test_count_not_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      size_t i = m.count(7);

      assert_msg(i == 0, "Count exists failed.");
    }

    /// @brief Test insertion when element is already in map
    void test_insert_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      pair<map<int, string>::iterator, bool> i = m.insert(make_pair(5, "o"));

      map<int, string>::iterator j = m.begin();
      while(j != m.end() && i.first != j)
        ++j;

      assert_msg(m.size() == 5 && i.first == j && !i.second,
          "Insert exists failed.");
    }

    /// @brief Test insertion when element is not already in map
    void test_insert_not_exists() {
      map<int, string> m;
      setup_dummy_map(m);

      pair<map<int, string>::iterator, bool> i = m.insert(make_pair(7, "!"));

      map<int, string>::iterator j = m.begin();
      while(j != m.end() && i.first != j)
        ++j;

      assert_msg(m.size() == 6 && i.first == j && i.second,
          "Insert not exists failed.");
    }

    /// @brief Test erase with an iterator
    void test_erase_iterator() {
      map<int, string> m;
      setup_dummy_map(m);
      map<int, string>::iterator j = ++m.begin();

      map<int, string>::iterator i = m.erase(m.begin());

      assert_msg(i == j && m.size() == 4, "Erase iterator failed.");
    }

    /// @brief Test erase with a key
    void test_erase_key() {
      map<int, string> m;
      setup_dummy_map(m);

      size_t i = m.erase(5);

      assert_msg(i == 1 && m.size() == 4, "Erase key failed.");
    }

    /// @brief Test copy constuction
    void test_copy_constructor() {
      map<int, string> m1;
      setup_dummy_map(m1);

      map<int, string> m2(m1);

      for(auto&& x : m2)
        x.second = "w";

      assert_msg(m2.size() == m1.size() &&
          all_of(m1.begin(), m1.end(),
            [](const map<int, string>::value_type& x) {
            return x.second != "w";}
            ) &&
          all_of(m2.begin(), m2.end(),
            [](const map<int, string>::value_type& x) {
            return x.second == "w";}
            ),
          "Copy constructor failed.");
    }

    /// @brief Test copy assignment
    void test_copy_assign() {
      map<int, string> m1;
      setup_dummy_map(m1);

      map<int, string> m2;
      m2[4] = "*";

      m2 = m1;

      for(auto&& x : m2)
        x.second = "w";

      assert_msg(m2.size() == m1.size() &&
          all_of(m1.begin(), m1.end(),
            [](const map<int, string>::value_type& x) {
            return x.second != "w";}
            ) &&
          all_of(m2.begin(), m2.end(),
            [](const map<int, string>::value_type& x) {
            return x.second == "w";}
            ),
          "Copy assign failed.");
    }
};

int main() {
  map_test lt;

  if(lt.run())
    std::cout << "All tests passed." << std::endl;

  return 0;
}

