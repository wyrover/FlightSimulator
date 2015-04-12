#include <fstream>
#include "XMLReader.h"

int main()
{
	XMLReader xmlReader;

	xmlReader.ReadFile("testing.xml");

	return 0;
}

