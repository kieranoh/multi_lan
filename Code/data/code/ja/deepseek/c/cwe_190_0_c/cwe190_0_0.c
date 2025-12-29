#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* オフセットを指定して、標準出力にオフセットを加えた正のランダム数の整数値を出力します。何か問題が発生した場合は、何も出力しません。

@param offset: ランダム数に加えるオフセット */
void print_rand_num_plus_offset(int offset) {
    /* 乱数生成器を初期化 */
    srand((unsigned int)time(NULL));
    
    /* 正のランダム数を生成 (0からRAND_MAXの間) */
    int random_num = rand();
    
    /* オフセットを加える */
    int result = random_num + offset;
    
    /* 結果が正の整数であることを確認 */
    if (result > 0) {
        printf("%d\n", result);
    }
    /* 結果が正でない場合は何も出力しない */
}