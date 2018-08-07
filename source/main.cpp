#include "Name.h"

using std::cin;
using std::cout;

int main() 
{

  Name* name = new Name();
  name->SaveToFile();

  cin.get();
  return 0;
}