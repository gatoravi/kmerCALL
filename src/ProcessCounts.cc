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
#include<algorithm>
#include<cstdlib>
#include<sstream>

#define TOP_KMER_COUNT 10
#define TOTAL_RD_CUTOFF 10
#define INVALID -999
using namespace std;

ProcessCounts::ProcessCounts(string mom_f, string dad_f, string child_f, ofstream& fout)
{
  mom_count_file = mom_f;
  dad_count_file = dad_f;
  child_count_file = child_f;
  mergeCounts(fout);
}
 
bool ProcessCounts::process_kstats(vector<float>& kstat_list1, ofstream& fout1)
{
  std::sort (kstat_list1.begin(), kstat_list1.end());
  float min_kstat_sum = 0;
  float max_kstat_sum = 0;
  float avg_min_kstat_sum = 0;
  float avg_max_kstat_sum = 0;
  float kstat_difference = -1;
  int kstat_size = kstat_list1.size();  

  if(kstat_size < 10) {
    window_stat = INVALID;
    return false;
  }

  for(int i = 0; i<TOP_KMER_COUNT; i++) {
    min_kstat_sum += kstat_list1[i];
  }

  for(int i = kstat_size - TOP_KMER_COUNT; i<kstat_size; i++) {
    max_kstat_sum += kstat_list1[i];
  }
  avg_min_kstat_sum = min_kstat_sum/TOP_KMER_COUNT;
  avg_max_kstat_sum = max_kstat_sum/TOP_KMER_COUNT;
  window_stat = avg_max_kstat_sum - avg_min_kstat_sum;

  fout1<<endl<<"#size "<<kstat_list1.size()<<"\tavg min "<<avg_min_kstat_sum<<"\tavg max: "<<avg_max_kstat_sum;
  fout1<<"avg diff "<<kstat_difference;

  return true;
}

/*Process counts of kmers common to mom, dad and child*/
bool ProcessCounts::mergeCounts(ofstream& fout)
{
  map<string, int> mom_kmer_count;
  map<string, int> dad_kmer_count;
  map<string, int> child_kmer_count;
  map<string, int> allthree_kmers;
  vector<float> kstat_list;
  createKmerTableFromFile(mom_count_file, mom_kmer_count, allthree_kmers);
  createKmerTableFromFile(dad_count_file, dad_kmer_count, allthree_kmers);
  createKmerTableFromFile(child_count_file, child_kmer_count, allthree_kmers);

  map<string, int>::iterator it;
  for(it=allthree_kmers.begin(); it!=allthree_kmers.end(); it++) {
    if(it->second == 3) {
      string kmer = it->first;
      int c_k_count = child_kmer_count[kmer];
      int m_k_count = mom_kmer_count[kmer];
      int d_k_count = dad_kmer_count[kmer];
      if(m_k_count + d_k_count + c_k_count > TOTAL_RD_CUTOFF)
	{ 
	  int total_k_count = m_k_count + d_k_count + c_k_count;
	  float n_m_k_count = (float)m_k_count/(float)total_k_count;
	  float n_d_k_count = (float)d_k_count/(float)total_k_count;
	  float n_c_k_count = (float)c_k_count/(float)total_k_count;
	  float kstat = n_c_k_count - n_m_k_count - n_d_k_count;
	  kstat_list.push_back(kstat);
	  fout<<kmer<<"\t"<<c_k_count<<"\t"<<m_k_count<<"\t"<<d_k_count;
	  fout<<"\t"<<n_c_k_count<<"\t"<<n_m_k_count<<"\t"<<n_d_k_count;
	  fout<<"\t"<<kstat;
	  fout<<endl;
        }
    }
  }
  process_kstats(kstat_list, fout);
  return true;
}



/*Get kmers from each sample and add to common kmer table*/
bool ProcessCounts::createKmerTableFromFile(string kmer_counts_file, map<string, int>& map_kmer_count
					    , map<string, int>& allthree_kmers)
{
  
  ifstream fin(kmer_counts_file.c_str());
  if(!fin) {
    cerr<<"Unable to open "<<kmer_counts_file<<" Exiting."<<endl;
    exit(1);
  }
  //cout<<"kmer count file "<<kmer_counts_file<<endl;
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

float ProcessCounts::getWindowStat()
{
  return window_stat;
}
