#include "defs.hpp"

using std::string, std::ifstream;

ObjModel::ObjModel(string path) 
{
	DEBUG_LOG("Loading OBJ model " << path);

	const string modelSource = utils::loadFile(path);
}