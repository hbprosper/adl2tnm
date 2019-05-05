#ifndef TNMAdapter_H
#define TNMAdapter_H
//------------------------------------------------------------------
// File: TNMAdapter.h
// Description: map input objects to TNMObjects
// Created:     Sun May  5 01:01:38 2019 by adl2tnm.py v2.0.0
//------------------------------------------------------------------
#include <vector>
#include <string>
#include "tnm.h"
#include "TNMObject.h"

struct TNMAdapter
{
  TNMAdapter();
  ~TNMAdapter();
  void operator()(eventBuffer& ev, std::string a, std::vector<TNMObject>& p);
  void operator()(eventBuffer& ev, std::string a, TNMObject& p);
};
#endif
