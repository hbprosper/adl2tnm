#ifndef DELPHESADAPTER_H
#define DELPHESADAPTER_H

#include <vector>
#include <string>
#include "tnm.h"
#include "TNMObject.h"

struct DelphesAdapter
{
  DelphesAdapter();
  ~DelphesAdapter();
  void operator()(eventBuffer& ev, std::string a, std::vector<TNMObject>& p);
  void operator()(eventBuffer& ev, std::string a, TNMObject& p);
};

#endif

