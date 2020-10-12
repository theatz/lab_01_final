// Copyright 2020 theatz
#include "Student.hpp"

void Student::printHor(){
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV;
  for (uint32_t i = 0;
       i < _studentSize[0] + 2;
       i++) _out += sepH;
  _out += sepV;
  for (uint32_t i = 0;
       i < _studentSize[1] + 2;
       i++) _out += sepH;
  _out += sepV;
  for (uint32_t i = 0;
       i < _studentSize[2] + 2;
       i++) _out += sepH;
  _out += sepV;
  for (uint32_t i = 0;
       i < _studentSize[3] + 2;
       i++) _out += sepH;
  _out += sepV + '\n';
}

Student::Student() {
  _studentSize[0] = 4;
  _studentSize[1] = 4;
  _studentSize[2] = 4;
  _studentSize[3] = 4;
  _out = "";
  _students.clear();
}
Student::~Student() {
  _students.clear();
}

void Student::from_json(const json& j, StudentInfo& st) {
  get_name(j.at("name"), st);
  get_group(j.at("group"), st);
  get_avg(j.at("avg"), st);
  get_debt(j.at("debt"), st);
}

void Student::get_name(const json& j, StudentInfo& st){
  st.name = j.get<std::string>();
}

void Student::get_debt(const json& j, StudentInfo& st){
  if (j.is_null())
    st.debt.push_back(nullptr);
  else if (j.is_string())
    st.debt.push_back(j.get<std::string>());
  else if (j.is_array())
    for (json::const_iterator it = j.cbegin(); it != j.cend(); ++it)
      st.debt.push_back(it->get<std::string>());
}

void Student::get_avg(const json& j, StudentInfo& st){
  if (j.is_null())
    st.debt.push_back(nullptr);
  else if (j.is_string())
    st.avg = j.get<std::string>();
  else if (j.is_number_float())
    st.avg = j.get<double>();
  else
    st.avg = j.get<std::size_t>();
}

void Student::get_group(const json& j, StudentInfo& st){
  if (j.is_string())
    st.group = j.get<std::string>();
  else
    st.group = j.get<std::size_t>();
}

uint32_t Student::getNameLength(const StudentInfo& st) {
  return static_cast<uint32_t>(st.name.length());
}

uint32_t Student::getGroupLength(const StudentInfo& st) {
  if (st.group.type() == typeid(std::string))
    return static_cast<uint32_t>(\
            std::any_cast<std::string>(st.group).length());
  else if (st.group.type() == typeid(int))
    return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(st.group)).length());
  else
    return 0;
}

uint32_t Student::getAvgLength(const StudentInfo& st){
  if (st.avg.type() == typeid(int)) {
    return static_cast<uint32_t>(\
            std::to_string(std::any_cast<int>(st.avg)).length());
  } else if (st.avg.type() == typeid(float)) {
    return static_cast<uint32_t>(\
            std::to_string(std::any_cast<float>(st.avg)).length());
  } else if (st.avg.type() == typeid(std::string)) {
    return static_cast<uint32_t>(\
            std::any_cast<std::string>(st.avg).length());
  } else {
    return 0;
  }
}

uint32_t Student::getDebtLength(const StudentInfo& st){
  if (st.debt.size() == 1 && st.debt[0].type() == typeid(std::nullptr_t))
    return 4;
  else if (st.debt.size() == 1 && st.debt[0].type() == typeid(std::string))
    return std::any_cast<std::string>(st.debt[0]).length();
  else if (st.debt.size() == 0) return 0;
  else
    return std::to_string(st.debt.size()).length() + 6;
}
void Student::printName(const StudentInfo& st){
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV + " ";
  _out += st.name;
  uint32_t sp = _studentSize[0] - st.name.length() + 1;
  for (uint32_t i = 0;
       i < sp;
       i++) _out += " ";
}

void Student::printGroup(const StudentInfo& st) {
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV + " ";
  if (st.group.type() == typeid(std::string))
  {
    _out += std::any_cast<std::string>(st.group);
    uint32_t sp = _studentSize[1];
    sp = sp - std::any_cast<std::string>(st.group).length() + 1;
    for (uint32_t i = 0;
         i < sp;
         i++) _out += " ";
  } else if (st.group.type() == typeid(size_t)) {
    std::string group;
    group = std::to_string(std::any_cast<size_t>(st.group));
    _out += group;
    uint32_t sp = _studentSize[1] - group.length() + 1;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  }
}

