#include <Table.hpp>


Table::Table(std::string tableName){
  std::string filePath = "./datasets/" + tableName + ".csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in | std::fstream::out | std::fstream::app);

  if (!tableFile) {
    throw CreateFileException(filePath);
  }

  this->_tableName = tableName;
  this->_loadColumns();
};

void Table::_loadColumns(){
  std::vector<std::string> columns;
  std::string firstLine, currentColumn;

  std::string filePath = "./datasets/" + this->_tableName + ".csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  getline(tableFile, firstLine);

  if (firstLine.length()) {
    // Arquivo já existe, precisamos salvar as colunas
    std::stringstream columnStream(firstLine);

    while (getline(columnStream, currentColumn, ',')) { 
        columns.push_back(currentColumn); 
    }

    for (auto const& columnName : columns) {
      this->_columns.push_back(columnName);
    }


    // Como o arquivo já existe, precisamos recuperar o último ID
    std::vector<std::string> row;
  	std::string line, value;
	  while (getline(tableFile, line)) {
	    row.clear();

	    if (line.length()) {
	      std::stringstream valuesStream(line);

	      // Carrega todo o registro em uma linha em row
	      while (getline(valuesStream, value, ',')) {
	        row.push_back(value);
	      }
	    }
	  }

    if (row.size()) {
	    this->_lastId = std::stoi(*row.begin()); // posicao 0 = id
    } else { 
      this->_lastId = 0;
    }
  } else {
    // @LOG criação de tabela
  }

  tableFile.close();
}

void Table::setColumns(std::vector<std::string> columns){
  std::string filePath = "./datasets/" + this->_tableName + ".csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::ios::out);

  this->_columns.clear();

  std::string idCol = "id";
  tableFile << idCol << ",";
  this->_columns.push_back(idCol);

  for (auto columnName = columns.begin(); columnName != columns.end(); ++columnName) {
    this->_columns.push_back(*columnName);
    if (std::next(columnName) == columns.end()) {
      tableFile << *columnName << std::endl;
    } else {
      tableFile << *columnName << ",";
    }
  }

  tableFile.close();
  this->_lastId = 0;
}

std::vector<std::string> Table::getShape(){
  return this->_columns;
};

// Operations on tables
Register Table::insertRegister(Register r){
	std::string filePath = "./datasets/" + this->_tableName + ".csv";
	std::fstream tableFile;
 	tableFile.open(filePath, std::ios::app);

 	this->_lastId++;
	tableFile << this->_lastId << ",";
	for (auto column = this->_columns.begin(); column != this->_columns.end(); ++column) {
    if (*column != "id") {   

      tableFile << r.getData(*column);

      if (std::next(column) != this->_columns.end()) {
        tableFile << ",";
      }
    }
  }

  tableFile << std::endl;
  tableFile.close();
  return r;
}

std::vector<Register> Table::select(propertyMap queryProperties){
  std::vector<Register> queryReturn;

  std::string filePath = "./datasets/" + this->_tableName + ".csv";
  std::fstream tableFile;
  tableFile.open(filePath, std::fstream::in);

  std::vector<std::string> row;
  std::string line, value;

  // Carrega linha (registro) da tabela
  while (getline(tableFile, line)) {
    bool isRegisterValid = true;
    row.clear();

    if (line.length()) {
      std::stringstream valuesStream(line);

      // Carrega todo o registro em uma linha em row
      while (getline(valuesStream, value, ',')) {
        row.push_back(value);
      }

      for (auto const& property : queryProperties) {
        // Encontra indice equivalente à coluna procurada
        std::vector<std::string>::iterator it = std::find(this->_columns.begin(), this->_columns.end(), property.first);
        if (it == this->_columns.end()) {
          throw UnknownColumnException(property.first);
        }

        int columnIndex = std::distance(this->_columns.begin(), it);
        if (row[columnIndex] != property.second) {
          isRegisterValid = false;
        }
      }

      if (isRegisterValid) {
        int i = 0;
        propertyMap p;
        for (auto const& column : this->_columns) {
          p[column] = row[i];
          i++;
        }

        Register r(p);
        queryReturn.push_back(r);
      }
    }
  }

  tableFile.close();
  return queryReturn;
}

