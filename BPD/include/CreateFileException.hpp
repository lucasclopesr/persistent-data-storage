#ifndef CREATEFILEEXCEPTION_H
#define CREATEFILEEXCEPTION_H

#include <string>

/**
 * A classe CreateFileException define uma exceção para
 * as operações de criação de arquivos realizadas pelo
 * banco de dados.
 */
class CreateFileException : public std::exception {
  private:
    std::string _fileName;

  public:
    /**
     * Construtor da exceção `CreateFileException`
     * @param file uma string com o nome do arquivo que não pôde ser criado
     */
    CreateFileException(std::string file) : _fileName(file) {}

    /**
     * `throws` um aviso com o nome do arquivo que não pôde ser criado.
     */
    virtual const char* what() const throw() {
      std::string error = "Impossivel criar o arquivo: " + this->_fileName;
      return error.c_str();
    }
};

#endif