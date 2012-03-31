#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int i;
  int home_length;
  int upper_bound;
  FILE *fp = NULL;

  if(argc < 3)
  {
    printf("\n"
           " Generate data for Trick or Treat test - (C) 2012 Li Chaozheng<lczxster@gmail.com>\n"
           " generateData <n> <u> <f>\n"
           " n : The number of home\n"
           " u : The upper bound\n"
           " f : output filename\n\n");
    return -1;
  }

  fp = fopen(argv[3], "w");

  if(NULL == fp)
  {
    fprintf(stderr, "Output file %s can't be created!\n", argv[3]);
    return -1;
  }

  home_length = atoi(argv[1]);
  upper_bound = atoi(argv[2]);

	fprintf(fp,"%d\n",home_length);
	fprintf(fp,"%d\n",upper_bound);

  for(i = 0; i < home_length; ++i)
  {
    fprintf(fp, "%d\n", (int)((10 * upper_bound * (float)rand() / (RAND_MAX - 1)))) % (10 * upper_bound);
  }

  fclose(fp);


  return 0;
}
