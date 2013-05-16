/*	
	Copyright (C) 2013 Avinash Ramu <aramu@genetics.wustl.edu>

	This file is part of kmerCall.

	kmerCall is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	kmerCall is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with kmerCall.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ProcessCounts.h"
#include<cstdlib>
#include<sstream>

using namespace std;

ProcessCounts::ProcessCounts(string mom_f, string dad_f, string child_f, ofstream& fout)
{
  mom_count_file = mom_f;
  dad_count_file = dad_f;
  child_count_file = child_f;
  mergeCounts(fout);
  //processKmerTable();
}
 
bool ProcessCounts::mergeCounts(ofstream& fout)
{
  map<string, int> mom_kmer_count;
  map<string, int> dad_kmer_count;
  map<string, int> child_kmer_count;
  map<string, int> allthree_kmers;
  
  createKmerTableFromFile(mom_count_file, mom_kmer_count, allthree_kmers);
  createKmerTableFromFile(dad_count_file, dad_kmer_count, allthree_kmers);
  createKmerTableFromFile(child_count_file, child_kmer_count, allthree_kmers);

  map<string, int>::iterator it;
  for(it=allthree_kmers.begin(); it!=allthree_kmers.end(); it++) {
    if(it->second == 3) {
      string kmer = it->first;
      c_k_count = child_kmer_count[kmer];
      m_k_count = mom_kmer_count[kmer];
      d_k_count = dad_kmer_count[kmer];
      fout<<kmer<<"\t"<<c_k_count<<"\t"<<m_k_count<<"\t"<<d_k_count;
      fout<<"\t"<<c_k_count - m_k_count - d_k_count<<child"\n";
      cout<<kmer<<endl;
    }
  }

  return true;
}

bool ProcessCounts::createKmerTableFromFile(string kmer_counts_file, map<string, int>& map_kmer_count
					    , map<string, int>& allthree_kmers)
{
  
  ifstream fin(kmer_counts_file.c_str());
  if(!fin) {
    cerr<<"Unable to open "<<kmer_counts_file<<" Exiting."<<endl;
    exit(1);
  }
  cout<<" kmer count file "<<kmer_counts_file<<endl;
  char line[1024];
  string kmer;
  int count;
  while(fin.good()) {
    fin.getline(line, 1024);
    //    cout<<line<<endl;
    istringstream iss(line);
    iss>>kmer;
    iss>>count;
    //    cout<<kmer<<"\t"<<count<<endl;
    map_kmer_count[kmer] = count;
    allthree_kmers[kmer] += 1;
  }
  return true;
}


bool ProcessCounts::processKmerTable()
{
  //set<string>::iterator it;
  //for(it=kmers.begin(); it != kmers.end(); it++)
  //cout<<*it<<" it"<<endl;
}
