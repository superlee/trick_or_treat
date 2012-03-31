#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <omp.h>
#define HOMES_MAX 10000
#define PIECES_MAX 1000

//#define DEBUG

struct path
{
  int start;
  int stop;
  int candy;
};

struct path search_path(unsigned left, unsigned right, const unsigned *pieces, unsigned length, unsigned upper_bound)
{
  struct path result;
  int tail, head;
  int temp_sum;

  /// initial
  result.start = -999;
  result.stop = -999;
  result.candy = 0;

  temp_sum = 0;

  head = left;

  for(tail = left; tail < right; ++tail)
  {
    /// sync tail and head when the pieces after head is greater than upper bound
    if(tail > head)
      head = tail;

    /// the candy should decrease when tail move on
    if(temp_sum != 0)
      temp_sum -= pieces[tail - 1];

    /// head move on until arrive the end of sequence or exceed upper bound
    while(head < length
          && temp_sum + pieces[head] <= upper_bound)
    {
      temp_sum += pieces[head];
      head++;
    }

    /// compare and then get the best result
    if(temp_sum > result.candy)
    {
      result.start = tail;
      result.stop = head - 1;///head is the next step
      result.candy = temp_sum;

    }

    /// current result is the best when head arrive the end of sequence or already get upper bound
    if(head == length
        || result.candy == upper_bound)
    {
      return result;
    }
  }

  return result;
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("\n"
           "Trick or Treat problem - (C)2012 Li Chaozheng<lczxster@gmail.com>\n"
           "\n"
           "trickOrTreat <n> <i> \n"
           " n : the number of threads\n"
           " i : input filename\n");
    return -1;
  }

  struct path *result;

  unsigned home_length;

  unsigned upper_bound;

  unsigned pieces[PIECES_MAX];

  int nid;

  int i;

	int rank,size;

  /// step1 read parameter
  result = (struct path *)malloc(nid * sizeof(struct path));

  FILE *inputfp = fopen(argv[2], "r");

  if(NULL == inputfp)
  {
    fprintf(stderr, "Input file %s can't be opened!\n", argv[1]);
    return -1;
  }

  fscanf(inputfp, "%u\n", &home_length);

  if(home_length > HOMES_MAX)
  {
    fprintf(stderr, "The number of home %u is greater than %u!\n", home_length, HOMES_MAX);
    return -1;
  }

#ifdef DEBUG
  printf("home_length = %d\n", home_length);
#endif

  fscanf(inputfp, "%u\n", &upper_bound);
#ifdef DEBUG
  printf("upper_bound = %d\n", upper_bound);
#endif

  for(i = 0; i < home_length; ++i)
  {
    if(fscanf(inputfp, "%u\n", pieces + i) == EOF)
    {
      fprintf(stderr, "The number of pieces' line is less than the number of home\n ");
      return -1;
    }

#ifdef DEBUG
    printf("pieces[%u] = %d\n", i + 1, pieces[i]);
#endif
  }

  fclose(inputfp);

  nid = atoi(argv[1]);

  if(nid <= 0 || nid > home_length)
  {
    fprintf(stderr, "The number of threads must be greater than 0 and smaller than the length of homes!\n");
    return -1;
  }


  /// step 2 find the sequences of home
  #pragma omp parallel num_threads(nid) private(rank)

  {
    rank = omp_get_thread_num();
    size = omp_get_num_threads();

		int left=rank * (home_length/size);
		int right=(rank+1)*(home_length/size)>home_length?home_length:(rank+1)*(home_length/size);
    result[rank] = search_path(left, right, pieces, home_length, upper_bound);
  }

  int start_home;
  int stop_home;
  int total_candy;
	int tmp_index;
	
	for (i = 0, tmp_index=0; i < nid; ++i)
	{
    if(result[i].candy>result[tmp_index].candy)
			tmp_index=i;
	}

	start_home=result[tmp_index].start+1;
	stop_home=result[tmp_index].stop+1;
	total_candy=result[tmp_index].candy;
  /// step 3 write the result to the output file

  if(start_home < 0)
  {
    fprintf(stdout, "Don't go here!\n");
  }
  else
  {
    fprintf(stdout, "Start at home %d and go to home %d getting %d pieces of candy \n", start_home, stop_home, total_candy);
  }

  free(result);
  return 0;
}