std::vector<Register> Table::updateRegister(propertyMap queryProperties, propertyMap newProperties){
  std::vector<Register> queryReturn;
  std::fstream tableFile, newTableFile;

  // Open table file
  std::string filePath = "./datasets/" + this->_tableName + ".csv";
  tableFile.open(filePath, std::fstream::in);

  // Open new table file
  std::string newFilePath = "./datasets/" + this->_tableName + "new.csv";
  newTableFile.open(newFilePath, std::fstream::out);

  std::vector<std::string> row;
  std::string line, value;

  // Carrega linha (registro) da tabela
  while (getline(tableFile, line)) {
    bool isRegisterValid = true;
    row.clear();

    if (line.length()) {
      std::stringstream valuesStream(line);

      // Carrega todo o registro em uma linha em row
      while (getline(valuesStream, value, ',')) {
        row.push_back(value);
      }

      for (auto const& property : queryProperties) {
        // Encontra indice equivalente à coluna procurada
        std::vector<std::string>::iterator it = std::find(this->_columns.begin(), this->_columns.end(), property.first);

        if (it == this->_columns.end()) {
          throw UnknownColumnException(property.first);
        }

        int columnIndex = std::distance(this->_columns.begin(), it);
        if (row[columnIndex] != property.second) {
          isRegisterValid = false;
        }
      }

      if (isRegisterValid) {
        // fazer as alterações no registro
        // Encontra indice equivalente à coluna procurada
        for (auto const& property : newProperties) {
          // Encontra indice equivalente à coluna procurada
          std::vector<std::string>::iterator it = std::find(this->_columns.begin(), this->_columns.end(), property.first);
          if (it == this->_columns.end()) {
            throw UnknownColumnException(property.first);
          }

          int columnIndex = std::distance(this->_columns.begin(), it);
          row[columnIndex] = property.second;
        }

        // Adiciona registro no retorno (lista de registros alterados)
        int i = 0;
        propertyMap p;
        for (auto const& column : this->_columns) {
          p[column] = row[i];
          i++;
        }

        Register r(p);
        queryReturn.push_back(r);
      }

      for (auto property = row.begin(); property != row.end(); ++property) {
        newTableFile << *property;
        if (std::next(property) != row.end()) {
          newTableFile << ",";
        }
      }

      newTableFile << std::endl;
    }
  }

  tableFile.close();
  newTableFile.close();

  remove(filePath.c_str());
  rename(newFilePath.c_str(), filePath.c_str());

  return queryReturn;
}

std::vector<Register> Table::deleteRegister(propertyMap queryProperties){
	std::vector<Register> queryReturn;

  std::string inPath = "./datasets/" + this->_tableName + ".csv";
  std::fstream tableIn,tableOut;
  tableIn.open(inPath, std::fstream::in);
 	std::string outPath = "./datasets/" + this->_tableName + "new" + ".csv";
 	tableOut.open(outPath, std::fstream::out);

  std::vector<std::string> row;
  std::string line, value;

  // Carrega linha (registro) da tabela
  while (getline(tableIn, line)) {
    bool registerMatch = true;
    row.clear();

    if (line.length()) {
      std::stringstream valuesStream(line);

      // Carrega todo o registro em uma linha em row
      while (getline(valuesStream, value, ',')) {
        row.push_back(value);
      }

      for (auto const& property : queryProperties) {
        // Encontra indice equivalente à coluna procurada
        std::vector<std::string>::iterator it = std::find(this->_columns.begin(), this->_columns.end(), property.first);
        if (it == this->_columns.end()) {
          throw UnknownColumnException(property.first);
        }

        int columnIndex = std::distance(this->_columns.begin(), it);
        if (row[columnIndex] != property.second) {
          registerMatch = false;
        }
      }

      if (!registerMatch) {
    	for (auto property = row.begin(); property != row.end(); ++property) {
        tableOut << *property;
        if (std::next(property) != row.end()) {
          tableOut << ",";
        }
      }
      	tableOut << std::endl;
      }else{
      	int i = 0;
        propertyMap p;
        for (auto const& column : this->_columns) {
          p[column] = row[i];
          i++;
        }
      	Register r(p);
        queryReturn.push_back(r);
      }
    }
  }
  tableOut.close();
  tableIn.close();

  remove(inPath.c_str());
  rename(outPath.c_str(),inPath.c_str());
  return queryReturn;
}

