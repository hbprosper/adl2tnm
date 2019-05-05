#ifndef TNMOBJECT_H
#define TNMOBJECT_H
// ---------------------------------------------------------------------------
// File: TNMObject.h
// Description: Prototype of a generic ADL particle class.
// created: Les Houches 2015 HBP
// updated: 21-Mar-2019 HBP add cutvalue template class
// ---------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "TROOT.h"
#include "TLorentzVector.h"
// ---------------------------------------------------------------------------

class TNMBool : public std::vector<bool>
{
 public:
  TNMBool() : std::vector<bool>() {}
  TNMBool(size_t n) : std::vector<bool>(n, false) {}
  ~TNMBool() {}

  bool OR()
  {
    bool value = false;
    for(size_t c=0; c < size(); c++) value = value || (*this)[c];
    return value;
  }

  bool AND()
  {
    bool value = true;
    for(size_t c=0; c < size(); c++) value = value && (*this)[c];
    return value;
  }  
  bool value;
};

struct TNMObject : public TLorentzVector
{
  TNMObject();
  TNMObject(std::string name, double PT, double Eta, double Phi, double Mass=0);
  TNMObject(const TNMObject& p);
  ~TNMObject();

  static std::string name(int pdgid);
  
  bool       operator<(const TNMObject& p) const;
  TNMObject& operator=(const TNMObject& p);
  TNMObject& operator=(const TLorentzVector& p);
  TNMObject  operator+(const TNMObject& o) const;
  TNMObject  operator-(const TNMObject& o) const;
  TNMObject  operator*(double a) const;
  inline     operator float()  {return Pt(); }
  inline     operator double() {return Pt(); }
  inline     double     operator()(std::string varname) { return Value[varname]; }
  void       operator()(std::string varname, double x);
  
  int  UID;   // event unique identifier
  int  PID;   // PDG ID
  int  ID;
  int  Status;  
  int  Mother;
  bool Skip;
  double Order;
  std::string Name;
  std::vector<int> Daughters;
  std::map<std::string, double> Value;
  
  static int s_UID;

  ClassDef(TNMObject,0)
};
std::ostream& operator<<(std::ostream& os, const TNMObject& o);

#endif
