程序运行环境：Linux Centos 5.7 x86_64

版本管理：git
				
程序编译命令： 
1.进入代码所在目录
2.make all
3.在目录中会生成三个可执行程序:　generateData、trickOrTreat、trickOrTreat_omp

程序运行命令：

1.测试数据生成程序
 generateData <n> <u> <f>
 n : The number of home
 u : The upper bound
 f : output filename
 e.g.:
				./generateData 10000 200 input.txt
2.串行版Trick Or Treat程序
 trickOrTreat <i> 
 i : input filename
 e.g.:
				./trickOrTreat input.txt
3.并行版Trick Or Treat程序
 trickOrTreat <n> <i> 
 n : the number of threads
 i : input filename
 e.g.:
				./trickOrTreat_omp 8 input.txt

问题抽象：
求一个序列的一个连续子集，其和是不大于给定上限最大值，输出第一个符合条件的子集。

算法描述：

解决问题的过程类似于蠕虫蠕动

1.初始化，头和尾都设置为左边界，初始化最佳路径，跳转2
2.头向右移动，直到再移一步超过糖果的上限或超过home序列的长度，跳转3
3.若当前收集到的糖果更多则更新当前的最佳路径，若是头到达home序列的长度或是收集到的糖果已经到达糖果的上限，说明这已经是最好路径，退出，否则跳转2
4.尾向右移动一格（不越过右边界），并更新临时结果，如果尾超过头,则把头和尾放在一格，跳转2

并行化

并行版通过限制尾移动的范围，来划分不同的线程。达到把串行程序并行化的目的。