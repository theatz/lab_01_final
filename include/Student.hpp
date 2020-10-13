// Copyright 2020 theatz
#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <vector>
#include "serializer.hpp"
#include <any>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
using nlohmann::json;

struct StudentInfo{
  std::string name;
  std::any group;
  std::any avg;
  std::vector<std::any> debt;
};

class Student {
 public:
  Student();
  ~Student();

  void parse_string(const std::string& str);

  void parse_file(const std::string& path);

  void from_json(const json& j, StudentInfo& st);

  void get_name(const json& j, StudentInfo& st);

  void get_debt(const json& j, StudentInfo& st);

  void get_avg(const json& j, StudentInfo& st);

  void get_group(const json& j, StudentInfo& st);

  void printName(const StudentInfo& st);

  void printGroup(const StudentInfo& st);

  void printAvg(const StudentInfo& st);

  void printDebt(const StudentInfo& st);

  uint32_t getNameLength(const StudentInfo& st);

  uint32_t getGroupLength(const StudentInfo& st);

  uint32_t getAvgLength(const StudentInfo& st);

  uint32_t getDebtLength(const StudentInfo& st);

  void pushStudent(const StudentInfo& st);

  void pushSize(const StudentInfo& st);

  void printTable();

  void printHor();

  std::string retString();

 private:
  std::vector<StudentInfo> _students;
  uint32_t _studentSize[4];
  std::string _out;
};
#endif  // INCLUDE_STUDENT_HPP_
