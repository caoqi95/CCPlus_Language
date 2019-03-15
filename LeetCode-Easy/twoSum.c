#include <stdio.h>
#include <stdlib.h>

int* twoSum(int* nums, int numsSize, int target);

int* twoSum(int* nums, int numsSize, int target) 
{
    int *answer = (int *)malloc(2 * sizeof(int));

    int sum = 0;

    for (int i = 0; i < numsSize - 1; i++){
        for(int j = i + 1; j < numsSize; j++){
            sum = nums[i] + nums[j];
            if (sum == target)
            {
                answer[0] = i;
                answer[1] = j;

                return answer;
            }
        }
    }
    return 0;
}

int main()
{
    int nums[4] = {2, 3, 7, 6};
    int numsSize = (int)sizeof(nums)/sizeof(int);
    int target = 9;
    

    int *res = twoSum(nums, numsSize, target);
    printf("result: [%d, %d]\n", res[0], res[1]);
    free(res);
    return 0;
}