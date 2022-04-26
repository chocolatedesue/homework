## 参考command

1. g++ rle.cpp -o rle
   - rle file1.txt -c file2.txt   (压缩文件)
   - rle file2.txt -c file3.txt   (解压文件)
   - 用**winhex**查看效果

> 
>
> 原理
>
> - char占8位，第一位作标识符，后七位表示字符数
>
> 注意事项：
>
> 1. strlen运算前要置0  (memset)
> 2. 指针加减可以避免数组运算
> 3. 面向对象，编写zip类