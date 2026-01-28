  //'Space'  ''      ''      ''      ''       ''        ''      ''        ''      ''       ''  		   		  		  		 '-'			   		 			   		  		  					  
/*******************************************************************************
*Copyright (C) 2005 ÉîÛÚ°¬¿Æ´´ÐÂÓÐÏÞ¹«Ë¾²úÆ·Ó¦ÓÃÒ»²¿
* All rights reserved.

*File name: ¡¡ AMT_0sdBootDrv.c	  
*Version:      1.0
*update:       2011-12-06
*Description:
  		  AMT OSDµ×²ãÇý¶¯¡£
	   
*History:  yshuizhou   2011/12/19    1.0    build  this  moudle
******************************************************************************/
#include "AMT_Mcu.h"
#include "Flash.h"

#define RedColor       	0x000f //ºìÉ«:
#define GreenColor     	0x00f0 //ÂÌÉ«:
#define BlueColor      	0x0f00 //À¶É«: 
#define YellowColor    	0x00ff //»ÆÉ«:
#define Red1Color      	0x0f0f //Æ·ºì:
#define GrayColor      	0x0888 //»ÒÉ«: 
#define WhiteColor     	0x0fff //°×É«: 
#define CyanColor      	0x0ff0 //ÇàÉ«:
#define OrangeColor    	0x008f //³ÈÉ«:
#define PurpleColor    	0x0f08 //×ÏÉ«:
#define MalachiteColor 	0x08f0 //ÂÌÇà:

static UCHAR XDATA g_ucCurOsdBlockId = 0;
OsdCtrlerType  XDATA g_OsdContrller;


//ATM630A OSD ASCII MAP:
static UINT CODE  ASCIIMap[256] = 
{
#if(ICON_SIZE == SIZE_12X16)
//(1,2-0)    (1,3-1)   (1,4-2)     (1,5-3)   (1,6-4)     (1,7-5)     (1,8-6)     (1,9-7)    (1,10-8)  (1,11-9)   (1,12-10)   (1,13-11)   (1,14-12)  (1,15-13)  (1,16-14)    (1,17-15)
  0X1E5,    0X1E6,   0X1E7,    0X1E8,    0X1E9,    0X1EA,     0X1EB,    0X1EC,    0X1ED,   0X1EE,    0X1EF,     0X1F0,    0X1F1,    0X1F2,    0X1F3,      0X1F4,

//(1,18-16)  (1,19-17) (1,20-18)   (1,21-19)  (1,22-20)  (1,23-21)   (1,24-22)   (1,25-23)  (1,26-24) (1,27-25)  (1,28-26)   (1,29-27)   (1,30-28)  (1,31-29)  (1,32-30)    (1,33-31)
  0X1F5,    0X1F6,   0X1F7,    0X1F8,    0X1F9,    0X1FA,     0X1FB,    0X1FC,    0X1FD,   0X1FE,    0X1FF,     0X200,    0X201,    0X202,    0X203,      0X204,

  //Space      !       (1,34-34)    #         (2,2-36)   (2,3-37)      &         (2,5-39)   (2,6-40)  (2,9-41)    *  	     (2,10-43) 	 (2,11-44)  (2,12-45)	 ¡£         (2,18-47)
  0X1C0,    0X210,   0X205,    ' ',        0X208,   0X209,      ' ',       0X20B,    0X20C,   0X242,	  0X206,    0X241,    0X051,    0X052,    0X20D,		 0X058,

  //0          1        2           3          4          5            6          7          8         9          :          (2,19-59)     <        (2,27-61)     >           ?
  0x1C1, 	 0x1C2,   0x1C3,    0x1C4,    0x1C5,    0x1C6,     0x1C7,    0x1C8,    0x1C9,   0x1CA,    0X20E,     0X059,    0X04D,    0X211,    0X04E ,     0X20F,

  //(2,28-64)  A       B           C          D          E            F          G           H         I          J           K           L          M           N            O  
  0X212,  	 0X1CB,  0X1CC,     0X1CD,    0X1CE,    0X1CF,     0X1D0,    0X1D1,    0X1D2,   0X1D3,    0X1D4,     0X1D5,    0X1D6,    0X1D7,    0X1D8,	     0X1D9,

  //P          Q       R           S          T          U            V          W           X         Y          Z          (6,2-91)    (6,3-92)   (7,17-93)  (7,18-94)    (7,19-95)
  0X1DA,	 0X1DB,  0X1DC,     0X1DD,    0X1DE,    0X1DF,     0X1E0,    0X1E1,    0X1E2,   0X1E3,    0X1E4,     0X063,    0X064,    0X065,    0x066,      0x067,    		  		  		 			   		 			   		  		  					  

  //(7,20-96)  A        B          C          D          E            F          G           H         I          J           K           L          M           N           O
  0X109,    0X1CB, 0X1CC,      0X1CD,    0X1CE,    0X1CF,     0X1D0,    0X1D1,    0X1D2,   0X1D3,    0X1D4,     0X1D5,    0X1D6,    0X1D7,    0X1D8,      0X1D9,

  //P          Q        R          S          T          U            V          W           X         Y          Z          (7,21-123)  (7,22-124)  (7,24-125)  (8,26-126)  (8,27-127) 
  0X1DA,    0X1DB, 0X1DC,      0X1DD,   0X1DE,    0X1DF,      0X1E0,    0X1E1,    0X1E2,   0X1E3,    0X1E4,     0X10A,    0X10B,    0X10D,    0X239,      0X133,

  //(8,31-128) (8,32-129)  (8,33-130)   (8,34-131)  (9,0-132) (9,1-133)  (9,2-134) (9,3-135)  (9,4-136)   (9,5-137)  (9,6-138) (9,7-139)  (9,8-140)  (9,9-141)   (9,10-142) (9,11-143)
  0X137,     0X138,     0X139,     0X13A,    0X13B,    0X213,    0X214,   0X215,    0X216,    0X217,    0X218,   0X21A,    0X21B,   0X21C,    0X21D,      0X21E,

  //(9,12-144) (9,13-145) (9,14-146)  (9,15-147)  (9,16-148) (9,17-149)  (9,18-150) (9,19-151) (9,20-152) (9,21-153) (9,22-154) (9,23-155) (9,24-156) (9,25-157) (9,26-158) (9,27-159)
  0X21F ,    0X220,     0X221,     0X225,    0X226,    0X227,    0X228,   0X22A,    0X22B,    0X22C,    0X22D,   0X22E,    0X22F,   0X230,    0X229,      0X23B,

  //(9,28-160) (9,29-161) (9,30-162)  (9,31-163)  (9,32-164) (9,33-165)  (9,34-166) (10,0-167) (10,1-168) (10,2-169) (10,3-170) (10,4-171) (10,5-172) (10,6-173) (10,7-174) (10,29-175)   
  ' ',        0X23F,     0X222,     0X240,    0X219,    0X223,     ' ',      ' ',       ' ',       0X224,    0X232,    0X233,   0X23E,   0X23A,    0X23C,      0X17B,
 
 //(10,30-176) (11,23-177) (11,24-178) (11,25-179) (11,30-180) (11,31-181) (11,32-182) (2,1-183) (2,4-184)
  0X17C,     0X198,  	   0X199,     0X19A,    0X19F,     0X1A0,    0X1A1,   0X207,   0X20A,
#elif(ICON_SIZE == SIZE_16X22)
//(1,2-0)    (1,3-1)   (1,4-2)     (1,5-3)   (1,6-4)     (1,7-5)     (1,8-6)     (1,9-7)    (1,10-8)  (1,11-9)   (1,12-10)   (1,13-11)   (1,14-12)  (1,15-13)  (1,16-14)    (1,17-15)
  0X025,    0X026,   0X027,    0X028,    0X029,    0X02A,     0X02B,    0X02C,    0X02D,   0X02E,    0X02F,     0X030,    0X031,    0X032,    0X033,      0X034,

//(1,18-16)  (1,19-17) (1,20-18)   (1,21-19)  (1,22-20)  (1,23-21)   (1,24-22)   (1,25-23)  (1,26-24) (1,27-25)  (1,28-26)   (1,29-27)   (1,30-28)  (1,31-29)  (1,32-30)    (1,33-31)
  0X035,    0X036,   0X037,    0X038,    0X039,    0X03A,     0X03B,    0X03C,    0X03D,   0X03E,    0X03F,     0X040,    0X041,    0X042,    0X043,      0X044,

  //Space      !       (1,34-34)    #         (2,2-36)   (2,3-37)      &         (2,5-39)   (2,6-40)  (2,9-41)    *  	     (2,10-43) 	 (2,11-44)  (2,12-45)	 ¡£         (2,18-47)
  0X000,    0X135,   0X045,    ' ',        0X048,   0X049,      ' ',       0X04B,    0X04C,   0X04F,    0x046,     0X050,    0X051,    0X052,    0X10C,      0X058,

  //0          1        2           3          4          5            6          7          8         9          :          (2,19-59)     <        (2,27-61)     >           ?
  0x001, 	 0x002,   0x003,    0x004,    0x005,    0x006,     0x007,    0x008,    0x009,   0x00A,    0X134,     0X059,    0X04D,    0X061,    0X04E ,     0X136,

  //(2,28-64)  A       B           C          D          E            F          G           H         I          J           K           L          M           N            O  
  0X062,  	 0X00B,  0X00C,     0X00D,    0X00E,    0X00F,     0X010,    0X011,    0X012,   0X013,    0X014,     0X015,    0X016,    0X017,    0X018,	     0X019,

  //P          Q       R           S          T          U            V          W           X         Y          Z          (6,2-91)    (6,3-92)   (7,17-93)  (7,18-94)    (7,19-95)
  0X01A,	 0X01B,  0X01C,     0X01D,    0X01E,    0X01F,     0X020,    0X021,    0X022,   0X023,    0X024,     0X063,    0X064,    0X065,    0x066,      0x067,    		  		  		 			   		 			   		  		  					  

  //(7,20-96)  A        B          C          D          E            F          G           H         I          J           K           L          M           N           O
  0X109,    0X00B, 0X00C,      0X00D,   0X00E,    0X00F,      0X010,    0X011,    0X012,   0X013,    0X014,     0X015,    0X016,    0X017,    0X018,      0X019,

  //P          Q        R          S          T          U            V          W           X         Y          Z          (7,21-123)  (7,22-124)  (7,24-125)  (8,26-126)  (8,27-127) 
  0X01A,    0X01B, 0X01C,      0X01D,   0X01E,    0X01F,      0X020,    0X021,    0X022,   0X023,    0X024,     0X10A,    0X10B,    0X10D,    0X132,      0X133,

  //(8,31-128) (8,32-129)  (8,33-130)   (8,34-131)  (9,0-132) (9,1-133)  (9,2-134) (9,3-135)  (9,4-136)   (9,5-137)  (9,6-138) (9,7-139)  (9,8-140)  (9,9-141)   (9,10-142) (9,11-143)
  0X137,     0X138,     0X139,     0X13A,    0X13B,    0X13C,    0X13D,   0X13E,    0X13F,    0X140,    0X141,   0X142,    0X143,   0X144,    0X145,      0X146,

  //(9,12-144) (9,13-145) (9,14-146)  (9,15-147)  (9,16-148) (9,17-149)  (9,18-150) (9,19-151) (9,20-152) (9,21-153) (9,22-154) (9,23-155) (9,24-156) (9,25-157) (9,26-158) (9,27-159)
  0X147 ,    0X148,     0X149,     0X14A,    0X14B,    0X14C,    0X14D,   0X14E,    0X14F,    0X150,    0X151,   0X152,    0X153,   0X154,    0X155,      0X156,

  //(9,28-160) (9,29-161) (9,30-162)  (9,31-163)  (9,32-164) (9,33-165)  (9,34-166) (10,0-167) (10,1-168) (10,2-169) (10,3-170) (10,4-171) (10,5-172) (10,6-173) (10,7-174) (10,29-175)   
  0X157,     0X158,     0X159,     0X15A,    0X15B,    0X15C,    0X15D,   0X15E,   0X15F,    0X160,    0X161,    0X162,   0X163,   0X164,    0X165,      0X17B,
 
 //(10,30-176) (11,23-177) (11,24-178) (11,25-179) (11,30-180) (11,31-181) (11,32-182) (2,1-183) (2,4-184)
  0X17C,     0X198,  	   0X199,     0X19A,    0X19F,     0X1A0,    0X1A1,   0X207,   0X20A,
#endif
};



