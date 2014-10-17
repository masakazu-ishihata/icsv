#include "icsv.h"

/*----------------------------------------------------------------------------*/
/* new / free */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* new */
/*------------------------------------*/
icsv *icsv_new(const char *_name)
{
  return icsv_new_delimiter(_name, ",");
}
/*------------------------------------*/
/* new with delimiter(s) */
/*------------------------------------*/
icsv *icsv_new_delimiter(const char *_name, const char *_del)
{
  size_t i, j;

  /*------------------------------------*/
  /* init */
  /*------------------------------------*/
  icsv *csv = (icsv *)malloc(sizeof(icsv));
  if(csv == NULL){
    perror("icsv_new");
    exit(EXIT_FAILURE);
  }

  /*------------------------------------*/
  /* load file */
  /*------------------------------------*/
  ilist *ls = ilist_import(_name); /* lines */
  ilist *ll = ilist_new();         /* line list */
  ilist *il = NULL;                /* item list */
  char *line, *p;

  /* list of lines */
  while((line = ilist_shift(ls)) != NULL){
    /* list of items */
    il = ilist_new();
    p = strtok(line, _del);
    while(p != NULL){
      /* skip head & tail spaces : ^' '* & ' '*$ */
      for(; *p == ' '; p++);
      for(i=strlen(p)-1; i>=0 && *(p+i) == ' '; *(p+i) = '\0', i--);

      /* push */
      ilist_push(il, strcln(p));
      p = strtok(NULL, _del);
    }
    /* add a line to csv's stack */
    ilist_push(ll, il);
    free(line);
  }
  ilist_free(ls);


  /*------------------------------------*/
  /* init item table */
  /*------------------------------------*/
  csv->nl = ilist_size(ll);
  csv->ni = (size_t *)malloc(csv->nl * sizeof(size_t));
  csv->item = (char ***)malloc(csv->nl * sizeof(char **));
  for(i=0; i<csv->nl; i++){
    /* init ni[i] & item[i] */
    il = (ilist *)ilist_shift(ll);
    csv->ni[i] = ilist_size(il);
    csv->item[i] = (char **)malloc(csv->ni[i] * sizeof(char *));

    /* set csv->item[i][j] */
    for(j=0; j<csv->ni[i]; j++){
      csv->item[i][j] = (char *)ilist_shift(il);
    }
    ilist_free(il);
  }
  ilist_free(ll);

  return csv;
}
/*------------------------------------*/
/* free */
/*------------------------------------*/
void icsv_free(icsv *_csv)
{
  size_t i, j;

  for(i=0; i<_csv->nl; i++){
    for(j=0; j<_csv->ni[i]; j++){
      free(_csv->item[i][j]);
      _csv->item[i][j] = NULL;
    }
    free(_csv->item[i]);
    _csv->item[i] = NULL;
  }
  free(_csv->ni);
  free(_csv->item);
  _csv->ni = NULL;
  _csv->item = NULL;

  /* main */
  free(_csv);
}
/*------------------------------------*/
/* show */
/*------------------------------------*/
void icsv_show(icsv *_csv, FILE *_fp)
{
  size_t i, j;

  fprintf(_fp, "%zd lines\n", _csv->nl);
  for(i=0; i<_csv->nl; i++){
    for(j=0; j<_csv->ni[i]; j++){
      fprintf(_fp, "%zd, %zd, \"%s\"\n", i, j, _csv->item[i][j]);
    }
  }
}

/*----------------------------------------------------------------------------*/
/* getters */
/*----------------------------------------------------------------------------*/
/*------------------------------------*/
/* # lines */
/*------------------------------------*/
size_t icsv_num_line(icsv *_csv)
{
  return _csv->nl;
}
/*------------------------------------*/
/* # items in _i-th line */
/*------------------------------------*/
size_t icsv_num_item(icsv *_csv, size_t _i)
{
  return _csv->ni[_i];
}
/*------------------------------------*/
/* _j-th item in _i-th line */
/*------------------------------------*/
char *icsv_get(icsv *_csv, size_t _i, size_t _j)
{
  if(_i < 0 || _i >= _csv->nl){
    return NULL;
  }
  if(_j < 0 || _j >= _csv->ni[_i]){
    return NULL;
  }
  return _csv->item[_i][_j];
}
