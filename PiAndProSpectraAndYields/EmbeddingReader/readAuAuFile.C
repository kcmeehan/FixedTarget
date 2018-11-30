#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>


//-----------------------------------------------------------------------------------------------------------------------
// 
//  Note: This file was made to work only on Au + Au FXT 2015 runs... please feel free to generalize the code
//
//-----------------------------------------------------------------------------------------------------------------------

using namespace std;

vector< std::vector< std::vector <int> > > readAuAuFile(const char* FILE_NAME, int start=-999, int end=99999999){
  vector< std::vector< std::vector <int> > > vCentDB;
	vector< std::vector<int> > vRun33;
	vector< std::vector<int> > vRun34;
	vector< std::vector<int> > vRun35;
	vector< std::vector<int> > vRun36;
	vector< std::vector<int> > vRun37;
	vector< std::vector<int> > vRun38;
	vector <int> v_ithRow; 
 
  ifstream myfile(FILE_NAME);
  if(!myfile) //Always test the file open.
	{
	   cout<<"Error opening output file"<<endl;
	}
	int i=0;
	int runIndex = -999;
	while (!myfile.eof())//why does end of file repeat last line?
	{
    if (i>end) break;
		if (i<start) continue;
		if (v_ithRow.size() > 0) v_ithRow.clear();
	  int a;
		int b;
		int c;
		myfile>>a>>b>>c;
	  //cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<endl;
		v_ithRow.push_back(a);
		v_ithRow.push_back(b);
		v_ithRow.push_back(c);
		runIndex = a-16140000;
		if (runIndex == 33) vRun33.push_back(v_ithRow);
		if (runIndex == 34) vRun34.push_back(v_ithRow);
		if (runIndex == 35) vRun35.push_back(v_ithRow);
		if (runIndex == 36) vRun36.push_back(v_ithRow);
		if (runIndex == 37) vRun37.push_back(v_ithRow);
		if (runIndex == 38) vRun38.push_back(v_ithRow);
		i++;
	}

	vCentDB.push_back(vRun33);
	vCentDB.push_back(vRun34);
	vCentDB.push_back(vRun35);
	vCentDB.push_back(vRun36);
	vCentDB.push_back(vRun37);
	vCentDB.push_back(vRun38);

	return vCentDB;
}
