#include <fstream>
#include <iostream>
#include <string.h>
#include <sstream>
#include <limits>
#include <math.h>
#include <time.h>
#include <stdlib.h>

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
int ReadLine(char *filename, int line, double nnn, int natoms, const char *output)//, const char *file)  
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


 for(int i = 0; i < line-natoms ; ++i)//
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
polar[0] = nnn;
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

int Read(char *filename, int ne_min)
{


                        string temp;
                        //if(ne_min < ne_max)
                        {
                        int lo = 0;
                        //int i = 0;

                        ifstream input;
                        input.open(filename, ios::in);

                        while(!input.eof())
                        {
                                char *a = new char[strlen("poldump_") +  sizeof(lo)];
                                sprintf(a, "%s%d", "poldump_", lo);
                                ofstream output(a, ios::out|ios::trunc);

                                getline(input, temp);

                                while(temp != "0" && !input.eof())
                                {

                                                if(temp != "ITEM: TIMESTEP")
                                                {output << temp << endl;}
                                                //cout << temp<< endl;

                                                getline(input, temp);

                                }//


                                        output.close();
                                        delete []a;

                                        ++lo;
                        }
                        input.close();}

                       /* else
                        {
                                int lo = ne_min + 1;
                                ifstream input;
                                input.open(filename, ios::in);

                                while(!input.eof())
                                {
                                        char *b = new char[strlen("poldump_") + sizeof(lo)];
                                        sprintf(b, "%s%d", "poldump_", lo);
                                        ofstream output(b, ios::out|ios::trunc);
                                        getline(input, temp);
                                        while(temp != "0" && !input.eof())
                                        {
                                                if(temp != "ITEM: TIMESTEP")
                                                        {output<<temp<<endl;}
                                                getline(input, temp);

                                        }
                                        output.close();
                                        delete []b;
                                        --lo;
                                }
                        }*/
}



int main(int argc,char **argv)
{

    clock_t t1, t2;
    t1 = clock();
        if(argc != 5)
                {
                cout << "Usage: ./readpol nz ne_min ne_max delta filename.\n" << "nz: the number of unit cells in z-direction\n" << "ne_min and ne_max are the min and max number your loop used in infile of lammps\n" << "delta is the number multipled the min and the max number to get the final loop of electric strength.\n" << "filename is the file name you need to read.\n" <<endl;
                }
        else
                        {
                        int nz = atoi(argv[1]);
                        int ne_min = atoi(argv[2]);
                       // int ne_max = atoi(argv[3]);
                        double delta = atof(argv[3]);
                        char *file = argv[4];
                        char *c;
                        c = new char[strlen("polarization_")+sizeof(nz)];
			int ne_max = -(ne_min);
                        //char *d;
                        //d = new char[strlen("polarization_fin_")+sizeof(nz)];
                        sprintf(c, "%s%d", "polarization_", nz);
                        Read(file, ne_min);
                        //sprintf(d, "%s%d", "polarization_fin_", nz);
                        //if(ne_min < ne_max)
                        //  {
                                for(int i = ne_min; i < ne_max +1; ++i)
                                {
                                double e = double(i) * delta;
                                char *a;
				int j = i - ne_min + 1;
                                a = new char[strlen("poldump_")+sizeof(j)];
                                //char *b;
                                //b = new char[strlen("poldump")+sizeof(i)];
                                sprintf(a, "%s%d", "poldump_", j);
                                //sprintf(b, "%s%d", "displdump", i);
                                char *filename = a;
                                //char *finalname = b;

                                int n = CountLines(filename);
                                //int nf = CountLines(finalname);
                                int natoms = 10 * 6 * 6 * nz;//10 * nx * ny * nz;    
                                cout<<"number of lines:"<< n <<"\n"<<endl;
                                //cout<<"number of lines��~Z"<< nf <<"\n"<<endl;


                                        ReadLine(filename, n, e, natoms, c);
			cout<<"done "<<e<<endl;

                                //ReadLine(finalname, nf, e, natoms, d);
                                t2 = clock();
                                cout<<"Time: "<< double (t2-t1)/CLOCKS_PER_SEC << " s."<<endl;
                                delete []a;
                                //delete []b;
                                }
                       // delete []c;
                        //delete []d;
                          //}
                        //else
                         // {
                                for(int i = ne_max -1; i > ne_min -1 ; --i)
                                {
                                double e = double(i) * delta;
                                char *b;
				int j = 3 * abs(ne_min) - i +1;
                                b = new char[strlen("poldump_") + sizeof(j)];
                                sprintf(b, "%s%d", "poldump_", j);
                                char *filename = b;
                                int n = CountLines(filename);
                                int natoms = 10 * 6 * 6 * nz;
                                cout << "number of lines:" << n << "\n" << endl;
                                ReadLine(filename, n , e, natoms, c);
cout<<"done "<<e<<endl;

                                t2 = clock();
                                cout << "time:"<< double(t2-t1)/CLOCKS_PER_SEC << " s." << endl;
                                delete []b;
                                }
                        delete []c;


                        //}

}
}

