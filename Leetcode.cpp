//
//  Leetcode.cpp
//  Leetcode
//
//  Created by zhiyu zhang on 2020/4/7.
//  Copyright © 2020 zhiyu zhang. All rights reserved.
//

#include "Leetcode.hpp"
#include"iostream"
#include "cstring"
#include <vector>
#include <map>
#include <list>
using namespace std;


//2sum
//Given nums = [2, 7, 11, 15], target = 9,
//
//Because nums[0] + nums[1] = 2 + 7 = 9,
//return [0, 1].
class solution_2sum_hashmap{
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> res;
        vector<int> ans;
        for(int i=0;i<nums.size();i++){
            res[nums[i]]=i;
        }
        for(int i=0;i<nums.size();i++){
            int left=target-nums[i];
            if(res.count(left)&&res[left]!=i){//res.count(left)代表存在left这个数&&且右数并不是与i相等
                return {i,res[left]};
            }
        }
        return {};
    }
    
};



//three sum
class Solution_threesum {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> result;
        for (int i = 0; i<nums.size()-2;i++) {
            if (i>0 &&nums[i]== nums[i - 1]) continue;//    去重
            int low=i+1;
            int high=nums.size()-1;
            int target=0-nums[i];
            while(low<high){
                if(nums[low]+nums[high]==target){
                    result.push_back({nums[i],nums[low],nums[high]});
                    while (low<high&&nums[low]==nums[low+1]) {
                        low++;
                    }
                    while (low<high&&nums[high]==nums[high-1]) {
                        high--;
                    }
                    low++;
                    high--;
                }else if(nums[low]+nums[high]<target){
                    low++;
                }else{
                    high--;
                }
            }
        }
        return result;
    }
};

//Add two Numbers
//Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
//Output: 7 -> 0 -> 8
//
struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };
class solution_addtwonumbers{
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        ListNode dummy(0);
        ListNode *tail=&dummy;
        int sum=0;
        while(sum||l1||l2){
            sum+=(l1?l1->val:0)+(l2?l2->val:0);
            l1=l1?l1->next:nullptr;
            l2=l2?l2->next:nullptr;
            tail->next=new ListNode(sum%10);
            sum=sum/10;
            tail=tail->next;
        }
        return dummy.next;
    }
};

//最长无回文字串，动态规划
//原理就是保存上一次该字母出现的位置
class Solution_longestsustringnoduplication {
public:
    int lengthOfLongestSubstring(string s) {
        int ans=0;
        vector<int> index(128,-1);
        for(int i=0,j=0;j<s.size(); j++){
            i=max(i,index[s[j]]);
            ans=max(j-i+1,0);
            index[s[j]]=j;
        }
        return ans;
    }
};
//leetcode3 Given a string, find the length of the longest substring without repeating characters.

class Solution_lengthOfLongestSubstring {
public:
    int lengthOfLongestSubstring(string s) {
        int ans=0;
        vector<int> temp(128,-1);//保存每个字符最近出现的位置
        for(int i=0,j=0;j<s.size();j++){
            i=max(i,temp[s[j]]+1);//上一次该字母出现的地方+1
            ans=max(ans,j-i+1);
            temp[s[j]]=j;
        }
        return ans;
    }
};


//最长回文字串
//Input: "babad"
//Output: "bab"
//Note: "aba" is also a valid answer.
//从中间开始找，分奇偶数讨论

class Solution_longestPalindrome {
public:
    string longestPalindrome(string s) {
        int len=0;
        int start=0;
        for(int i=0;i<s.size();i++){
            int cur=max(getlen(s, i, i),getlen(s, i, i+1));
            if(cur>len){
                len=cur;
                start=i-(len-1)/2;
            }
        }
        return s.substr(start,len);
    }
    int getlen(string s,int l,int r){
        while(l>=0&&r<s.size()&&s[l]==s[r]){
            l--;
            r++;
        }
        return r-l-1;
    }
};



//Reverse Integer
class Solution_ReverseInteger {
public:
    long reverse(int x) {
        long ans=0;
        while(x){
            ans=ans*10+x%10;
            x=x/10;
        }
        return ans;
    }
};

//container with most water

