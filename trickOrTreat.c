#include <stdio.h>
#define HOMES_MAX 10000
#define PIECES_MAX 1000

#define DEBUG

int main(int argc, char *argv[])
{
  if(argc < 1)
  {
    printf("\n"
           "Trick or Treat problem - (C) 2012 Li Chaozheng<lczxster@gmail.com>\n"
           "\n"
           "trickOrTreat <i> <o>\n"
           " i : input filename\n");
    return -1;
  }

  unsigned int home;
  unsigned int upper_bound;
  unsigned int pieces[PIECES_MAX];
  unsigned int i, j;

  unsigned int recieve_candy = 0;
  unsigned int max_candy = 0;
  unsigned int start_home = 0;
  unsigned int stop_home = 0;
  unsigned int find_result = 0;


  /// step1 read parameter from input file
  /// open input file
  FILE *inputfp = fopen(argv[1], "r");

  if(NULL == inputfp)
  {
    fprintf(stderr, "Input file %s can't be opened!\n", argv[1]);
    return -1;
  }

  /// read the number of home
  fscanf(inputfp, "%u\n", &home);

  if(home > HOMES_MAX)
  {
    fprintf(stderr, "The number of home %u is greater than %u!\n", home, HOMES_MAX);
    return -1;
  }

#ifdef DEBUG
  printf("home = %d\n", home);
#endif

  /// read the number of upper bound
  fscanf(inputfp, "%u\n", &upper_bound);
#ifdef DEBUG
  printf("upper_bound = %d\n", upper_bound);
#endif

  for(i = 0; i < home; ++i)
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

/// step 2 find the sequences of home

  for(i = 0; i < home && find_result == 0; ++i)
  {
    recieve_candy = 0;
    start_home = i;

    for(j = i; j < home; ++j)
    {
      if(pieces[j] == upper_bound)
      {
        start_home = j;
        stop_home = j;
        max_candy = upper_bound;
        find_result = 1;
        break;
      }
      else if(pieces[j] > upper_bound)
      {
        break;
      }
      else if(pieces[j] < upper_bound)
      {
        recieve_candy += pieces[j];

        if(recieve_candy > upper_bound)
        {
          break;
        }
        else if(recieve_candy > max_candy)
        {
          stop_home = j;
          max_candy = recieve_candy;

          if(max_candy == upper_bound)
          {
            find_result = 1;
            break;
          }
        }

      }
    }
  }

  /// home start from 1
  start_home++;
  stop_home++;
  /// step 3 write the result to the output file

  if(max_candy == 0)
  {
    fprintf(stdout, "Don't go here!\n");
    return 0;
  }

  printf("Start at home %u and go to home %u getting %u pieces of candy \n", start_home, stop_home, max_candy);

  return 0;
}
