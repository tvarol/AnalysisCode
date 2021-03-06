#ifndef hh2bbyy_yybbaux_H
#define hh2bbyy_yybbaux_H

#include "HGamAnalysisFramework/HgammaAnalysis.h"
#include "hhTruthWeightTools/hhWeightTool.h"

class yybbaux : public HgammaAnalysis
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.
public:
  // float cutValue;
  float m_yy_truth;
  float m_bbyy_truth;
  float m_yy_1t_l;
  float m_yy_1t_h;
  float m_yy_2t_l;
  float m_yy_2t_h;
  float m_bbyy_1t_l;
  float m_bbyy_1t_h;
  float m_bbyy_2t_l;
  float m_bbyy_2t_h;
  float weight_l;
  float weight_h;

  // variables that don't get filled at submission time should be
  // protected from being send from the submission node to the worker
  // node (done by the //!)
private:
  TTree *myTree; //!
  // TH1 *myHist; //!



public:
  // this is a standard constructor
  yybbaux() { }
  yybbaux(const char *name);
  virtual ~yybbaux();

  // these are the functions inherited from HgammaAnalysis
  virtual EL::StatusCode initialize();
  virtual EL::StatusCode createOutput();
  virtual EL::StatusCode execute();

  xAOD::hhWeightTool* m_hhWeightTool = nullptr;
  
  // this is needed to distribute the algorithm to the workers
  ClassDef(yybbaux, 1);
};

#endif // HGamTools_yybbaux_H