class Solution_maxarea {
public:
    int maxArea(vector<int>& height) {
        int l=0;
        int r=height.size()-1;
        int res=0;
        while(l<r){
            int h=min(height[r],height[l]);
            int res=max(((r-l)*h),res);
            if(height[r]>height[l]){
                l++;
            }else{
                r--;
            }
        }
        return res;
    }
};

//commonpreflix
class Solution_commonpreflix {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        if(strs.size()==0){
            return res;
        }else{
            for(int i=0;i<strs[0].size();i++){
                char c=strs[0][i];
                for(int j=0;j<strs.size();j++){
                    if(i>strs[j].size()){
                        return res;
                    }
                    if(c!=strs[j][i]){
                        return res;
                    }
                }
                res=c+res;
            }
        }
        return res;
    }
};

//牛顿法 求开方
class Solution_sqrt {
public:
    int mySqrt(int x) {
        long r = x;
        while (r*r > x)
            r = (r + x/r) / 2;
        return r;
    }
};
//leetcode 123
//best time to sell stock at max 1 times
class Solution_bttssI{
public:
    int maxProfit(vector<int> prices){
        if(prices.size()==0){
            return 0;
        }
        int profit=0;
        int min_price=prices[0];
        for(int i=0;i<prices.size();i++){
            if(prices[i]>min_price){
                profit=max(profit,prices[i]-min_price);
            }else{
                min_price=prices[i];
            }
        }
        return profit;
    }
};


//leetcode122
class Solution_bttssII{
public:
    int maxProfit(vector<int> prices){
        if(prices.size()==0){
            return 0;
        }
        int profit=0;
        for(int i=1;i<prices.size();i++){
            if(prices[i]>prices[i-1]){
                profit+=prices[i]-prices[i-1];
            }
        }
        return profit;
    }
};
//Unique path
class Solution_uq {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m,vector<int>(n,1));
        for(int i=1;i<m;i++){
            for (int j=1;j<n; j++){
                dp[i][j] =dp[i-1][j]+dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

//链表反转
class solution_reverselinkedlist{
public:
    ListNode *reverselist(ListNode *head){
        ListNode *p=head;
        ListNode *q=head->next;
        head->next=NULL;
        while(q){
            ListNode *r=q->next;
            q->next=p;
            p=q;
            q=r;
        }
        return p;
    }
};


//leetcode 73
//Input:
//[
// [1,1,1],
// [1,0,1],
// [1,1,1]
// ]
//Output:
//[
// [1,0,1],
// [0,0,0],
// [1,0,1]
// ]

class Solution_Set_Matrix_Zeroes {
public:
    //标志位做法
    void setZeroes(vector<vector<int>>& matrix) {
        if(matrix.empty()){
            return;
        }
        int m=matrix.size();
        int n=matrix[0].size();
        
        bool rowzero=false;
        bool colzero=false;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(matrix[i][j]==0){
                    if(i==0) colzero=true;
                    if(j==0) rowzero=true;
                    matrix[i][0]=0;
                    matrix[0][j]=0;
                }
            }
        }
        for(int i=1;i<m;i++){
            if(matrix[i][0]==0){
                for(int j=0;j<n;j++){
                    matrix[i][j]=0;
                }
            }
        }
        for(int j=1;j<n;j++){
            if(matrix[0][j]==0){
                for(int i=0;i<m;i++){
                    matrix[i][j]=0;
                }
            }
        }
        
        
        
        if(colzero){
            for(int j=0;j<n;j++){
                matrix[0][j]=0;
            }
        }
        if(rowzero){
            for(int i=0;i<m;i++){
                matrix[i][0]=0;
            }
        }
    }
};


//Spiral Matrix

//Input:
//[
// [ 1, 2, 3 ],
// [ 4, 5, 6 ],
// [ 7, 8, 9 ]
// ]
//Output: [1,2,3,6,9,8,7,4,5]


