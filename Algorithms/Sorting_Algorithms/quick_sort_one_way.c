#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))
#define SWAP(arr, i, j) {   \
    int tmp = arr[i];       \
    arr[i] = arr[j];        \
    arr[j] = tmp;           \
}
// 打印数组的函数
void print_arr(int arr[], int left, int right) {
    for (int i = left; i <= right; i++) 
        printf("%d ", arr[i]);
    printf("\n");
}
// 分区核心操作实现,返回一轮快排选择的pivot的下标
int partition(int arr[], int left, int right) {
    // 1.随机选择一个基准值,然后把它先放到数组末尾
    int pivot_idx = left + rand() % (right - left + 1); // 得到一个[left, right]范围内的随机索引
    int pivot = arr[pivot_idx];
    SWAP(arr, pivot_idx, right);
    // 2.设置一个partition_idx索引,指示小于pivot的元素应该插入的位置
    // 同时该索引最终表示分区的界限索引,所以命名为partition_idx
    int partition_idx = left;
    // 3.遍历整个数组,当元素小于pivot时,将它和partition_idx位置元素交换,partition_idx加1
    // 希望遍历结束时，i指向数组末尾的pivot，所以i < right
    for (int i = left; i < right; i++) {
        if (arr[i] < pivot) {
            SWAP(arr, i, partition_idx);
            partition_idx++;
        }
    }
    // 4.遍历结束后,将pivot元素(最后一个元素)交换到partition_idx位置
    SWAP(arr, right, partition_idx);
    printf("此一轮分区操作,选择的pivot是: %d\n分区结束后的数组是: ", pivot);
    print_arr(arr, left, right);
    // 5.返回基准值的位置索引
    return partition_idx;
}
/*
 * 辅助函数
 * 用于对[left, right]区间中的元素进行递归分区操作
 */
void partition_recursion(int arr[], int left, int right) {
    // 递归出口
    if (left >= right) {
        return;
    }
    // 递归体
    int idx = partition(arr, left, right);  // 分区操作,找到pivot元素的下标位置
    partition_recursion(arr, left, idx - 1);
    partition_recursion(arr, idx + 1, right);
}
void quick_sort_one_way(int arr[], int len) {
    // 初始化随机数生成器,time(NULL)获取当前时间戳
    // 用于生成随机索引
    srand(time(NULL));
    // 调用辅助函数进行递归分解
    partition_recursion(arr, 0, len - 1);
}
int main(void) {
    int arr[] = { 8,3,2,6,9,5 };
    int len = ARR_SIZE(arr);
    printf("Before quick sort, the array is: ");
    print_arr(arr, 0, len -1);
    // 测试单向分区快速排序
    quick_sort_one_way(arr, len);
    printf("After quick sort, the array is: ");
    print_arr(arr, 0, len -1);

    return 0;
}
