#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <limits>
#include <math.h>
#include <time.h>

using namespace std;

int CountLines(char *filename)  
{  
    ifstream ReadDump;  
    int n=0;  
    string tmp;  
    ReadDump.open(filename, ios::in);
    if(ReadDump.fail())
    {  
        return 0;  
    }  
    else  
    {  
        while(getline(ReadDump,tmp,'\n'))  
        {  
            n++;  
        }  
       
        ReadDump.close();  
        return n;  
    }  
}  

int sgn(double d)
{
      if(d<0) return -1;
      else if (d==0) return 0;
      else return 1;
}

//
int ReadLine(char *filename, int line, int nz, int natoms, const char *output, double ne)//, const char *file)  
{  
   
   double data[natoms][5];  
   double polar[5];

    ifstream ReadDump;  
    ReadDump.open(filename,ios::in);  
    
    
    if(!ReadDump)  
    {  
        cout << "No displdump file, please check again." << endl;
        return 1;  
    }  
    
    for(int i = 0; i < line-natoms; ++i)
    {
        ReadDump.ignore (numeric_limits<streamsize>::max(),'\n' );
    }

    while (!ReadDump.eof())
   {  
         for(int j = 0; j < natoms; j++)
         {    
             for(int k = 0; k < 5; k++)
             {
              ReadDump >>  data[j][k];
//cout << data[j][k] << " " << endl; 
             }
         }
         
   }
    ReadDump.close();
polar[0] = (double)ne;
//cout<< polar[0] <<endl;
      for(int k = 2; k < 5; k++)
         {   double sum =0.0;
             for(int j = 0; j < natoms; j++)
             {
              sum += data[j][k];
              polar[k - 1] = sum;
		//cout << sum << " " << endl; 

             }
             //cout << polar[k-1] << " " << endl;
         }  
           polar[4] = sqrt(polar[2] * polar[2] + polar[2] * polar[2] + polar[3] * polar[3]) * sgn(polar[1]) * sgn(polar[2]) * sgn(polar[3]);

    ofstream fout(output, ios::app|ios::out);
    
            fout << polar[0] << " " <<  polar[1] << " " << polar[2] << " " << polar[3] << " " << polar[4] << endl;
          fout.close(); 
   
    return 0;  
}  

int main(int argc,char **argv)  
{  
    
    clock_t t1, t2;
    t1 = clock();
    for(int i = 1; i < 6; ++i)
	{//
    //char filename[]="polpldump_1";  
    //char finalname[]="polpldump_fin_1";
	if(argc != 5) 
		{
		cout << "Usage: ./readpol nz ne_min ne_max delta.\n" <<// "filename: type of dump file you'd like to read, such as pol, displ, etc. ATTENTION: the word of dump will be added after the input type.\n" 
 "nz: the number of unit cells in z-direction" << endl;
		}
	else
			{      // char w = char(argv[1]);
                                //strcat(w,"dump");
				int nz = argv[1];
				int ne_min = argv[2];
				int ne_max = argv[3];
				double delta = argv[4];
   			 	char *a;
				for (int i = ne_min; i < ne_max + 1; i++)
    				{
					double ne = delta * i;
				a = new char[strlen("poldump_")+sizeof(i)];
        			//char *b;
        			//b = new char[strlen("displdump")+sizeof(ne)];
    				sprintf(a, "%s%d", "poldump_", i);
    				//sprintf(b, "%s%d", "displdump", ne);
    				char *filename = a; 
    				//char *finalname = b;

    				int n = CountLines(filename);
    				//int nf = CountLines(finalname);
    				int natoms = 10 * 6* 6 * nz;//10 * 10 * 10 * nz;//10 * nx * ny * nz;    
    				cout<<"number of lines："<< n <<"\n"<<endl;  
   	 			//cout<<"number of lines："<< nf <<"\n"<<endl;
   	 			const char *c = "polarization";
   	 			//const char *d = "polarization_final";
    

  	 			ReadLine(filename, n, nz, natoms, c, ne);
 				//ReadLine(finalname, nf, nz, natoms, d);
}
  				t2 = clock();
  				cout<<"Time: "<< double (t2-t1)/CLOCKS_PER_SEC << " s."<<endl;
				delete []a;
        			delete []b;
    			}
	}
}  