class Solution_spiral_matrix {
public://using violent way to solve problem O(m*n)
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> res;
        if(matrix.empty()||matrix[0].empty()){
            return res;
        }
        else{
            int rbegin=0;
            int rend=matrix.size()-1;
            int cbegin=0;
            int cend=matrix[0].size()-1;
            while(rbegin<=rend&&cbegin<=cend){
                for(int i=cbegin;i<=cend;i++){
                    res.push_back(matrix[rbegin][i]);
                }
                rbegin++;
                for(int i=rbegin;i<=rend;i++){
                    res.push_back(matrix[i][cend]);
                }
                cend--;
                for(int i=cend;i>=cbegin;i--){
                    res.push_back(matrix[rend][i]);
                }
                rend--;
                for(int i=rend;i>=rbegin;i--){
                    res.push_back(matrix[i][cbegin]);
                }
                cbegin++;
            }
        }
        return res;
    }
};




//leetcode 198 robbery 间隔一家才能抢劫 r动态规划
class Solution_house_robbery {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()){
            return 0;
        }
        vector<int> res(nums.size(),0);
        for(int i=0;i<nums.size();i++){
            res[i]=max((i-1>=0?res[i-1]:0),(i-2>=0?res[i-2]:0)+nums[i]);
        }
        return res[nums.size()-1];
    }
};


//二叉树层次遍历
class TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution_levelorder {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        DFS(root,0,res);
        return res;
    }
    void DFS(TreeNode &root,int level,vector<vector<int>> &res){
        if(!root){
            return;
        }
        while(res.size()<=level){
            res.push_back({});
        }
        res[level].push(root->val);
        DFS(root->left,level+1,res);
        DFS(root->right,level+1,res);
    }
};






//Meituan

Class Meituan{
    public:
    int getans(){
        int n,k;
        cin>>n>>k;
        int bigger=0,smaller=0,equal=0;
        for(int i=0;i<n;i++){
            int tmp;
            cin>>tmp;
            if(tmp<k){
                smaller++;
            }else if(tmp>k){
                bigger++;
            }else{
                equal++;
            }
        }
        cout << max(max(smaller-bigger + 1, bigger -smaller) - equal, 0);
        
        return 0;
    }
    //需要补的k的个数即max(big-small, small-big+1) - equal
}


//46 Permutation
//用DFS来做
//Given a collection of distinct integers, return all possible permutations.
//
//Example:
//
//Input: [1,2,3]
//Output:
//[
// [1,2,3],
// [1,3,2],
// [2,1,3],
// [2,3,1],
// [3,1,2],
// [3,2,1]
// ]

class Solution_permutation {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        dfs(nums,ans,0,nums.size());
        return ans;
    }
    
    void dfs(vector<int>& output,vector<vector<int>>& ans,int start,int len){
        if(start==len){
            ans.push_back(output);
            return;
        }
        for(int i=0;i<len;i++){
            swap(output[i],output[start]);
            dfs(output,ans,start+1,len);
            swap(output[i],output[i])
        }
        
    }
};


//leetcode 47 unique permutation
//对于这个问题，我们需要将引入k，来检查是否有重复，如果重复m，直接跳过
class Solution_uniquepermutation {
public:
    vector<vector<int>> permuteunique(vector<int>& nums) {
        vector<vector<int>> ans;
        std::sort(nums.begin(),nums.end());
        dfs(nums,ans,0,nums.size());
        return ans;
    }
    
    void dfs(vector<int>& output,vector<vector<int>>& ans,int start,int len){
        if(start==len){
            ans.push_back(output);
            return;
        }
        for(int i=start;i<len;i++){
            if(i==start){
                dfs(output,ans,start+1,len);
                continue;
            }
            
            int k;//引入k
            for(k=i-1;k>=start;k--){//对于每次遍历，如果发现相同的数字，直接跳出
                if(output[k]==output[i])
                    break;
            }
            if(k!=start-1){//如果一直未跳出，那么直接跳过这个数字
                continue;
            }
            
            swap(output[i],output[start]);
            dfs(output,ans,start+1,len);
            swap(output[i],output[i])
        }
        
    }
};

//leetcode34
//Find First and Last Position of Element in Sorted Array
//Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
//
//Your algorithm's runtime complexity must be in the order of O(log n).
//
//If the target is not found in the array, return [-1, -1].
//
//Example 1:
//
//Input: nums = [5,7,7,8,8,10], target = 8
//Output: [3,4]
//Example 2:
//
//Input: nums = [5,7,7,8,8,10], target = 6
//Output: [-1,-1]


