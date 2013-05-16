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

#ifndef PROCESS_COUNTS_H
#define PROCESS_COUNTS_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<map>
#include<set>
#include<fstream>
class ProcessCounts
{
 private:
  std::string mom_count_file;
  std::string dad_count_file;
  std::string child_count_file;
  std::string merged_count_file;
 public:
  ProcessCounts(std::string mom_f, std::string dad_f, std::string child_f, std::ofstream& fout);
  bool mergeCounts(std::ofstream& fout);
  bool createKmerTableFromFile(std::string kmer_counts_file, std::map<std::string, int>& map_kmer_count
			       , std::map<std::string, int>& allthree_kmers);
  bool processKmerTable();
};


#endif
