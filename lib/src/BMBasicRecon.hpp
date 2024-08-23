#ifndef _INC_BMBASICRECON
#define _INC_BMBASICRECON

#include <iostream>
#include <vector>

#include "BMConst.hpp"

class BMBasicRecon
{
  
private:

public:
  
  //Baby MIND DATA STRUCTURE
  vector<double> mod;
  vector<double> view;
  vector<double> pln;
  vector<double> channel;
  vector<double> HG;
  vector<double> LHG;
  vector<double> RHG;
  vector<double> THG;
  vector<double> BHG;
  vector<double> Lgain;
  vector<double> Rgain;
  vector<double> Tgain;
  vector<double> Bgain;
  vector<double> Lpe;
  vector<double> Rpe;
  vector<double> Tpe;
  vector<double> Bpe;
  vector<double> LG;
  vector<double> Ltime;
  vector<double> Ftime;
  vector<double> Htime;
  vector<double> timedif;
  vector<double> bunch;
  
  int bm_event;
  int year;
  int date;
  int mon;
  int run;
  int hour;

  BMBasicRecon();
  ~BMBasicRecon(); 
  
  void Clear();
  void CopyClass(BMBasicRecon* bmbasicrecon1, BMBasicRecon* bmbasicrecon2);

};

#endif
