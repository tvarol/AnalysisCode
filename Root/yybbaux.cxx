#include "hh2bbyy/yybbaux.h"
#include "HGamAnalysisFramework/HgammaIncludes.h"
#include "HGamAnalysisFramework/HGamVariables.h"

// this is needed to distribute the algorithm to the workers
ClassImp(yybbaux)



yybbaux::yybbaux(const char *name)
: HgammaAnalysis(name)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().
}



yybbaux::~yybbaux()
{
  // Here you delete any memory you allocated during your analysis.
}


EL::StatusCode yybbaux::initialize()
{
  // Before the Event Loop 
  m_hhWeightTool = new xAOD::hhWeightTool("hhWeights");
  m_hhWeightTool->initialize();
  this->HgammaAnalysis::initialize();

  TFile *output_file = dynamic_cast<TFile*>(wk()->getOutputFile("MxAOD"));
  myTree = new TTree("massDistr","");
  myTree->SetDirectory(output_file);

  myTree->Branch("m_yy_truth",&m_yy_truth);
  myTree->Branch("m_bbyy_truth",&m_bbyy_truth);
  myTree->Branch("m_yy_1t_l",&m_yy_1t_l);
  myTree->Branch("m_yy_1t_h",&m_yy_1t_h);
  myTree->Branch("m_yy_2t_l",&m_yy_2t_l);
  myTree->Branch("m_yy_2t_h",&m_yy_2t_h);
  myTree->Branch("m_bbyy_1t_l",&m_bbyy_1t_l);
  myTree->Branch("m_bbyy_1t_h",&m_bbyy_1t_h);
  myTree->Branch("m_bbyy_2t_l",&m_bbyy_2t_l);
  myTree->Branch("m_bbyy_2t_h",&m_bbyy_2t_h);
  myTree->Branch("weight_l",&weight_l);
  myTree->Branch("weight_h",&weight_h);


  return EL::StatusCode::SUCCESS;
}

