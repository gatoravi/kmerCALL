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

#include <iostream>
#include <string>
#include <cstdlib>
#include "Arguments.h"
#include "Bam.h"
#include "JFCaller.h"
#include "ProcessCounts.h"

#define INVALID -999 // Check for invalid kmerstat

using namespace std;



float processWindow(Arguments& A, string chr, long start, long end) 
{
  char window_op_file[100];
  sprintf(window_op_file, "window_%ld.txt", start);
  //cout<<"\nWOF"<<window_op_file<<"\t"<<chr<<"\t"<<start<<"\t"<<end;
  
  char child_fastq[] = "child_fastq.txt";
  char mom_fastq[] = "mom_fastq.txt";
  char dad_fastq[] = "dad_fastq.txt";

  Bam B_child(A.getChildBAMName(), chr, start, end, child_fastq);
  Bam B_mom(A.getMomBAMName(), chr, start, end, mom_fastq);
  Bam B_dad(A.getDadBAMName(), chr, start, end, dad_fastq);

  if(B_child.is_fastq_empty() || B_mom.is_fastq_empty() || B_dad.is_fastq_empty())
    return INVALID;
  //cout<<"3"<<endl;

  JFCaller JF_child(B_child.get_fastq_name());
  JFCaller JF_mom(B_mom.get_fastq_name());
  JFCaller JF_dad(B_dad.get_fastq_name());

  JF_child.callJFCount();
  if(JF_child.is_mer_empty())
    return INVALID;
  JF_child.callJFDump();

  JF_mom.callJFCount();
  if(JF_mom.is_mer_empty())
    return INVALID;
  JF_mom.callJFDump();

  JF_dad.callJFCount();
  if(JF_dad.is_mer_empty())
    return INVALID;
  JF_dad.callJFDump();

  //cout<<"done DUMP 4"<<endl;

  ofstream fout(window_op_file);
  ProcessCounts P1(JF_mom.get_dump_op_file(), JF_dad.get_dump_op_file(), JF_child.get_dump_op_file(), fout);
  float window_stat = P1.getWindowStat();
  //cout<<"done process"<<endl;

  fout.close();
  return window_stat;
}

int main(int argc, char*argv[])
{
  Arguments A(argc, argv);
  //cout<<endl<<" chr "<<A.getChr()<<" start "<<A.getStart()<<" end "<<A.getEnd()<<" window "<<A.getWindowSize();
  ofstream fout_window_stat(A.getOPName().c_str());
  long end = A.getEnd();
  string chr = A.getChr();
  for(long start_window = A.getStart(); start_window < end; start_window += A.getWindowSize()/2) {
    //cout<<"start_window "<<start_window;
    float window_stat = processWindow(A, A.getChr(), start_window, start_window + A.getWindowSize()/2);
    if(window_stat != INVALID) {
      fout_window_stat<<chr<<"\t"<<start_window<<"\t"<<window_stat<<endl;
      cout<<chr<<"\t"<<start_window<<"\t"<<window_stat<<endl;
    }
    else
      cerr<<"\nINVALID";
  }
  fout_window_stat.close();
  exit(EXIT_SUCCESS);
}
