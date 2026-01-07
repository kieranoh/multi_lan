#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* 给定一个偏移量，将一个正随机数加上该偏移量的整数值打印到标准输出。如果发生任何错误，则不打印任何内容。
@param offset: 要加到随机数上的偏移量 */
void print_rand_num_plus_offset(int offset) {
    if (offset < 0) {
        return; // 如果偏移量为负，则不执行任何操作
    }

    // 初始化随机数生成器
    srand(time(NULL));
    int rand_num = rand(); // 生成随机正数

    // 检查是否生成了有效的随机数
    if (rand_num < 0) {
        return; // 如果随机数无效，则不打印
    }

    // 打印结果
    printf("%d\n", rand_num + offset);
}