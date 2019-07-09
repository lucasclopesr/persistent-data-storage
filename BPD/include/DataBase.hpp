#ifndef DB_H
#define DB_H

#include <UnknownTableException.hpp>
#include <CreateFolderException.hpp>
#include <DeleteFileException.hpp>

#include <Table.hpp>
#include <map>
#include <vector>
#include <string>
#include <cstring>

// Manipulação de arquivos
#include <dirent.h>
#include <cstdlib>
#include <stdio.h>

typedef std::map<std::string, Table*> mapOfTables;

/**
 * A classe `DataBase` oferece uma API para operações sobre
 * o banco de dados. As operações que o usuário pode realizar
 * são:
 *  - Criar uma tabela.
 *  - Recuperar uma tabela.
 *  - Excluir uma tabela.
 *  - Listar as tabelas existentes.
 * 
 * Para realizar as operações, `DataBase` oferece um Singleton
 * que é o ponteiro para a instância de DataBase que acessa
 * os arquivos necessários. Portanto, a classe não pode ser
 * instanciada diretamente.
 * 
 * Para recuperar uma instância de `DataBase`, o usuário deve
 * utilizar o método `DataBase::getDBConnection`, que retorna
 * um ponteiro para `DataBase`.
 */
class DataBase {
  private:
    static DataBase* _DB;
    static mapOfTables _tables;

    DataBase() {}
    static void loadAllTables();

  public:
    /**
     * Gerencia a instância de `DataBase` que pode existir no sistema.
     * @return Um ponteiro para a instância de `DataBase`.
     */
    static DataBase* getDBConnection();

    /**
     * Cria uma tabela no banco de dados.
     * @param name uma `string` com o nome da tabela
     * @param columns um vetor de strings contendo o nome de cada uma das colunas da tabela
     * @return Um ponteiro para a tabela criada.
     */
    Table* createTable(std::string name, std::vector<std::string> columns);

    /**
     * Recupera uma tabela a partir de seu nome.
     * @param name uma `string` com o nome da tabela que está sendo buscada
     * @return Um ponteiro para a tabela buscada.
     */
    Table* getTable(std::string name);

    /**
     * Remove uma tabela do banco de dados.
     * @param name uma `string` com o nome da tabela que será removida
     * @return Um ponteiro para a tabela removida.
     */
    Table* deleteTable(std::string name);

    /**
     * Lista todas as tabelas do banco de dados.
     * @return Uma `string` com o nome de todas as tabelas do banco de dados, separados por espaço.
     */
    std::string listTables();
};

#endif