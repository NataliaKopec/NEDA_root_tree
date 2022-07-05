#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int readGammaEventsFile()
{

	std::ifstream in("/home/homek2/nkopec/NEDA/GammaEvents.0000");
	std::ofstream results("/home/homek2/nkopec/NEDA/dane.txt");

	std::string line;
	int offset1, offset2, number1, number2; 
	double energy1, x1, y1, z1, detectionTime1, energy2, x2, y2, z2, detectionTime2;

	for (int i = 0; i < 24; i++)
	{
		getline(in, line);
		printf("%s\n",line.c_str());
	}

	in >> offset1 >> energy1 >> x1 >> y1 >> z1 >> number1;

	if(offset1 != -2)

	{in >> detectionTime1;}

	printf("%d\t %f\t %f\t %f\t %f\t %d\t %f\n", offset1, energy1, x1, y1, z1, number1, detectionTime1);

	while (true)
	{	
		in >> offset2 >> energy2 >> x2 >> y2 >> z2 >> number2;

		if(offset2 != -2)

		{in >> detectionTime2;}

		if( in.eof() ) break;
		if (offset1 == -2 && offset2 == -2)
		{
			offset1 = 0;
			detectionTime1 = 0;
		}

		results << offset1 << "\t" << energy1 << "\t" << x1 << "\t" << y1 << "\t" << z1 << "\t" << number1 << "\t"  << detectionTime1 << "\n";

		//	printf("%d\t %f\t %f\t %f\t %f\t %d\t %f\n", offset1, energy1, x1, y1, z1, number1, detectionTime1);
	

		offset1 = offset2;
		energy1 = energy2;
	        x1 = x2;
		y1 = y2;
		z1 = z2;
		number1 = number2;
		detectionTime1 = detectionTime2;	
	}

	results.close();
	return 1;
}
