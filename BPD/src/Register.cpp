#include <Register.hpp>

Register::Register(propertyMap propsIn){
	this->properties = propsIn;
}

void Register::insertProperty(std::pair<std::string, std::string> propIn){
	this->properties[propIn.first] = propIn.second;
}
std::string Register::getData(std::string name){
	if(this->properties.find(name) == this->properties.end())
		return DEFAULT_NULL;
	return this->properties[name];
}
