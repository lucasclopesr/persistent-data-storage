#ifndef CREATEFOLDEREXCEPTION_H
#define CREATEFOLDEREXCEPTION_H

/**
 * A classe CreateFolderException define uma exceção para
 * a operação de criação do diretório `datasets`.
 */
class CreateFolderException : public std::exception {
  public:
    /**
     * `throws` um aviso que o diretório `datasets` não pôde ser criado.
     */
    virtual const char* what() const throw() {
      return "Impossivel criar pasta 'datasets'";
    }
};

#endif