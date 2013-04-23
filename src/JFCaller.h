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

#ifndef JF_CALLER_H
#define JF_CALLER_H

#include <iostream>
#include <cstring>
#include <string>

int jf_main2(int argc, char *argv[]);


class JFCaller
{
 private:
  std::string fasta_file;
  std::string mer_file;
  std::string dump_op_file;
 public:
  JFCaller(const char* fasta);
  bool callJFCount();
  bool callJFDump();

};
#endif
