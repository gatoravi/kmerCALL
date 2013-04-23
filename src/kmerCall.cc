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

using namespace std;


int main(int argc, char*argv[])
{
  Arguments A(argc, argv);

  Bam B_child(A.getChildBAMName(), A.getRegion(), A.getOPName());
  Bam B_mom(A.getMomBAMName(), A.getRegion(), A.getOPName());
  Bam B_dad(A.getDadBAMName(), A.getRegion(), A.getOPName());

  JFCaller JF_child(B_child.get_fastq_name());
  JFCaller JF_mom(B_mom.get_fastq_name());
  JFCaller JF_dad(B_dad.get_fastq_name());
  JF_child.callJFCount();
  JF_child.callJFDump();
  JF_mom.callJFCount();
  JF_mom.callJFDump();
  JF_dad.callJFCount();
  JF_dad.callJFDump();

  exit(EXIT_SUCCESS);
}
