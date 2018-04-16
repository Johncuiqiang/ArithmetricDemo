//
// Created by qing on 2018/4/16.
//

#include "BinarySearch.h"

BinarySearch::BinarySearch() {

}

BinarySearch::~BinarySearch() {

}

int BinarySearch::binarySearch(int *arr, int length, int target) {
    int l = 0, r = length - 1;//在l到r的范围中，寻找和target值
    while (l < r) {
        int mid = (l + r) / 2;
        if (target == arr[mid]) {
            return mid;
        } else if (target > arr[mid]) {
            l = mid + 1;//大于，寻找右边的，所以中间位置+1
        } else {
            r = mid - 1;//小于，寻找左边的，所以中间位置-1
        }
    }
    return  -1;
}

