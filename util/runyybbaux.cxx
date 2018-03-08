#include "hh2bbyy/yybbaux.h"
#include "HGamAnalysisFramework/RunUtils.h"

int main(int argc, char *argv[])
{
  // Set up the job for xAOD access
  xAOD::Init().ignore();

  // Create our algorithm
  yybbaux *alg = new yybbaux("yybbaux");

  // Use helper to start the job
  HG::runJob(alg, argc, argv);

  return 0;
}