//ATM630A OSD Asian MAP:
static UINT CODE  AsianMap[256] = 
{
#if(ICON_SIZE == SIZE_12X16)
  //(É«-0)   (ÎÂ-1)   (×¼-2)     (¶È-3)   (ÏÔ-4)    (Ê¾-5)     (Ä¬-6)    (ÈÏ-7)     (Ïµ-8)     (Í³-9)     (»­-10)    (ÖÊ-11)    (µ÷-12)     (Õû-13)    (Óï-14)   (ÑÔ-15)
  0X243,   0X064,   0X065,   0x257,  0x067,   0X068,	   0X069,   0X06A,    0X06B,   0X06C,    0X06D,    0X06E,    0X24F,    0X070,   0X249,    0X24A,

 //(Ñ¡-16)  (Ôñ-17)   (¿ª-18)    (¹Ø-19)  (¶Ô-20)   (±È-21)    (Ë¯-22)   (Ãß-23)    (Ïñ-24)    (¶¨-25)    (Êä-26)    (Èë-27)    (»Ö-28)     (¸´-29)   (ºÍ-30)    (ËÑ-31) 
  0X073,   0X074,   0X075,   0X076,  0X245,   0X246,	   0X079,   0X07A,    0X07B,   0X07C,    0X07D,    0X07E,    0X07F,    0X255,   0X081,    0X082,

 //(Äê-32)  (ÔÂ-33)   (ÈÕ-34)    (·Ö-35)  (Ãë-36)   (ÐÇ-37)    (ÆÚ-38)   (Ò»-39)     (¶þ-40)   (Èý-41)    (ËÄ-42)    (Îå-43)    (Áù-44)    (´ó-45)   (Ä£-46)     (Ê½-47) 
  0X083,   0X084,   0X085,   0X086,  0X087,   0X088,    0X089,  0X08A,     0X08B,   0X08C,    0X08D,   0X08E,    0X08F,    0X090,   0X250,    0X251,

 //(½µ-48)  (Ôë-49)   (Èá-50)    (Öµ-51)  (Ð¡-52)   (¸½-53)    (¼þ-54)   (·­-55)     (×ª-56)    (ÉÏ-57)   (ÏÂ-58)    (×ó-59)    (ÓÒ-60)    (ÖÆ-61)   (Éù-62)     (ÖÃ-63)
  0X093,   0X094,   0X095,   0X096,  0X097,	0X098,    0X099,  0X247,     0X248,   0X09C,    0X09D,    0X09E,   0X09F,    0X0A0,   0X0A1,  	 0X0A2,

 //(ºÅ-64)  (ÎÞ-65)   (°é-66)    (Ìå-67)  (Ô´-68)   (×Ö-69)    (Ãæ-70)   (Àö-71)     (´æ-72)    (Ì¨-73)   (ÊÖ-74)    (×Ô-75)    (¶¯-76)    (Î»-77)   (Æµ-78)     (µÀ-79)
  0X24B,   0X252,	  0X0A5,   0X254,  0X258,   0X0A8,    0X0A9,  0X0AA,     0X0AB,   0X0AC,    0X0AD,    0X0AE,    0X0AF,   0X256,   0X0B1,     0X0B2, 

//(¶Î-80)   (±£-81)   (²Ê-82)    (Çå-83)  (Îú-84) 	(¾²-85)    (Òô-86)   (Ê±-87)     (¼ä-88)    (¼ò-89)    (ÖÐ-90)    (ÎÄ-91)    (Ìø-92)    (Ô½-93)  (Í¼-94)      (Ô¤-95)
  0X0B3,   0X0B4,   0X262,   0X0B6,  0X0B7,   0X0B8,    0X0B9,  0X0BA,     0X0BB,   0X24C,    0X24D,    0X24E,    0X0BF,    0X0C0,  0X0C1,     0X0C2,

//(Éè-96)   (È·-97)   (ÐÅ-98)    (Á¿-99)  (ÁÁ-100)  (5,25-101) (5,26-102) (5,27-103) (5,28-104) (5,29-105) (5,30-106) (5,31-107)  (5,32-108) (5,33-109) (5,34-110) (6,0-111)
  0X0C3,   0X0C4,   0X253,   0X0C6,  0X244,   0X260,    0X0C9,   0X0CA,    0X0CB,    0X267,    0X0CD,    0X25D,   0X25E,    0X25F,  0X261,   0X25B,

//(6,1-112) (6,4-113) (6,5-114)  (6,6-115) (6,7-116) (6,8-117) (6,9-118)  (6,10-119) (6,11-120) (6,12-121)  (6,13-122) (6,14-123) (6,15-124) (6,16-125) (6,17-126) (6,18-127)
  0X25C,   0X263,   0X0D7,   0X0D8,   0X0D9,  0X0DA,    0X269,   0X0DC,    0X0DD,    0X0DE,     0X0DF,    0X0E0,    0X0E1,    0X0E2,   0X0E3,   0X0E4,

//(6,19-128) (6,20-129) (6,21-130) (6,22-131) (6,23-132) (6,24-133) (6,25-134) (6,26-135) (6,27-136) (6,28-137)  (6,29-138) (6,30-139) (6,31-140) (6,32-141) (6,33-142) (6,34-143)
  0X0E5,    0X268,    0X266,    0X264,    0X265,   0X259,    0X25A,    0X0EC,   0X0ED,    0X0EE,     0X0EF,    0X0F0,    0X0F1,    0X0F2,   0X0F3,    0X0F4,

//(7,0-144)  (7,1-145)  (7,2-146)  (7,3-147) (7,4-148)   (7,5-149)  (7,6-150)  (7,7-151)  (7,8-152)  (7,9-153)   (7,10-154)  (7,11-155) (7,12-156) (7,13-157) (7,14-158) (7,15-159)
 0X0F5,     0X0F6,    0X0F7,    0X0F8,    0X0F9,   0X0FA,    0X0FB,    0X0FC,   0X0FD,    0X0FE,     0X0FF,    0X100,    0X101 ,   0X102,   0X103,    0X104, 

//(7,16-160) (7,25-161) (7,26-162) (7,27-163)  (7,28-164) (7,29-165) (7,30-166) (7,31-167) (7,32-168) (7,33-169)  (7,34-170)  (8,0-171)  (8,1-172)  (8,2-173)  (8,3-174)  (8,4-175)
 0X105,     0X10E,    0X10F,    0X110,    0X111,   0X112,   0X113,    0X114,    0X115,    0X116,     0X117,    0X118,  	0X119,    0X11A,   0X11B,    0X11C,

//(8,5-176)  (8,6-177)   (8,7-178)  (8,8-179)  (8,9-180) (8,10-181) (8,11-182) (8,12-183) (8,13-184) (8,14-185)   (8,15-186) (8,16-187) (8,17-188) (8,18-189) (8,19-190) (8,20-191)
 0X11D,     0X11E,    0X11F,    0X120,    0X121 ,  0X122,   0X123,    0X124,    0X125,    0X126,     0X127,   0X128,  	0X129,    0X12A,   0X12B,    0X12C,

//(8,21-192) (8,22-193)  (8,23-194) (8,24-195) (8,25-196) (10,8-197) (10,9-198) (10,10-199) (10,11-200) (10,12-201) (10,13-202) (10,14-203) (10,15-204) (10,16-205) (10,17-206) (10,18-207)
 0X12D,     0X12E,    0X12F,    0X130,    0X131,    0X166,    0X167,    0X168,    0X169,     0X16A,     0X16B,    0X16C,     0X16D,     0X16E,     0X16F,     0X170, 

//(10,19-208) (10,20-209) (10,21-210) (10,22-211) (10,23-212) (10,24-213)  (10,25-214)  (10,26-215) (10,27-216) (10,28-217)  (10,31-218) (10,32-219) (10,33-220)  (10,34-221) (11,0-222)  (11,1-223)
 0X171,     0X172,     0X173,     0X174,     0X175,     0X176,      0X177,     0X178,  	 0X179,     0X17A,     0X17D,     0X17E,     0X17F,     0X180,    0X181,     0X182,

//(11,2-224)  (11,3-225)  (11,4-226)  (11,5-227)   (11,6-228) (11,7-229)   (11,8-230)   (11,9-231)  (11,10-232) (11,11-233) (11,12-234) (11,13-235) (11,14-236) (11,15-237) (11,16-238)  (11,17-239)
0X183,      0X184,     0X185,     0X186,      0X187,    0X188,  	    0X189,     0X18A,     0X18B,    0X18C,     0X18D,     0X18E,     0X18F,     0X190,    0X191,      0X192,

//(11,18-240) (11,19-241) (11,20-242) (11,21-243)  (11,22-244) (11,26-245) (11,27-246) (11,28-247)  (11,29-248)
0X193,      0X194,      0X195,     0X196,     0X197,    0X19B,      0X19C,     0X19D,      0X19E,
#elif(ICON_SIZE == SIZE_16X22)
  //(É«-0)   (ÎÂ-1)   (×¼-2)     (¶È-3)   (ÏÔ-4)    (Ê¾-5)     (Ä¬-6)    (ÈÏ-7)     (Ïµ-8)     (Í³-9)     (»­-10)    (ÖÊ-11)    (µ÷-12)     (Õû-13)    (Óï-14)   (ÑÔ-15)
  0X063,   0X064,   0X065,   0x066,  0x067,   0X068,	   0X069,   0X06A,    0X06B,   0X06C,    0X06D,    0X06E,    0X06F,    0X070,   0X071,    0X072,

 //(Ñ¡-16)  (Ôñ-17)   (¿ª-18)    (¹Ø-19)  (¶Ô-20)   (±È-21)    (Ë¯-22)   (Ãß-23)    (Ïñ-24)    (¶¨-25)    (Êä-26)    (Èë-27)    (»Ö-28)     (¸´-29)   (ºÍ-30)    (ËÑ-31) 
  0X073,   0X074,   0X075,   0X076,  0X077,   0X078,	   0X079,   0X07A,    0X07B,   0X07C,    0X07D,    0X07E,    0X07F,    0X080,   0X081,    0X082,

 //(Äê-32)  (ÔÂ-33)   (ÈÕ-34)    (·Ö-35)  (Ãë-36)   (ÐÇ-37)    (ÆÚ-38)   (Ò»-39)     (¶þ-40)   (Èý-41)    (ËÄ-42)    (Îå-43)    (Áù-44)    (´ó-45)   (Ä£-46)     (Ê½-47) 
  0X083,   0X084,   0X085,   0X086,  0X087,   0X088,    0X089,  0X08A,     0X08B,   0X08C,    0X08D,   0X08E,    0X08F,    0X090,   0X091,    0X092,

 //(½µ-48)  (Ôë-49)   (Èá-50)    (Öµ-51)  (Ð¡-52)   (¸½-53)    (¼þ-54)   (·­-55)     (×ª-56)    (ÉÏ-57)   (ÏÂ-58)    (×ó-59)    (ÓÒ-60)    (ÖÆ-61)   (Éù-62)     (ÖÃ-63)
  0X093,   0X094,   0X095,   0X096,  0X097,	0X098,    0X099,  0X09A,     0X09B,   0X09C,    0X09D,    0X09E,   0X09F,    0X0A0,   0X0A1,  	 0X0A2,

 //(ºÅ-64)  (ÎÞ-65)   (°é-66)    (Ìå-67)  (Ô´-68)   (×Ö-69)    (Ãæ-70)   (Àö-71)     (´æ-72)    (Ì¨-73)   (ÊÖ-74)    (×Ô-75)    (¶¯-76)    (Î»-77)   (Æµ-78)     (µÀ-79)
  0X0A3,   0X0A4,	  0X0A5,   0X0A6,  0X0A7,   0X0A8,    0X0A9,  0X0AA,     0X0AB,   0X0AC,    0X0AD,    0X0AE,    0X0AF,   0X0B0,   0X0B1,     0X0B2, 

//(¶Î-80)   (±£-81)   (²Ê-82)    (Çå-83)  (Îú-84) 	(¾²-85)    (Òô-86)   (Ê±-87)     (¼ä-88)    (¼ò-89)    (ÖÐ-90)    (ÎÄ-91)    (Ìø-92)    (Ô½-93)  (Í¼-94)      (Ô¤-95)
  0X0B3,   0X0B4,   0X0B5,   0X0B6,  0X0B7,   0X0B8,    0X0B9,  0X0BA,     0X0BB,   0X0BC,    0X0BD,    0X0BE,    0X0BF,    0X0C0,  0X0C1,     0X0C2,

//(Éè-96)   (È·-97)   (ÐÅ-98)    (Á¿-99)  (ÁÁ-100)  (5,25-101) (5,26-102) (5,27-103) (5,28-104) (5,29-105) (5,30-106) (5,31-107)  (5,32-108) (5,33-109) (5,34-110) (6,0-111)
  0X0C3,   0X0C4,   0X0C5,   0X0C6,  0X0C7,   0X0C8,    0X0C9,   0X0CA,    0X0CB,    0X0CC,    0X0CD,    0X0CE,    0X0CF,    0X0D0,    0X0D1,   0X0D2,

//(6,1-112) (6,4-113) (6,5-114)  (6,6-115) (6,7-116) (6,8-117)   (6,9-118) (6,10-119) (6,11-120) (6,12-121)  (6,13-122) (6,14-123) (6,15-124) (6,16-125) (6,17-126) (6,18-127)
  0X0D3,   0X0D6,   0X0D7,   0X0D8,   0X0D9,  0X0DA,     0X0DB,   0X0DC,    0X0DD,    0X0DE,     0X0DF,    0X0E0,    0X0E1,    0X0E2,   0X0E3,   0X0E4,

//(6,19-128) (6,20-129) (6,21-130) (6,22-131) (6,23-132) (6,24-133) (6,25-134) (6,26-135) (6,27-136) (6,28-137)  (6,29-138) (6,30-139) (6,31-140) (6,32-141) (6,33-142) (6,34-143)
  0X0E5,    0X0E6,    0X0E7,    0X0E8,    0X0E9,   0X0EA,    0X0EB,    0X0EC,   0X0ED,    0X0EE,     0X0EF,    0X0F0,    0X0F1,    0X0F2,   0X0F3,    0X0F4,

//(7,0-144)  (7,1-145)  (7,2-146)  (7,3-147) (7,4-148)   (7,5-149)  (7,6-150)  (7,7-151)  (7,8-152)  (7,9-153)   (7,10-154)  (7,11-155) (7,12-156) (7,13-157) (7,14-158) (7,15-159)
 0X0F5,     0X0F6,    0X0F7,    0X0F8,    0X0F9,   0X0FA,    0X0FB,    0X0FC,   0X0FD,    0X0FE,     0X0FF,    0X100,    0X101 ,   0X102,   0X103,    0X104, 

//(7,16-160) (7,25-161) (7,26-162) (7,27-163)  (7,28-164) (7,29-165) (7,30-166) (7,31-167) (7,32-168) (7,33-169)  (7,34-170)  (8,0-171)  (8,1-172)  (8,2-173)  (8,3-174)  (8,4-175)
 0X105,     0X10E,    0X10F,    0X110,    0X111,   0X112,   0X113,    0X114,    0X115,    0X116,     0X117,    0X118,  	0X119,    0X11A,   0X11B,    0X11C,

//(8,5-176)  (8,6-177)   (8,7-178)  (8,8-179)  (8,9-180) (8,10-181) (8,11-182) (8,12-183) (8,13-184) (8,14-185)   (8,15-186) (8,16-187) (8,17-188) (8,18-189) (8,19-190) (8,20-191)
 0X11D,     0X11E,    0X11F,    0X120,    0X121 ,  0X122,   0X123,    0X124,    0X125,    0X126,     0X127,   0X128,  	0X129,    0X12A,   0X12B,    0X12C,

//(8,21-192) (8,22-193)  (8,23-194) (8,24-195) (8,25-196) (10,8-197) (10,9-198) (10,10-199) (10,11-200) (10,12-201) (10,13-202) (10,14-203) (10,15-204) (10,16-205) (10,17-206) (10,18-207)
 0X12D,     0X12E,    0X12F,    0X130,    0X131,    0X166,    0X167,    0X168,    0X169,     0X16A,     0X16B,    0X16C,     0X16D,     0X16E,     0X16F,     0X170, 

//(10,19-208) (10,20-209) (10,21-210) (10,22-211) (10,23-212) (10,24-213)  (10,25-214)  (10,26-215) (10,27-216) (10,28-217)  (10,31-218) (10,32-219) (10,33-220)  (10,34-221) (11,0-222)  (11,1-223)
 0X171,     0X172,     0X173,     0X174,     0X175,     0X176,      0X177,     0X178,  	 0X179,     0X17A,     0X17D,     0X17E,     0X17F,     0X180,    0X181,     0X182,

//(11,2-224)  (11,3-225)  (11,4-226)  (11,5-227)   (11,6-228) (11,7-229)   (11,8-230)   (11,9-231)  (11,10-232) (11,11-233) (11,12-234) (11,13-235) (11,14-236) (11,15-237) (11,16-238)  (11,17-239)
0X183,      0X184,     0X185,     0X186,      0X187,    0X188,  	    0X189,     0X18A,     0X18B,    0X18C,     0X18D,     0X18E,     0X18F,     0X190,    0X191,      0X192,

//(11,18-240) (11,19-241) (11,20-242) (11,21-243)  (11,22-244) (11,26-245) (11,27-246) (11,28-247)  (11,29-248)
0X193,      0X194,      0X195,     0X196,     0X197,    0X19B,      0X19C,     0X19D,      0X19E,
#endif
};


