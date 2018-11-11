# ***自顶向下，逐步求精***  
&emsp;&emsp;这个词好像是来源于一本书《计算机网络自顶向下方法》。这本书是2009年机械工业出版社出版的图书，作者是库罗斯。本书采用作者独创的自顶向下的方法来讲授计算机网络的原理及其协议。   
***概括的说***   
&emsp;&emsp;自顶而下是一种 **逐步求精** 的设计程序的过程和方法。对要完成的任务进行分解，**先对最高层次中的问题进行定义、设计、编程和测试，而将其中未解决的问题作为一个子任务放到下一层次中去解决**。这样逐层、逐个地进行定义、设计、编程和测试，直到所有层次上的问题均由实用程序来解决，就能设计出具有层次结构的程序。  
&emsp;&emsp;所以，首先要求你必须对你所设计的系统有一个全面的理解.然后从顶层开始,连续地逐层向下分解,分解到所有的模块都能用具体的程序运行，这样就能逻辑地构造整个系统。  

<img title="" alt="这里写图片描述" src="https://img-blog.csdn.net/20171130122542055?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveno5NjI5/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast" width="400"/>  
  
<img title="" alt="这里写图片描述" src="https://img-blog.csdn.net/20171129184722808?watermark/2/text/aHR0cDovL2Jsb2cuY3Nkbi5uZXQveHVhbl90aW5n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70/gravity/SouthEast">

&emsp;&emsp;具体到程序编码中，就是将解决问题的 **最主要的、最表面的步骤**写在Main中，而解决问题的 **细节、具体的步骤** 则用函数来保存。

# ***在这里用洗衣机的洗衣程序来当例子：***

## 洗衣步骤：  
（1） 按下启动按扭及水位选择开关；  
（2） 开始进水直到高（中、 低）水位，关水；  
（3） 2秒后开始洗涤；  
（4） 洗涤时，正转30s，停2s，然后反转30s，停2s；  
（5） 如此循环5次，总共320s后开始排水，排空后脱水30s；  
（6） 开始清洗，重复（2）～（5），清洗两遍；  
（7） 清洗完成，报警3秒并自动停机；  
（8） 若按下停车按扭，可手动排水（不脱水）和手动脱水（不计数）；  

***Main函数：***

```
Main()
 {
    start()                             //启动函数（1）
    WHILE three times                           //循环三次
        in_water()                      //注水函数（1）
        wash()                          //洗函数（1）
        out_water()                     //排水函数（1）
        dry_water()                     //脱水函数（1）
    ENDWHILE
    close()                             //停机函数（1）
 }
 ```

 ***一层函数：***  
```
in_water()                      
{
    water_in_switch(open)                //打开上水开关函数（2）    
    WHILE get_water_volume() is enough   //测量水的高度函数（2）
    ENDWHILE
    water_in_switch(close)               //关闭上水开关函数（2）
}  
wash()                                           //洗涤剂加入是人为控制，与机器无关
{
    WHILE five times                              //循环五次
        timelimit_motorrun(right,30)     //定时定向转动函数（2）
        timelimit_motorrun(stop,2)       //同上
        timelimit_motorrun(left,30)      //同上        
}
out_water()                     
{
    water_out_switch(open)              //打开排水开关函数（2）
    WHILE get_water_volume() is 0       //测量水的高度函数（2）
    ENDWHILE
    water_out_switch(close)             //关闭排水开关函数（2）
}
dry_water()                     
{
    timelimit_motorrun(right,30)        //定时定向转动函数（2）
}
```  

***二层函数：***  
```  
water_in_switch(open/close)

get_water_volume(return height)

timelimit_motorrun(position,time)
{
    time=time_counter()                 //计时函数（3）      WHILE(time_counter()-time<=time)
        motor_run(position)             //转动函数（3）
    ENDWHILE
}

water_out_switch(open/close)
```

***三层函数：***
```
time_counter()
motor_run(position)

  