void Student::printAvg(const StudentInfo& st) {
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV + " ";
  if (st.avg.type() == typeid(std::string))
  {
    _out += std::any_cast<std::string>(st.avg);
    uint32_t sp = _studentSize[2];
    sp = sp - std::any_cast<std::string>(st.avg).length() + 1;
    for (uint32_t i = 0;
         i < sp;
         i++) _out += " ";
  } else if (st.avg.type() == typeid(size_t)) {
    std::string avg;
    avg = std::to_string(std::any_cast<size_t>(st.avg));
    _out += avg;
    uint32_t sp = _studentSize[2] - avg.length() + 1;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  } else if (st.avg.type() == typeid(double)) {
    std::ostringstream avg_pr;
// Set Fixed -Point Notation
    avg_pr << std::fixed;
// Set precision to 2 digits
    avg_pr << std::setprecision(2);
//Add double to stream
    avg_pr << std::any_cast<double>(st.avg);
// Get string from output string stream
    std::string avg = avg_pr.str();
    _out += avg;
    uint32_t sp = _studentSize[2] - avg.length() + 1;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  }
}

void Student::printDebt(const StudentInfo& st) {
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV + " ";
  if (st.debt.size() == 1 && st.debt[0].type() == typeid(nullptr)){
    _out += "null";
    uint32_t sp = _studentSize[3] - 3;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  } else if (st.debt.size() == 1 && st.debt[0].type() == typeid(std::string)){
    std::string debt = std::any_cast<std::string>(st.debt[0]);
    uint32_t sp = _studentSize[3] - debt.length() + 1;
    _out += debt;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  } else if (st.debt.size() > 1){
    _out = _out + std::to_string(st.debt.size()) + " items";
    uint32_t sp = _studentSize[3] - std::to_string(st.debt.size()).length() - 5;
    for (uint32_t i = 0; i < sp; i++) _out += " ";
  }
  _out += sepV + '\n';
}


void Student::pushStudent(const StudentInfo& st) {
  _students.push_back(st);
}

void Student::pushSize(const StudentInfo& st) {
  if (getNameLength(st) > _studentSize[0])
    _studentSize[0] = getNameLength(st);
  if (getGroupLength(st) > _studentSize[1])
    _studentSize[1] = getGroupLength(st);
  if (getAvgLength(st) > _studentSize[2])
    _studentSize[2] = getAvgLength(st);
  if (getDebtLength(st) > _studentSize[3])
    _studentSize[3] = getDebtLength(st);
}

void Student::parse_string(const std::string& str) {
  json j = json::parse(str);
  if (!j.at("items").is_array()) throw std::runtime_error("Not array");
  if (j.at("items").size() != j.at("_meta").at("count").get<size_t>())
    throw std::runtime_error("Invalid _meta count");
  StudentInfo st;
  for (json::const_iterator it = j.at("items").cbegin();\
                            it != j.at("items").cend();\
                          ++it){
    from_json(it.value(), st);
    pushStudent(st);
    pushSize(st);
    st.debt.clear();
  }
}

void Student::parse_file(const std::string& path) {
  std::ifstream input_file;
  std::filesystem::path cwd = std::filesystem::current_path() / path;
  //std::ofstream file(cwd.string());
  input_file.open(cwd.string() + path);
  if (!input_file.is_open())
    throw std::runtime_error("File error");
  std::string string;
  input_file >> string;
  input_file.close();
  std::cout << string << std::endl;
  parse_string(string);
}

void Student::printTable() {
  std::string sepV = "|";
  std::string sepH = "-";
  _out += sepV;
  _out += " name";
  for (uint32_t i = 0;
       i < _studentSize[0] - 3;
       i++) _out += " ";
  _out += sepV;
  _out += " group";
  for (uint32_t i = 0;
       i < _studentSize[1] - 4;
       i++) _out += " ";
  _out += sepV;
  _out += " avg";
  for (uint32_t i = 0;
       i < _studentSize[2] - 2;
       i++) _out += " ";
  _out += sepV;
  _out += " debt";
  for (uint32_t i = 0;
       i < _studentSize[3] - 3;
       i++) _out += " ";
  _out = _out + sepV + '\n';
  printHor();

  for (uint32_t i = 0;
       i < _students.size();
       i++){
    printName(_students[i]);
    printGroup(_students[i]);
    printAvg(_students[i]);
    printDebt(_students[i]);
    printHor();
  }
  std::cout << _out;
}

std::string Student::retString() {
  return _out;
}
