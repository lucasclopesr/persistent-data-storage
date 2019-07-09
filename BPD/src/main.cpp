#include <DataBase.hpp>
#include <iostream>

int main() {
  DataBase* DBConn = DataBase::getDBConnection();

  std::cout << "-> Tabelas já existentes: " << DBConn->listTables() << std::endl;

  std::cout << "=== Cria / Carrega tabela Aluno ===" << std::endl;
  try {
    std::vector<std::string> columns = {"nome", "matricula", "curso"};
    DBConn->createTable("Aluno", columns);
  } catch(std::exception& e) {
    std::cout << "Não foi possível criar a tabela." << std::endl;
  }
  
  std::cout << "=== Cria / Carrega tabela Professor ===" << std::endl;
  try {
    std::vector<std::string> columns = {"nome", "cpf", "departamento"};
    DBConn->createTable("Professor", columns);
  } catch(std::exception& e) {
    std::cout << "Não foi possível criar a tabela." << std::endl;
  }

  // Recupera a tabela Professor e imprime suas colunas
  std::cout << std::endl;
  std::cout << "-> Colunas da tabela Professor: ";
  try {
    Table* t = DBConn->getTable("Professor");
    std::vector<std::string> tCols = t->getShape();
    for (auto const& col : tCols) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  } catch(std::exception& e) {
    std::cout << "Colunas inválidas." << std::endl;
  }

  std::cout << std::endl;
  std::cout << "=== Insere registros na tabela Professor ===" << std::endl;
  try {
    Table* t = DBConn->getTable("Professor");
    propertyMap propsProfessor;

    propsProfessor["nome"] = "Chicão";
    propsProfessor["departamento"] = "comp";
    Register r2(propsProfessor);

    propsProfessor["nome"] = "Salles";
    propsProfessor["cpf"] = "1";
    propsProfessor["departamento"] = "comp";
    Register r1(propsProfessor);

    propsProfessor["nome"] = "Luquinha";
    propsProfessor["cpf"] = "3";
    propsProfessor["departamento"] = "mat";
    Register r3(propsProfessor);

    t->insertRegister(r1);
    t->insertRegister(r2);
    t->insertRegister(r3);
  } catch(std::exception& e) {
    std::cout << "Colunas inválidas" << std::endl;
  }

  // Prepara query para tabela Professor
  propertyMap query;
  query["nome"] = "Luquinha";
  query["cpf"] = "3";
  query["departamento"] = "mat"; // a query pode ser feita com menos colunas (deve retornar todos os registros compatíveis)

  // Prepara update para tabela Professor
  propertyMap update;
  update["departamento"] = "comp";

  std::cout << std::endl;
  std::cout << "=== Realiza alteração na tabela Professor ===" << std::endl;
  try {
    Table* t = DBConn->getTable("Professor");
    std::vector<Register> queryReturn = t->select(query);
    std::cout << "-> Registros que serão alterados: " << std::endl;
    for (auto qReg : queryReturn) {
      std::cout << "=====" << std::endl;
      std::cout << "ID: " << qReg.getData("id") << std::endl
                << "Nome: " << qReg.getData("nome") << std::endl
                << "Departamento: " << qReg.getData("departamento") << std::endl;
      std::cout << "=====" << std::endl;
    }

    std::cout << "=== Confere atualização na tabela Professor ===" << std::endl;
    queryReturn = t->updateRegister(query, update);
    std::cout << "-> Registros alterados: " << std::endl;
    for (auto qReg : queryReturn) {
      std::cout << "=====" << std::endl;
      std::cout << "ID: " << qReg.getData("id") << std::endl
                << "Nome: " << qReg.getData("nome") << std::endl
                << "Departamento: " << qReg.getData("departamento") << std::endl;
      std::cout << "=====" << std::endl;
    }
  } catch(std::exception& e) {
    std::cout << "Colunas inválidas" << std::endl;
  }

  std::cout << std::endl;
  std::cout << "=== Remove registro da tabela Professor ===" << std::endl;
  propertyMap del;
  del["nome"] = "Salles";
  try{
    Table* t = DBConn->getTable("Professor");
    std::vector<Register> delReturn = t->deleteRegister(del);
    std::cout << "-> Registros removidos: " << std::endl;
    for (auto qReg : delReturn) {
      std::cout << "=====" << std::endl;
      std::cout << "ID: " << qReg.getData("id") << std::endl
                << "Nome: " << qReg.getData("nome") << std::endl
                << "Departamento: " << qReg.getData("departamento") << std::endl;
      std::cout << "=====" << std::endl;
    }
  }catch(std::exception& e) {
    std::cout << "Colunas inválidas" << std::endl;
  }

  // Prepara alteraçao de Professores
  std::vector<std::string> columnIn, columnOut;
  columnOut.push_back("departamento");
  columnIn.push_back("carisma");

  std::cout << std::endl;
  std::cout << "=== Altera as colunas da tabela Professor ===" << std::endl;
  try{
    Table* t = DBConn->getTable("Professor");
    t->alterTable(columnIn, columnOut);
  }catch(std::exception& e) {
    std::cout << "Colunas inválidas" << std::endl;
  }

  std::cout << "-> Colunas da tabela Professor: ";
  try {
    Table* t = DBConn->getTable("Professor");
    std::vector<std::string> tCols = t->getShape();
    for (auto const& col : tCols) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  } catch(std::exception& e) {
    std::cout << "Tabela não encontrada." << std::endl;
  }

  std::cout << std::endl;
  std::cout << "=== Confere alteração das colunas da tabela Professor ===" << std::endl;
  propertyMap check;
  check["nome"] = "Luquinha";
  try {
    Table* t = DBConn->getTable("Professor");
    std::vector<Register> queryReturn = t->select(check);

    for (auto qReg : queryReturn) {
      std::cout << "=====" << std::endl;
      std::cout << "ID: " << qReg.getData("id") << std::endl
                << "Nome: " << qReg.getData("nome") << std::endl
                << "Carisma: " << qReg.getData("carisma") << std::endl;
      std::cout << "=====" << std::endl;
    }
  }catch(std::exception& e) {
    std::cout << "Colunas não encontradas" << std::endl;
  }

  return 0;
}