//ATM630A OSD Font Ram MAP:
static UINT CODE  FontRamMap[256] = 
{
#if(ICON_SIZE == SIZE_12X16)
   //0        1       2       3       4       5       6       7       8        9       10       11     12      13      14      15
  0X26A, 0X26B, 0X26C, 0X26D,0X26E, 0X26F, 0X270, 0X271, 0X272, 0X273, 0X274, 0X275, 0X276, 0X277, 0X278, 0X279, 
#elif(ICON_SIZE == SIZE_16X22)
  // --- 0 ~ 15 ---
  0X1C0, 0X1C1, 0X1C2, 0X1C3, 0X1C4, 0X1C5, 0X1C6, 0X1C7, 0X1C8, 0X1C9, 0X1CA, 0X1CB, 0X1CC, 0X1CD, 0X1CE, 0X1CF, 
  // --- 16 ~ 31 ---
  0X1D0, 0X1D1, 0X1D2, 0X1D3, 0X1D4, 0X1D5, 0X1D6, 0X1D7, 0X1D8, 0X1D9, 0X1DA, 0X1DB, 0X1DC, 0X1DD, 0X1DE, 0X1DF, 
  // --- 32 ~ 47 ---
  0X1E0, 0X1E1, 0X1E2, 0X1E3, 0X1E4, 0X1E5, 0X1E6, 0X1E7, 0X1E8, 0X1E9, 0X1EA, 0X1EB, 0X1EC, 0X1ED, 0X1EE, 0X1EF, 
  // --- 48 ~ 63 ---
  0X1F0, 0X1F1, 0X1F2, 0X1F3, 0X1F4, 0X1F5, 0X1F6, 0X1F7, 0X1F8, 0X1F9, 0X1FA, 0X1FB, 0X1FC, 0X1FD, 0X1FE, 0X1FF, 
  // --- 64 ~ 79 ---
  0X200, 0X201, 0X202, 0X203, 0X204, 0X205, 0X206, 0X207, 0X208, 0X209, 0X20A, 0X20B, 0X20C, 0X20D, 0X20E, 0X20F, 
  // --- 80 ~ 95 ---
  0X210, 0X211, 0X212, 0X213, 0X214, 0X215, 0X216, 0X217, 0X218, 0X219, 0X21A, 0X21B, 0X21C, 0X21D, 0X21E, 0X21F, 
  // --- 96 ~ 111 (接着原来的 0x223 继续) ---
  0X220, 0X221, 0X222, 0X223, 0X224, 0X225, 0X226, 0X227, 0X228, 0X229, 0X22A, 0X22B, 0X22C, 0X22D, 0X22E, 0X22F, 
  // --- 112 ~ 127 ---
  0X230, 0X231, 0X232, 0X233, 0X234, 0X235, 0X236, 0X237, 0X238, 0X239, 0X23A, 0X23B, 0X23C, 0X23D, 0X23E, 0X23F,
  // --- 128 ~ 143 ---
  0X240, 0X241, 0X242, 0X243, 0X244, 0X245, 0X246, 0X247, 0X248, 0X249, 0X24A, 0X24B, 0X24C, 0X24D, 0X24E, 0X24F,
  // --- 144 ~ 159 ---
  0X250, 0X251, 0X252, 0X253, 0X254, 0X255, 0X256, 0X257, 0X258, 0X259, 0X25A, 0X25B, 0X25C, 0X25D, 0X25E, 0X25F,
  // --- 160 ~ 175 ---
  0X260, 0X261, 0X262, 0X263, 0X264, 0X265, 0X266, 0X267, 0X268, 0X269, 0X26A, 0X26B, 0X26C, 0X26D, 0X26E, 0X26F,
  // --- 176 ~ 191 ---
  0X270, 0X271, 0X272, 0X273, 0X274, 0X275, 0X276, 0X277, 0X278, 0X279, 0X27A, 0X27B, 0X27C, 0X27D, 0X27E, 0X27F,
  // --- 192 ~ 207 (实际上只用到 199, 即 0x287) ---
  0X280, 0X281, 0X282, 0X283, 0X284, 0X285, 0X286, 0X287, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
#endif
};
code UCHAR BigNum_Table[10][6] = {
// 数字 0 (0x24 - 0x29)
    {0x24, 0x25, 0x26, 0x27, 0x28, 0x29},

    // 数字 1 (0x2A - 0x2F)
    {0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F},

    // 数字 2 (0x30 - 0x35)
    {0x30, 0x31, 0x32, 0x33, 0x34, 0x35},

    // 数字 3 (0x36 - 0x3B)
    {0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B},

    // 数字 4 (0x3C - 0x41)
    {0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41},

    // 数字 5 (0x42 - 0x47)
    {0x42, 0x43, 0x44, 0x45, 0x46, 0x47},

    // 数字 6 (0x48 - 0x4D)
    {0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D},

    // 数字 7 (0x4E - 0x53)
    {0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53},

    // 数字 8 (0x54 - 0x59)
    {0x54, 0x55, 0x56, 0x57, 0x58, 0x59},

    // 数字 9 (0x5A - 0x5F)
    {0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F}
};
code UCHAR Radar_Wave_Table_Correct[8][4] = {
// Front 3 (Far) -> 原0x6E -> 现0x61
    {0x61, 0x63, 0x65, 0x67},
    
    // Front 2 (Mid) -> 原0x76 -> 现0x69
    {0x69, 0x6B, 0x6D, 0x6F},
    
    // Front 1 (Near) -> 原0x7E -> 现0x71
    {0x71, 0x73, 0x75, 0x77},

    // Rear 1 (Near) -> 原0x86 -> 现0x79
    {0x79, 0x7B, 0x7D, 0x7F},
    
    // Rear 2 (Mid) -> 原0x8E -> 现0x81
    {0x81, 0x83, 0x85, 0x87},
    
    // Rear 3 (Far) -> 原0x96 -> 现0x89
    {0x89, 0x8B, 0x8D, 0x8F}
};
//===================================ÒÔÏÂÊÇºÍOSD BLOCK ÎÞ¹ØµÄ============================
void OsdCofigPalette(void)
{
	ICON_CR1_L = RedColor&0xff;	
	ICON_CR1_H = RedColor>>8;	
	ICON_CR2_L = GreenColor&0xff;	
	ICON_CR2_H = GreenColor>>8;	
	ICON_CR3_L = CyanColor&0xff;	
	ICON_CR3_H = CyanColor>>8;	
	ICON_CR4_L = YellowColor&0xff;	
	ICON_CR4_H = YellowColor>>8;	
	ICON_CR5_L = GrayColor&0xff;	
	ICON_CR5_H = GrayColor>>8;
	ICON_CR6_L = WhiteColor&0xff;	
	ICON_CR6_H = WhiteColor>>8;
}

