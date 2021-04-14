## 许可证(license)

本项目涉及的模板的源代码来自[royiori-qian](https://gitee.com/royiori-qian/G4Study.git)

,使用请联系原作者取得授权,改动部分(particle gun, analysis manager, detector construction等)使用[GNU GPL V3.0](http://www.gnu.org/copyleft/gpl.html) 许可证.

以下为[royiori-qian](https://gitee.com/royiori-qian/G4Study.git)的许可证


---
### UCAS组Geant4分析框架

### 1. 基于XML/GDML开发

### 2. 提供ROOT支持

### 3. 提供Optical光学/TRD穿越辐射物理过程支持

### 开发联系： liuqian@ucas.ac.cn

---


---
### 更新
#### 2021/4/12
更改TELFLON厚度,取为0.2*4=0.8mm,更改PMT,更改探测器位置  
更改飞行时间的取数方式
尝试$3\times10^5$个事例数,并记录多次散射


#### 2021/4/07
&emsp; 更改结构和入射中子能谱(32.6度厚靶D-D中子能谱)以使模拟更符合实际情况,加入探测器,内容物为液闪,5.2cm直径,厚度约5cm"Material components of the EJ301 scintillator were H and C (ratio of atoms is 1.212, density of the scintillator is 0.874 g/cm3). The scintillator was filled into a 5 cm in diameter and 20 cm in height cylindrical vessel with 0.5 mm thick aluminum. The light pipe and PMT were ignored."

ref:Su-Ya-La-Tu, Zhang & Chen, Zhiqiang & Rui, Han & Xing-Quan, Liu & Wada, Roy & Wei-Ping, Lin & Zeng-Xue, Jin & Yin-Yin, Xi & Jian-Li, Liu & Fu-Dong, Shi. (2013). Study on gamma response function of EJ301 organic liquid scintillator with GEANT4 and FLUKA. Chinese Physics C. 37. 10.1088/1674-1137/37/12/126003. 
&emsp; 注意到液闪没有加入闪烁功能,因为没有发光光谱.仅保留计数功能.故模拟粒子鉴别尚无法做到
&emsp; 更改视角及PMT的位置 z = 22,  x= 20 ,y =15, PMT在y上累加,但是视角为(0,0,-1),令x轴向上,z轴垂直纸面向外
&emsp; 更改存数方式,飞行时间(从射入CsI开始计时,射入探测器终止计时),每个探测器计数
&emsp;一个有意思的点是在G4Analysis Manager中

```
    const G4Track *aTrack = aStep->GetTrack();
    ...
    aStep->GetTrack()->SetTrackStatus(fStopAndKill);
```
其中第二步不可替换为
```
 aTrack->G4Track::SetTrackStatus(fStopAndKill);
```
因为在~/geant4.10.6-install/include/Geant4/G4Step.icc中
```
inline 
 G4Track* G4Step::GetTrack() const
 { 
   return fpTrack; 
 }
   
```
返回的被const限定,这一点在第一步中亦有体现.
#### 2021/4/02
&emsp;加入飞行时间探测(实验室系),注意默认单位为nm.解决PMT计数为0的bug.原因是加入TEFLON后TEFLON尺寸不对,即没有让CsI与PMT直接接触
&emsp;附注:几何体结构  /vis/scene/add/axes    # Simple axes: x=red(15mm), y=green(22mm), z=blue(20mm)(CsI)  即x沿纸面向里,y向上,入射方向为z,  y向上叠加PMT, 除顶部PMT外均覆盖有2mmTEFLON
&emsp;fParticleGun->SetParticlePosition(G4ThreeVector(G4UniformRand()*2-1, G4UniformRand()*2-1, -132.8)); 即设定 z = -132.8mm 处入射粒子
121583
474649
&emsp; 电子的计数比中子少,是因为切伦科夫辐射和韧致辐射.

当在MyParticlegun中选择抽样后,mac文件无法进行控制
#### 2021/3/24
&emsp;打开了所有的光学过程.
&emsp;在[royiori-qian](https://gitee.com/royiori-qian/G4Study.git)的帮助下通过版本源码找到了问题所在,可以通过降级至4.10.4版本,或者修改genat4源码解决.
&emsp;在Analysis中增加了多重散射部分.注意到AddNtuple的用法,与Instance不必一一对应.
&emsp;多次散射结果分析: 入射1000个1MeV的中子,无散射,单次散射,二次散射,三次散射的事例数分别为656, 273 , 55 ,12 ,使用Possion Distribution 模型. 

$$
f(k)= e^{-\lambda}  \frac{\lambda ^n}{n!}
$$
即
$$
\frac{f(1)}{f(0)}= \lambda , \frac{f(2)}{f(1)}=\frac{\lambda}{2}
$$
实验结果中比值分别为0.416, 0.201,可见结果自洽.但第二个比值与理论预期不符.注意到若中子的散射截面随中子能量改变较大,则不再遵循泊松分布,但目前调研指出二者弱相关.

#### 2021/3/17 
&emsp;确定不出光是版本问题,在geant4.10.6及4.10.7中中子发生弹性散射沉积能量无法产生次级粒子,但在版本4.10.4中可以正常产生;
&emsp;更改verbose输出,以使输出更简洁;
&emsp;优化光学界面及一些光学参数;