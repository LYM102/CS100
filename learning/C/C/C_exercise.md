# C语言个人练手试题
> 说明：本习题集来自于个人练习和作业复习
> this page is by YiMing Li
## Exercise One - 主要考察不同的排序算法
请生成100个0~1000（包括0和1000）的随机数，然后通过选择排序和冒泡排序将他们进行排序，并且对排序所用时间分别记时。
并且最后输出随机生成的数组（数组的每一个数字之间请使用制表符来分割），以及两种排完序之后的数组以及对应的排序时间。
```
示例输出：
The array without duplications is completed
Original array:
334	553	733	815	65	240	15	671	893	904	480	301	208	867	225	322	899	901	875	746	497	179	308	246	520	918	574	708	353	469	43	258	203	210	675	443	347	336	129	989	689	46	215	12	297	468	239	395	687	737	995	983	446	913	909	155	618	378	550	228	581	112	376	603	818	782	54	859	180	621	223	477	89	463	872	776	552	798	771	535	245	37	444	752	7	174	654	236	756	766	140	484	455	743	549	625	525	956	705	577	
function_1 is executed 85 times with 0.000026 seconds
Sorted by find_way_1:
7	12	15	37	43	46	54	65	89	112	129	140	155	174	179	180	203	208	210	215	223	225	228	236	239	240	245	246	258	297	301	308	322	334	336	347	353	376	378	395	443	444	446	455	463	468	469	477	480	484	497	520	525	535	549	550	552	553	574	577	581	603	618	621	625	654	671	675	687	689	705	708	733	737	743	746	752	756	766	771	776	782	798	815	818	859	867	872	875	893	899	901	904	909	913	918	956	983	989	995	
function_2 is executed 99 times with 0.000023 seconds
Sorted by find_way_2:
7	12	15	37	43	46	54	65	89	112	129	140	155	174	179	180	203	208	210	215	223	225	228	236	239	240	245	246	258	297	301	308	322	334	336	347	353	376	378	395	443	444	446	455	463	468	469	477	480	484	497	520	525	535	549	550	552	553	574	577	581	603	618	621	625	654	671	675	687	689	705	708	733	737	743	746	752	756	766	771	776	782	798	815	818	859	867	872	875	893	899	901	904	909	913	918	956	983	989	995
```
```c
个人正确答案：
// 比较两种排序方法的效率
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
void find_way_1(int arr[], int len);
void find_way_2(int arr[], int len);
int is_duplicate(int arr[], int num, int i);
void make_arr(int arr[], int len);
void make_arr(int arr[], int len)
{
    srand(time(NULL));
    for (int i = 0; i < len; i++)
    {
        int num = rand() % 1001;
        while (is_duplicate(arr, num, i))
        {
            num = rand() % 1001;
        }
        arr[i] = num;
    }
}
int is_duplicate(int arr[], int num, int i)
{
    int flag = 0;
    for (int j = 0; j < i; j++)
    {
        if (arr[j] == num)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}
int main()
{
    int arr[100] = {0}, arr_copy[100];
    int len = sizeof(arr) / sizeof(int);
    make_arr(arr, len);
    printf("The original array:");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr[i]);
    }
    puts("\n");
    memcpy(arr_copy, arr, len * sizeof(int));
    printf("The array without duplications is completed\n");
    find_way_1(arr, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr[i]);
    }
    puts("\n");
    find_way_2(arr_copy, len);
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr_copy[i]);
    }
    return 0;
}
void find_way_1(int arr[], int len)
{
    int flag = 1, times = 0;
    clock_t time_start = clock();
    for (int i = 0; i < len - 1; i++)
    {
        times++;
        flag = 1;
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                flag = 0;
            }
        }
        if (flag == 1)
            break;
    }
    clock_t time_stop = clock();
    printf("function_1 is excute %d times with %f seconds\n", times, (double)(time_stop - time_start) / CLOCKS_PER_SEC);
}
void find_way_2(int arr[], int len)
{
    clock_t time_start = clock();
    int times = 0;
    for (int i = 0; i < len - 1; i++)
    {
        times++;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[i] > arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
    clock_t time_stop = clock();
    printf("function_2 is excute %d times with %f seconds\n", times, (double)(time_stop - time_start) / CLOCKS_PER_SEC);
}
```
```C
标准答案：
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// 冒泡排序
void find_way_1(int arr[], int len);
// 选择排序
void find_way_2(int arr[], int len);
// 生成不重复的随机数组
void make_arr(int arr[], int len);

int main()
{
    int arr[100] = {0}, arr_copy[100];
    int len = sizeof(arr) / sizeof(int);

    // 生成不重复的随机数组
    make_arr(arr, len);
    printf("The original array:\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr[i]);
    }
    puts("\n");

    // 复制数组用于第二种排序
    memcpy(arr_copy, arr, len * sizeof(int));

    // 冒泡排序
    find_way_1(arr, len);
    printf("Sorted by find_way_1:\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr[i]);
    }
    puts("\n");

    // 选择排序
    find_way_2(arr_copy, len);
    printf("Sorted by find_way_2:\n");
    for (int i = 0; i < len; i++)
    {
        printf("%d\t", arr_copy[i]);
    }
    puts("\n");

    return 0;
}

// 冒泡排序
void find_way_1(int arr[], int len)
{
    int times = 0;
    clock_t time_start = clock();
    for (int i = 0; i < len - 1; i++)
    {
        int last_swap = 0; // 记录最后一次交换的位置
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                last_swap = j + 1; // 更新最后一次交换位置
            }
        }
        if (last_swap == 0) // 如果没有发生交换，提前结束
            break;
        i = len - last_swap; // 更新外层循环的起始位置
        times++;
    }
    clock_t time_stop = clock();
    printf("function_1 is executed %d times with %.6f seconds\n", times, (double)(time_stop - time_start) / CLOCKS_PER_SEC);
}

// 选择排序
void find_way_2(int arr[], int len)
{
    int times = 0;
    clock_t time_start = clock();
    for (int i = 0; i < len - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < len; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
        times++;
    }
    clock_t time_stop = clock();
    printf("function_2 is executed %d times with %.6f seconds\n", times, (double)(time_stop - time_start) / CLOCKS_PER_SEC);
}

// 生成不重复的随机数组
void make_arr(int arr[], int len)
{
    srand(time(NULL));
    int count = 0;
    while (count < len)
    {
        int num = rand() % 1001;
        int is_duplicate = 0;
        for (int i = 0; i < count; i++)
        {
            if (arr[i] == num)
            {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate)
        {
            arr[count++] = num;
        }
    }
}
```
## Exercise Two - 考察循环，条件判断和随机数
请生成一段随机数，表明a,b,c,d的投票结果（一共80票），并公布最高票数的地点，如果景点投票数量相同的话，按照a,b,c,d的顺序进行排列
```c
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
typedef struct place
{
    char name;
    int num;
} P;
int main()
{
    srand(time(NULL));
    P pl_arr[4] = {{'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}};
    for (int i = 0; i < 80; i++)
    {
        pl_arr[(rand() % 4)].num++;
    }
    for (int i = 0; i < 4; i++)
    {
        printf("the people of %c is %d\n", pl_arr[i].name, pl_arr[i].num);
    }
    int flag = pl_arr[0].num, record = 0;
    for (int j = 1; j < 4; j++)
    {
        if (pl_arr[j].num > flag)
        {
            flag = pl_arr[j].num;
            record = j;
        }
    }
    printf("the last desicion is %c", 'A' + record);
}
```
## Exercise Three - 算法余数
### 题目描述