//ÅäÖÃÎ»Í¼µ÷É«°å
void OsdConfigBitmapPalette(UCHAR *paletColor)     
{
	UCHAR XDATA i=0;
	
	for(i=0;i<16;i++)
	{
		XBYTE[0xFB36+2*i] = paletColor[2*i+1];
		XBYTE[0xFB36+2*i+1] = paletColor[2*i];
	}
}


UINT OsdConfigBlockIndexStarAddr(UCHAR blockId,UINT starAddr)
{
	 if(blockId == 1)
	 {
		  INDEXRAM_ADD_BK1_START = (UCHAR)(starAddr&0xff);
		  OSD_POS_XY_H_BK1 &= (~_BIT7);
		  OSD_POS_XY_H_BK1 |= (UCHAR)((starAddr>>8)&0xff)<< 7; 
	 }
	 if(blockId == 2)
	 {
         INDEXRAM_ADD_BK2_START = (UCHAR)(starAddr&0xff);
		 OSD_POS_XY_H_BK2 &= (~_BIT7);
		 OSD_POS_XY_H_BK2 |= (UCHAR)((starAddr>>8)&0xff)<< 7;
	 }
	 if(blockId == 3)
	 {
         INDEXRAM_ADD_BK3_START = (UCHAR)(starAddr&0xff);
		 OSD_POS_XY_H_BK3 &= (~_BIT7);
		 OSD_POS_XY_H_BK3 |= (UCHAR)((starAddr>>8)&0xff)<< 7;
	 }
	 if(blockId == 4)
	 {
         INDEXRAM_ADD_BK4_START = (UCHAR)(starAddr&0xff);
		 OSD_POS_XY_H_BK4 &= (~_BIT7);
		 OSD_POS_XY_H_BK4 |= (UCHAR)((starAddr>>8)&0xff)<< 7;
	 }  
	 return starAddr;
}


UINT OsdGetStartIndexAddr(void)
{
     UINT XDATA starAddr = 0;
	 
	 if(g_ucCurOsdBlockId == 1)
	 {
	      starAddr = (OSD_POS_XY_H_BK1 & _BIT7)>>7;
		  starAddr<<=8;
		  starAddr|=INDEXRAM_ADD_BK1_START;
	 }
	 if(g_ucCurOsdBlockId == 2)
	 {
		  starAddr = (OSD_POS_XY_H_BK2 & _BIT7)>>7;
		  starAddr<<=8;
		  starAddr|=INDEXRAM_ADD_BK2_START;
	 }
	 if(g_ucCurOsdBlockId == 3)
	 {
	      starAddr = (OSD_POS_XY_H_BK3 & _BIT7)>>7;		  
		  starAddr<<=8;
		  starAddr|=INDEXRAM_ADD_BK3_START;
	 }
	 if(g_ucCurOsdBlockId == 4)
	 {
	      starAddr = (OSD_POS_XY_H_BK4 & _BIT7)>>7;
		  starAddr<<=8;
		  starAddr|=INDEXRAM_ADD_BK4_START;
	 }  
	 //printf("block start index addr = %x", starAddr);
	 return starAddr;
}


