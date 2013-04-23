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

#include "Arguments.h"
#include <iostream>

Arguments::Arguments(int argc, char* argv[]) 
{
    parseArguments(argc, argv);
}

Arguments::~Arguments() {}

bool Arguments::parseArguments(int argc, char* argv[])
{
    std::string empty = "EMPTY";
    op_f = empty;
    bam_f = empty;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
                                                {"bam", required_argument, 0, 0}, 
                                                {"output", required_argument, 0, 1},
                                                {"region", required_argument, 0, 2}
                                              };
        int c = getopt_long(argc, argv, "", long_options, &option_index);
        if(c == -1)
            break;
        switch(c) 
        {      
            case 0:
	            bam_f = optarg;
                break;
            case 1:
                op_f = optarg;
                break;
            case 2:
                region = optarg;
                break;
    	    default:
    	        break;
        }
    }
    if(op_f == empty) {
      std::string suffix = "_kmerCallOP.txt";
      op_f = bam_f + suffix;
    }
    return true;
}

std::string Arguments::getBAMName()
{
  return bam_f;
}

std::string Arguments::getOPName()
{
  return op_f;
}

std::string Arguments::getRegion()
{
  return region;
}