给你三个整数 $a,b,p$，求 $a^b \bmod p$。

### 输入格式

输入只有一行三个整数，分别代表 $a,b,p$。

### 输出格式

输出一行一个字符串 `a^b mod p=s`，其中 $a,b,p$ 分别为题目给定的值， $s$ 为运算结果。

### 输入输出样例 #1

#### 输入 #1

```
2 10 9
```

#### 输出 #1

```
2^10 mod 9=7
```

### 说明/提示

**样例解释**

$2^{10} = 1024$，$1024 \bmod 9 = 7$。

**数据规模与约定**

对于 $100\%$ 的数据，保证 $0\le a,b < 2^{31}$，$a+b>0$，$2 \leq p \lt 2^{31}$。
### 题解
- 背景知识：
    1. 平方求余法（离散数学）
    2. 位运算技巧
```c
int quickPower(int a, int b)//是求a的b次方
{
	int ans = 1, base = a;//ans为答案，base为a^(2^n)
	while(b > 0)//b是一个变化的二进制数，如果还没有用完
    {
		if(b & 1)//&是位运算，b&1表示b在二进制下最后一位是不是1，如果是：
			ans *= base;//把ans乘上对应的a^(2^n)
		
        base *= base;//base自乘，由a^(2^n)变成a^(2^(n+1))
		b >>= 1;//位运算，b右移一位，如101变成10（把最右边的1移掉了），10010变成1001。现在b在二进制下最后一位是刚刚的倒数第二位。结合上面b & 1食用更佳
	}
	return ans;
}
```
## Exercise Four - 神奇的幻方（control flow训练）

幻方是一种很神奇的 $N\times N$ 矩阵：它由数字 $1,2,3,\cdots \cdots ,N \times N$ 构成，且每行、每列及两条对角线上的数字之和都相同。

当 $N$ 为奇数时，我们可以通过下方法构建一个幻方：

首先将 $1$ 写在第一行的中间。

之后，按如下方式从小到大依次填写每个数 $K \ (K=2,3,\cdots,N \times N)$ ：

1. 若 $(K-1)$ 在第一行但不在最后一列，则将 $K$ 填在最后一行， $(K-1)$ 所在列的右一列；
2. 若 $(K-1)$ 在最后一列但不在第一行，则将 $K$ 填在第一列， $(K-1)$ 所在行的上一行；
3. 若 $(K-1)$ 在第一行最后一列，则将 $K$ 填在 $(K-1)$ 的正下方；
4. 若 $(K-1)$ 既不在第一行，也不在最后一列，如果 $(K-1)$ 的右上方还未填数，则将 $K$ 填在 $(K-1)$ 的右上方，否则将 $K$ 填在 $(K-1)$ 的正下方。