//ÉèÖÃOSD Block´°¿Ú´óÐ¡  ¿é´óÐ¡
void OsdConfigWndSize(BYTE width, BYTE height)
{
     //printfStr("OsdConfigWndSize");
     if(g_ucCurOsdBlockId == 0)
	 {
	      OSD_SIZE_X_BK0 = width;
		  OSD_SIZE_Y_BK0 = height;
	 }
     if(g_ucCurOsdBlockId == 1)
	 {
	      OSD_SIZE_X_BK1 = width;
		  OSD_SIZE_Y_BK1 = height;
	 }
	 if(g_ucCurOsdBlockId == 2)
	 {
	      OSD_SIZE_X_BK2 = width;
		  OSD_SIZE_Y_BK2 = height;
	 }
	 if(g_ucCurOsdBlockId == 3)
	 {
	      OSD_SIZE_X_BK3 = width;
		  OSD_SIZE_Y_BK3 = height;
	 }
	 if(g_ucCurOsdBlockId == 4)
	 {
	      OSD_SIZE_X_BK4 = width;
		  OSD_SIZE_Y_BK4 = height;
	 }  
}

UINT OsdGetWndWidth(void)
{	 
     if(g_ucCurOsdBlockId == 0)
	 {
		  return OSD_SIZE_X_BK0; 
	 }
     if(g_ucCurOsdBlockId == 1)
	 {
	      return OSD_SIZE_X_BK1; 
	 }
	 if(g_ucCurOsdBlockId == 2)
	 {
	      return OSD_SIZE_X_BK2; 
	 }
	 if(g_ucCurOsdBlockId == 3)
	 {
	      return OSD_SIZE_X_BK3; 
	 }
	 if(g_ucCurOsdBlockId == 4)
	 {
	      return OSD_SIZE_X_BK4; 
	 }  
	 return 0;
}


UINT OsdGetBlockSize(void)
{
     UINT XDATA wcOsdWndSize = 0;

     if(g_ucCurOsdBlockId == 0)
	 {    
		  wcOsdWndSize =  g_OsdContrller.block0Size; 
	 }
     if(g_ucCurOsdBlockId == 1)
	 {
	      wcOsdWndSize =  g_OsdContrller.block1Size; 
	 }
	 if(g_ucCurOsdBlockId == 2)
	 {
	      wcOsdWndSize =  g_OsdContrller.block2Size; 
	 }
	 if(g_ucCurOsdBlockId == 3)
	 {
	      wcOsdWndSize =  g_OsdContrller.block3Size; 
	 }
	 if(g_ucCurOsdBlockId == 4)
	 {
	      wcOsdWndSize =  g_OsdContrller.block4Size; 
	 }  

	 return wcOsdWndSize;
}

//====================================================================================//
void OsdBlockShow(UCHAR ucOsdBlockId)
{
    // printf("OsdBlockShow = %x",ucOsdBlockId);
    OSD_1CON |= (0x01 << ucOsdBlockId);
}


void OsdBlockHide(UCHAR ucOsdBlockId)
{
    //printf("OsdBlockHide = %x",ucOsdBlockId);
    OSD_1CON &= (~(0x01 << ucOsdBlockId));
}

void OsdHide(void)
{
    //printfStr("OsdHide");
	OSD_1CON &= 0xe1;
}


void OsdBlockEnable(UCHAR ucOsdBlockId)
{
    g_ucCurOsdBlockId = ucOsdBlockId;
}

void OsdIconSize(UCHAR Size_X,UCHAR Size_Y)
{
    CHAR_SIZE_X=Size_X;
	CHAR_SIZE_Y=Size_Y;
}

void OsdClear(void)
{	  
#define FONTROM_SIZE  418

	UINT XDATA indexAddr;
	
	for(indexAddr = 0; indexAddr < FONTROM_SIZE; indexAddr++)
	{
		INDEX_RAM_ADD_H=(indexAddr>>8);
		INDEX_RAM_ADD_L=(indexAddr&0XFF);

		INDEX_RAM_DATA_H=0;
		INDEX_RAM_DATA_L = 0;
	}
}

void OsdBlockClear(UCHAR ucOsdBlockId)
{
    UINT XDATA wcIndexAddr = 0;
    UINT XDATA wcWinSize = 0;
    UINT XDATA EndAddr = 0;
    UINT XDATA curAddr = wcIndexAddr;
    OsdBlockEnable(ucOsdBlockId);
    wcIndexAddr = OsdGetStartIndexAddr();
    wcWinSize = 2048; 
    EndAddr = wcIndexAddr + wcWinSize;
     
    
    for(; curAddr < EndAddr; curAddr++)
    {   
        INDEX_RAM_ADD_H = (curAddr >> 8);
        INDEX_RAM_ADD_L = (curAddr & 0xff);

        INDEX_RAM_DATA_H = 0;
        INDEX_RAM_DATA_L = 0;
    }

    curAddr = wcIndexAddr; 
    
    for(; curAddr < EndAddr; curAddr++)
    {
        INDEX_RAM_ADD_H = (curAddr >> 8);
        INDEX_RAM_ADD_L = (curAddr & 0xff);
        
        EACH_ICON_COLOR = 0x00; 
    }
}


void OsdWndClear(UCHAR starRow,UCHAR starLine,UCHAR endRow,UCHAR endLine)
{
     UINT XDATA wcStartIndexAddr;
	 UINT XDATA ucIndexOffset;
	 UCHAR XDATA xIndex,yIndex;
 
	 for(yIndex=starRow;yIndex<=(starRow+(endRow-starRow));yIndex++)
	 {
	     wcStartIndexAddr = OsdGetStartIndexAddr();
         ucIndexOffset = (OsdGetWndWidth()*yIndex)+starLine;  //row ÐÐ   line ÁÐ
	     wcStartIndexAddr = wcStartIndexAddr + ucIndexOffset;
		 
		 INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
		 INDEX_RAM_ADD_L = (wcStartIndexAddr&0xff);
		 
		for(xIndex=starLine; xIndex<=(starLine+(endLine-starLine)); xIndex++,wcStartIndexAddr++)
		{
		    INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
			INDEX_RAM_DATA_H = 0;
			INDEX_RAM_DATA_L = 0;
		}
	 }

 }


void OsdConfigAlpha(UCHAR enFlg,UCHAR mode,UCHAR alphaLev)
{
#define Enable  1
#define OsdBlending     0
#define OsdBackBlending 1
	if(enFlg == Enable)
	{
		OSD_2CON |= (_BIT6);
		if(mode == OsdBlending)
		{
			OSD_2CON |= (_BIT7); //osd blending 
		}
		else
		{
			OSD_2CON &= (~_BIT7); //osd back blending
		}
		OSD_alpha_bright = ((OSD_alpha_bright&0xF8)|(alphaLev));	
	}
	else
	{
		OSD_2CON &= (~_BIT6);
	}
}


void OsdConfigBright(UCHAR brightLev)
{
     OSD_alpha_bright = ((OSD_alpha_bright&0x1f)|(brightLev<<5));	
}

void OsdConfigDispMode(UCHAR dispMode,UCHAR  mirrorMode)
{
      OSD_1CON &= (~_BIT6);
      if(dispMode == OSD_BITMAP_MODE)
      {
           OSD_1CON |= _BIT7;
      }
	  else
	  {
	       OSD_1CON &= (~_BIT7);
	  }
	  switch(mirrorMode)
	  {
	     case OSD_DISP_NORMAL:
		      OSD_MIRROR_SET &= ~(_BIT4|_BIT5|_BIT6|_BIT7);
			  break;
			 
		 case OSD_DISP_H_MIRROR:
		      OSD_MIRROR_SET &= ~(_BIT6|_BIT7);
			  OSD_MIRROR_SET |=(_BIT4|_BIT5);
			  break;
			 
		 case OSD_DISP_V_MIRROR:
		      OSD_MIRROR_SET &= ~(_BIT4|_BIT5);
			  OSD_MIRROR_SET |=(_BIT6|_BIT7);
			  break;
			 
		 case OSD_DISP_HV_MIRROR:
		      OSD_MIRROR_SET |= (_BIT4|_BIT5|_BIT6|_BIT7);
			  break;
			 
	       default:
		   	  break;
	  }
}


// ÅäÖÃÏÔÊ¾¿éµÄÑÕÉ«
void OsdConfigBlockColor(UCHAR fbColor)
{
	UINT XDATA wcIndexAddr = 0;
	UINT XDATA wcWinSize = 0;

	wcIndexAddr = OsdGetStartIndexAddr();
	wcWinSize = OsdGetBlockSize();
	wcWinSize += wcIndexAddr;

	INDEX_RAM_ADD_H =(wcIndexAddr>>8);
	INDEX_RAM_ADD_L = (wcIndexAddr&0xff);	 
	
	for(;wcIndexAddr<wcWinSize;wcIndexAddr++)
	{   	
	    INDEX_RAM_ADD_H =(wcIndexAddr>>8);
		EACH_ICON_COLOR = fbColor; 
	}
 }


