#ifndef UNKNOWNCOLUMNEXCEPTION_H
#define UNKNOWNCOLUMNEXCEPTION_H

#include <string>

/**
 * A classe UnknownColumnException define uma exceção para
 * as operações sobre as tabelas, utilizada quando as colunas
 * especificadas não equivalem às colunas da tabela.
 */
class UnknownColumnException : public std::exception {
  private:
    std::string _columnName;

  public:
    /**
     * Construtor da exceção `UnknownColumnException`
     * @param column uma string com o nome da coluna que não foi encontrada
     */
    UnknownColumnException(std::string column) : _columnName(column) {}

    /**
     * `throws` um aviso com o nome da coluna que não foi encontrada.
     */
    virtual const char* what() const throw() {
      std::string error = "Coluna nao existe: " + this->_columnName;
      return error.c_str();
    }
};

#endif