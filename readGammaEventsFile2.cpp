#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <TFile.h>
#include <TTree.h>
#include <TCanvas.h>

using namespace std;

int readGammaEventsFile2()
{

	std::ifstream in("/home/homek2/nkopec/NEDA/dane.txt");
	std::ofstream results("/home/homek2/nkopec/NEDA/treedane.root");

	TFile *hfile = TFile::Open("treedane.root", "RECREATE");
		
	std::string line;
	int offset, number; 
	double energy, x, y, z, detectionTime;

	int multievent = 0;
	int numberOfDetections = 0;
	int numberOfEmitions = 0;

	TTree *tree = new TTree("T","Tree with data");

	tree->Branch("offset"        ,&offset        ,"offset/I"        );
	tree->Branch("energy"        ,&energy        ,"energy/D"        );
	tree->Branch("x"             ,&x             ,"x/D"             );
	tree->Branch("y"             ,&y             ,"y/D"             );
	tree->Branch("z"             ,&z             ,"z/D"             );
	tree->Branch("number"        ,&number        ,"number/I"        );
	tree->Branch("detectionTime" ,&detectionTime ,"detectionTime/D" );

	int bank;
	double energy_deposition;
	double Xposition;
	double Yposition;
	double Zposition;
	double time;

	double efficiency;
	double efficiencyUncertainty;

	while (true)
	{	
	        in >> offset >> energy >> x >> y >> z >> number >> detectionTime;
		if(offset == 0){
			tree->Fill();
		}

		if( in.eof() ) break;

		if(offset == -2){
			multievent = true;
			++numberOfEmitions;
		}

		if(offset > 0 && multievent == true){
			bank = offset;
			energy_deposition = energy;
			Xposition = x;
			Yposition = y;
			Zposition = z;
			time = detectionTime;
			multievent = false;
		}
	
		if (offset == bank && detectionTime < 50){
			energy_deposition += energy;
			++numberOfDetections;
		}

		else if (offset <= 0 && bank > 0 && energy > 200){
			energy = energy_deposition;
			x = Xposition;
			y = Yposition;
			z = Zposition;
			detectionTime = time;
			bank = 0;	
			tree->Fill();
		}

		efficiency = numberOfDetections/numberOfEmitions;
		efficiencyUncertainty = sqrt(numberOfDetections/pow(numberOfEmitions, 2) + numberOfEmitions*pow(numberOfDetections, 2)/pow(numberOfEmitions, 4));
	}

		printf("%f\t, %f\n", efficiency, efficiencyUncertainty);

	tree->Print();
	tree->Write();

	results.close();
	delete hfile;
	return 0;
}


