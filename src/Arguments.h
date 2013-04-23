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

#include <getopt.h>
#include <string>

class Arguments {
    private:
        std::string child_bam_f;
        std::string mom_bam_f;
        std::string dad_bam_f;
        std::string op_f;
        std::string region;
    public:        
        explicit Arguments(int argc, char* argv[]);
        virtual ~Arguments();
        bool parseArguments(int argc, char* argv[]);
        std::string getChildBAMName();
        std::string getMomBAMName();
        std::string getDadBAMName();
        std::string getOPName();
        std::string getRegion();
};
