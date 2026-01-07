#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* オフセットを指定して、標準出力にオフセットを加えた正のランダム数の整数値を出力します。何か問題が発生した場合は、何も出力しません。
@param offset: ランダム数に加えるオフセット */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // オフセットが負の場合は何もしない
    }

    // 乱数生成の初期化
    srand(time(NULL));
    
    // 正のランダム数を生成
    int rand_num = rand() % (RAND_MAX - offset) + offset + 1; // 1からRAND_MAXまでの範囲で生成
    printf("%d\n", rand_num);
}