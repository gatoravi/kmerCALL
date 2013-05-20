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

#include "Bam.h"
#include <iostream>
#include <fstream>
using namespace std;
ofstream fout;

Bam::Bam(string bam_f1, string chr1, long start1, long end1, string fastq) 
{ 
  bam_f = bam_f1;
  temp_fastq = fastq;
  chr = atoi(chr1.c_str());
  start = start1;
  end = end1;
  get_region_reads();
}

Bam::~Bam() 
{
}

int fetch_func(const bam1_t *bt, void *data)  
{  
  
  char *name  = (char *) bam1_qname(bt);
  
  int n=0;
  char *qseq = (char *) malloc(bt->core.l_qseq+1);
  char *s   = (char *) bam1_seq(bt);
  for(n=0;n<(bt->core.l_qseq);n++) {
    char v = bam1_seqi(s,n);
    qseq[n] = bam_nt16_rev_table[v];
  }
  qseq[n] = 0;
  char *t = (char *) malloc(bt->core.l_qseq + strlen(name) + 10);
  strcpy(t, ">");
  strcat(t, name);
  strcat(t, "\n");
  strcat(t, qseq);
  data = t;
  fout<<(char*) data<<endl;
  free(t);
  free(qseq);
  return 0; 
} 

int pileup_func(uint32_t tid, uint32_t pos, int n, const bam_pileup1_t *pl, void *data)  
{  
    return 0;  
}  

bool Bam::get_region_reads()
{
    sam_in = samopen(bam_f.c_str(), "rb", 0);  
    if (sam_in == 0) {  
        cerr<<"Fail to open BAM file "<<bam_f;
        return EXIT_FAILURE; 
    } 
    //    cerr<<"openedbam "<<chr<<"\t"<<start<<endl;
    bam_index_t *idx = bam_index_load(bam_f.c_str()); // load BAM index
    if (idx == 0) {
        cerr<<"BAM indexed file is not available for "<<bam_f<<endl;
        return EXIT_FAILURE;
    }
    //cerr<<"openedbam index "<<chr<<"\t"<<start<<endl;
    /*
    bam_parse_region(sam_in->header, region.c_str(), &chr, &start, &end); // parse the region
    if (chr < 0) {
        cerr<<"Invalid region "<<region<<endl;
        return EXIT_FAILURE;
    }
    */
    //cout<<endl<<chr<<"\t"<<start;
    //strcpy(temp_fastq, "kmercall.XXXXXX.fasta");
    //mkstemps(temp_fastq, 6);
    fout.open(temp_fastq.c_str());
    //cout<<"PARSED REGION "<<chr<<"\t"<<start<<"\t"<<end;
    bam_header_t *data = sam_in->header;
    buf = bam_plbuf_init(pileup_func, data); // initialize pileup
    bam_fetch(sam_in->x.bam, idx, chr, start, end, buf, fetch_func);
    bam_header_destroy(data); 
    bam_plbuf_destroy(buf);
    bam_index_destroy(idx); 
    fout.close();   
    samclose(sam_in);
    return true;
}

char* Bam::get_fastq_name()
{
  return (char*) temp_fastq.c_str();
}

bool Bam::is_fastq_empty()
{
  fstream fin(temp_fastq.c_str());
  fin.seekp(0,ios::end);
  size_t size = fin.tellg();
  fin.close();

  if(size == 0) 
    return true;
  else 
    return false;
}




