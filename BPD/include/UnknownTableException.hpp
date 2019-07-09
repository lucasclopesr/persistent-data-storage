#ifndef UNKOWNTABLEEXCEPTION_H
#define UNKOWNTABLEEXCEPTION_H

#include <string>

/**
 * A classe UnknownTableException define uma exceção para
 * as operações relacionadas à tabela, realizadas pelo
 * banco de dados. Utilizada quando a tabela não é encontrada.
 */
class UnknownTableException : public std::exception {
  private:
    std::string _tableName;

  public:
    /**
     * Construtor da exceção `UnknownTableException`
     * @param table uma string com o nome da tabela que não foi encontrada
     */
    UnknownTableException(std::string table) : _tableName(table) {}

    /**
     * `throws` um aviso com o nome da tabela que não foi encontrada.
     */
    virtual const char* what() const throw() {
      std::string error = "Tabela nao existe: " + this->_tableName;
      return error.c_str();
    }
};

#endif