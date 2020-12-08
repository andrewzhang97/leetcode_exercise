//
//  sort.cpp
//  sort
//
//  Created by zhiyu zhang on 2018/8/23.
//

#include <iostream>
using namespace std;
// 冒泡排序
void Bubblesort(int a[],int n){
    int i,j;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1;j++)
        {
            if(a[j]>a[j+1]){
                swap(a[j],a[j+1]);
            }
        }
    }
}
// 直接插入排序
void Insertsort(int a[], int n)
{
    int i,j;
    for (i=0;i<n;i++){
        for(j=i;j>0;j--){
             if(a[j]<a[j-1]){
                  swap(a[j],a[j-1]);
             }
        }
    }
}
// 希尔排序(分组插入排序，增量为d，d=1是直接插入排序)
void Shellsort(int a[], int n) {
    int i, j, gap;
    
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        //for (i = 0; i < gap; i++)
        for (i = gap; i < n; i++)
        {
            for (j = i - gap; j >= 0; j -= gap)
            {
                if (a[j + gap] < a[j])
                    swap(a[j + gap], a[j]);
            }
        }
    }
}

// 直接选择排序
void Selectsort(int a[], int n) {
    int i, j;
    for (i = 0; i < n; i++)
    {
        int minIndex = i;
        for (j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }
        swap(a[i], a[minIndex]);
    }
}

// 归并排序(分治法)

