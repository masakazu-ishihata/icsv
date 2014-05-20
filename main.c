#include "main.h"

int main(void)
{
  int i, j;
  icsv *csv;

  /* load csv file with delimiter " " */
  csv = icsv_new_delimiter("test.csv", " ");

  /* show by method */
  icsv_show(csv, stdout);

  /* show by self */
  for(i=0; i<icsv_num_line(csv); i++){
    for(j=0; j<icsv_num_item(csv, i); j++){
      printf("%d-th item in %d-th line is \"%s\".\n", j, i, icsv_get(csv, i, j));
    }
  }

  icsv_free(csv);

  return 0;
}
