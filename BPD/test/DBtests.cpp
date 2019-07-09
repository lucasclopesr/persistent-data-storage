#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <DataBase.hpp>

TEST_CASE("DB Cria tabela de acordo com o especificado"){
  system("rm -rf ./datasets");
  DataBase* DBConn = DataBase::getDBConnection();

  std::vector<std::string> columns = {"nome", "matricula", "curso"};
  DBConn->createTable("Aluno", columns);

  std::vector<std::string> fileNames;
  DIR *dir;
  struct dirent *entry;
  while((dir = opendir("./datasets/")) != NULL){
    while ((entry = readdir(dir)) != NULL) {
      bool isEntryValid = (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0);

      if (isEntryValid) {
        fileNames.push_back(entry->d_name);
      }
    }
  }

  CHECK(fileNames.at(0) == "Aluno.csv");
}

TEST_CASE("DB Abre as tabelas que já existem"){
  DataBase* DBConn = DataBase::getDBConnection();
  Table* tAluno = DBConn->getTable("Aluno");

  CHECK(tAluno->getShape().size() == 4);
}

TEST_CASE("DB joga erro ao tentar acessar tabela inexistente"){
  DataBase* DBConn = DataBase::getDBConnection();

  CHECK_THROWS_AS(DBConn->getTable("Professor"), UnknownTableException);
}

TEST_CASE("DB remove tabela de acordo com o especificado"){
  DataBase* DBConn = DataBase::getDBConnection();

  DBConn->deleteTable("Aluno");

  CHECK_THROWS_AS(DBConn->getTable("Aluno"), UnknownTableException);
}

TEST_CASE("DB falha ao tentar remover tabela inexistente"){
  DataBase* DBConn = DataBase::getDBConnection();

  CHECK_THROWS_AS(DBConn->deleteTable("Aluno"), UnknownTableException);
}
