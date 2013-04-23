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
#include "JFCaller.h"
#include <cstring>

JFCaller::JFCaller(const char* fasta)
{ 
  std::string temp(fasta);
  fasta_file = temp;
}

bool JFCaller::callJFCount()
{
  std::cout<<"Calling JellyFish Count"<<std::endl;
  char arg1[] = "jellyfish\0";
  char arg2[] = "count\0";
  char arg3[] = "-m\0";
  char arg4[] = "10\0";// kmer size
  char arg5[] = "-s\0";
  char arg6[] = "1000000000\0";// hashtable size, reduce number of op files
  char arg7[] = "-o\0";
  char arg8[220] = "jf_call_op_\0";
  
  strcat(arg8, fasta_file.c_str());
  std::string temp(arg8);
  mer_file = temp;

  char arg9[200];
  strcpy(arg9, fasta_file.c_str()); 
  
  char* argv1[] = {arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9};
  int argc1 = sizeof(argv1)/sizeof(argv1[0]);
  std::cout<<std::endl<<"ARGC1 "<<argc1<<"\t"<<arg9;
  jf_main2(argc1, argv1);
  std::cout<<std::endl<<"AFTER JF MAIN";
  return true;
}

bool JFCaller::callJFDump()
{
  std::cout<<std::endl<<"Calling JellyFish Dump"<<std::endl;
  char arg1[] = "jellyfish\0";
  char arg2[] = "dump\0";
  char arg3[] = "-c\0";
  char arg4[] = "-o\0";

  char arg5[200];
  strcpy(arg5, fasta_file.c_str()); 
  strcat(arg5, "_jf_dump_op.txt\0");
  dump_op_file.assign(arg5, sizeof(char) * strlen(arg5));
  
  char arg6[220];
  strcpy(arg6, mer_file.c_str());

  char* argv1[] = {arg1, arg2, arg3, arg4, arg5, arg6};
  int argc1 = sizeof(argv1)/sizeof(argv1[0]);
  jf_main2(argc1, argv1);
  //std::cout<<std::endl<<"done dump";
}
