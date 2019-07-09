#ifndef DELETEFILEEXCEPTION_H
#define DELETEFILEEXCEPTION_H

#include <string>

/**
 * A classe DeleteFileException define uma exceção para
 * as operações de remoção de arquivos realizadas pelo
 * banco de dados.
 */
class DeleteFileException : public std::exception {
  private:
    std::string _fileName;

  public:
    /**
     * Construtor da exceção `DeleteFileException`
     * @param file uma string com o nome do arquivo que não pôde ser removido
     */
    DeleteFileException(std::string file) : _fileName(file) {}

    /**
     * `throws` um aviso com o nome do arquivo que não pôde ser removido.
     */
    virtual const char* what() const throw() {
      std::string error = "Erro ao deletar arquivo: " + this->_fileName;
      return error.c_str();
    }
};

#endif