bool Table::alterTable(std::vector<std::string> columnsIn, std::vector<std::string> columnsOut){

	std::string inPath = "./datasets/" + this->_tableName + ".csv";
  std::fstream tableIn,tableOut;
  tableIn.open(inPath, std::fstream::in);
 	std::string outPath = "./datasets/" + this->_tableName + "new" + ".csv";
 	tableOut.open(outPath, std::fstream::out);

 	std::string line,value;
 	getline(tableIn,line);
 	std::vector<bool> toStay;
 	int i,j;

  // Detecta em que posição estao as colunas para serem removidas e cria vetor de condçao para copia de colunas. 
 	for( i = 0 ; i < (int)this->_columns.size(); i++){
 		bool columnStays = 1;
 		for( j = 0; j < (int)columnsOut.size(); j++){
 			if(this->_columns[i] == columnsOut[j]){
 				columnStays = 0;
 			}
 		}
 		toStay.push_back(columnStays);
 	}
  //Detecta erro de remoção de coluna não existente.
 	for( i = 0 ; i <  (int)columnsOut.size(); i++){
 		bool columnsExists = 0;
 		for( j = 0; j < (int)this->_columns.size(); j++){
 			if(columnsOut[i] == this->_columns[j]){
 				columnsExists = 1;
 			}
 		}
 		if(!columnsExists){
 			throw UnknownColumnException(columnsOut[i]);
 		}
 	}
  // Cria novo vetor de colunas da tabela.
 	std::vector<std::string> newColums;
 	for(i = 0 ; i < (int)this->_columns.size(); i++){
 		if(toStay[i]){
 			std::string column = this->_columns[i]; 
 			newColums.push_back(column);
 		}
 	}
  // Extende vetor de condiçao para copia de colunas.
 	for(j = 0; j < (int)columnsIn.size(); j++){
 		std::string column = columnsIn[j];
 		newColums.push_back(column);
 		bool columnStays = 1;
 		toStay.push_back(columnStays);
 	}
  // Copia header da tabela editada para o aruivo.
 	std::vector<std::string> row;
 	for(i = 0; i < (int)newColums.size(); i++){
 		tableOut << newColums[i];
 		if(i < (int)newColums.size() - 1){
 			tableOut << ",";
 		}
 	}
 	tableOut << "\n"; 
  // Copia colunas da tabela original com alteraçoes.
 	while(getline(tableIn,line)){
		row.clear();

    if (line.length()) {
      std::stringstream valuesStream(line); 
    
	    while (getline(valuesStream, value, ',')) {
	        row.push_back(value);
	    }
	    for(j = 0; j < (int)columnsIn.size(); j++){
	    	std::string voidCol = DEFAULT_NULL;
	    	row.push_back(voidCol);
	    }
	    for(i = 0; i < (int)row.size(); i++){
	    	if(toStay[i]){
	    		tableOut << row[i];
	    		if(i < (int)row.size() - 1){
	    			tableOut << ",";
	    		}
	    	}
	    }
	    tableOut << "\n";
	  }
 	}
 	tableOut.close();
  tableIn.close();

  this->_columns = newColums;

  remove(inPath.c_str());
  rename(outPath.c_str(),inPath.c_str());
  return 1;
}