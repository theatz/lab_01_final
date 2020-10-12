// Copyright 2020 theatz
#include <gtest/gtest.h>
#include "Student.hpp"

TEST(Parse, FromString){
  std::string test_string =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 3
  }
})";
  std::string ref_string =\
R"(| name          | group  | avg  | debt    |
|---------------|--------|------|---------|
| Ivanov Petr   | 1      | 4.25 | null    |
|---------------|--------|------|---------|
| Sidorov Ivan  | 31     | 4    | C++     |
|---------------|--------|------|---------|
| Petrov Nikita | IU8-31 | 3.33 | 3 items |
|---------------|--------|------|---------|
)";
  Student st;
  st.parse_string(test_string);
  st.printTable();
  std::string expected = st.retString();
  EXPECT_EQ(expected, ref_string);
}

TEST(Parse, FromFileInvalid){
  try {
    Student st;
    std::string path = "table.json";
    st.parse_file(path);
    st.printTable();
  } catch (const std::runtime_error& e) {
    std::string expected = e.what();
    std::string ref_string = "File error";
    EXPECT_EQ(expected, ref_string);
  }
}


TEST(String, InvalidCount){
  std::string test_string =\
R"({
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Petrov Nikita",
      "group": "IU8-31",
      "avg": 3.33,
      "debt": [
        "C++",
        "Linux",
        "Network"
      ]
    }
  ],
  "_meta": {
    "count": 2
  }
})";
  try {
    Student st;
    st.parse_string(test_string);
    st.printTable();
  } catch (const std::runtime_error& e) {
    std::string expected = e.what();
    std::string ref_string = "Invalid _meta count";
    EXPECT_EQ(expected, ref_string);
  }
}

TEST(String, NotArray){
  std::string test_string =\
R"({
  "items":
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    }
  ,
  "_meta": {
    "count": 1
  }
})";
  try {
    Student st;
    st.parse_string(test_string);
    st.printTable();
  } catch (const std::runtime_error& e) {
    std::string expected = e.what();
    std::string ref_string = "Not array";
    EXPECT_EQ(expected, ref_string);
  }
}
