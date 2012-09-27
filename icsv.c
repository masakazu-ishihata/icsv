#include "icsv.h"

/* new */
icsv *icsv_new(const char *_name)
{
  return icsv_new_delimiter(_name, ",");
}
/* new with delimiter(s) */
icsv *icsv_new_delimiter(const char *_name, const char *_del)
{
  int i, j;
  icsv *csv;
  FILE *fp;
  char buf[ICSV_BUFFER_SIZE], *p;

  ilist *ll;  /* line list */
  ilist *il;  /* item list */

  /* init */
  if( (csv = (icsv *)malloc(sizeof(icsv))) == NULL){
    perror("icsv_new");
    exit(EXIT_FAILURE);
  }

  /*------------------------------------*/
  /* load file */
  /*------------------------------------*/
  if( (fp = fopen(_name, "r")) == NULL){
    perror("icsv_new");
    exit(EXIT_FAILURE);
  }

  ll = ilist_new(); /* list of lines */
  while( fscanf(fp, "%[^\n]\n", buf) != EOF){
    il = ilist_new(); /* list of items */

    p = strtok(buf, _del);
    while( p != NULL){
      /* skip ^' '* & ' '*$ */
      for(; *p == ' '; p++);
      for(i=strlen(p)-1; i>=0 && *(p+i) == ' '; *(p+i) = '\0', i--);

      /* push */
      ilist_push(il, istrcln(p));
      p = strtok(NULL, _del);
    }

    /* add a line to csv's stack */
    ilist_push(ll, il);
  }

  /* file close */
  fclose(fp);

  /*------------------------------------*/
  /* init item table */
  /*------------------------------------*/
  /* init csv->ni[i] */
  csv->nl = ilist_size(ll);
  if( (csv->ni = (size_t *)malloc(csv->nl * sizeof(size_t))) == NULL){
    perror("icsv_new (ni)");
    exit(EXIT_FAILURE);
  }
  /* init csv->item[i] */
  if( (csv->item = (char ***)malloc(csv->nl * sizeof(char **))) == NULL){
    perror("icsv_new (item)");
    exit(EXIT_FAILURE);
  }
  for(i=0; i<csv->nl; i++){
    il = ilist_shift(ll);

    /* init csv->item[i][j] */
    csv->ni[i] = ilist_size(il);
    if( (csv->item[i] = (char **)malloc(csv->ni[i] * sizeof(char *))) == NULL){
      perror("icsv_new (item)");
      exit(EXIT_FAILURE);
    }

    /* set csv->item[i][j] */
    for(j=0; j<csv->ni[i]; j++){
      csv->item[i][j] = ilist_shift(il);
    }
    ilist_free(il);
  }
  ilist_free(ll);

  return csv;
}

/* free */
void icsv_free(icsv *_csv)
{
  int i, j;

  if(_csv != NULL){
    /* free lines */
    for(i=0; i<_csv->nl; i++){
      /* free items */
      for(j=0; j<_csv->ni[i]; j++){
        free(_csv->item[i][j]);
        _csv->item[i][j] = NULL;
      }
      free(_csv->item[i]);
      _csv->item[i] = NULL;
    }
    free(_csv->ni);
    _csv->ni = NULL;
    free(_csv->item);
    _csv->item = NULL;
    free(_csv);
  }
}

/* show */
void icsv_show(icsv *_csv, FILE *_fp)
{
  int i,j;

  fprintf(_fp, "%zd lines\n", _csv->nl);

  for(i=0; i<_csv->nl; i++){
    for(j=0; j<_csv->ni[i]; j++){
      fprintf(_fp, "%d, %d, \"%s\"\n", i, j, _csv->item[i][j]);
    }
  }
}

/* get */
size_t icsv_num_line(icsv *_csv)
{
  return _csv->nl;
}
size_t icsv_num_item(icsv *_csv, int _i)
{
  return _csv->ni[_i];
}
char *icsv_get(icsv *_csv, int _i, int _j)
{
  if(_i < 0 || _i >= _csv->nl){
    return NULL;
  }
  if(_j < 0 || _j >= _csv->ni[_i]){
    return NULL;
  }
  return _csv->item[_i][_j];
}
