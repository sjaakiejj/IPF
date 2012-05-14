#include "error_lib.h"

void error_lib::NotSupported(std::string p_arg)
{
  std::cout << p_arg << " currently not supported" << std::endl;
}
