#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <DataBase.hpp>


TEST_CASE("Insere registro na tabela como especificado"){
  system("rm -rf ./datasets");
  DataBase* DBConn = DataBase::getDBConnection();

  std::vector<std::string> columns = {"nome"};
  Table* tAluno = DBConn->createTable("Aluno", columns);

  propertyMap propsAluno;
  propsAluno["nome"] = "Salles";
  Register r1(propsAluno);

  tAluno->insertRegister(r1);

  std::string firstLine, registerLine, columnValue;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  getline(tableFile, registerLine);
  std::stringstream valuesStream(registerLine);
  while (getline(valuesStream, columnValue, ',')) {
    row.push_back(columnValue);
  }

  CHECK(std::strcmp(row.at(1).c_str(),("Salles")) == 0);
}

TEST_CASE("Associa ID corretamente ao registro inserido"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap propsAluno;
  propsAluno["nome"] = "Lucas";
  Register r1(propsAluno);

  tAluno->insertRegister(r1);

  std::string firstLine, registerLine, columnValue;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  getline(tableFile, registerLine); // lê primeiro registro ("nome" = "Salles")
  getline(tableFile, registerLine); // lê segundo  registro ("nome" = "Lucas")
  std::stringstream valuesStream(registerLine);
  while (getline(valuesStream, columnValue, ',')) {
    row.push_back(columnValue);
  }

  CHECK(std::strcmp(row.at(0).c_str(),("2")) == 0);
}

TEST_CASE("Busca registro corretamente"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap query;
  query["nome"] = "Lucas";
  std::vector<Register> aluno = tAluno->select(query);

  CHECK(aluno.at(0).getData("id") == "2");
}

TEST_CASE("Dispara erro ao buscar registro com coluna inválida"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap query;
  query["departamento"] = "comp";

  CHECK_THROWS_AS(tAluno->select(query), UnknownColumnException);
}

TEST_CASE("Altera registro corretamente"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap queryAluno;
  queryAluno["nome"] = "Lucas";
  propertyMap newAluno;
  newAluno["nome"] = "Luquinha";

  tAluno->updateRegister(queryAluno, newAluno);

  std::string firstLine, registerLine, columnValue;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  getline(tableFile, registerLine); // lê primeiro registro ("nome" = "Salles")
  getline(tableFile, registerLine); // lê segundo  registro ("nome" = "Luquinha")
  std::stringstream valuesStream(registerLine);
  while (getline(valuesStream, columnValue, ',')) {
    row.push_back(columnValue);
  }

  CHECK(std::strcmp(row.at(1).c_str(),("Luquinha")) == 0);
}

TEST_CASE("Dispara erro ao tentar alterar registro com colunas inválidas"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap queryAluno;
  queryAluno["nome"] = "Salles";
  propertyMap newAluno;
  newAluno["departamento"] = "matematica";

  CHECK_THROWS_AS(tAluno->updateRegister(queryAluno, newAluno), UnknownColumnException);
}

TEST_CASE("Remove corretamente o registro da tabela"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  propertyMap queryAluno;
  queryAluno["nome"] = "Salles";

  tAluno->deleteRegister(queryAluno);

  std::string firstLine, registerLine, columnValue;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  getline(tableFile, registerLine); // lê primeiro registro ("nome" = "Luquinha")
  std::stringstream valuesStream(registerLine);
  while (getline(valuesStream, columnValue, ',')) {
    row.push_back(columnValue);
  }

  CHECK(std::strcmp(row.at(0).c_str(), "2") == 0);
}

TEST_CASE("Adiciona coluna corretamente"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  std::vector<std::string> columnsIn = {"curso"};
  std::vector<std::string> columnsOut = {};

  tAluno->alterTable(columnsIn, columnsOut);

  std::string firstLine, columnName;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  std::stringstream valuesStream(firstLine);
  while (getline(valuesStream, columnName, ',')) {
    row.push_back(columnName);
  }

  CHECK(std::strcmp(row.at(2).c_str(), "curso") == 0);
}

TEST_CASE("Remove coluna corretamente"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  std::vector<std::string> columnsIn = {};
  std::vector<std::string> columnsOut = {"nome"};

  tAluno->alterTable(columnsIn, columnsOut);

  std::string firstLine, columnName;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  std::stringstream valuesStream(firstLine);
  while (getline(valuesStream, columnName, ',')) {
    row.push_back(columnName);
  }

  CHECK(std::strcmp(row.at(1).c_str(), "curso") == 0);
}

TEST_CASE("Adiciona e remove colunas simultaneamente"){
  DataBase* DBConn = DataBase::getDBConnection();

  Table* tAluno = DBConn->getTable("Aluno");

  std::vector<std::string> columnsIn = {"nome"};
  std::vector<std::string> columnsOut = {"curso"};

  tAluno->alterTable(columnsIn, columnsOut);

  std::string firstLine, columnName;
  std::string filePath = "./datasets/Aluno.csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;

  getline(tableFile, firstLine);
  std::stringstream valuesStream(firstLine);
  while (getline(valuesStream, columnName, ',')) {
    row.push_back(columnName);
  }

  CHECK(std::strcmp(row.at(1).c_str(), "nome") == 0);
}