#ifndef TABLE_H
#define TABLE_H

#include <UnknownColumnException.hpp>
#include <CreateFileException.hpp>

#include <Register.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <sstream>

/**
 * A classe `Table` provê uma interface para realização das operações
 * nas tabelas. As operações podem ser:
 *  - Alterar as colunas de uma tabela.
 *  - Recuperar o formato (as colunas) de uma tabela.
 *  - Inserir um registro em uma tabela.
 *  - Selecionar um ou mais registros de uma tabela.
 *  - Remover um ou mais registros de uma tabela.
 *  - Atualizar um ou mais registros de uma tabela.
 * 
 * Ao ser instanciada, a tabela decide entre abrir o arquivo da tabela
 * (se ele já existir) ou criar um novo arquivo para a tabela (indica
 * uma nova tabela sendo criada). Para o segundo caso, é necessário
 * invocar também o método setColumns junto com a instanciação do objeto.
 */
class Table {
  private:
    std::string _tableName;
    std::vector<std::string> _columns;
    int _lastId;

    void _loadColumns();

  public:
    /**
     * Construtor do objeto `Table`.
     * @param tableName uma string com o nome da tabela
     * @return Um ponteiro para a instância de Tabela
     */
    Table(std::string tableName);

    /**
     * Define as colunas pertencentes à tabela.
     * @param columns um vetor de strings contendo o nome de cada uma das colunas da tabela
     */
    void setColumns(std::vector<std::string> columns);

    /**
     * Altera as colunas da tabela, inserindo novas colunas ou removendo colunas existentes.
     * @param columnsIn um vetor de strings contendo o nome de cada uma das colunas da tabela que serão adicionadas
     * @param columnsOut um vetor de strings contendo o nome de cada uma das colunas da tabela que serão removidas
     * @return Um booleano indicando o sucesso ou fracasso da operação.
     */
    bool alterTable(std::vector<std::string> columnsIn, std::vector<std::string> columnsOut);

    /**
     * Recupera o formato (as colunas) da tabela.
     * @return Um vetor de strings contendo o nome das colunas da tabela.
     */
    std::vector<std::string> getShape();

    /**
     * Insere um registro na tabela.
     * @param r um objeto do tipo `Registro` contendo os valores que devem ser inseridos para cada coluna
     * @return O objeto do tipo `Registro` que foi inserido.
     */
    Register insertRegister(Register r);

    /**
     * Recupera um registro da tabela.
     * @param query um objeto do tipo `propertyMap` mapeando colunas e valores do(s) registro(s) buscado(s)
     * @return Um vetor de objetos do tipo `Register` contendo os registros resultados da query.
     */
    std::vector<Register> select(propertyMap query);

    /**
     * Remove um registro da tabela.
     * @param query um objeto do tipo `propertyMap` mapeando colunas e valores do(s) registro(s) buscado(s)
     * @return Um vetor de objetos do tipo `Register` contendo os registros removidos.
     */
    std::vector<Register> deleteRegister(propertyMap query);

    /**
     * Atualiza um registro da tabela.
     * @param queryProperties um objeto do tipo `propertyMap` mapeando colunas e valores dos registros que será alterado
     * @param newProperties um objeto do tipo `propertyMap` mapeando colunas e os novos valores dos registros que serão alterados
     * @return Um vetor de objetos do tipo `Register` com os registros alterados.
     */
    std::vector<Register> updateRegister(propertyMap queryProperties, propertyMap newProperties);
};

#endif