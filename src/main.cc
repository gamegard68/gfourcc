/*
 ============================================================================
 Name        : main.cc
 Author      : Edgard Matthijs
 Version     : 0.5
 Copyright   : Copyleft
 Description : AVI File FourCC Changer written in gtkmm3
 ============================================================================
 */

#include "gfourcc_application.h"

using namespace std;

int main (int argc, char *argv[])
{
  auto application = GFourCCApplicaton::create();
  application->run(argc, argv);
}