//ÉèÖÃ¿éµÄÎ»ÖÃ ¸ü¾ß·Ö±æÂÊ²»Í¬ÓÐËù²»Í¬
void OsdConfigWndPosition(UINT xPos, UINT yPos)
{  
    //printfStr("OsdConfigWndPosition");
	
	if(g_ucCurOsdBlockId == 0)
	{
		OSD_POS_X_L_BK0 = xPos%256;
		OSD_POS_Y_L_BK0 = yPos%256;
		OSD_POS_XY_H_BK0 &= 0x88; 
		OSD_POS_XY_H_BK0  |= ((xPos >> 8) & 0x07)|(((yPos >> 8) & 0x07) << 4);
	}
	if(g_ucCurOsdBlockId == 1)
	{
        OSD_POS_X_L_BK1 = xPos%256;
		OSD_POS_Y_L_BK1 = yPos%256;
		OSD_POS_XY_H_BK1 &= 0x88;
		OSD_POS_XY_H_BK1  |= ((xPos >> 8) & 0x07)|(((yPos >> 8) & 0x07) << 4);
	}
	if(g_ucCurOsdBlockId == 2)
	{
        OSD_POS_X_L_BK2 = xPos%256;
		OSD_POS_Y_L_BK2 = yPos%256;
		OSD_POS_XY_H_BK2 &= 0x88; 
	    OSD_POS_XY_H_BK2  |= ((xPos >> 8) & 0x07)|(((yPos >> 8) & 0x07) << 4);
	}
	if(g_ucCurOsdBlockId == 3)
	{
        OSD_POS_X_L_BK3 = xPos%256;
		OSD_POS_Y_L_BK3 = yPos%256;
		OSD_POS_XY_H_BK3 &= 0x88; 
		OSD_POS_XY_H_BK3  |= ((xPos >> 8) & 0x07)|(((yPos >> 8) & 0x07) << 4);
	}
	if(g_ucCurOsdBlockId == 4)
	{
        OSD_POS_X_L_BK4 = xPos%256;
		OSD_POS_Y_L_BK4 = yPos%256;
		OSD_POS_XY_H_BK4 &= 0x88; 
		OSD_POS_XY_H_BK4  |= ((xPos >> 8) & 0x07)|(((yPos >> 8) & 0x07) << 4);
	}  
}

void Draw_Big_Number(UCHAR startRow, UCHAR startLine, UCHAR num,UCHAR color)
{
    UCHAR r, c;
    UINT wcStartIndexAddr;
    UINT rowAddr;
    UCHAR wndWidth;
    UINT charData;
    UCHAR tileIndex; 
    if(num > 9) return;

    wndWidth = OsdGetWndWidth();
    wcStartIndexAddr = OsdGetStartIndexAddr();
    wcStartIndexAddr = wcStartIndexAddr + (startRow * wndWidth) + startLine;
    for(r = 0; r < 3; r++)
    {
        rowAddr = wcStartIndexAddr + (r * wndWidth);
        INDEX_RAM_ADD_H = (rowAddr >> 8);
        INDEX_RAM_ADD_L = (rowAddr & 0xff);
        for(c = 0; c < 2; c++)
        {
            tileIndex = BigNum_Table[num][r*2 + c];
            charData = FontRamMap[tileIndex];
            //charData = (UINT)tileIndex; // <--- 直接用索引当地址 (0x000 + Index)
            INDEX_RAM_DATA_H = charData >> 8;
            INDEX_RAM_DATA_L = charData & 0xff;
        }
        INDEX_RAM_ADD_H = (rowAddr >> 8);
        INDEX_RAM_ADD_L = (rowAddr & 0xff);
        
        for(c = 0; c < 2; c++)
        {
            EACH_ICON_COLOR = color; 
        }
    }
}
void Draw_Big_Dot(UCHAR startRow, UCHAR startLine,UCHAR color)
{   
		UINT wcStartIndexAddr;
    UINT rowAddr;
    UCHAR wndWidth;
    UINT charData;
    UCHAR tileIndex; 	
		wndWidth = OsdGetWndWidth();
    wcStartIndexAddr = OsdGetStartIndexAddr();
    wcStartIndexAddr = wcStartIndexAddr + (startRow * wndWidth) + startLine;
		charData = FontRamMap[0x60];
		INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
    INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);
	//charData = (UINT)tileIndex; // <--- 直接用索引当地址 (0x000 + Index)
		INDEX_RAM_DATA_H = charData >> 8;
		INDEX_RAM_DATA_L = charData & 0xff;
			
		INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
    INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);
		
		EACH_ICON_COLOR = color; 
}
void Draw_Radar_Segment(UCHAR row_idx, UCHAR seg_idx, UCHAR color, UCHAR screen_row, UCHAR screen_col_start)
{
    UCHAR i;
    UINT wcStartIndexAddr;
    UCHAR wndWidth;
    UINT charData;
    UCHAR tileIndex;      // 当前字的逻辑索引
    UCHAR tileIndex_Base; // 当前段的起始索引
    UCHAR current_col;

    // 安全检查
    if(row_idx > 7 || seg_idx > 3) return;

    wndWidth = OsdGetWndWidth();
    wcStartIndexAddr = OsdGetStartIndexAddr();

    // 1. 获取基准字库索引 (从我们定义的二维数组里取)
    tileIndex_Base = Radar_Wave_Table_Correct[row_idx][seg_idx];

    // 2. 计算屏幕列位置 (每个段占2列)
    current_col = screen_col_start + (seg_idx * 2);

    // 3. 计算显存起始地址
    wcStartIndexAddr = wcStartIndexAddr + (screen_row * wndWidth) + current_col;

    // 4. 设置写地址 (写数据)
    INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
    INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);

    // --- 循环写 2 个 Tile 的数据 ---
    for(i = 0; i < 2; i++)
    {
        if(color == 0) 
        {
            // 如果颜色是0，直接写空数据清屏，不需要查表
            charData = 0x00; 
        }
        else
        {
            // 1. 计算当前块的逻辑索引 (基准 + 偏移)
            tileIndex = tileIndex_Base + i;
            
            // 2. 【关键修改】这里加上了 FontRamMap 查表！
            // 严格仿照 Draw_Big_Number 的写法
            charData = FontRamMap[tileIndex]; 
        }

        // 写入数据
        INDEX_RAM_DATA_H = charData >> 8;
        INDEX_RAM_DATA_L = charData & 0xff;
    }

    // 5. 重新设置地址 (因为写完Data地址会自动后移，写Color需要拉回来)
    INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
    INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);

    // --- 循环写 2 个 Tile 的颜色 ---
    for(i = 0; i < 2; i++)
    {
        // 写颜色属性
        EACH_ICON_COLOR = color; 
    }
}
// =========================================================================
// 新增: 暴力擦除半个屏幕 (0=左半屏, 1=右半屏)
// 左屏范围: 0-17列, 右屏范围: 18-35列
// =========================================================================
void Clear_Half_Screen(UCHAR half,UCHAR color)
{
    UCHAR r, c;
    UCHAR c_start, c_end;
    UINT wcStartIndexAddr;
    UCHAR wndWidth = OsdGetWndWidth();
    UINT startAddr = OsdGetStartIndexAddr();

    // 1. 界定范围
    if(half == 0) // 左半边
    {
        c_start = 0; c_end = 15; // 建议改成17，防止中间有缝隙
    }
    else // 右半边
    {
        c_start = 16; c_end = 32;
    }

    // 2. 循环填充红色
    for(r = 0; r < 17; r++)
    {
        wcStartIndexAddr = startAddr + (r * wndWidth) + c_start;
        
        for(c = c_start; c <= c_end; c++)
        {
            // --- 第一步：写字库索引 (形状) ---
            INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
            INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);

            // 【关键】这里不能写 0x00！0x00是透明的！
            // 你需要填入一个“实心方块”的字库索引。
            // 如果你没有，暂时填 0x61 (波纹) 试试效果，之后在字库里加一个全0xFF的字。
	        INDEX_RAM_DATA_H = FontRamMap[0x91] >> 8;  
					INDEX_RAM_DATA_L = FontRamMap[0x91] & 0xff; 

            // --- 第二步：写颜色属性 (红色) ---
            // 写完数据后地址会自动+1，所以必须重新把地址拉回来！
            INDEX_RAM_ADD_H = (wcStartIndexAddr >> 8);
            INDEX_RAM_ADD_L = (wcStartIndexAddr & 0xff);
            
            EACH_ICON_COLOR = color; // 0x01 = 红色 (COL_RED)

            // 地址自增准备画下一个
            wcStartIndexAddr++; 
        }
    }
}
void OsdDrawStr(UCHAR starRow,UCHAR starLine,UCHAR fbColor, UCHAR *str)
{
     UINT XDATA wcStartIndexAddr;
	 UINT XDATA wcColorStartIndexAddr;
	 UINT XDATA ucIndexOffset;

	 if(str == NULL)
	 {
	     return;
	 }
	 
     wcStartIndexAddr = OsdGetStartIndexAddr();
     ucIndexOffset = (OsdGetWndWidth()*starRow)+starLine;
	 wcStartIndexAddr = wcStartIndexAddr + ucIndexOffset;
	 wcColorStartIndexAddr = wcStartIndexAddr;

     INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
     INDEX_RAM_ADD_L = (wcStartIndexAddr&0xff);

	 //printf("draw str addr = %x", wcStartIndexAddr);

#define strOffset  starRow
#define DrawNum    starLine
#define ColorIndex ucIndexOffset

#define ASIAN      '#'
#define FONTRAM    '&'

     strOffset = 0;
 	 DrawNum = 0;

	 while(str[strOffset] != '\0')
	 { 
	    INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
	    if(str[strOffset] == ASIAN)//ÑÇÖÞÎÄ×Ö
	    {   
		   	strOffset++;
	        INDEX_RAM_DATA_H = AsianMap[str[strOffset]] >> 8;  
			INDEX_RAM_DATA_L = AsianMap[str[strOffset]] & 0xff; 
		   
            //printf("str[strOffset] = %x", str[strOffset]);
			//printf("AsianMap[str[strOffset]] = %x", AsianMap[str[strOffset]]);

	    }
		else if(str[strOffset] == FONTRAM) //Font Ram ¶¯Ì¬ÔØÈë
		{   
	    
		   	strOffset++;
	        INDEX_RAM_DATA_H = FontRamMap[str[strOffset]] >> 8;  
			INDEX_RAM_DATA_L = FontRamMap[str[strOffset]] & 0xff; 
		   
        printf("str[strOffset] = %x", str[strOffset]);
			  printf("FontRamMap[str[strOffset]] = %x", FontRamMap[str[strOffset]]);

	    }
	 	else//×ÖÄ¸±í
	 	{
	 	    INDEX_RAM_DATA_H = ASCIIMap[str[strOffset]] >> 8;
			INDEX_RAM_DATA_L = ASCIIMap[str[strOffset]] & 0xff;

            //printf("str[strOffset] = %x", str[strOffset]);
			//printf("ASCIIMap[str[strOffset]] = %x", ASCIIMap[str[strOffset]]);
			
	 	}
		wcStartIndexAddr++;
		strOffset++;
		DrawNum++;
	 }	 

	 INDEX_RAM_ADD_H =(wcColorStartIndexAddr>>8);
     INDEX_RAM_ADD_L = (wcColorStartIndexAddr&0xff);

	 while(DrawNum)
	 {
	      INDEX_RAM_ADD_H =(wcColorStartIndexAddr>>8);
	      EACH_ICON_COLOR = fbColor;
		  DrawNum--;
		  wcColorStartIndexAddr++;
	 }
}


