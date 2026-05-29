/********************************************
[PannelName]
SAT070CP50D18Y0
[PannelType]
D_RGB888
[PannelResolution]
 800
 480
1056
 525
   8
  10
  46
  23
 210
  22
  -1
  -1
1200
 650
  40
  20
  46
  23
 354
 147
  -1
  -1
 862
 510
   1
   1
  46
  23
  16
   7
Update date:Monday, November 16, 2015
Update time:16:05:13
History:

********************************************/

typedef struct _PanlstaticPara
{
    unsigned int addr;
    unsigned char dat;
}PanlstaticPara;

typedef struct _PanlPosDynPara
{
    unsigned int addr;
    unsigned char dat_posDyn[6];
}PanlPosDynPara;

typedef struct _PanlSysDynPara
{
    unsigned int addr;
    unsigned char dat_sysDyn[8];
}PanlSysDynPara;



/*==============start===============*/
/*AV1
[VideoChannel]
AV1
[VideoType]
CVBS
[VideoPI]
VIDEO_P
[VideoPicSys]
PAL
[VideoData]
13500000
 690
 280
 864
 312

Update date:Monday, November 16, 2015
Update time:16:05:13
*/
PanlstaticPara code AV1_staticPara[]=
{
//GLOBAL
    {0XFD0D,0XE0}, 
    {0XFD0F,0X07}, 
    {0XFD14,0X01}, 
    {0XFD15,0X04}, 
    {0XFD16,0X0A}, 
    {0XFD1A,0X04}, 
//PWM
//DECODER
    {0XFE83,0XFE}, 
    {0XFEC9,0X01}, 
//VP
    {0XFFB0,0X67}, 
    {0XFFB1,0X0F}, 
    {0XFFB2,0X10}, 
    {0XFFB3,0X20}, 
    {0XFFB4,0X10}, 
    {0XFFC9,0X18}, 
    {0XFFF0,0X21}, 
    {0XFFF1,0XD2}, 
    {0XFFF2,0XFE}, 
    {0XFFF3,0X00}, 
    {0XFFF4,0X3D}, 
    {0XFFF5,0XD7}, 
    {0XFFF6,0X05}, 
    {0XFFF7,0X00}, 
    {0XFFF8,0X00}, 
    {0XFFF9,0X00}, 
    {0XFFFA,0XE0}, 
    {0XFFFB,0X80}, 
//TCON
    {0XFC00,0X00}, 
//SCALE
    {0XFC90,0X02}, 
    {0XFC91,0X01}, 
    {0XFC92,0X04}, 
    {0XFC93,0X00}, 
    {0XFC94,0X00}, 
    {0XFC95,0X00}, 
    {0XFC98,0XE7}, 
    {0XFC99,0X01}, 
    {0XFC9A,0XEA}, 
    {0XFC9B,0X03}, 
    {0XFC9C,0X01}, 
    {0XFC9D,0X00}, 
    {0XFC9E,0X06}, 
    {0XFC9F,0X00}, 
    {0XFCA0,0X24}, 
    {0XFCA1,0X00}, 
    {0XFCA2,0X8D}, 
    {0XFCA3,0X03}, 
    {0XFCA4,0X09}, 
    {0XFCA5,0X00}, 
    {0XFCA6,0X13}, 
    {0XFCA7,0X00}, 
    {0XFCA8,0X20}, 
    {0XFCA9,0X00}, 
    {0XFCAA,0X00}, 
    {0XFCAB,0X02}, 
    {0XFCB1,0X14}, 
    {0XFCB2,0X00}, 
    {0XFCB3,0X00}, 
    {0XFCB4,0X00}, 
    {0XFCB5,0X00}, 
    {0XFCB7,0X25}, 
    {0XFCB8,0X02}, 
    {0XFCBB,0X25}, 
    {0XFCBC,0X02}, 
    {0XFCBD,0X01}, 
    {0XFCBE,0X00}, 
    {0XFCBF,0X00}, 
    {0XFCC0,0X00}, 
    {0XFCC1,0X00}, 
    {0XFCC4,0X48}, 
    {0XFCC5,0X02}, 
    {0XFCC6,0XB2}, 
    {0XFCC7,0X04}, 
    {0XFCC8,0X01}, 
    {0XFCC9,0X00}, 
    {0XFCCA,0X06}, 
    {0XFCCB,0X00}, 
    {0XFCCC,0X24}, 
    {0XFCCD,0X00}, 
    {0XFCCE,0X8D}, 
    {0XFCCF,0X03}, 
    {0XFCD1,0X00}, 
    {0XFCD2,0X0F}, 
    {0XFCD3,0X00}, 
    {0XFCD4,0X1C}, 
    {0XFCD5,0X00}, 
    {0XFCD6,0XFC}, 
    {0XFCD7,0X01}, 
    {0XFCDD,0X14}, 
    {0XFCDE,0X00}, 
    {0XFCDF,0X00}, 
    {0XFCE0,0X00}, 
    {0XFCE1,0X00}, 
    {0XFCD0,0X05}, 
    {0XFCE2,0X02}, 
    {0XFCB6,0X02}, 
    {0XFB35,0X28}, 
    {0XFB89,0X00}, 
//GAMMA
    {0XFF00,0X03}, 
    {0XFF01,0X01}, 
    {0XFF02,0X03}, 
    {0XFF03,0X06}, 
    {0XFF04,0X0C}, 
    {0XFF05,0X15}, 
    {0XFF06,0X22}, 
    {0XFF07,0X2F}, 
    {0XFF08,0X3E}, 
    {0XFF09,0X4C}, 
    {0XFF0A,0X5B}, 
    {0XFF0B,0X69}, 
    {0XFF0C,0X77}, 
    {0XFF0D,0X83}, 
    {0XFF0E,0X8F}, 
    {0XFF0F,0X9A}, 
    {0XFF10,0XA6}, 
    {0XFF11,0XB0}, 
    {0XFF12,0XBB}, 
    {0XFF13,0XC4}, 
    {0XFF14,0XCD}, 
    {0XFF15,0XD4}, 
    {0XFF16,0XDB}, 
    {0XFF17,0XE1}, 
    {0XFF18,0XE6}, 
    {0XFF19,0XEA}, 
    {0XFF1A,0XEE}, 
    {0XFF1B,0XF2}, 
    {0XFF1C,0XF5}, 
    {0XFF1D,0XF7}, 
    {0XFF1E,0XFA}, 
    {0XFF1F,0XFC}, 
    {0XFF20,0X01}, 
    {0XFF21,0X03}, 
    {0XFF22,0X06}, 
    {0XFF23,0X0C}, 
    {0XFF24,0X15}, 
    {0XFF25,0X22}, 
    {0XFF26,0X2F}, 
    {0XFF27,0X3E}, 
    {0XFF28,0X4C}, 
    {0XFF29,0X5B}, 
    {0XFF2A,0X69}, 
    {0XFF2B,0X77}, 
    {0XFF2C,0X83}, 
    {0XFF2D,0X8F}, 
    {0XFF2E,0X9A}, 
    {0XFF2F,0XA6}, 
    {0XFF30,0XB0}, 
    {0XFF31,0XBB}, 
    {0XFF32,0XC4}, 
    {0XFF33,0XCD}, 
    {0XFF34,0XD4}, 
    {0XFF35,0XDB}, 
    {0XFF36,0XE1}, 
    {0XFF37,0XE6}, 
    {0XFF38,0XEA}, 
    {0XFF39,0XEE}, 
    {0XFF3A,0XF2}, 
    {0XFF3B,0XF5}, 
    {0XFF3C,0XF7}, 
    {0XFF3D,0XFA}, 
    {0XFF3E,0XFC}, 
    {0XFF3F,0X01}, 
    {0XFF40,0X03}, 
    {0XFF41,0X06}, 
    {0XFF42,0X0C}, 
    {0XFF43,0X15}, 
    {0XFF44,0X22}, 
    {0XFF45,0X2F}, 
    {0XFF46,0X3E}, 
    {0XFF47,0X4C}, 
    {0XFF48,0X5B}, 
    {0XFF49,0X69}, 
    {0XFF4A,0X77}, 
    {0XFF4B,0X83}, 
    {0XFF4C,0X8F}, 
    {0XFF4D,0X9A}, 
    {0XFF4E,0XA6}, 
    {0XFF4F,0XB0}, 
    {0XFF50,0XBB}, 
    {0XFF51,0XC4}, 
    {0XFF52,0XCD}, 
    {0XFF53,0XD4}, 
    {0XFF54,0XDB}, 
    {0XFF55,0XE1}, 
    {0XFF56,0XE6}, 
    {0XFF57,0XEA}, 
    {0XFF58,0XEE}, 
    {0XFF59,0XF2}, 
    {0XFF5A,0XF5}, 
    {0XFF5B,0XF7}, 
    {0XFF5C,0XFA}, 
    {0XFF5D,0XFC}, 
    {0XFF5E,0XFF}, 
    {0XFF5F,0XFF}, 
    {0XFF60,0XFF}, 
};
PanlPosDynPara code AV1_posDynPara[]=
{
//dispmode:  16:9  4:3  DM_EX0  DM_EX1  DM_EX2  DM_EX3
//GLOBAL
//PAD MUX
//PWM
//GPIO
//DECODER
//VP
//TCON
//SCALE
    {0XFC96,{0X51,0X69,0X69,0X69,0X69,0X69}},
    {0XFC97,{0X03,0X03,0X03,0X03,0X03,0X03}},
    {0XFCAC,{0X28,0X17,0X17,0X17,0X17,0X17}},
    {0XFCAD,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCAE,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCAF,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCB0,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCC2,{0X5A,0X6D,0X6D,0X6D,0X6D,0X6D}},
    {0XFCC3,{0X03,0X03,0X03,0X03,0X03,0X03}},
    {0XFCD8,{0X10,0X00,0X00,0X00,0X00,0X00}},
    {0XFCD9,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCDA,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCDB,{0X00,0X00,0X00,0X00,0X00,0X00}},
    {0XFCDC,{0X00,0X00,0X00,0X00,0X00,0X00}},
//GAMMA
};
PanlSysDynPara code AV1_sysDynPara[]=
{
//picSys:   PAL  PAL-N  PAL-M  NTSC SECAM PAL-60 NTSC-J NTSC-4.43
//GLOBAL
    {0XFD0A,{0X89, 0XC5, 0XC5, 0X89, 0XC5, 0XC5, 0XC5, 0XC5}},
//PAD MUX
//PWM
//GPIO
//DECODER
//VP
    {0XFFD3,{0X80, 0X86, 0X86, 0X80, 0X86, 0X86, 0X86, 0X86}},
    {0XFFD4,{0X60, 0X92, 0X92, 0X60, 0X92, 0X92, 0X92, 0X92}},
    {0XFFD5,{0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00}},
    {0XFFD6,{0X50, 0X38, 0X38, 0X50, 0X38, 0X38, 0X38, 0X38}},
//TCON
//SCALE
//GAMMA
};
/*============== end ===============*/



