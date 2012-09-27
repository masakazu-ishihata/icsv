# iCSV

csv ファイルを読んでくれる生かしたやつ。（しょぼい）   
[ilist][ilist] を使ってます。   
iHoge の i は ishihata の i です。（重要）   

[ilist]: https://github.com/masakauz-ishihata/ilist "ilist"

## methods
### new/free

    icsv *icsv_new(const char *_name);

CSV ファイル _name を読み込み icsv インスタンスを返す。   

    void icsv_free(icsv *_csv);

icsv _csv を free する。


## show

    void icsv_show(icsv *_csv, FILE *_fp);

icsv _csv の中身を _fp に出力する。   
出力形式は以下の CSV 形式。

    i, j,  i 行目の j 番目の要素


## 使い方