void OsdDrawIcon(UCHAR starRow,UCHAR starLine,UCHAR xSize,UCHAR ySize,UCHAR BackColor,UINT *pIconStr)
{

	 UINT XDATA wcStartIndexAddr;
	 UINT XDATA ucIndexOffset;
	 UCHAR XDATA xIndex,yIndex;
     UINT  XDATA IconIndex;

	 if(pIconStr == NULL)
	 {
	     return;
	 }

	 if(BackColor == TRANSPARENCE)
	 {
	     OSD_MIRROR_SET &= (~_BIT6);
	 }
	 else
	 {
	     OSD_MIRROR_SET |= (_BIT6);
		 switch(BackColor)
		 {
		     case RED:
				 XBYTE[0xFBC6] = RedColor&0xff;	
				 XBYTE[0xFBC7] = RedColor>>8;	
	             break;
				 
		     case GREEN:
				 XBYTE[0xFBC6] = GreenColor&0xff;	
				 XBYTE[0xFBC7] = GreenColor>>8;	
			 	 break;

		     case CYAN:	
			 	 XBYTE[0xFBC6] = CyanColor&0xff;	
	             XBYTE[0xFBC7] = CyanColor>>8;
			 	 break;

			 case YELLOW:
			 	 XBYTE[0xFBC6] = YellowColor&0xff;	
	             XBYTE[0xFBC7] = YellowColor>>8;	
			 	 break;

	         case GRAY:	 
			 	 XBYTE[0xFBC6] = GrayColor&0xff;	
	             XBYTE[0xFBC7] = GrayColor>>8;	   
			 	 break;

			 case WHITE:
			 	 XBYTE[0xFBC6] = WhiteColor&0xff;	
	             XBYTE[0xFBC7] = WhiteColor>>8;
				 break;
	
		 }
	
	 }

	 for(yIndex=starRow;yIndex<(starRow+ySize);yIndex++)
	 {
	     wcStartIndexAddr = OsdGetStartIndexAddr();
         ucIndexOffset = (OsdGetWndWidth()*yIndex)+starLine;  //row ÐÐ   line ÁÐ
	     wcStartIndexAddr = wcStartIndexAddr + ucIndexOffset;
		 //printf("wcStartIndexAddr = %x", wcStartIndexAddr);
		 INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
		 INDEX_RAM_ADD_L = (wcStartIndexAddr&0xff);
		 
		for(xIndex=starLine; xIndex<(starLine+xSize); xIndex++,wcStartIndexAddr)
		{
		    IconIndex = *pIconStr;
		    INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);	
			INDEX_RAM_DATA_H = IconIndex >> 8;
			INDEX_RAM_DATA_L = IconIndex & 0xff;
			pIconStr++;
		}
	 }
	//printfStr("OsdDrawIcon");
}


void DMALoadFontRam(ULONG SrcAddr,UINT DstAddr,UINT numOper)
{	
    EA=OFF; 
    while(!(IDLE_DF&0x80));
	CTRL_DE = FLASH_INT_EN;	
	STATUS_DD = 0;	
	MCU_CFG_REG   |= 0X08;//font ram	
    FADDR_REG0_D6 = (UCHAR)SrcAddr;
    FADDR_REG1_D7 = (UCHAR)(SrcAddr>>8);
    FADDR_REG2_D8 = (UCHAR)(SrcAddr>>16);
    DADDR_REG0_D9 = (UCHAR)DstAddr;
    DADDR_REG1_DA = (UCHAR)(DstAddr/256);
    LOAD_LENGTH0_DB = (numOper-1)&0xff;             
    LOAD_LENGTH1_DC = ((numOper-1)>>8)&0xff;  	  
    INSTR_D0 = 0x40;
	while(!(STATUS_DD&0x40));
	while(!(IDLE_DF&0x80));	
	MCU_CFG_REG  &= (~0X08);
	EA=ON;
	
}


void OsdWriteCharToFontram(BYTE indexAddr, UCHAR *pCharData)
{
    UCHAR XDATA i;
    UCHAR XDATA IconSize;
	UCHAR XDATA Size_X,Size_Y;
	
	if(pCharData == NULL)
	{
	     return;
	}

    Size_X=CHAR_SIZE_X;
	Size_Y=CHAR_SIZE_Y;

	if(Size_X <= 16)
	{
	  IconSize=Size_Y;	
	}
	else if((Size_Y%2)==0)
	{
	  IconSize=(3*Size_Y)/2;
	}
	else
	{
      IconSize=(3*Size_Y)/2+1;
	}
	
    FONT_RAM_ADD_L = (UCHAR)((IconSize*(indexAddr))&0XFF);

	for(i=0;i<IconSize;i++)
    {
        FONT_RAM_ADD_H = ( IconSize*indexAddr+i)>>8; ; 
	    FONT_RAM_DATA_H= *(pCharData+2*i);
        FONT_RAM_DATA_L = *(pCharData+2*i+1);
    }
}



void LoadMulCharToFontram(UINT indexAddr, UCHAR Size, UCHAR *pCharData)
{   
    UCHAR XDATA i, j;
    UCHAR XDATA IconSize;
    UCHAR XDATA Size_X, Size_Y;
    UINT  XDATA AbsoluteAddr;
	
    if(pCharData == NULL) return;

    Size_X = 16;
    Size_Y = 22;

    if(Size_X <= 16) IconSize = Size_Y;	
    else if((Size_Y%2)==0) IconSize = (3*Size_Y)/2;
    else IconSize = (3*Size_Y)/2+1;
    
    AbsoluteAddr = (UINT)indexAddr * IconSize;

    printf("Write: Idx=%x\n", indexAddr); 
		 printf(" AbsAddr=%x\n", AbsoluteAddr); 
    
    // 写低位 (只写一次)
    FONT_RAM_ADD_L = (UCHAR)(AbsoluteAddr & 0xFF);

    for(i = 0; i < Size; i++)
    {
        for(j = 0; j < IconSize; j++)
        {
            FONT_RAM_ADD_H = (AbsoluteAddr + j) >> 8; 
            
            FONT_RAM_DATA_H = *(pCharData + 2*j);
            FONT_RAM_DATA_L = *(pCharData + 2*j + 1);
        }
        pCharData += 2 * IconSize;
        AbsoluteAddr += IconSize; 
    }
}


void LoadBitMapToFontRam(UCHAR indexAddr,UCHAR BitMapSize,UCHAR *pBitMapData)
{
    UCHAR XDATA i,FontRamSize;
    UINT BitMap_Size,Size_X,Size_Y,Ramdata;
   
	if(pBitMapData == NULL)
	{
	     return;
	}
     Size_X=CHAR_SIZE_X;
	 Size_Y=CHAR_SIZE_Y;
	 
	 if((Size_X%4)==0)//4
	 {
	    BitMap_Size=(Size_X*Size_Y)/2;
	 }
	 else if((Size_X%4)==2)//4
	 {
	    BitMap_Size=(Size_X/2+1)*Size_Y;
	 }
	 else
	 {
	    BitMap_Size=(Size_X/2+2)*Size_Y;
	 }
	 if(Size_X <= 16)
	 {
	 	FontRamSize=Size_Y;
	 }
	 else
	 {
	   	FontRamSize=2*Size_Y;
	 }
	 	
	FONT_RAM_ADD_L = (UCHAR)((FontRamSize*indexAddr)&0XFF); 		    
	for(i=0;i<BitMapSize;i++)
    {
        for(Ramdata=0;Ramdata<(BitMap_Size/2);Ramdata++)
		{   
		    FONT_RAM_ADD_H = ((UINT)((BitMap_Size/2)*i)+FontRamSize*indexAddr+Ramdata)>>8;
			FONT_RAM_DATA_H = *(pBitMapData+2*Ramdata);
			FONT_RAM_DATA_L = *(pBitMapData+2*Ramdata+1);	
		} 
        pBitMapData += BitMap_Size;
    }	
}


