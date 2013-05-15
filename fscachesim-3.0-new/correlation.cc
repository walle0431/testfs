
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>


#include "Cache.hh"



#define NUM 8
#define BEGIN 1
#define BLOCKSIZE 4096



int main()
{
	FILE *file;
	char filename[50];
	double timeIssued;
	int rc, i, j;
	uint64_t objID, off, len;
	uint64_t overlap[NUM], blocks[NUM];
	double overlap_perc[NUM];
	Cache cache[NUM];
	Block::block_t b;
	bool isOverlap;

	uint64_t op, numRecords, pid;
	double processsstime;

	for (i = BEGIN; i < NUM; i++)
	{
		overlap[i] = 0;
	}
	
	for (i = BEGIN; i < NUM; i++)
	{
		sprintf(filename,"/home/ol/fscachesim-3.0/traces/httpd.%d.txt",i);  
//		sprintf(filename,"/home/ol/fscachesim-3.0/traces/db2.%d.txt",i);
		if ((file = fopen(filename, "r")) == NULL) {
		    perror(filename);
		    abort();
		}


		while (fscanf(file,
			"%lf %llu %llu %llu",
			&timeIssued,
			&objID,
			&off,
			&len) != EOF)

		{



			b.objID = objID;
			b.blockID = off/BLOCKSIZE;
			len = len/BLOCKSIZE + 1;
			while(len > 0)
			{
				if (!cache[i].isCached(b))
					cache[i].blockPutAtTail(b);
				len --;
				b.blockID++;
			}

		}

		fclose(file);
		blocks[i] = cache[i].numGet();
	}

	// compare

	for (i = BEGIN; i < NUM; i++)
	{
		
		
		while(!cache[i].isEmpty())
		{
			isOverlap = false;
			cache[i].blockGetAtHead(b);
			for (j = i+1;  j < NUM; j++)
			{
				if (cache[j].isCached(b))
				{
					cache[j].blockGet(b);
					overlap[j]++;
					isOverlap = true;
				}

			}
			if (isOverlap)
				overlap[i]++;
		}
		if (blocks[i])
			overlap_perc[i] = (double)overlap[i]/(double)blocks[i];
		else
			overlap_perc[i] = 0;
		printf ("file %d overlap %llu blocks of %llu blocks, percent %lf\n", i, 
			overlap[i], blocks[i], overlap_perc[i]);
	} 

	return 0;
}
