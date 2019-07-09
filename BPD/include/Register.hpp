#ifndef REGISTER_H
#define REGISTER_H

#include <map>
#include <string>

#define DEFAULT_NULL "-.-" //valor "place-holder" para valores vazios
                            // Nao pode ser igualado a um string vazio ->("") 


typedef std::map<std::string, std::string> propertyMap;

/**
 * A classe `Register` provê uma interface para facilitar a criação
 * de Registros aceitos pelo banco de dados. Para isso, ela define
 * um tipo `propertyMap` da seguinte maneira:
 * `typedef std::map<std::string, std::string> propertyMap;`
 * 
 * Esse tipo é um _map_ de colunas para valores, indicando qual o
 * valor em cada coluna para o dado registro.
 */
class Register {
  private:
    propertyMap properties;
    
  public:
    /**
     * Construtor do objeto `Register`.
     * @param propsIn um objeto do tipo `propertyMap` contendo os valores no registro para cada coluna
     * @return Um ponteiro para instância de Register.
     */
    Register(propertyMap propsIn);

    /**
     * Insere propriedades no registro.
     * @param prop um `pair` contendo nome da coluna e valor a serem inseridos no registro
     */
    void insertProperty(std::pair<std::string, std::string> prop);

    /**
     * Recupera uma propriedade do registro.
     * @param name nome da propriedade (coluna) que se está buscando do registro
     * @return Uma string contendo o valor daquela propriedade (coluna) do registro
     */
    std::string getData(std::string name);
};

#endif