void OsdDrawNum(UCHAR starRow,UCHAR starLine,UCHAR fbColor,SWORD value)
{
#define Len    4
	 UCHAR CODE DatBuf[] = {'0','1','2','3','4','5','6','7','8','9'};
	 UCHAR XDATA DispValBuf[Len+1] = "";
     WORD  XDATA tmpvalue;

	 if(value >= 0)
	 {
	   tmpvalue = value;
	 }
	 else
	 {
       	tmpvalue = (~value)+1; 
	 }
	 
     #if Len == 4
	 if(value >=0)
	 {
       DispValBuf[0]=DatBuf[tmpvalue/1000];       
	   DispValBuf[1]=DatBuf[(tmpvalue%1000)/100];
	   DispValBuf[2]=DatBuf[((tmpvalue%1000)%100)/10];
	   DispValBuf[3]=DatBuf[(((tmpvalue%1000)%100)%10)%10];
	 }
	 else
	 {
		DispValBuf[0]  = '-';
		DispValBuf[1]=DatBuf[tmpvalue/100];       
		DispValBuf[2]=DatBuf[(tmpvalue%100)/10];
		DispValBuf[3]=DatBuf[((tmpvalue%100)%10)];
		
	 }
     #endif

	 #if Len == 6
	 DispValBuf[0]=DatBuf[tmpvalue/100000];       
	 DispValBuf[1]=DatBuf[(tmpvalue%100000)/10000];
	 DispValBuf[2]=DatBuf[((tmpvalue%100000)%10000)/1000];
	 DispValBuf[3]=DatBuf[(((tmpvalue%100000)%10000)%1000)/100];
	 DispValBuf[4]=DatBuf[((((tmpvalue%100000)%10000)%1000)%100)/10];
	 DispValBuf[5]=DatBuf[((((tmpvalue%100000)%10000)%1000)%100)%10];
	 #endif
	 
	 #if Len == 4
	 if(value >= 0)
	 {
		 if(0== (tmpvalue/1000))
		 {
		    DispValBuf[0]  = ' ';
		    if(0==((tmpvalue%1000)/100))
		   	{
		   	   	DispValBuf[1]  = ' ';
		   	}
		 }
		 
	 }
	 else
	 {
	     if(0==(tmpvalue/100))
		 {  
		    DispValBuf[0]  = ' ';
		    DispValBuf[1] =  '-';
		    if(0==((tmpvalue%100)/10))
		   	{
		   	    DispValBuf[1]  = ' ';
		   	    DispValBuf[2]  = '-';
		   	}
		 }
	 }
	 #endif
	 
     OsdDrawStr(starRow,starLine,fbColor,DispValBuf);
}

void OsdDrawHex(UCHAR starRow,UCHAR starLine,UCHAR fbColor,SWORD value)
{
//max 0x7fff
    #define HexLen    4
	UCHAR CODE HexDatBuf[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
	UCHAR XDATA HexDispValBuf[HexLen+1] = "";

	#if HexLen == 2
    HexDispValBuf[0]=HexDatBuf[(value/0x10)%0x10];       
	HexDispValBuf[1]=HexDatBuf[value%0x10]; 
	#endif

	#if HexLen == 4
	HexDispValBuf[0]=HexDatBuf[value/0x1000];   
	HexDispValBuf[1]=HexDatBuf[(value%0x1000)/0x100]; 
	HexDispValBuf[2]=HexDatBuf[((value%0x1000)%0x100)/0x10]; 
	HexDispValBuf[3]=HexDatBuf[((value%0x1000)%0x100)%0x10]; 
	#endif
	
	OsdDrawStr(starRow,starLine,fbColor,HexDispValBuf);
}


// »æÖÆÌõ×´½ø¶ÈÌõ
//input starRow:ÐÐ  starLine:ÁÐ   length:½ø¶ÈÌõµÄ³¤¶È        value:½ø¶ÈÌõµÄ¿í¶È
//return: void
void OsdDrawGuage(UCHAR starRow, UCHAR starLine, UCHAR length,UCHAR fbColor, UCHAR value)
{    
     #if(ICON_SIZE == SIZE_12X16)
	 UINT CODE GuageStepBuf[5] = {0x234,0x235,0x236,0x237,0x238};
	 #elif(ICON_SIZE == SIZE_16X22)
	 UINT CODE GuageStepBuf[5] = {0x053,0x054,0x055,0x056,0x057};
	 #endif
	 
	 UINT XDATA wcStartIndexAddr;
	 UINT XDATA wcColorStartIndexAddr;
	 UINT XDATA i,ucIndexOffset;
	 UCHAR result;
	 
#define GuageStepNum   (sizeof(GuageStepBuf)/sizeof(UINT)-1)

#define GuageIconNum    18  

     wcStartIndexAddr = OsdGetStartIndexAddr();
     ucIndexOffset = (OsdGetWndWidth()*starRow)+starLine;
	 wcStartIndexAddr = wcStartIndexAddr + ucIndexOffset;
	 wcColorStartIndexAddr = wcStartIndexAddr;

     INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
     INDEX_RAM_ADD_L = (wcStartIndexAddr&0xff);

	 result = ((UINT)value*GuageIconNum*GuageStepNum)/length;
	 
	 for(i=0;i<(GuageIconNum);i++)
	 {
	      INDEX_RAM_ADD_H =(wcStartIndexAddr>>8);
	      if(result > 0)
	      {
		      if(result>=GuageStepNum)
		      {
			      INDEX_RAM_DATA_H = GuageStepBuf[GuageStepNum] >> 8;
			      INDEX_RAM_DATA_L = GuageStepBuf[GuageStepNum] & 0xff;
				  result = result-GuageStepNum;
		      }
		      else
		      {
		           INDEX_RAM_DATA_H = GuageStepBuf[result %= GuageStepNum] >> 8;
			       INDEX_RAM_DATA_L = GuageStepBuf[result %= GuageStepNum] & 0xff;
				   result=0;
		      }
	      }
		  else
	  	  {
		       INDEX_RAM_DATA_H = GuageStepBuf[result] >> 8;
		       INDEX_RAM_DATA_L = GuageStepBuf[result] & 0xff;
	  	 }
	     wcStartIndexAddr++;
	 }	 

#define DrawNum    starLine

	 //write color
     INDEX_RAM_ADD_H =(wcColorStartIndexAddr>>8);
     INDEX_RAM_ADD_L = (wcColorStartIndexAddr&0xff);
     DrawNum = GuageIconNum+2;
	 
	 while(DrawNum)
	 {
	      INDEX_RAM_ADD_H =(wcColorStartIndexAddr>>8);
	      EACH_ICON_COLOR = fbColor;
		  DrawNum--;
		  wcColorStartIndexAddr++;
	 } 
}


void OsdConfigScaler(UCHAR zoom)
{
     //printfStr("OsdConfigScaler");
	 
     if(g_ucCurOsdBlockId == 0)
	 {
	      if(zoom >= 2)
	      {		
              OSD_V_SCALE_L_BK0  = 0xff;	
              OSD_V_SCALE_M_BK0  = 0xff;
              OSD_V_SCALE_H_BK0  = 0xff;	
              OSD_H_SCALE_L_BK0  = 0xff;
              OSD_H_SCALE_M_BK0  = 0xff;
              OSD_H_SCALE_H_BK0  = 0xff;
				
	          zoom -= 2;
			  zoom <<= 4;
	          zoom |= (zoom<<2);
			  OSD_H_SCALE_H_V_COEF &= 0X0F;
			  OSD_H_SCALE_H_V_COEF |= zoom;
		  
	      }
		  else if(zoom == 1)
		  {   
              OSD_V_SCALE_L_BK0  = 0x00;	
              OSD_V_SCALE_M_BK0  = 0x00;
              OSD_V_SCALE_H_BK0  = 0x00;	
              OSD_H_SCALE_L_BK0  = 0x00;
              OSD_H_SCALE_M_BK0  = 0x00;
              OSD_H_SCALE_H_BK0  = 0x00;
              OSD_H_SCALE_H_V_COEF = 0x00;
		  }
	 }
     if(g_ucCurOsdBlockId == 1)
	 {
	      zoom -= 1;
		  zoom <<= 0;
          zoom |= (zoom<<2);
	      HV_SCALE_COEF_BK1_BK2 &= 0xf0;
		  HV_SCALE_COEF_BK1_BK2 |= zoom;
	 }
	 if(g_ucCurOsdBlockId == 2)
	 {
	      zoom -= 1;
		  zoom <<= 4;
          zoom |= (zoom<<2);
	      HV_SCALE_COEF_BK1_BK2 &= 0xf0;
		  HV_SCALE_COEF_BK1_BK2 |= zoom; 
	 }
	 if(g_ucCurOsdBlockId == 3)
	 {
	      zoom -= 1;
		  zoom <<= 0;
          zoom |= (zoom<<2);
	      HV_SCALE_COEF_BK3_BK4 &= 0xf0;
		  HV_SCALE_COEF_BK3_BK4 |= zoom; 
	 }
	 if(g_ucCurOsdBlockId == 4)
	 {
	      zoom -= 1;
		  zoom <<= 4;
          zoom |= (zoom<<2);
	      HV_SCALE_COEF_BK3_BK4 &= 0xf0;
		  HV_SCALE_COEF_BK3_BK4 |= zoom;
	 }     
}

void OsdConfigBitmapStarIndex(UCHAR starIndexAddr)
{
      BITMAP_SATRT_L_ICON  = starIndexAddr&0xff;
      BITMAP_SATRT_H_ICON  = starIndexAddr>>8;
}

//============================Osd Color change====================================//
void OsdConfigColorChangeRGB(UCHAR R,UCHAR G,UCHAR B)
{
	OSD_CHANGE_R   = R;
	OSD_CHANGE_G   = G;
	OSD_CHANGE_B   = B;
}
void OsdColorChangeSwitch(UCHAR operatDat)
{
    OSD_CHANGE_CON &= 0xfe;
	OSD_CHANGE_CON |= operatDat;
}

void OsdConfigColorChangWndSize(UINT Length,UINT Width)
{

	//printfStr("OsdConfigColorChangWndSize");
    OSD_CHANGE_LENGTH_WIDTH_H = 0;
	OSD_CHANGE_LENGTH_L = Length&0XFF;
	OSD_CHANGE_LENGTH_WIDTH_H |= (Length>>8)&0X07;
	OSD_CHANGE_WIDTH_L = Width&0XFF;
	OSD_CHANGE_LENGTH_WIDTH_H |= ((Width>>8)<<4)&0X70;
}

void OsdConfigColorChangWndPosition(UINT XPos, UINT YPos)
{
    //printfStr("OsdConfigColorChangWndPosition");
    OSD_CHANGE_XY_START_H = 0;
	OSD_CHANGE_X_START_L = XPos&0XFF;
	OSD_CHANGE_XY_START_H |= (XPos>>8)&0XFF;
	OSD_CHANGE_Y_START_L = YPos&0XFF;
	OSD_CHANGE_XY_START_H |= ((YPos>>8)<<4)&0XFF;
}


