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
#include <cstdlib>
#include "sam.h"

class Bam {
    private:
        std::string bam_f;
        std::string region;
	std::string op_f;
        char temp_fastq[30];
        int chr; 
        int start;
        int end;
        samfile_t *sam_in;  
        bam_plbuf_t *buf;
        bam1_t* bt;
    public:        
	    explicit Bam(std::string bam_f, std::string region, std::string op_f);
	    virtual ~Bam();
        bool get_region_reads(); 
        char* get_fastq_name();
};