现给定 $N$ ，请按上述方法构造 $N \times N$ 的幻方。

### 输入格式

一个正整数 $N$，即幻方的大小。

### 输出格式

共 $N$ 行，每行 $N$ 个整数，即按上述方法构造出的 $N \times N$ 的幻方，相邻两个整数之间用单空格隔开。

### 输入输出样例 #1

#### 输入 #1

```
3
```

#### 输出 #1

```
8 1 6
3 5 7
4 9 2
```

### 输入输出样例 #2

#### 输入 #2

```
25
```

#### 输出 #2

```
327 354 381 408 435 462 489 516 543 570 597 624 1 28 55 82 109 136 163 190 217 244 271 298 325
353 380 407 434 461 488 515 542 569 596 623 25 27 54 81 108 135 162 189 216 243 270 297 324 326
379 406 433 460 487 514 541 568 595 622 24 26 53 80 107 134 161 188 215 242 269 296 323 350 352
405 432 459 486 513 540 567 594 621 23 50 52 79 106 133 160 187 214 241 268 295 322 349 351 378
431 458 485 512 539 566 593 620 22 49 51 78 105 132 159 186 213 240 267 294 321 348 375 377 404
457 484 511 538 565 592 619 21 48 75 77 104 131 158 185 212 239 266 293 320 347 374 376 403 430
483 510 537 564 591 618 20 47 74 76 103 130 157 184 211 238 265 292 319 346 373 400 402 429 456
509 536 563 590 617 19 46 73 100 102 129 156 183 210 237 264 291 318 345 372 399 401 428 455 482
535 562 589 616 18 45 72 99 101 128 155 182 209 236 263 290 317 344 371 398 425 427 454 481 508
561 588 615 17 44 71 98 125 127 154 181 208 235 262 289 316 343 370 397 424 426 453 480 507 534
587 614 16 43 70 97 124 126 153 180 207 234 261 288 315 342 369 396 423 450 452 479 506 533 560
613 15 42 69 96 123 150 152 179 206 233 260 287 314 341 368 395 422 449 451 478 505 532 559 586
14 41 68 95 122 149 151 178 205 232 259 286 313 340 367 394 421 448 475 477 504 531 558 585 612
40 67 94 121 148 175 177 204 231 258 285 312 339 366 393 420 447 474 476 503 530 557 584 611 13
66 93 120 147 174 176 203 230 257 284 311 338 365 392 419 446 473 500 502 529 556 583 610 12 39
92 119 146 173 200 202 229 256 283 310 337 364 391 418 445 472 499 501 528 555 582 609 11 38 65
118 145 172 199 201 228 255 282 309 336 363 390 417 444 471 498 525 527 554 581 608 10 37 64 91
144 171 198 225 227 254 281 308 335 362 389 416 443 470 497 524 526 553 580 607 9 36 63 90 117
170 197 224 226 253 280 307 334 361 388 415 442 469 496 523 550 552 579 606 8 35 62 89 116 143
196 223 250 252 279 306 333 360 387 414 441 468 495 522 549 551 578 605 7 34 61 88 115 142 169
222 249 251 278 305 332 359 386 413 440 467 494 521 548 575 577 604 6 33 60 87 114 141 168 195
248 275 277 304 331 358 385 412 439 466 493 520 547 574 576 603 5 32 59 86 113 140 167 194 221
274 276 303 330 357 384 411 438 465 492 519 546 573 600 602 4 31 58 85 112 139 166 193 220 247
300 302 329 356 383 410 437 464 491 518 545 572 599 601 3 30 57 84 111 138 165 192 219 246 273
301 328 355 382 409 436 463 490 517 544 571 598 625 2 29 56 83 110 137 164 191 218 245 272 299
```

### 说明/提示

对于 $100\%$ 的数据，对于全部数据， $1 \leq N \leq 39$ 且 $N$ 为奇数。

### 解答
```c
#include <stdio.h>
int N;
int main()
{
    int num_arr[39][39] = {0};
    scanf("%d", &N);
    int N_2 = N * N;
    num_arr[0][(N - 1) / 2] = 1;
    int x = (N - 1) / 2, y = 0;
    for (int i = 2; i <= N_2; i++)
    {
        if (y == 0)
        {
            if (x != N - 1)
            {
                x++;
                y = N - 1;
            }
            else if (x == N - 1)
            {
                y++;
            }
        }
        else if (x == N - 1 && y != 0)
        {
            x = 0;
            y--;
        }
        else if (y != 0 && x != N - 1)
        {
            if (num_arr[y - 1][x + 1] == 0)
            {
                x++;
                y--;
            }
            else
            {
                y++;
            }
        }
        num_arr[y][x] = i;
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", num_arr[i][j]);
        }
        printf("\n");
    }
}
```