/*点屏 PAD MUX 参数*/
PanlstaticPara code AMT_PadMuxStaticPara[]=
{
//PAD MUX
    {0XFD32,0X11}, 
    {0XFD33,0X11}, 
    {0XFD34,0X11}, 
    {0XFD35,0X21}, 
    {0XFD36,0X11}, 
    {0XFD37,0X11}, 
    {0XFD38,0X11}, 
    {0XFD39,0X11}, 
    {0XFD3A,0X11}, 
    {0XFD3B,0X11}, 
    {0XFD3C,0X11}, 
    {0XFD3D,0X11}, 
    {0XFD3E,0X11}, 
    {0XFD3F,0X11}, 
    {0XFD40,0X12}, 
    {0XFD41,0X11}, 
    {0XFD44,0X01}, 
    {0XFD45,0X00}, 
    {0XFD46,0X00}, 
    {0XFD47,0X00}, 
    {0XFD48,0X00}, 
    {0XFD49,0X00}, 
    {0XFD4A,0X00}, 
    {0XFD4B,0X00}, 
    {0XFD50,0X0F}, 
};



/*屏参参数相关的结构体*/
typedef struct _PannelPara
{
   PanlstaticPara  *pVideoStaicPara;
   PanlPosDynPara *pVideoPosDynPara;
   PanlSysDynPara  *pVideoSysDynPara;
}PannelPara;
typedef struct _VideoChannel
{
   unsigned char INPUT_ID;
   PannelPara    VideoPara;
}VideoChannel;
/*不同通道屏参的定义、初始化*/
VideoChannel code VideoChannelPara[]=
{
{ INPUT_AV1,{AV1_staticPara,AV1_posDynPara,AV1_sysDynPara}},
};
#define STATIC_NUM 193
#define POS_DYN_NUM 14
#define SYS_DYN_NUM 5
#define PAD_MUX_NUM 25
#define VCOM_AC_Def 0X00
#define VCOM_DC_Def 0X00
#define PWMA_VAL 0X0000
#define PWMB_VAL 0X0000
#define PAL_PLL_CLK 0X0089
#define NTSC_PLL_CLK 0X0089
#define PWM0_CYCLE_VAL 0X00FF
#define PWM1_CYCLE_VAL 0X00FF
#define PWM2_CYCLE_VAL 0X00FF
#define PWM3_CYCLE_VAL 0X00FF
#define PWM0_DUTY_VAL 0X0080
#define PWM1_DUTY_VAL 0X0080
#define PWM2_DUTY_VAL 0X0080
#define PWM3_DUTY_VAL 0X0080


