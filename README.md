# iCSV

csv ファイルを読んでくれる生かしたやつ。（しょぼい）   
[ilist][ilist], [istring][istring] を使ってます。   
iHoge の i は ishihata の i です。（重要）   

[ilist]: https://github.com/masakazu-ishihata/ilist "ilist"
[istring]: https://github.com/masakazu-ishihata/istring "istring"

## methods
### new/free

    icsv *icsv_new(const char *_name);

CSV ファイル _name を読み込み icsv インスタンスを返す。   

    void icsv_free(icsv *_csv);

icsv _csv を free する。


### show

    void icsv_show(icsv *_csv, FILE *_fp);

icsv _csv の中身を _fp に出力する。   
出力形式は以下の CSV 形式。

    i, j,  i 行目の j 番目の要素

### getters

    size_t icsv_num_line(icsv *_csv);

icsv _csv の行数を返す。

    size_t icsv_num_item(icsv *_csv, int _i);

icsv _csv の _i 行目のアイテム数を返す。

    char *icsv_get(icsv *_csv, int _i, int _j);

icsv _csv の _i 行目の _j 番目のアイテムを返す。   



## 使い方

以下みたいに使う予感がします。

    icsv *csv = icsv_new("hoge.csv");

    for(i=0; i<icsv_num_line(csv); i++){
      for(j=0; j<icsv_num_item(csv, i); j++){
        printf("%d, %d, \"%s\"\n", i, j, icsv_get(csv, i, j));
      }
    }

    icsv_free(csv);