class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {firstp(nums,target),lastp(nums,target)};
    }
    int firstp(vector<int>& nums, int target){
        int left=0;
        int right=nums.size()-1;
        while(left<right){
            int mid=left+(left+right)/2;
            if(nums[mid]>=target){
                right=mid;
            }
            if(nums[mid]<target){
                left=mid+1;
            }
        }
        if(left==nums.size()||nums[l]!=target) return -1;
        return left;
    }
    int lastp(vector<int>& nums, int target){
        int left=0;
        int right=nums.size()-1;
        while(left<right){
            int mid=left+(left+right)/2;
            if(nums[mid]>target){
                right=mid-1;
            }
            if(nums[mid]<target){
                left=mid;
            }
        }
        if(left==nums.size()||nums[l]!=target) return -1;
        return left;
    }
};

//leetcode 16 threesumtarget
//给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
//
//例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.
//
//与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).
class Solution_3Sum_Closest {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int ans=nums[0]+nums[1]+nums[2];
        std::sort(nums.begin(),nums.end());
        for(int i=0;i<nums.size();i++){
            int left=i+1;
            int right=nums.size()-1;
            while(left<right){
                int sum=nums[i]+nums[left]+nums[right];
                if(abs(target-sum)<abs(target-ans)){
                    ans=sum;
                }else if(sum<target){
                    left++;
                }else{
                    right--;
                }
            }
        }
        return ans;
    }
};

//leetcode14
//编写一个函数来查找字符串数组中的最长公共前缀。
//
//如果不存在公共前缀，返回空字符串 ""。
//
//示例 1:
//
//输入: ["flower","flow","flight"]
//输出: "fl"
//示例 2:
//
//输入: ["dog","racecar","car"]
//输出: ""
//解释: 输入不存在公共前缀。
class Solution_commonpreflix {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string res;
        if(strs.size()==0){
            return res;
        }
        for(int i=0;i<strs[0].size();i++){
            char c=strs[0][i];
            for(int j=0;j<strs.size();j++){
                if(i>strs[j].size()){
                    return res;
                }
                if(c!=strs[j][i]){
                    return res;
                }
            }
            res=res+c;
        }
        return res;
    }
};

//leetcode 20
//20. 有效的括号
//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
//
//有效字符串需满足：
//
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
//注意空字符串可被认为是有效字符串。
//
//示例 1:
//
//输入: "()"
//输出: true

class Solution_validParentheses {
public:
    bool isValid(string s) {
        unordered_map<char,int> mp;
        mp['[']=']';
        mp['(']=')';
        mp['{']='}';
        stack<char> st;
        for(int i=0;i<s.size();i++){
            char ch=s[i];
            if(mp.count(ch)>0){
                st.push(ch);//push in stack. Stack is used to preserve the left one
            }
            else if(ch==']'||ch=='}'||ch==')'){
                if(!st.empty()&&ch==mp[st.top()]){//if stack is empty it must be wrong and if ch matches the the top of the stack it is true.
                    st.pop();
                }
                else
                    return false;
            }
            else return false;
        }
        if(st.empty()) return true;
        else return false;
    }
};



//22. 括号生成
//数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
//
//
//
//示例：
//
//输入：n = 3
//输出：[
//    "((()))",
//    "(()())",
//    "(())()",
//    "()(())",
//    "()()()"
//    ]

class Solution_generateParenthesis {
    //使用C++，基本结构和上面一样，不过这里 lc 和 rc 分别表示左括号的个数和右括号的个数。vector的push_back()方法调用的时候实际上是使用的值传递，也就是会进行赋值到vector里。
    //回溯法的代码套路是使用两个变量： res 和 path，res 表示最终的结果，path 保存已经走过的路径。如果搜到一个状态满足题目要求，就把 path 放到 res 中。
    
    
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        dfs(n,"",res,0,0);
        return res;
    }
    void dfs(int n,string path,vector<string> &res,int l,int r){
        if(r>l||l>n||r>n) return;
        if(l==r&&l==n){
            res.push_back(path);
            return;
        }
        dfs(n,path + '(',res, l+1,r);
        dfs(n,path + ')',res, l,r+1);
    }
};


//回溯法个人理解
//        （
//        / \
//       ((  ()
//       /\  /\
//
//   ((( (() ()( ())
//满足于条件的直接加入res中间，不满足的直接break掉，可以作为模板j记住