// 将有序数组a[first...mid]和a[mid...last]合并
void MergeArray(int a[], int first, int mid, int last, int tmp[])
{
    int i = first, n = mid;
    int j = mid + 1, m = last;
    int k = 0;
    
    while (i <= n&&j <= m)
    {
        if (a[i] < a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    
    while (i <= n)
    {
        tmp[k++] = a[i++];
    }
    
    while (j <= m)
        tmp[k++] = a[j++];
    
    for (i = 0; i < k; i++)
        a[first + i] = tmp[i];
}

// 先递归地分解数列，再合并数列完成归并排序
void MergesortSection(int a[], int first, int last, int tmp[])
{
    if (first < last)
    {
        int mid = (first + last) / 2;
        MergesortSection(a, first, mid, tmp);  // 左边有序
        MergesortSection(a, mid + 1, last, tmp); // 右边有序
        MergeArray(a, first, mid, last, tmp); // 合并两个有序序列
    }
}

void Mergesort(int a[], int n)
{
    int *p = new int[n];
    if (p == NULL)
        return;
    MergesortSection(a, 0, n - 1, p);
    delete[] p;
}



// 快速排序

// 找中枢（挖坑填数）
void Quick_Sort(int iArray[],int left, int right)
{
     //快速排序之前先判断一下当前待排序数组元素个数是不是大于1 否则就没有必要排序
     if (left >= right)
     {
          //直接退出排序代码  没有必要进行排序了
          return;
     }
     //开始进行快排算法
     //首先我们先保存left索引对应的数据  当前数据作为切割数组的轴
     int piovt = iArray[left];
     
     //定义临时变量保存数组2端的索引
     int leftIndex = left;
     int rightIndex = right;
     while (leftIndex < rightIndex)
     {
          //现在我们通过循环从右边开始搜索一个比轴值小的数据
          while (leftIndex < rightIndex)//现比较右边的数，然后
          {
               //如果右边的数大于当前的参数轴值
               if (piovt <= iArray[rightIndex])
               {
                    //右端索引指示器左移
                    rightIndex--;
               }
               else
               {
                    //说明我们右端出现比轴值更大的数据
                    //这个时候我们就可以把这个更大的数据填充到索引轴索引对应的地方
                    iArray[leftIndex] = iArray[rightIndex];
                    leftIndex++;
                    //我们需要跳出循环了当前工作完毕
                    break;
               }
          }
          
          //从左边开始搜索一个比轴值更大的数填写上次留下的坑
          while (leftIndex < rightIndex)
          {
               //如果左边的数据小于轴值 我们索引指示器就往右走
               if (piovt >= iArray[leftIndex])
               {
                    leftIndex++;
               }
               else
               {
                    //说明我们在左端找到了比轴值更大的数据
                    iArray[rightIndex] = iArray[leftIndex];
                    rightIndex--;
                    break;
               }
          }
     }
     
     iArray[leftIndex] = piovt;
     Quick_Sort(iArray, left, leftIndex - 1);
     Quick_Sort(iArray, rightIndex + 1, right);
}



void Quicksort(int a[], int n)
{
    int left = 0;
    int right = n - 1;
    Quick_Sort(a, left, right);
}//递归法快速排序

// 堆排序

// 新加入节点i  其父节点为(i-1)/2
void MinHeapFixUp(int a[], int i)
{
    for (int j = (i - 1) / 2; a[i] > a[j] && i != 0 && j >= 0; i = j, j = (i - 1) / 2)
        swap(a[i], a[j]);
}

// 插入节点，只能在最小堆的末尾插入
void MinHeapAddNumber(int a[], int n, int nNum)
{
    a[n] = nNum;
    MinHeapFixUp(a, n);
}

// 删除节点i  调整堆  只能删除最小堆的堆顶元素，将最后一个元素a[n]放在堆顶，进行调整
void MinHeapFixDown(int a[], int i, int n)
{
    int j, tmp;
    tmp = a[i];
    j = 2 * i + 1;  // 左儿子
    while (j < n)
    {
        if (j + 1 < n&&a[j + 1] < a[j]) // 在左儿子和右儿子中找最小
            j++;
        
        if (a[j] >= tmp)
            break;
        
        swap(a[j], a[i]);
        i = j;
        j = 2 * i + 1;
    }
    a[i] = tmp;
}

void MinHeapDeleteNumber(int a[], int n)
{
    swap(a[0], a[n - 1]);
    MinHeapFixDown(a, 0, n - 1);
}

// 建立最小堆，数组画成堆后，叶子节点已经是合法的堆了，只要从最后一个叶子（即数组的最后一个元素）的双亲节点，向下调整就好
void MakeMinHeap(int a[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        MinHeapFixDown(a, i, n);
}

// 堆排序，对于小顶堆，我们只能从删除堆顶元素开始
// 对于堆用数组表示，我们将堆顶元素a[0]与a[n-1]交换， a[1]与a[n-2]交换...
// 相当于删除堆顶元素，所以向下调整堆
// 结果小顶堆对应的是从大到小的排序，若要从小到大，需要对结果逆序（或者用大顶堆）
void Minheapsort(int a[], int n)
{
    MakeMinHeap(a, 5);
    for (int i = n - 1; i >= 1; i--)
    {
        swap(a[i], a[0]);
        MinHeapFixDown(a, 0, i);
    }
}

int main()
{
    int a[] = { 10,3,5,8,30 };
    //Bubblesort(a, 5);
    //Insertsort(a, 5);
    //Shellsort(a, 5);
    //Selectsort(a, 5);
    //Mergesort(a, 5);
    Quicksort(a, 5);
    //Minheapsort(a, 5);
    
    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << ",";
    }
    return 0;
}



struct Linkedlist{
     int val;
     Linkedlist* next;
     Linkedlist(int x){
          this->val=x;
          this->next=NULL;
     }
};

//class stringm{
//     char* m;
//     int m_size;
//     stringm(char *str=NULL){
//          if(str==NULL){
//               m=new char[1];
//               m[0]='\0';
//               m_size=0;
//          }else{
//               m_size=strlen(str);
//               m=new char[m_size+1];
//               strcpy(m,str);
//          }
//     }
//     stringm(stringm& other){
//          m_size=strlen(other);
//          m=new char(m_size+1);
//          strcpy(m,other);
//     }
//     ~stringm(){
//          delete[] m;
//     }
//};


int match(string s,string m){
     int i,j;
     for(i=0;i<s.size();i++){
          for(j=0;j<m.size();j++){
               if(s[i+j]!=m[j]){
                    break;
               }
          }
          if(j==m.size()){
               return i;
          }
     }
     return 0;
}



