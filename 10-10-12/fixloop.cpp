#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main(int argc,char **argv)
{
	clock_t t1, t2;
	t1 = clock();
	if(argc != 3) 
		{
		cout << "Usage: ./fixloop ne_min delta.\n" << "ne_min is the min number(<0) your loop used in infile of lammps\n" << "delta is the number multipled the min and the max number to get the final loop of electric strength." << endl;
		}
	else
		{
			int ne_min = atoi(argv[1]);
			//int ne_max = atoi(argv[2]);
			double delta = atof(argv[2]);
			const char *filename = "loop.in";
			int ne_max = -(ne_min);
			ofstream fout(filename, ios::out|ios::trunc);
				for(int i = ne_min; i < ne_max +1; ++i)
				{
				
					double exf = double(i) * delta;
					double ex = exf / sqrt(3.0);
					double ey = exf / sqrt(3.0);
					double ez = exf / sqrt(3.0);
				
					fout << "reset_timestep 0" << endl;
					fout << "fix ef all efield " << ex << " " << ey << " " << ez << endl;
					fout << "print \" electric field strength = " << exf << " .\"" << endl;
					fout << "fix_modify ef energy yes " << endl;
					fout << "min_style fire" << endl;
					fout << "minimize 0.0 1e-07 30000 100000" << endl;	
					fout << "min_style quickmin" << endl;
					fout << "minimize 0.0 1e-07 30000 100000" << endl;	
					fout << "unfix ef" << endl;
				}
				for(int i = ne_max - 1; i > ne_min -1; --i)
				{
				
					double exf = double(i) * delta;
					double ex = exf / sqrt(3.0);
					double ey = exf / sqrt(3.0);
					double ez = exf / sqrt(3.0);
				
					fout << "reset_timestep 0" << endl;
					fout << "fix ef all efield " << ex << " " << ey << " " << ez << endl;
					fout << "print \" electric field strength = " << exf << " .\"" << endl;
					fout << "fix_modify ef energy yes " << endl;
					fout << "min_style fire" << endl;
					fout << "minimize 0.0 1e-07 30000 100000" << endl;	
					fout << "min_style quickmin" << endl;
					fout << "minimize 0.0 1e-07 30000 100000" << endl;	
					fout << "unfix ef" << endl;
				}
				fout.close();
				return 0;
		}



}