EL::StatusCode yybbaux::createOutput()
{
  // Here you setup the histograms needed for you analysis. This method
  // gets called after the Handlers are initialized, so that the systematic
  // registry is already filled.

  histoStore()->createTH1F("mass_bbyy_1t_l", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_l", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_1t_h", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_h", 130, 200., 1500.);

  histoStore()->createTH1F("mass_bbyy_1t_l_NLO", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_l_NLO", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_1t_h_NLO", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_h_NLO", 130, 200., 1500.);

  histoStore()->createTH1F("mass_bbyy_1t_l_hh1", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_l_hh1", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_1t_h_hh1", 130, 200., 1500.);
  histoStore()->createTH1F("mass_bbyy_2t_h_hh1", 130, 200., 1500.);

  histoStore()->createTH1F("mass_yy_1t_l", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_l", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_1t_h", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_h", 50, 100., 150.);
 
  histoStore()->createTH1F("mass_yy_1t_l_NLO", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_l_NLO", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_1t_h_NLO", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_h_NLO", 50, 100., 150.);

  histoStore()->createTH1F("mass_yy_1t_l_hh1", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_l_hh1", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_1t_h_hh1", 50, 100., 150.);
  histoStore()->createTH1F("mass_yy_2t_h_hh1", 50, 100., 150.);

  histoStore()->createTH1F("mass_jj_1t_l", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_l", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_1t_h", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_h", 250, 0., 250.);

  histoStore()->createTH1F("mass_jj_1t_l_NLO", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_l_NLO", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_1t_h_NLO", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_h_NLO", 250, 0., 250.);

  histoStore()->createTH1F("mass_jj_1t_l_hh1", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_l_hh1", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_1t_h_hh1", 250, 0., 250.);
  histoStore()->createTH1F("mass_jj_2t_h_hh1", 250, 0., 250.);

  histoStore()->createTH1F("leading_jet_pT_1t_l", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_l", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_l", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_l", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_1t_h", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_h", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_h", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_h", 250., 0., 500.);

  histoStore()->createTH1F("leading_jet_pT_1t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_1t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_h_NLO", 250., 0., 500.);

  histoStore()->createTH1F("leading_jet_pT_1t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_1t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_1t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_jet_pT_2t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_jet_pT_2t_h_hh1", 250., 0., 500.);

  histoStore()->createTH1F("leading_y_pT_1t_l", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_l", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_l", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_l", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_1t_h", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_h", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_h", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_h", 250., 0., 500.);

  histoStore()->createTH1F("leading_y_pT_1t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_1t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_h_NLO", 250., 0., 500.);

  histoStore()->createTH1F("leading_y_pT_1t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_1t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_1t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("leading_y_pT_2t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("subleading_y_pT_2t_h_hh1", 250., 0., 500.);

  histoStore()->createTH1F("y_pT_1t_l", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_l", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_1t_h", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_h", 250., 0., 500.);

  histoStore()->createTH1F("y_pT_1t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_l_NLO", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_1t_h_NLO", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_h_NLO", 250., 0., 500.);

  histoStore()->createTH1F("y_pT_1t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_l_hh1", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_1t_h_hh1", 250., 0., 500.);
  histoStore()->createTH1F("y_pT_2t_h_hh1", 250., 0., 500.);

  histoStore()->createTH1F("njets_1tag_l", 10., 0., 10.);
  histoStore()->createTH1F("njets_1tag_h", 10., 0., 10.);
  histoStore()->createTH1F("njets_2tag_l", 10., 0., 10.);
  histoStore()->createTH1F("njets_2tag_h", 10., 0., 10.);
  histoStore()->createTH1F("partonShower", 10., 0., 10.);

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode yybbaux::execute()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  // Important to keep this, so that internal tools / event variables
  // are filled properly.
  HgammaAnalysis::execute();

  //xAOD::PhotonContainer photons = photonHandler()->getCorrectedContainer();
  //if (photons.size() < 2) return EL::StatusCode::SUCCESS;
  //TLorentzVector h = photons[0]->p4() + photons[1]->p4();
  //histoStore()->fillTH1F("m_yy", h.M()/HG::GeV);

  // get event                                                                                                                                                                                          
  xAOD::TEvent *event = wk()->xaodEvent();

  const xAOD::EventInfo* eventInfo = 0;
  if( ! event->retrieve( eventInfo, "EventInfo").isSuccess() ){
    Error("execute()", "Can't find event info collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  }

  const xAOD::EventInfo* HgameventInfo = 0;
  if( ! event->retrieve( HgameventInfo, "HGamEventInfo").isSuccess() ){
    Error("execute()", "Can't find Hgam event info collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  } 
  
  //----------------------                                                                                                                                 
  // TRUTH PARTICLES                                                                                                                                      
  //----------------------                                                                                                                                    
  m_yy_truth = -999.;
  m_bbyy_truth = -999.;
  m_yy_1t_l = -999.;
  m_yy_1t_h = -999.;
  m_yy_2t_l = -999.;
  m_yy_2t_h = -999.;
  m_bbyy_1t_l = -999.;
  m_bbyy_1t_h = -999.;
  m_bbyy_2t_l = -999.;
  m_bbyy_2t_h = -999.;
  weight_l = -999;
  weight_h = -999;

  const xAOD::TruthParticleContainer* truthParticles = 0;
  if( ! event->retrieve( truthParticles, "HGamTruthHiggsBosons").isSuccess() ){
    Error("execute()", "Can't find truth particles collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  }

  // Loop over truth particles to find Higgses                                                                                                             
  const xAOD::TruthParticle *h1 = nullptr, *h2 = nullptr; // hh 

  int nHiggs=0;

  for(const auto& truthPar : *truthParticles) {
    if(nHiggs==0) h1 = truthPar;
    else if(nHiggs==1) h2 = truthPar;
    else Error("execute()", "More than two Higgsessss in the event record. Run away!!"); 
    nHiggs++;
  } // end of loop over truth particles    
  
  if (h1==nullptr || h2==nullptr || nHiggs!=2) return EL::StatusCode::SUCCESS;

  /*  
  const xAOD::JetContainer* truthJets = 0;
  if( ! event->retrieve( truthJets, "HGamAntiKt4TruthJets").isSuccess() ){
    Error("execute()", "Can't find truth jet collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  }

  //  const std::vector<float> weights = eventInfo->mcEventWeights();
  //mcweight = weights[0];


  for(const auto& trueJet : *truthJets) {
    std::cout << "PartonTruthLabelID " << trueJet->auxdata<int>("PartonTruthLabelID") << std::endl;
    //    if(trueJet->auxdata<int>("HadronConeExclTruthLabelID")==5) {
    // std::cout << "There is a b quark" << std::endl;
    // }
  }
  */
  // Pass mhh in MeV 
  m_bbyy_truth = (h1->p4()+h2->p4()).M()/1000;

  //float m_weight_mhh = m_hhWeightTool->getWeight(mhh);
  
  float m_weight_mhh = 1.;

  const xAOD::PhotonContainer* Hgamphotons = 0;
  if( ! event->retrieve( Hgamphotons, "HGamPhotons").isSuccess() ){
    Error("execute()", "Can't find hgam photons collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  }

  const xAOD::JetContainer* jets = 0;
  if( ! event->retrieve( jets, "HGamAntiKt4EMTopoJets").isSuccess() ){
    Error("execute()", "Can't find hgam jet collection. Run away!!" );
    return EL::StatusCode::FAILURE;
  }

  const xAOD::Photon *y1 = nullptr, *y2 = nullptr, *y3 = nullptr; 

  int nGamma = 0;

  for(const auto& truthPhoton : *Hgamphotons) {
    if(nGamma==0) y1 = truthPhoton;
    else if (nGamma==1) y2 = truthPhoton;
    else if (nGamma==2) y3 = truthPhoton;
    else Error("execute()", "More than three photons in the event record. Run away!!");     
    nGamma++;
  } // end of loop over truth particles 

  if (y1==nullptr || y2==nullptr) return EL::StatusCode::SUCCESS;  

  float min = 0;
  float chosenMass = 0;

  chosenMass = (y1->p4()+y2->p4()).M()/1000;

  if (nGamma==3){
    float mass12 = (y1->p4()+y2->p4()).M()/1000;
    float mass13 = (y1->p4()+y3->p4()).M()/1000;
    float mass23 = (y2->p4()+y3->p4()).M()/1000;
    float dmass12 = std::abs(125 - (y1->p4()+y2->p4()).M()/1000);
    float dmass13 = std::abs(125 - (y1->p4()+y3->p4()).M()/1000);
    float dmass23 = std::abs(125 - (y2->p4()+y3->p4()).M()/1000);

    min = dmass12;
    chosenMass = mass12;
    if(dmass12 > dmass13){
      min = dmass13;
      chosenMass = mass13;
      if(dmass13 > dmass23){
	min = dmass23;
	chosenMass = mass23;
      }
    }
    else{
      if(dmass12 > dmass23){
	min = dmass23;
	chosenMass = mass23;
      }
    }
  }

  m_yy_truth = chosenMass;
  
  bool isPassed = eventHandler()->getVar<char>("isPassed");

  float weight = eventHandler()->getVar<float>("weight");

  // MxAOD with OLD hh WEIGHTS
  /*
  float weight_bbyy_hh1_l = eventHandler()->getVar<float>("yybb_lowMass_weight"); // WITH FIRST (WRONG) hh WEIGHT
  float weight_bbyy_hh1_h = eventHandler()->getVar<float>("yybb_highMass_weight"); // WITH FIRST (WRONG) hh WEIGHT
  float weight_bbyy_l = eventHandler()->getVar<float>("yybb_lowMass_weight_LO"); // WITHOUT hh WEIGHT
  float weight_bbyy_h = eventHandler()->getVar<float>("yybb_highMass_weight_LO"); // WITHOUT hh WEIGHT

  float norm_weight = lumiXsecWeight();

  float event_weight_l = weight*weight_bbyy_l*norm_weight*36.1;
  float event_weight_h = weight*weight_bbyy_h*norm_weight*36.1;

  float event_weight_l_NLO = event_weight_l*m_weight_mhh;
  float event_weight_h_NLO = event_weight_h*m_weight_mhh;

  float event_weight_hh1_l = weight*weight_bbyy_hh1_l*norm_weight*36.1;
  float event_weight_hh1_h = weight*weight_bbyy_hh1_h*norm_weight*36.1;
  */

  /*
  //MxAOD with NEW hh WEIGHTS
  float weight_bbyy_hh1_l = eventHandler()->getVar<float>("yybb_lowMass_weight"); // WITH NEW hh WEIGHT                                  
  float weight_bbyy_hh1_h = eventHandler()->getVar<float>("yybb_highMass_weight"); // WITH NEW hh WEIGHT                                 
  float weight_bbyy_l = eventHandler()->getVar<float>("yybb_lowMass_weight_LO"); // WITHOUT hh WEIGHT                                              
  float weight_bbyy_h = eventHandler()->getVar<float>("yybb_highMass_weight_LO"); // WITHOUT hh WEIGHT     
  */

  // Multiplying by 0.34 only for different lambda samples to correct for filter efficiency
  
  float weight_bbyy_l = eventHandler()->getVar<float>("yybb_lowMass_weight"); 
  float weight_bbyy_h = eventHandler()->getVar<float>("yybb_highMass_weight");

  //  float norm_weight = lumiXsecWeight()*0.34*(8.8111E-05/(1.4412E-02*7.8752E-03*0.34));
  float norm_weight = lumiXsecWeight();

  float event_weight_l = weight*weight_bbyy_l*norm_weight*36.1;
  float event_weight_h = weight*weight_bbyy_h*norm_weight*36.1;

  weight_l = event_weight_l;
  weight_h = event_weight_h;
  //  float event_weight_l_NLO = event_weight_l*m_weight_mhh;
  //float event_weight_h_NLO = event_weight_h*m_weight_mhh;

  float event_weight_l_NLO =1.;
  float event_weight_h_NLO = 1.;

  float event_weight_hh1_l = 1.;
  float event_weight_hh1_h = 1.;

  //  float event_weight_hh1_l = weight*weight_bbyy_hh1_l*norm_weight*36.1;
  //float event_weight_hh1_h = weight*weight_bbyy_hh1_h*norm_weight*36.1;

  //hh1 ==> with new weights in MxAOD
  //NLO ==> kendi hesapladigim weight
  //hicbir ek olmadan ==> weightsiz


  //  float event_weight = event_weight_h;

  float m_yy = eventHandler()->getVar<float>("m_yy");
  float m_yyjj_l = eventHandler()->getVar<float>("yybb_lowMass_m_yybb");
  float m_yyjj_h = eventHandler()->getVar<float>("yybb_highMass_m_yybb");

  float m_bb_l = eventHandler()->getVar<float>("yybb_lowMass_m_bb_uncnstrnd");
  float m_bb_h = eventHandler()->getVar<float>("yybb_highMass_m_bb_uncnstrnd");

  float j1_pT_l = eventHandler()->getVar<float>("yybb_lowMass_pT_j1");
  float j2_pT_l = eventHandler()->getVar<float>("yybb_lowMass_pT_j2");

  float j1_pT_h = eventHandler()->getVar<float>("yybb_highMass_pT_j1");
  float j2_pT_h = eventHandler()->getVar<float>("yybb_highMass_pT_j2");

  float y1_pT = eventHandler()->getVar<float>("pT_y1");
  float y2_pT = eventHandler()->getVar<float>("pT_y2");

  int  btag_cat = eventHandler()->getVar<int>("yybb_bTagCat");

  int cutFlowyy = eventHandler()->getVar<int>("cutFlow");
  int cutFlowyybb_l = eventHandler()->getVar<int>("yybb_lowMass_cutFlow");
  int cutFlowyybb_h = eventHandler()->getVar<int>("yybb_highMass_cutFlow");

  /*
  histoStore()->fillTH1F("mass_bbyy_allEvents_l", m_yyjj_l/1000, event_weight_l);
  histoStore()->fillTH1F("mass_yy_allEvents_l", m_yy/1000, event_weight_l);
  histoStore()->fillTH1F("mass_jj_allEvents_l", m_bb_l/1000, event_weight_l);

  histoStore()->fillTH1F("mass_bbyy_allEvents_h", m_yyjj_h/1000, event_weight_h);
  histoStore()->fillTH1F("mass_yy_allEvents_h", m_yy/1000, event_weight_h);
  histoStore()->fillTH1F("mass_jj_allEvents_h", m_bb_h/1000, event_weight_h);
  */

  //Selection
  if(btag_cat==1 && isPassed){

    if(cutFlowyy>14 && cutFlowyybb_l>3){
      histoStore()->fillTH1F("mass_bbyy_1t_l", m_yyjj_l/1000, event_weight_l);
      histoStore()->fillTH1F("mass_yy_1t_l", m_yy/1000, event_weight_l);
      histoStore()->fillTH1F("mass_jj_1t_l", m_bb_l/1000, event_weight_l);

      m_yy_1t_l = m_yy/1000;
      m_bbyy_1t_l = m_yyjj_l/1000;

      histoStore()->fillTH1F("mass_bbyy_1t_l_NLO", m_yyjj_l/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("mass_yy_1t_l_NLO", m_yy/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("mass_jj_1t_l_NLO", m_bb_l/1000, event_weight_l_NLO);

      histoStore()->fillTH1F("mass_bbyy_1t_l_hh1", m_yyjj_l/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("mass_yy_1t_l_hh1", m_yy/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("mass_jj_1t_l_hh1", m_bb_l/1000, event_weight_hh1_l);

      histoStore()->fillTH1F("njets_1tag_l", jets->size(), event_weight_l);


      if(j1_pT_l > j2_pT_l){
        histoStore()->fillTH1F("leading_jet_pT_1t_l", j1_pT_l/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l", j2_pT_l/1000, event_weight_l);

	histoStore()->fillTH1F("leading_jet_pT_1t_l_NLO", j1_pT_l/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l_NLO", j2_pT_l/1000, event_weight_l_NLO);

	histoStore()->fillTH1F("leading_jet_pT_1t_l_hh1", j1_pT_l/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l_hh1", j2_pT_l/1000, event_weight_hh1_l);
      }
      else{
        histoStore()->fillTH1F("leading_jet_pT_1t_l", j2_pT_l/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l", j1_pT_l/1000, event_weight_l);

	histoStore()->fillTH1F("leading_jet_pT_1t_l_NLO", j2_pT_l/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l_NLO", j1_pT_l/1000, event_weight_l_NLO);
     
	histoStore()->fillTH1F("leading_jet_pT_1t_l_hh1", j2_pT_l/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_jet_pT_1t_l_hh1", j1_pT_l/1000, event_weight_hh1_l);
      }

      histoStore()->fillTH1F("y_pT_1t_l", y1_pT/1000, event_weight_l);
      histoStore()->fillTH1F("y_pT_1t_l", y2_pT/1000, event_weight_l);

      histoStore()->fillTH1F("y_pT_1t_l_NLO", y1_pT/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("y_pT_1t_l_NLO", y2_pT/1000, event_weight_l_NLO);

      histoStore()->fillTH1F("y_pT_1t_l_hh1", y1_pT/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("y_pT_1t_l_hh1", y2_pT/1000, event_weight_hh1_l);

      if(y1_pT > y2_pT){
        histoStore()->fillTH1F("leading_y_pT_1t_l", y1_pT/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_y_pT_1t_l", y2_pT/1000, event_weight_l);

	histoStore()->fillTH1F("leading_y_pT_1t_l_NLO", y1_pT/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_y_pT_1t_l_NLO", y2_pT/1000, event_weight_l_NLO);

	histoStore()->fillTH1F("leading_y_pT_1t_l_hh1", y1_pT/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_y_pT_1t_l_hh1", y2_pT/1000, event_weight_hh1_l);
      }
      else{
        histoStore()->fillTH1F("leading_y_pT_1t_l", y2_pT/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_y_pT_1t_l", y1_pT/1000, event_weight_l);

	histoStore()->fillTH1F("leading_y_pT_1t_l_NLO", y2_pT/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_y_pT_1t_l_NLO", y1_pT/1000, event_weight_l_NLO);

	histoStore()->fillTH1F("leading_y_pT_1t_l_hh1", y2_pT/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_y_pT_1t_l_hh1", y1_pT/1000, event_weight_hh1_l);
      }
    }

    if(cutFlowyy>14 && cutFlowyybb_h>3){
      histoStore()->fillTH1F("mass_bbyy_1t_h", m_yyjj_h/1000, event_weight_h);
      histoStore()->fillTH1F("mass_yy_1t_h", m_yy/1000, event_weight_h);
      histoStore()->fillTH1F("mass_jj_1t_h", m_bb_h/1000, event_weight_h);

      m_yy_1t_h = m_yy/1000;
      m_bbyy_1t_h = m_yyjj_h/1000;

      histoStore()->fillTH1F("mass_bbyy_1t_h_NLO", m_yyjj_h/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("mass_yy_1t_h_NLO", m_yy/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("mass_jj_1t_h_NLO", m_bb_h/1000, event_weight_h_NLO);

      histoStore()->fillTH1F("mass_bbyy_1t_h_hh1", m_yyjj_h/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("mass_yy_1t_h_hh1", m_yy/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("mass_jj_1t_h_hh1", m_bb_h/1000, event_weight_hh1_h);

      histoStore()->fillTH1F("njets_1tag_h", jets->size(), event_weight_h);

      if(j1_pT_h > j2_pT_h){
        histoStore()->fillTH1F("leading_jet_pT_1t_h", j1_pT_h/1000, event_weight_h);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h", j2_pT_h/1000, event_weight_h);

	histoStore()->fillTH1F("leading_jet_pT_1t_h_NLO", j1_pT_h/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h_NLO", j2_pT_h/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_jet_pT_1t_h_hh1", j1_pT_h/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h_hh1", j2_pT_h/1000, event_weight_hh1_h);
      }
      else{
        histoStore()->fillTH1F("leading_jet_pT_1t_h", j2_pT_h/1000, event_weight_h);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h", j1_pT_h/1000, event_weight_h);

	histoStore()->fillTH1F("leading_jet_pT_1t_h_NLO", j2_pT_h/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h_NLO", j1_pT_h/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_jet_pT_1t_h_hh1", j2_pT_h/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_jet_pT_1t_h_hh1", j1_pT_h/1000, event_weight_hh1_h);
      }

      histoStore()->fillTH1F("y_pT_1t_h", y1_pT/1000, event_weight_h);
      histoStore()->fillTH1F("y_pT_1t_h", y2_pT/1000, event_weight_h);

      histoStore()->fillTH1F("y_pT_1t_h_NLO", y1_pT/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("y_pT_1t_h_NLO", y2_pT/1000, event_weight_h_NLO);

      histoStore()->fillTH1F("y_pT_1t_h_hh1", y1_pT/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("y_pT_1t_h_hh1", y2_pT/1000, event_weight_hh1_h);

      if(y1_pT > y2_pT){
        histoStore()->fillTH1F("leading_y_pT_1t_h", y1_pT/1000, event_weight_h);
        histoStore()->fillTH1F("subleading_y_pT_1t_h", y2_pT/1000, event_weight_h);

	histoStore()->fillTH1F("leading_y_pT_1t_h_NLO", y1_pT/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_y_pT_1t_h_NLO", y2_pT/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_y_pT_1t_h_hh1", y1_pT/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_y_pT_1t_h_hh1", y2_pT/1000, event_weight_hh1_h);
      }
      else{
        histoStore()->fillTH1F("leading_y_pT_1t_h", y2_pT/1000, event_weight_h);
        histoStore()->fillTH1F("subleading_y_pT_1t_h", y1_pT/1000, event_weight_h);

	histoStore()->fillTH1F("leading_y_pT_1t_h_NLO", y2_pT/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_y_pT_1t_h_NLO", y1_pT/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_y_pT_1t_h_hh1", y2_pT/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_y_pT_1t_h_hh1", y1_pT/1000, event_weight_hh1_h);
      }
    }
    
  }

  if(btag_cat==2 && isPassed){

    if(cutFlowyy>14 && cutFlowyybb_l>3){
      histoStore()->fillTH1F("mass_bbyy_2t_l", m_yyjj_l/1000, event_weight_l);
      histoStore()->fillTH1F("mass_yy_2t_l", m_yy/1000, event_weight_l);
      histoStore()->fillTH1F("mass_jj_2t_l", m_bb_l/1000, event_weight_l);

      m_yy_2t_l = m_yy/1000;
      m_bbyy_2t_l = m_yyjj_l/1000;

      histoStore()->fillTH1F("mass_bbyy_2t_l_NLO", m_yyjj_l/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("mass_yy_2t_l_NLO", m_yy/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("mass_jj_2t_l_NLO", m_bb_l/1000, event_weight_l_NLO);

      histoStore()->fillTH1F("mass_bbyy_2t_l_hh1", m_yyjj_l/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("mass_yy_2t_l_hh1", m_yy/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("mass_jj_2t_l_hh1", m_bb_l/1000, event_weight_hh1_l);

      histoStore()->fillTH1F("njets_2tag_l", jets->size(), event_weight_l);

      if(j1_pT_l > j2_pT_l){
        histoStore()->fillTH1F("leading_jet_pT_2t_l", j1_pT_l/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_jet_pT_2t_l", j2_pT_l/1000, event_weight_l);

	histoStore()->fillTH1F("leading_jet_pT_2t_l_NLO", j1_pT_l/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_2t_l_NLO", j2_pT_l/1000, event_weight_l_NLO);
 
	histoStore()->fillTH1F("leading_jet_pT_2t_l_hh1", j1_pT_l/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_jet_pT_2t_l_hh1", j2_pT_l/1000, event_weight_hh1_l);
      }
      else{
        histoStore()->fillTH1F("leading_jet_pT_2t_l", j2_pT_l/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_jet_pT_2t_l", j1_pT_l/1000, event_weight_l);

	histoStore()->fillTH1F("leading_jet_pT_2t_l_NLO", j2_pT_l/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_2t_l_NLO", j1_pT_l/1000, event_weight_l_NLO);

	histoStore()->fillTH1F("leading_jet_pT_2t_l_hh1", j2_pT_l/1000, event_weight_hh1_l);
	histoStore()->fillTH1F("subleading_jet_pT_2t_l_hh1", j1_pT_l/1000, event_weight_hh1_l);
      }

      histoStore()->fillTH1F("y_pT_2t_l", y1_pT/1000, event_weight_l);
      histoStore()->fillTH1F("y_pT_2t_l", y2_pT/1000, event_weight_l);

      histoStore()->fillTH1F("y_pT_2t_l_NLO", y1_pT/1000, event_weight_l_NLO);
      histoStore()->fillTH1F("y_pT_2t_l_NLO", y2_pT/1000, event_weight_l_NLO);

      histoStore()->fillTH1F("y_pT_2t_l_hh1", y1_pT/1000, event_weight_hh1_l);
      histoStore()->fillTH1F("y_pT_2t_l_hh1", y2_pT/1000, event_weight_hh1_l);

      if(y1_pT > y2_pT){
        histoStore()->fillTH1F("leading_y_pT_2t_l", y1_pT/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_y_pT_2t_l", y2_pT/1000, event_weight_l);

	histoStore()->fillTH1F("leading_y_pT_2t_l_NLO", y1_pT/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_y_pT_2t_l_NLO", y2_pT/1000, event_weight_l_NLO);

	histoStore()->fillTH1F("leading_y_pT_2t_l_hh1", y1_pT/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_y_pT_2t_l_hh1", y2_pT/1000, event_weight_hh1_l);
      }
      else{
        histoStore()->fillTH1F("leading_y_pT_2t_l", y2_pT/1000, event_weight_l);
        histoStore()->fillTH1F("subleading_y_pT_2t_l", y1_pT/1000, event_weight_l);

	histoStore()->fillTH1F("leading_y_pT_2t_l_NLO", y2_pT/1000, event_weight_l_NLO);
        histoStore()->fillTH1F("subleading_y_pT_2t_l_NLO", y1_pT/1000, event_weight_l_NLO);
     
	histoStore()->fillTH1F("leading_y_pT_2t_l_hh1", y2_pT/1000, event_weight_hh1_l);
        histoStore()->fillTH1F("subleading_y_pT_2t_l_hh1", y1_pT/1000, event_weight_hh1_l);
      }
    }

    if(cutFlowyy>14 && cutFlowyybb_h>3){
      histoStore()->fillTH1F("mass_bbyy_2t_h", m_yyjj_h/1000, event_weight_h);
      histoStore()->fillTH1F("mass_yy_2t_h", m_yy/1000, event_weight_h);
      histoStore()->fillTH1F("mass_jj_2t_h", m_bb_h/1000, event_weight_h);

      m_yy_2t_h = m_yy/1000;
      m_bbyy_2t_h =  m_yyjj_h/1000;

      histoStore()->fillTH1F("mass_bbyy_2t_h_NLO", m_yyjj_h/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("mass_yy_2t_h_NLO", m_yy/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("mass_jj_2t_h_NLO", m_bb_h/1000, event_weight_h_NLO);

      histoStore()->fillTH1F("mass_bbyy_2t_h_hh1", m_yyjj_h/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("mass_yy_2t_h_hh1", m_yy/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("mass_jj_2t_h_hh1", m_bb_h/1000, event_weight_hh1_h);

      histoStore()->fillTH1F("njets_2tag_h", jets->size(), event_weight_h);

      //    if(jets->size()==5) std::cout << "Event number - 5jet " << eventInfo->eventNumber() << " jet size " << jets->size() <<std::endl;
      // if(jets->size()==6) std::cout << "Event number - 6jet " << eventInfo->eventNumber() << " jet size " << jets->size() <<std::endl;
      // if(jets->size()==7) std::cout << "Event number - 7jet " << eventInfo->eventNumber() << " jet size " << jets->size() <<std::endl;
      //if(jets->size()==8) std::cout << "Event number - 8jet " << eventInfo->eventNumber() << " jet size " << jets->size() <<std::endl;
      //if(jets->size()==9) std::cout << "Event number - 9jet " << eventInfo->eventNumber() << " jet size " << jets->size() <<std::endl;
      // int count = 0.;
      //for(const auto& eachJet : *jets){
      //  std::cout << "jet pT " << eachJet->pt() * 0.001  << " jet eta " << eachJet->eta() << std::endl;
      //  count++;
      //	}

      //	histoStore()->fillTH1F("njets_2tag_h_30", count, event_weight_h);

      if(j1_pT_h > j2_pT_h){
	histoStore()->fillTH1F("leading_jet_pT_2t_h", j1_pT_h/1000, event_weight_h);
	histoStore()->fillTH1F("subleading_jet_pT_2t_h", j2_pT_h/1000, event_weight_h);
     
	histoStore()->fillTH1F("leading_jet_pT_2t_h_NLO", j1_pT_h/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_2t_h_NLO", j2_pT_h/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_jet_pT_2t_h_hh1", j1_pT_h/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_jet_pT_2t_h_hh1", j2_pT_h/1000, event_weight_hh1_h);
      }
      else{
	histoStore()->fillTH1F("leading_jet_pT_2t_h", j2_pT_h/1000, event_weight_h);
	histoStore()->fillTH1F("subleading_jet_pT_2t_h", j1_pT_h/1000, event_weight_h);

	histoStore()->fillTH1F("leading_jet_pT_2t_h_NLO", j2_pT_h/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_jet_pT_2t_h_NLO", j1_pT_h/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_jet_pT_2t_h_hh1", j2_pT_h/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_jet_pT_2t_h_hh1", j1_pT_h/1000, event_weight_hh1_h);
      }

      histoStore()->fillTH1F("y_pT_2t_h", y1_pT/1000, event_weight_h);
      histoStore()->fillTH1F("y_pT_2t_h", y2_pT/1000, event_weight_h);

      histoStore()->fillTH1F("y_pT_2t_h_NLO", y1_pT/1000, event_weight_h_NLO);
      histoStore()->fillTH1F("y_pT_2t_h_NLO", y2_pT/1000, event_weight_h_NLO);

      histoStore()->fillTH1F("y_pT_2t_h_hh1", y1_pT/1000, event_weight_hh1_h);
      histoStore()->fillTH1F("y_pT_2t_h_hh1", y2_pT/1000, event_weight_hh1_h);

      if(y1_pT > y2_pT){
	histoStore()->fillTH1F("leading_y_pT_2t_h", y1_pT/1000, event_weight_h);
	histoStore()->fillTH1F("subleading_y_pT_2t_h", y2_pT/1000, event_weight_h);

	histoStore()->fillTH1F("leading_y_pT_2t_h_NLO", y1_pT/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_y_pT_2t_h_NLO", y2_pT/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_y_pT_2t_h_hh1", y1_pT/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_y_pT_2t_h_hh1", y2_pT/1000, event_weight_hh1_h);
      }
      else{
        histoStore()->fillTH1F("leading_y_pT_2t_h", y2_pT/1000, event_weight_h);
        histoStore()->fillTH1F("subleading_y_pT_2t_h", y1_pT/1000, event_weight_h);

	histoStore()->fillTH1F("leading_y_pT_2t_h_NLO", y2_pT/1000, event_weight_h_NLO);
        histoStore()->fillTH1F("subleading_y_pT_2t_h_NLO", y1_pT/1000, event_weight_h_NLO);

	histoStore()->fillTH1F("leading_y_pT_2t_h_hh1", y2_pT/1000, event_weight_hh1_h);
        histoStore()->fillTH1F("subleading_y_pT_2t_h_hh1", y1_pT/1000, event_weight_hh1_h);
      }

    }
  }
  myTree->Fill();
  m_yy_truth = 0.;
  m_bbyy_truth = 0;
  m_yy_1t_l = 0.;
  m_yy_1t_h = 0.;
  m_yy_2t_l = 0.;
  m_yy_2t_h = 0.;
  m_bbyy_1t_l = 0.;
  m_bbyy_1t_h = 0.;
  m_bbyy_2t_l = 0.;
  m_bbyy_2t_h = 0.;
  weight_l = 0;
  weight_h =0;

  return EL::StatusCode::SUCCESS;
}
