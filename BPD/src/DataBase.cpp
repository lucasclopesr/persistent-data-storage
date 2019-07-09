#include <DataBase.hpp>

DataBase *DataBase::_DB = 0;
mapOfTables DataBase::_tables;

DataBase* DataBase::getDBConnection() {
  if (!DataBase::_DB) {
    // @LOG DB connection created
    DataBase::_DB = new DataBase;
    DataBase::loadAllTables();

  }

  return DataBase::_DB;
};

void DataBase::loadAllTables(){
  DIR *dir;
  struct dirent *entry;
  if ((dir = opendir("./datasets/")) != NULL) {
    while ((entry = readdir(dir)) != NULL) {
      bool isEntryValid = (std::strcmp(entry->d_name, ".") != 0 && std::strcmp(entry->d_name, "..") != 0);

      if (isEntryValid) {
        std::string tableFile = entry->d_name;
        std::string tableName = tableFile.substr(0, tableFile.length() -4);

        Table *t = new Table(tableName);
        DataBase::_tables.insert(std::pair<std::string, Table*>(tableName, t));
        // @LOG all tables loaded
      }
    }
  } else { 
    int operationFailed = system("mkdir -p ./datasets");
    if (operationFailed) {
      throw CreateFolderException();
      // @LOG error
    }
  }
}

Table* DataBase::createTable(std::string tableName, std::vector<std::string> tableColumns){
  if (this->_tables.find(tableName) == this->_tables.end()) {
    Table* t = new Table(tableName);
    t->setColumns(tableColumns);
    this->_tables.insert(std::pair<std::string, Table*>(tableName, t));
    // @LOG criou com sucesso
    return t;
  } else {
    return this->getTable(tableName);
  }
}

Table* DataBase::getTable(std::string tableName){
  if (this->_tables.find(tableName) == this->_tables.end()) {
    throw UnknownTableException(tableName);
  }

  return this->_tables[tableName];
}

Table* DataBase::deleteTable(std::string tableName){
  if (this->_tables.find(tableName) == this->_tables.end()) {
    throw UnknownTableException(tableName);
  }

  Table* t = this->_tables[tableName];
  this->_tables.erase(tableName);

  std::string filePath = "./datasets/" + tableName + ".csv";
  if (std::remove(filePath.c_str())) {
    throw DeleteFileException(filePath);
  }

  // @LOG deletou com sucesso
  return t;
}

std::string DataBase::listTables(){
  std::string tableNames = "";
  for (auto const& table : DataBase::_tables) {
    tableNames += table.first + " ";
  }

  return tableNames;
}