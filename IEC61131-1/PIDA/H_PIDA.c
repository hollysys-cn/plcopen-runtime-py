#include "H_AI_ALM.h"
#include "H_B_GET.h"
#include "H_B_WRITE.h"
#include "H_GETIECINTERVAL.h"
#include "H_PIDA.h"
#include "TASK-COMMON-DEFINE.h"
#include "TASK-DEFINE.h"
#include "TASK-EXCEPTION.h"
#include "common-internal.h"
#include"math.h"
void H_PIDA(void* pData, long unsigned int uiFORCE_OFFSET)
{
//Parameter assignment
struct __AT__PIDA* pHead = (struct __AT__PIDA*)pData;
// Temporary Variable Declaration
// Begin Translate AM:=AMAND16#0080;
{
*((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_AM)+0)))&(128)); 
}
// End Translate
// Begin Translate HHIND:=0;
{
*((bool*)((bool*)(pHead->H_HHIND)+0)) = (0); 
}
// End Translate
// Begin Translate AHIND:=0;
{
*((bool*)((bool*)(pHead->H_AHIND)+0)) = (0); 
}
// End Translate
// Begin Translate ALIND:=0;
{
*((bool*)((bool*)(pHead->H_ALIND)+0)) = (0); 
}
// End Translate
// Begin Translate LLIND:=0;
{
*((bool*)((bool*)(pHead->H_LLIND)+0)) = (0); 
}
// End Translate
// Begin Translate RALALMDB:=(PVU-PVL)*ALMDB*0.01;
{
*((float*)((bool*)(pHead->H_RALALMDB)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*(*(float*)((float*)((bool*)(pHead->H_ALMDB)+0)))*(0.01f)); 
}
// End Translate
// Begin Translate IFALMOPTTHENIF(H2>0ANDINHH2=0)THENHHIND:=AI_ALM(PV,0,0,HH,PREHH,RALALMDB,1);IFHHIND=1THENAM:=B_WRITE(AM,3,TRUE);IF(H1>0ANDINHH1=0)THENAHIND:=1;AM:=B_WRITE(AM,2,TRUE);END_IFEND_IFEND_IFIFHHIND=0AND(PV>=AH-RALALMDB)THENIF(H1>0ANDINHH1=0)THENAHIND:=AI_ALM(PV,0,0,AH,PREAH,RALALMDB,1);IFAHIND=1THENAM:=B_WRITE(AM,2,TRUE);END_IFEND_IFEND_IFIF(HHIND=0ANDAHIND=0)AND(L2>0ANDINHL2=0)AND(PV<=LL+RALALMDB)THENLLIND:=AI_ALM(PV,0,0,LL,PRELL,RALALMDB,0);IFLLIND=1THENAM:=B_WRITE(AM,0,TRUE);IF(L1>0ANDINHL1=0)THENALIND:=1;AM:=B_WRITE(AM,1,TRUE);END_IFEND_IFEND_IFIF(HHIND=0ANDAHIND=0ANDLLIND=0)AND(L1>0ANDINHL1=0)AND(PV<=AL+RALALMDB)THENALIND:=AI_ALM(PV,0,0,AL,PREAL,RALALMDB,0);IFALIND=1THENAM:=B_WRITE(AM,1,TRUE);END_IFEND_IFELSE;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ALMOPT)+0)))) 
 { 
	// Begin Translate IF(H2>0ANDINHH2=0)THENHHIND:=AI_ALM(PV,0,0,HH,PREHH,RALALMDB,1);IFHHIND=1THENAM:=B_WRITE(AM,3,TRUE);IF(H1>0ANDINHH1=0)THENAHIND:=1;AM:=B_WRITE(AM,2,TRUE);END_IFEND_IFEND_IF
{
if(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_H2)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHH2)+0)))  ==  (0)) ) 
 { 
	// Begin Translate HHIND:=AI_ALM(PV,0,0,HH,PREHH,RALALMDB,1);
{
{
bool  constVar7151  =0;
bool  constVar7152  =0;
bool  constVar7156  =1;
struct  __AT__AI_ALM   Head715 ;
Head715.H_AV = (float*)((bool*)(pHead->H_PV)+0);
Head715.H_AP = (bool*)&constVar7151;
Head715.H_AN = (bool*)&constVar7152;
Head715.H_HL = (float*)((bool*)(pHead->H_HH)+0);
Head715.H_PV = (bool*)((bool*)(pHead->H_PREHH)+0);
Head715.H_DI = (float*)((bool*)(pHead->H_RALALMDB)+0);
Head715.H_AS = (bool*)&constVar7156;
bool  Var715 = false  ;
Head715.H_AI_ALM=(bool*)&Var715; 
 *((bool*)((bool*)(pHead->H_HHIND)+0)) = ((H_AI_ALM(&Head715, uiFORCE_OFFSET), Var715));
}
 
}
// End Translate
// Begin Translate IFHHIND=1THENAM:=B_WRITE(AM,3,TRUE);IF(H1>0ANDINHH1=0)THENAHIND:=1;AM:=B_WRITE(AM,2,TRUE);END_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_HHIND)+0)))  ==  (1)) 
 { 
	// Begin Translate AM:=B_WRITE(AM,3,TRUE);
{
{
int16_t  constVar9161  =3;
bool  constVar9162  =1;
struct  __AT__B_WRITE   Head916 ;
Head916.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head916.H_WB = (int16_t*)&constVar9161;
Head916.H_IN = (bool*)&constVar9162;
uint16_t  Var916 = 0  ;
Head916.H_B_WRITE=(uint16_t*)&Var916; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head916, uiFORCE_OFFSET), Var916));
}
 
}
// End Translate
// Begin Translate IF(H1>0ANDINHH1=0)THENAHIND:=1;AM:=B_WRITE(AM,2,TRUE);END_IF
{
if(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_H1)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHH1)+0)))  ==  (0)) ) 
 { 
	// Begin Translate AHIND:=1;
{
*((bool*)((bool*)(pHead->H_AHIND)+0)) = (1); 
}
// End Translate
// Begin Translate AM:=B_WRITE(AM,2,TRUE);
{
{
int16_t  constVar12171  =2;
bool  constVar12172  =1;
struct  __AT__B_WRITE   Head1217 ;
Head1217.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head1217.H_WB = (int16_t*)&constVar12171;
Head1217.H_IN = (bool*)&constVar12172;
uint16_t  Var1217 = 0  ;
Head1217.H_B_WRITE=(uint16_t*)&Var1217; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head1217, uiFORCE_OFFSET), Var1217));
}
 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFHHIND=0AND(PV>=AH-RALALMDB)THENIF(H1>0ANDINHH1=0)THENAHIND:=AI_ALM(PV,0,0,AH,PREAH,RALALMDB,1);IFAHIND=1THENAM:=B_WRITE(AM,2,TRUE);END_IFEND_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_HHIND)+0)))  ==  (0)) &((fabs((*(float*)((float*)((bool*)(pHead->H_PV)+0))) - ((*(float*)((float*)((bool*)(pHead->H_AH)+0)))-(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_PV)+0)))>(*(float*)((float*)((bool*)(pHead->H_AH)+0)))-(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))) )) ) 
 { 
	// Begin Translate IF(H1>0ANDINHH1=0)THENAHIND:=AI_ALM(PV,0,0,AH,PREAH,RALALMDB,1);IFAHIND=1THENAM:=B_WRITE(AM,2,TRUE);END_IFEND_IF
{
if(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_H1)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHH1)+0)))  ==  (0)) ) 
 { 
	// Begin Translate AHIND:=AI_ALM(PV,0,0,AH,PREAH,RALALMDB,1);
{
{
bool  constVar19161  =0;
bool  constVar19162  =0;
bool  constVar19166  =1;
struct  __AT__AI_ALM   Head1916 ;
Head1916.H_AV = (float*)((bool*)(pHead->H_PV)+0);
Head1916.H_AP = (bool*)&constVar19161;
Head1916.H_AN = (bool*)&constVar19162;
Head1916.H_HL = (float*)((bool*)(pHead->H_AH)+0);
Head1916.H_PV = (bool*)((bool*)(pHead->H_PREAH)+0);
Head1916.H_DI = (float*)((bool*)(pHead->H_RALALMDB)+0);
Head1916.H_AS = (bool*)&constVar19166;
bool  Var1916 = false  ;
Head1916.H_AI_ALM=(bool*)&Var1916; 
 *((bool*)((bool*)(pHead->H_AHIND)+0)) = ((H_AI_ALM(&Head1916, uiFORCE_OFFSET), Var1916));
}
 
}
// End Translate
// Begin Translate IFAHIND=1THENAM:=B_WRITE(AM,2,TRUE);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_AHIND)+0)))  ==  (1)) 
 { 
	// Begin Translate AM:=B_WRITE(AM,2,TRUE);
{
{
int16_t  constVar21171  =2;
bool  constVar21172  =1;
struct  __AT__B_WRITE   Head2117 ;
Head2117.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head2117.H_WB = (int16_t*)&constVar21171;
Head2117.H_IN = (bool*)&constVar21172;
uint16_t  Var2117 = 0  ;
Head2117.H_B_WRITE=(uint16_t*)&Var2117; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head2117, uiFORCE_OFFSET), Var2117));
}
 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(HHIND=0ANDAHIND=0)AND(L2>0ANDINHL2=0)AND(PV<=LL+RALALMDB)THENLLIND:=AI_ALM(PV,0,0,LL,PRELL,RALALMDB,0);IFLLIND=1THENAM:=B_WRITE(AM,0,TRUE);IF(L1>0ANDINHL1=0)THENALIND:=1;AM:=B_WRITE(AM,1,TRUE);END_IFEND_IFEND_IF
{
if(((((*(bool*)((bool*)((bool*)(pHead->H_HHIND)+0)))  ==  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_AHIND)+0)))  ==  (0)) ) &(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_L2)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHL2)+0)))  ==  (0)) ) ) &((fabs((*(float*)((float*)((bool*)(pHead->H_PV)+0))) - ((*(float*)((float*)((bool*)(pHead->H_LL)+0)))+(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_PV)+0)))<(*(float*)((float*)((bool*)(pHead->H_LL)+0)))+(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))) )) ) 
 { 
	// Begin Translate LLIND:=AI_ALM(PV,0,0,LL,PRELL,RALALMDB,0);
{
{
bool  constVar27151  =0;
bool  constVar27152  =0;
bool  constVar27156  =0;
struct  __AT__AI_ALM   Head2715 ;
Head2715.H_AV = (float*)((bool*)(pHead->H_PV)+0);
Head2715.H_AP = (bool*)&constVar27151;
Head2715.H_AN = (bool*)&constVar27152;
Head2715.H_HL = (float*)((bool*)(pHead->H_LL)+0);
Head2715.H_PV = (bool*)((bool*)(pHead->H_PRELL)+0);
Head2715.H_DI = (float*)((bool*)(pHead->H_RALALMDB)+0);
Head2715.H_AS = (bool*)&constVar27156;
bool  Var2715 = false  ;
Head2715.H_AI_ALM=(bool*)&Var2715; 
 *((bool*)((bool*)(pHead->H_LLIND)+0)) = ((H_AI_ALM(&Head2715, uiFORCE_OFFSET), Var2715));
}
 
}
// End Translate
// Begin Translate IFLLIND=1THENAM:=B_WRITE(AM,0,TRUE);IF(L1>0ANDINHL1=0)THENALIND:=1;AM:=B_WRITE(AM,1,TRUE);END_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_LLIND)+0)))  ==  (1)) 
 { 
	// Begin Translate AM:=B_WRITE(AM,0,TRUE);
{
{
int16_t  constVar29161  =0;
bool  constVar29162  =1;
struct  __AT__B_WRITE   Head2916 ;
Head2916.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head2916.H_WB = (int16_t*)&constVar29161;
Head2916.H_IN = (bool*)&constVar29162;
uint16_t  Var2916 = 0  ;
Head2916.H_B_WRITE=(uint16_t*)&Var2916; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head2916, uiFORCE_OFFSET), Var2916));
}
 
}
// End Translate
// Begin Translate IF(L1>0ANDINHL1=0)THENALIND:=1;AM:=B_WRITE(AM,1,TRUE);END_IF
{
if(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_L1)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHL1)+0)))  ==  (0)) ) 
 { 
	// Begin Translate ALIND:=1;
{
*((bool*)((bool*)(pHead->H_ALIND)+0)) = (1); 
}
// End Translate
// Begin Translate AM:=B_WRITE(AM,1,TRUE);
{
{
int16_t  constVar32171  =1;
bool  constVar32172  =1;
struct  __AT__B_WRITE   Head3217 ;
Head3217.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head3217.H_WB = (int16_t*)&constVar32171;
Head3217.H_IN = (bool*)&constVar32172;
uint16_t  Var3217 = 0  ;
Head3217.H_B_WRITE=(uint16_t*)&Var3217; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head3217, uiFORCE_OFFSET), Var3217));
}
 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(HHIND=0ANDAHIND=0ANDLLIND=0)AND(L1>0ANDINHL1=0)AND(PV<=AL+RALALMDB)THENALIND:=AI_ALM(PV,0,0,AL,PREAL,RALALMDB,0);IFALIND=1THENAM:=B_WRITE(AM,1,TRUE);END_IFEND_IF
{
if((((((*(bool*)((bool*)((bool*)(pHead->H_HHIND)+0)))  ==  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_AHIND)+0)))  ==  (0)) ) &((*(bool*)((bool*)((bool*)(pHead->H_LLIND)+0)))  ==  (0)) ) &(((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_L1)+0))))  >  (0)) &((*(bool*)((bool*)((bool*)(pHead->H_INHL1)+0)))  ==  (0)) ) ) &((fabs((*(float*)((float*)((bool*)(pHead->H_PV)+0))) - ((*(float*)((float*)((bool*)(pHead->H_AL)+0)))+(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_PV)+0)))<(*(float*)((float*)((bool*)(pHead->H_AL)+0)))+(*(float*)((float*)((bool*)(pHead->H_RALALMDB)+0))) )) ) 
 { 
	// Begin Translate ALIND:=AI_ALM(PV,0,0,AL,PREAL,RALALMDB,0);
{
{
bool  constVar38151  =0;
bool  constVar38152  =0;
bool  constVar38156  =0;
struct  __AT__AI_ALM   Head3815 ;
Head3815.H_AV = (float*)((bool*)(pHead->H_PV)+0);
Head3815.H_AP = (bool*)&constVar38151;
Head3815.H_AN = (bool*)&constVar38152;
Head3815.H_HL = (float*)((bool*)(pHead->H_AL)+0);
Head3815.H_PV = (bool*)((bool*)(pHead->H_PREAL)+0);
Head3815.H_DI = (float*)((bool*)(pHead->H_RALALMDB)+0);
Head3815.H_AS = (bool*)&constVar38156;
bool  Var3815 = false  ;
Head3815.H_AI_ALM=(bool*)&Var3815; 
 *((bool*)((bool*)(pHead->H_ALIND)+0)) = ((H_AI_ALM(&Head3815, uiFORCE_OFFSET), Var3815));
}
 
}
// End Translate
// Begin Translate IFALIND=1THENAM:=B_WRITE(AM,1,TRUE);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ALIND)+0)))  ==  (1)) 
 { 
	// Begin Translate AM:=B_WRITE(AM,1,TRUE);
{
{
int16_t  constVar40161  =1;
bool  constVar40162  =1;
struct  __AT__B_WRITE   Head4016 ;
Head4016.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head4016.H_WB = (int16_t*)&constVar40161;
Head4016.H_IN = (bool*)&constVar40162;
uint16_t  Var4016 = 0  ;
Head4016.H_B_WRITE=(uint16_t*)&Var4016; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head4016, uiFORCE_OFFSET), Var4016));
}
 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	}
}
// End Translate
// Begin Translate PREHH:=HHIND;
{
*((bool*)((bool*)(pHead->H_PREHH)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_HHIND)+0)))); 
}
// End Translate
// Begin Translate PREAH:=AHIND;
{
*((bool*)((bool*)(pHead->H_PREAH)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_AHIND)+0)))); 
}
// End Translate
// Begin Translate PREAL:=ALIND;
{
*((bool*)((bool*)(pHead->H_PREAL)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_ALIND)+0)))); 
}
// End Translate
// Begin Translate PRELL:=LLIND;
{
*((bool*)((bool*)(pHead->H_PRELL)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_LLIND)+0)))); 
}
// End Translate
// Begin Translate IF(MODE=1ORMODE=2)THENIFNOT(((AMANDMANCUT)AND16#008F)=16#0000)THENMODE:=0;END_IFIFNOT((QAND16#0020)=16#0000)ANDB_GET(MANCUT,9)THENEVENFAULT:=EVENFAULT+1;ELSEEVENFAULT:=0;END_IFIFEVENFAULT>2THENMODE:=0;END_IFIF(NOT((QAND16#0001)=16#0000)ANDB_GET(MANCUT,8))OR(NOT((QAND16#0006)=16#0000)ANDB_GET(MANCUT,9))OR(NOT((QAND16#0018)=16#0000)ANDB_GET(MANCUT,10))THENMODE:=0;END_IFEND_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) ) 
 { 
	// Begin Translate IFNOT(((AMANDMANCUT)AND16#008F)=16#0000)THENMODE:=0;END_IF
{
if(0x1 & (~(( ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_AM)+0)))&(*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MANCUT)+0)))) &(143) )  ==  (0)))) 
 { 
	// Begin Translate MODE:=0;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFNOT((QAND16#0020)=16#0000)ANDB_GET(MANCUT,9)THENEVENFAULT:=EVENFAULT+1;ELSEEVENFAULT:=0;END_IF
{
int16_t  constVar61421  =9;
struct  __AT__B_GET   Head6142 ;
Head6142.H_VALUE = (uint16_t*)((bool*)(pHead->H_MANCUT)+0);
Head6142.H_WB = (int16_t*)&constVar61421;
bool  Var6142 = false  ;
Head6142.H_B_GET=(bool*)&Var6142; 
 if((0x1 & (~(( (*(uint16_t*)((uint16_t*)((bool*)(pHead->H_Q)+0)))&(32) )  ==  (0)))) &((H_B_GET(&Head6142, uiFORCE_OFFSET), Var6142)) ) 
 { 
	// Begin Translate EVENFAULT:=EVENFAULT+1;
{
*((uint8_t*)((bool*)(pHead->H_EVENFAULT)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EVENFAULT)+0)))+(1)); 
}
// End Translate
} 
else  
 { 
	// Begin Translate EVENFAULT:=0;
{
*((uint8_t*)((bool*)(pHead->H_EVENFAULT)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate IFEVENFAULT>2THENMODE:=0;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EVENFAULT)+0)))  >  (2)) 
 { 
	// Begin Translate MODE:=0;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(NOT((QAND16#0001)=16#0000)ANDB_GET(MANCUT,8))OR(NOT((QAND16#0006)=16#0000)ANDB_GET(MANCUT,9))OR(NOT((QAND16#0018)=16#0000)ANDB_GET(MANCUT,10))THENMODE:=0;END_IF
{
int16_t  constVar70431  =8;
struct  __AT__B_GET   Head7043 ;
Head7043.H_VALUE = (uint16_t*)((bool*)(pHead->H_MANCUT)+0);
Head7043.H_WB = (int16_t*)&constVar70431;
bool  Var7043 = false  ;
Head7043.H_B_GET=(bool*)&Var7043; 
 int16_t  constVar70971  =9;
struct  __AT__B_GET   Head7097 ;
Head7097.H_VALUE = (uint16_t*)((bool*)(pHead->H_MANCUT)+0);
Head7097.H_WB = (int16_t*)&constVar70971;
bool  Var7097 = false  ;
Head7097.H_B_GET=(bool*)&Var7097; 
 int16_t  constVar701501  =10;
struct  __AT__B_GET   Head70150 ;
Head70150.H_VALUE = (uint16_t*)((bool*)(pHead->H_MANCUT)+0);
Head70150.H_WB = (int16_t*)&constVar701501;
bool  Var70150 = false  ;
Head70150.H_B_GET=(bool*)&Var70150; 
 if((((0x1 & (~(( (*(uint16_t*)((uint16_t*)((bool*)(pHead->H_Q)+0)))&(1) )  ==  (0)))) &((H_B_GET(&Head7043, uiFORCE_OFFSET), Var7043)) ) |((0x1 & (~(( (*(uint16_t*)((uint16_t*)((bool*)(pHead->H_Q)+0)))&(6) )  ==  (0)))) &((H_B_GET(&Head7097, uiFORCE_OFFSET), Var7097)) ) ) |((0x1 & (~(( (*(uint16_t*)((uint16_t*)((bool*)(pHead->H_Q)+0)))&(24) )  ==  (0)))) &((H_B_GET(&Head70150, uiFORCE_OFFSET), Var70150)) ) ) 
 { 
	// Begin Translate MODE:=0;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate lastukout:=OUT;
{
*((float*)((bool*)(pHead->H_LASTUKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))); 
}
// End Translate
// Begin Translate lastduout:=OUT;
{
*((float*)((bool*)(pHead->H_LASTDUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))); 
}
// End Translate
// Begin Translate lastOUT:=OUT;
{
*((float*)((bool*)(pHead->H_LASTOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))); 
}
// End Translate
// Begin Translate IF((AUXOVEAND16#08)=16#08)THENU1:=AUXCOMP;END_IF
{
if(( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(8) )  ==  (8)) 
 { 
	// Begin Translate U1:=AUXCOMP;
{
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_AUXCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate uk:=U1;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_U1)+0)))); 
}
// End Translate
// Begin Translate OVE:=OVEAND16#F4;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(244)); 
}
// End Translate
// Begin Translate IFPVU<=PVLTHENPVU:=100;PVL:=0;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_PVU)+0))) - ((*(float*)((float*)((bool*)(pHead->H_PVL)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_PVU)+0)))<(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )) 
 { 
	// Begin Translate PVU:=100;
{
*((float*)((bool*)(pHead->H_PVU)+0)) = (100); 
}
// End Translate
// Begin Translate PVL:=0;
{
*((float*)((bool*)(pHead->H_PVL)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFENGU<=ENGLTHENENGU:=100;ENGL:=0;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_ENGU)+0))) - ((*(float*)((float*)((bool*)(pHead->H_ENGL)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))<(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )) 
 { 
	// Begin Translate ENGU:=100;
{
*((float*)((bool*)(pHead->H_ENGU)+0)) = (100); 
}
// End Translate
// Begin Translate ENGL:=0;
{
*((float*)((bool*)(pHead->H_ENGL)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFOUTU<=OUTLTHENOUTU:=100;OUTL:=0;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTU)+0))) - ((*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))) )) 
 { 
	// Begin Translate OUTU:=100;
{
*((float*)((bool*)(pHead->H_OUTU)+0)) = (100); 
}
// End Translate
// Begin Translate OUTL:=0;
{
*((float*)((bool*)(pHead->H_OUTL)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFOUTU>ENGUTHENOUTU:=ENGU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))>(*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))) 
 { 
	// Begin Translate OUTU:=ENGU;
{
*((float*)((bool*)(pHead->H_OUTU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFOUTL<ENGLTHENOUTL:=ENGL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))<(*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))) 
 { 
	// Begin Translate OUTL:=ENGL;
{
*((float*)((bool*)(pHead->H_OUTL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(SPU<=SPL)OR(SPU>PVU)OR(SPL<PVL)THENSPU:=PVU;SPL:=PVL;END_IF
{
if((((fabs((*(float*)((float*)((bool*)(pHead->H_SPU)+0))) - ((*(float*)((float*)((bool*)(pHead->H_SPL)+0))))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0))) )) |((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))>(*(float*)((float*)((bool*)(pHead->H_PVU)+0)))) ) |((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))<(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))) ) 
 { 
	// Begin Translate SPU:=PVU;
{
*((float*)((bool*)(pHead->H_SPU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PVU)+0)))); 
}
// End Translate
// Begin Translate SPL:=PVL;
{
*((float*)((bool*)(pHead->H_SPL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PVL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRSPTV>SPUTHENRSPTV:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate RSPTV:=SPU;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRSPTV<SPLTHENRSPTV:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate RSPTV:=SPL;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate mu1:=PVU;
{
*((float*)((bool*)(pHead->H_MU1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PVU)+0)))); 
}
// End Translate
// Begin Translate md1:=PVL;
{
*((float*)((bool*)(pHead->H_MD1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PVL)+0)))); 
}
// End Translate
// Begin Translate IFTI<0THENTI:=0;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_TI)+0)))<(0)) 
 { 
	// Begin Translate TI:=0;
{
*((float*)((bool*)(pHead->H_TI)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFKP<=0THENKP:=100;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_KP)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_KP)+0)))<(0) )) 
 { 
	// Begin Translate KP:=100;
{
*((float*)((bool*)(pHead->H_KP)+0)) = (100); 
}
// End Translate
} 
}
// End Translate
// Begin Translate DT1:=0.01*KP;
{
*((float*)((bool*)(pHead->H_DT1)+0)) = ((0.01f)*(*(float*)((float*)((bool*)(pHead->H_KP)+0)))); 
}
// End Translate
// Begin Translate DeadInterval:=0.01*ABS(mu1-md1)*DVDB;
{
*((float*)((bool*)(pHead->H_DEADINTERVAL)+0)) = ((0.01f)*( (float)fabs((*(float*)((float*)((bool*)(pHead->H_MU1)+0)))-(*(float*)((float*)((bool*)(pHead->H_MD1)+0)))) )*(*(float*)((float*)((bool*)(pHead->H_DVDB)+0)))); 
}
// End Translate
// Begin Translate DevalmLimit:=0.01*ABS(mu1-md1)*DAL;
{
*((float*)((bool*)(pHead->H_DEVALMLIMIT)+0)) = ((0.01f)*( (float)fabs((*(float*)((float*)((bool*)(pHead->H_MU1)+0)))-(*(float*)((float*)((bool*)(pHead->H_MD1)+0)))) )*(*(float*)((float*)((bool*)(pHead->H_DAL)+0)))); 
}
// End Translate
// Begin Translate IFPK=0THENSV1:=0.01*ABS(mu1-md1)*INTEDB;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_PK)+0)))  ==  (0)) 
 { 
	// Begin Translate SV1:=0.01*ABS(mu1-md1)*INTEDB;
{
*((float*)((bool*)(pHead->H_SV1)+0)) = ((0.01f)*( (float)fabs((*(float*)((float*)((bool*)(pHead->H_MU1)+0)))-(*(float*)((float*)((bool*)(pHead->H_MD1)+0)))) )*(*(float*)((float*)((bool*)(pHead->H_INTEDB)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((OUTOPT=0)AND(NOT(mu1=md1))AND(NOT(ENGU=ENGL)))THENDT1:=DT1*(mu1-md1)/(ENGU-ENGL);END_IF
{
if((((*(bool*)((bool*)((bool*)(pHead->H_OUTOPT)+0)))  ==  (0)) &(0x1 & (~((fabs((*(float*)((float*)((bool*)(pHead->H_MU1)+0))) - ((*(float*)((float*)((bool*)(pHead->H_MD1)+0))))) <= 1.175494351e-38F )))) ) &(0x1 & (~((fabs((*(float*)((float*)((bool*)(pHead->H_ENGU)+0))) - ((*(float*)((float*)((bool*)(pHead->H_ENGL)+0))))) <= 1.175494351e-38F )))) ) 
 { 
	// Begin Translate DT1:=DT1*(mu1-md1)/(ENGU-ENGL);
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,130);
 return ;   
} 
*((float*)((bool*)(pHead->H_DT1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))*( (*(float*)((float*)((bool*)(pHead->H_MU1)+0)))-(*(float*)((float*)((bool*)(pHead->H_MD1)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFKD<=0THENKD:=1;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_KD)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_KD)+0)))<(0) )) 
 { 
	// Begin Translate KD:=1;
{
*((float*)((bool*)(pHead->H_KD)+0)) = (1); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRSPTV>SPUTHENRSPTV:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate RSPTV:=SPU;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRSPTV<SPLTHENRSPTV:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate RSPTV:=SPL;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRTIMESP<0THENRTIMESP:=0;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))<(0)) 
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFRRATSP<0THENRRATSP:=0;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))<(0)) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFMODE>4THENMODE:=nowRM;END_IF
{
if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  >  (4)) 
 { 
	// Begin Translate MODE:=nowRM;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_NOWRM)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate CYC:=DWORD_TO_REAL(GetIECInterval(1))/1000;
{
{
uint8_t  constVar155330  =1;
struct  __AT__GETIECINTERVAL   Head15533 ;
Head15533.H_BFIX = (uint8_t*)&constVar155330;
uint32_t  Var15533 = 0  ;
Head15533.H_GETIECINTERVAL=(uint32_t*)&Var15533; 
 	 	 if ( (0 ==((1000)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,155);
 return ;   
} 
*((float*)((bool*)(pHead->H_CYC)+0)) = (( ((float)((H_GETIECINTERVAL(&Head15533, uiFORCE_OFFSET), Var15533))) )/(1000));
}
 
}
// End Translate
// Begin Translate IFCYC<=0THENCYC:=0.5;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_CYC)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))<(0) )) 
 { 
	// Begin Translate CYC:=0.5;
{
*((float*)((bool*)(pHead->H_CYC)+0)) = (0.5f); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(PIDTYPE=2ANDNOT(MODE=0ORMODE=1ORMODE=2))OR(NOT(PIDTYPE=2))THENCTRBP:=0;END_IF
{
if((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &(0x1 & (~((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) ) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) ))) ) |(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)))) ) 
 { 
	// Begin Translate CTRBP:=0;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((bool*)((bool*)(pHead->H_CTRBP)+0)) || !(*((bool*)((bool*)((bool*)(pHead->H_CTRBP)+0))+uiFORCE_OFFSET))) 
{
*((bool*)((bool*)(pHead->H_CTRBP)+0)) = (0);}
  
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((NOT(CTRBP))ANDpreCTRBP=1ANDPIDTYPE=2AND(MODE=2ANDnowRM=2))THENMODE:=0;END_IF
{
if((((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))))) &((*(bool*)((bool*)((bool*)(pHead->H_PRECTRBP)+0)))  ==  (1)) ) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) ) &(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_NOWRM)+0)))  ==  (2)) ) ) 
 { 
	// Begin Translate MODE:=0;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(CTRBPANDPIDTYPE=2AND(NOT(MODE=2))ANDnowRM=2)THENCTRBP:=0;END_IF
{
if((((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))&((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) ) &(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)))) ) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_NOWRM)+0)))  ==  (2)) ) 
 { 
	// Begin Translate CTRBP:=0;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((bool*)((bool*)(pHead->H_CTRBP)+0)) || !(*((bool*)((bool*)((bool*)(pHead->H_CTRBP)+0))+uiFORCE_OFFSET))) 
{
*((bool*)((bool*)(pHead->H_CTRBP)+0)) = (0);}
  
}
// End Translate
} 
}
// End Translate
// Begin Translate IFNOT(MODE=1)THENRCMD:=0;END_IF
{
if(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)))) 
 { 
	// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(MODE<>0)THENPMSW:=0;END_IF
{
if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  !=  (0)) 
 { 
	// Begin Translate PMSW:=0;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((bool*)((bool*)(pHead->H_PMSW)+0)) || !(*((bool*)((bool*)((bool*)(pHead->H_PMSW)+0))+uiFORCE_OFFSET))) 
{
*((bool*)((bool*)(pHead->H_PMSW)+0)) = (0);}
  
}
// End Translate
} 
}
// End Translate
// Begin Translate IFPIDTYPE=2AND(MODE=1ORMODE=0ORMODE=3ORMODE=4)THENIFMODE=1THENIFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-INTERSP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFEND_IFIFINTERSP>SPUTHENINTERSP:=SPU;END_IFIFINTERSP<SPLTHENINTERSP:=SPL;END_IFSPMODE:=0;sp1:=INTERSP;ELSEIFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFINTERSP>SPUTHENINTERSP:=SPU;END_IFIFINTERSP<SPLTHENINTERSP:=SPL;END_IFSPMODE:=0;sp1:=INTERSP;END_IFELSEIFMODE=1THENIFRCMD=1ANDPIDTYPE<>3THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RRAT:=0;RCMD:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP>SPUTHENSP:=SPU;END_IFIFSP<SPLTHENSP:=SPL;END_IFEND_IFIF(PIDTYPE=3AND(MODE=1))THENIFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFSP1:=MIN(SPU,SP1);SP1:=MAX(SPL,SP1);SP:=SP1;END_IFSPMODE:=0;ELSESP1:=SP;END_IFSPMODE:=0;ELSEIFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP>SPUTHENSP:=SPU;END_IFIFSP<SPLTHENSP:=SPL;END_IFIF(PIDTYPE=3AND(MODE=0))THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP1>SPUTHENSP1:=SPU;END_IFIFSP1<SPLTHENSP1:=SPL;END_IFSP:=SP1;SPMODE:=0;ELSESP1:=SP;END_IFSPMODE:=0;END_IFEND_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &(((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) ) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (3)) ) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (4)) ) ) 
 { 
	// Begin Translate IFMODE=1THENIFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-INTERSP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFEND_IFIFINTERSP>SPUTHENINTERSP:=SPU;END_IFIFINTERSP<SPLTHENINTERSP:=SPL;END_IFSPMODE:=0;sp1:=INTERSP;ELSEIFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFINTERSP>SPUTHENINTERSP:=SPU;END_IFIFINTERSP<SPLTHENINTERSP:=SPL;END_IFSPMODE:=0;sp1:=INTERSP;END_IF
{
if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) 
 { 
	// Begin Translate IFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-INTERSP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (1)) 
 { 
	// Begin Translate RTYP:=preRTYP;
{
*((bool*)((bool*)(pHead->H_RTYP)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_PRERTYP)+0)))); 
}
// End Translate
// Begin Translate RSPTV:=preRSPTV;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERSPTV)+0)))); 
}
// End Translate
// Begin Translate IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-INTERSP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFRCMDFlag=0THENRRAT:=ABS(RSPTV-INTERSP)/RTIMESP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  ==  (0)) 
 { 
	// Begin Translate RRAT:=ABS(RSPTV-INTERSP)/RTIMESP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,197);
 return ;   
} 
*((float*)((bool*)(pHead->H_RRAT)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-INTERSP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENINTERSP:=INTERSP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSEINTERSP:=INTERSP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,203);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate INTERSP:=RSPTV;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) 
 { 
	// Begin Translate INTERSP:=INTERSP+RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,211);
 return ;   
} 
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-INTERSP)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(RSPTV-INTERSP)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,215);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate INTERSP:=INTERSP-RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,220);
 return ;   
} 
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(INTERSP-RSPTV)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(INTERSP-RSPTV)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,224);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RSPTV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-INTERSP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))<(0) )) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIME:=ABS(RSPTV-INTERSP)/RRATSP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,240);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate RRAT:=RRATSP;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>INTERSP))OR(NOTACTOPTAND(RSPTV<INTERSP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<INTERSP))OR(NOTACTOPTAND(RSPTV>INTERSP))))))THEN;ELSEIF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-INTERSP)<RRATSP*(CYC/60)ANDRCMDFlag<>0)ORABS(RSPTV-INTERSP)<0.000001THENINTERSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>INTERSP)THENRRATSP:=preRRATSP;INTERSP:=INTERSP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;INTERSP:=INTERSP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,245);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate INTERSP:=RSPTV;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))) 
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate INTERSP:=INTERSP+RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,254);
 return ;   
} 
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,255);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate INTERSP:=INTERSP-RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,259);
 return ;   
} 
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,260);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (0)) 
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate INTERSP:=INTERSP+SPFRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate INTERSP:=INTERSP-SPFRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate INTERSP:=INTERSP+SPSRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate INTERSP:=INTERSP-SPSRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate IFINTERSP>SPUTHENINTERSP:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate INTERSP:=SPU;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFINTERSP<SPLTHENINTERSP:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate INTERSP:=SPL;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
// Begin Translate sp1:=INTERSP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASEELSECASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:INTERSP:=INTERSP+SPFRAT;2:INTERSP:=INTERSP-SPFRAT;3:INTERSP:=INTERSP+SPSRAT;4:INTERSP:=INTERSP-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate INTERSP:=INTERSP+SPFRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate INTERSP:=INTERSP-SPFRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate INTERSP:=INTERSP+SPSRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate INTERSP:=INTERSP-SPSRAT;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);2:INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);3:INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);4:INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate INTERSP:=INTERSP+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate INTERSP:=INTERSP-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate INTERSP:=INTERSP+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate INTERSP:=INTERSP-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IFINTERSP>SPUTHENINTERSP:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate INTERSP:=SPU;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFINTERSP<SPLTHENINTERSP:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate INTERSP:=SPL;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
// Begin Translate sp1:=INTERSP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate IFMODE=1THENIFRCMD=1ANDPIDTYPE<>3THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RRAT:=0;RCMD:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP>SPUTHENSP:=SPU;END_IFIFSP<SPLTHENSP:=SPL;END_IFEND_IFIF(PIDTYPE=3AND(MODE=1))THENIFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFSP1:=MIN(SPU,SP1);SP1:=MAX(SPL,SP1);SP:=SP1;END_IFSPMODE:=0;ELSESP1:=SP;END_IFSPMODE:=0;ELSEIFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP>SPUTHENSP:=SPU;END_IFIFSP<SPLTHENSP:=SPL;END_IFIF(PIDTYPE=3AND(MODE=0))THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP1>SPUTHENSP1:=SPU;END_IFIFSP1<SPLTHENSP1:=SPL;END_IFSP:=SP1;SPMODE:=0;ELSESP1:=SP;END_IFSPMODE:=0;END_IF
{
if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) 
 { 
	// Begin Translate IFRCMD=1ANDPIDTYPE<>3THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RRAT:=0;RCMD:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP>SPUTHENSP:=SPU;END_IFIFSP<SPLTHENSP:=SPL;END_IFEND_IF
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (1)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  !=  (3)) ) 
 { 
	// Begin Translate RTYP:=preRTYP;
{
*((bool*)((bool*)(pHead->H_RTYP)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_PRERTYP)+0)))); 
}
// End Translate
// Begin Translate RSPTV:=preRSPTV;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERSPTV)+0)))); 
}
// End Translate
// Begin Translate IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RRAT:=0;RCMD:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP)/RTIMESP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  ==  (0)) 
 { 
	// Begin Translate RRAT:=ABS(RSPTV-SP)/RTIMESP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,336);
 return ;   
} 
*((float*)((bool*)(pHead->H_RRAT)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-SP)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RCMD:=0;RTIME:=0;RRAT:=0;RTIMESP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENSP:=SP+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP:=SP-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,343);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate SP:=RSPTV;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) 
 { 
	// Begin Translate SP:=SP+RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,351);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(RSPTV-SP)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,355);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate SP:=SP-RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,360);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP-RSPTV)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(SP-RSPTV)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,364);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RSPTV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RRAT:=0;RCMD:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))<(0) )) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIME:=ABS(RSPTV-SP)/RRATSP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,380);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate RRAT:=RRATSP;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP))OR(NOTACTOPTAND(RSPTV<SP))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP))OR(NOTACTOPTAND(RSPTV>SP))))))THEN;ELSEIF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-SP)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP)<0.000001THENSP:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP)THENRRATSP:=preRRATSP;SP:=SP+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP:=SP-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,385);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate SP:=RSPTV;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP)+0)))) 
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate SP:=SP+RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,394);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,395);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate SP:=SP-RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,399);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,400);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (0)) 
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP:=SP+SPFRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP:=SP-SPFRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP:=SP+SPSRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP:=SP-SPSRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP:=SP+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP:=SP-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP:=SP+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP:=SP-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IFSP>SPUTHENSP:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate SP:=SPU;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFSP<SPLTHENSP:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate SP:=SPL;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(PIDTYPE=3AND(MODE=1))THENIFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFSP1:=MIN(SPU,SP1);SP1:=MAX(SPL,SP1);SP:=SP1;END_IFSPMODE:=0;ELSESP1:=SP;END_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (3)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) ) 
 { 
	// Begin Translate IFRCMD=1THENRTYP:=preRTYP;RSPTV:=preRSPTV;IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IFELSIFRCMD=0THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFSP1:=MIN(SPU,SP1);SP1:=MAX(SPL,SP1);SP:=SP1;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (1)) 
 { 
	// Begin Translate RTYP:=preRTYP;
{
*((bool*)((bool*)(pHead->H_RTYP)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_PRERTYP)+0)))); 
}
// End Translate
// Begin Translate RSPTV:=preRSPTV;
{
*((float*)((bool*)(pHead->H_RSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERSPTV)+0)))); 
}
// End Translate
// Begin Translate IFRTYP=0THENRRATSP:=0;IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IFELSERTIMESP:=0;IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRTIMESP<0ORABS(RTIMESP)<0.000001THENRTIMESP:=0;RRAT:=0;RTIME:=0;RCMD:=0;RCMDFlag:=0;ELSEIFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IFIF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IFEND_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFRCMDFlag=0THENRRAT:=ABS(RSPTV-SP1)/RTIMESP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  ==  (0)) 
 { 
	// Begin Translate RRAT:=ABS(RSPTV-SP1)/RTIMESP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,447);
 return ;   
} 
*((float*)((bool*)(pHead->H_RRAT)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-SP1)<RRAT*(CYC/60)AND(RCMDFlag<>0))ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RCMD:=0;RTIME:=0;RTIMESP:=0;RRAT:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENSP1:=SP1+RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;ELSESP1:=SP1-RRAT*(CYC/60);IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IFRCMDFlag:=1;RTIMESP:=preRTIMESP;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,454);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate SP1:=RSPTV;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) 
 { 
	// Begin Translate SP1:=SP1+RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,462);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(RSPTV-SP1)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(RSPTV-SP1)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,466);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate SP1:=SP1-RRAT*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,471);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate IFRRAT<0ORABS(RRAT)<0.000001THEN;ELSERTIME:=(SP1-RSPTV)/RRAT;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RRAT)+0))))<(0.000001f)) ) 
 { 
	} 
else  
 { 
	// Begin Translate RTIME:=(SP1-RSPTV)/RRAT;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,475);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_RSPTV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_RRAT)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
// Begin Translate RTIMESP:=preRTIMESP;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERTIMESP)+0)))); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate IFRRATSP<=0THENRRATSP:=0;RTIME:=0;RCMD:=0;RRAT:=0;RCMDFlag:=0;ELSERTIME:=ABS(RSPTV-SP1)/RRATSP;RRAT:=RRATSP;IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IFEND_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))<(0) )) 
 { 
	// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RTIME:=ABS(RSPTV-SP1)/RRATSP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,491);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = (( (float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) )/(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate RRAT:=RRATSP;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate IF(ROVEP=1AND(((ABS(OUT-OUTU)<0.000001)ANDEK>0AND((ACTOPTAND(RSPTV>SP1))OR(NOTACTOPTAND(RSPTV<SP1))))OR((ABS(OUT-OUTL)<0.000001)ANDEK<0AND((ACTOPTAND(RSPTV<SP1))OR(NOTACTOPTAND(RSPTV>SP1))))))THEN;ELSEIF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IFEND_IF
{
if(((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  ==  (1)) &(((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) ) ) |((((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) &(((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))&((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))<(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) |((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))))) &((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) ) ) ) ) ) 
 { 
	} 
else  
 { 
	// Begin Translate IF(ABS(RSPTV-SP1)<(RRATSP*(CYC/60))ANDRCMDFlag<>0)ORABS(RSPTV-SP1)<0.000001THENSP1:=RSPTV;RTIME:=0;RCMD:=0;RRAT:=0;RRATSP:=0;RCMDFlag:=0;ELSIF(RSPTV>SP1)THENRRATSP:=preRRATSP;SP1:=SP1+RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;ELSERRATSP:=preRRATSP;SP1:=SP1-RRATSP*(CYC/60);RTIME:=RTIME-CYC/60;RCMDFlag:=1;END_IF
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,497);
 return ;   
} 
if((((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))))<(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )) &((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) ) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate SP1:=RSPTV;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
else if((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))>(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))) 
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate SP1:=SP1+RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,506);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,507);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
} 
else  
 { 
	// Begin Translate RRATSP:=preRRATSP;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PRERRATSP)+0)))); 
}
// End Translate
// Begin Translate SP1:=SP1-RRATSP*(CYC/60);
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,511);
 return ;   
} 
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))*( (*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60) )); 
}
// End Translate
// Begin Translate RTIME:=RTIME-CYC/60;
{
	 	 if ( (0 ==((60)) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,512);
 return ;   
} 
*((float*)((bool*)(pHead->H_RTIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIME)+0)))-(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))/(60)); 
}
// End Translate
// Begin Translate RCMDFlag:=1;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (1); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (0)) 
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP1:=SP1+SPFRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP1:=SP1-SPFRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP1:=SP1+SPSRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP1:=SP1-SPSRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP1:=SP1+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP1:=SP1-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP1:=SP1+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP1:=SP1-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate SP1:=MIN(SPU,SP1);
{
{
	float arr_534_12[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))};
*((float*)((bool*)(pHead->H_SP1)+0)) = (H_MIN_FLOAT(arr_534_12, 2));
}
 
}
// End Translate
// Begin Translate SP1:=MAX(SPL,SP1);
{
{
	float arr_535_12[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP1)+0)))};
*((float*)((bool*)(pHead->H_SP1)+0)) = (H_MAX_FLOAT(arr_535_12, 2));
}
 
}
// End Translate
// Begin Translate SP:=SP1;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate SP1:=SP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASEELSECASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:SP:=SP+SPFRAT;2:SP:=SP-SPFRAT;3:SP:=SP+SPSRAT;4:SP:=SP-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP:=SP+SPFRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP:=SP-SPFRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP:=SP+SPSRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP:=SP-SPSRAT;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:SP:=SP+0.01*SPFRAT*(PVU-PVL);2:SP:=SP-0.01*SPFRAT*(PVU-PVL);3:SP:=SP+0.01*SPSRAT*(PVU-PVL);4:SP:=SP-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP:=SP+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP:=SP-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP:=SP+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP:=SP-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IFSP>SPUTHENSP:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate SP:=SPU;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFSP<SPLTHENSP:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate SP:=SPL;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(PIDTYPE=3AND(MODE=0))THENIFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IFIFSP1>SPUTHENSP1:=SPU;END_IFIFSP1<SPLTHENSP1:=SPL;END_IFSP:=SP1;SPMODE:=0;ELSESP1:=SP;END_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (3)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) ) 
 { 
	// Begin Translate IFSMANOPTTHENCASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASEELSECASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASEEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_SMANOPT)+0)))) 
 { 
	// Begin Translate CASESPMODEOF1:SP1:=SP1+SPFRAT;2:SP1:=SP1-SPFRAT;3:SP1:=SP1+SPSRAT;4:SP1:=SP1-SPSRAT;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP1:=SP1+SPFRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP1:=SP1-SPFRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP1:=SP1+SPSRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP1:=SP1-SPSRAT;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate CASESPMODEOF1:SP1:=SP1+0.01*SPFRAT*(PVU-PVL);2:SP1:=SP1-0.01*SPFRAT*(PVU-PVL);3:SP1:=SP1+0.01*SPSRAT*(PVU-PVL);4:SP1:=SP1-0.01*SPSRAT*(PVU-PVL);END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (1))
{
// Begin Translate SP1:=SP1+0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (2))
{
// Begin Translate SP1:=SP1-0.01*SPFRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPFRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (3))
{
// Begin Translate SP1:=SP1+0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_SPMODE)+0))))== (4))
{
// Begin Translate SP1:=SP1-0.01*SPSRAT*(PVU-PVL);
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_SPSRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IFSP1>SPUTHENSP1:=SPU;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPU)+0)))) 
 { 
	// Begin Translate SP1:=SPU;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPU)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFSP1<SPLTHENSP1:=SPL;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))<(*(float*)((float*)((bool*)(pHead->H_SPL)+0)))) 
 { 
	// Begin Translate SP1:=SPL;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPL)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate SP:=SP1;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate SP1:=SP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate SPMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_SPMODE)+0)) = (0); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IF((RCMDFlag<>0)ANDRCMD=0)OR((RCMDFlag<>0)ANDABS(preSP1-SP1)<0.0000001ANDROVEP<>1)THENRCMD:=0;RTIME:=0;RRAT:=0;RRATSP:=0;RTIMESP:=0;RCMDFlag:=0;END_IF
{
if((((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) &((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_RCMD)+0)))  ==  (0)) ) |((((*(bool*)((bool*)((bool*)(pHead->H_RCMDFLAG)+0)))  !=  (0)) &((float)fabs((*(float*)((float*)((bool*)(pHead->H_PRESP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SP1)+0))))<(0.0000001f)) ) &((*(bool*)((bool*)((bool*)(pHead->H_ROVEP)+0)))  !=  (1)) ) ) 
 { 
	// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate RTIME:=0;
{
*((float*)((bool*)(pHead->H_RTIME)+0)) = (0); 
}
// End Translate
// Begin Translate RRAT:=0;
{
*((float*)((bool*)(pHead->H_RRAT)+0)) = (0); 
}
// End Translate
// Begin Translate RRATSP:=0;
{
*((float*)((bool*)(pHead->H_RRATSP)+0)) = (0); 
}
// End Translate
// Begin Translate RTIMESP:=0;
{
*((float*)((bool*)(pHead->H_RTIMESP)+0)) = (0); 
}
// End Translate
// Begin Translate RCMDFlag:=0;
{
*((bool*)((bool*)(pHead->H_RCMDFLAG)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate preRTYP:=RTYP;
{
*((bool*)((bool*)(pHead->H_PRERTYP)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_RTYP)+0)))); 
}
// End Translate
// Begin Translate preRSPTV:=RSPTV;
{
*((float*)((bool*)(pHead->H_PRERSPTV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RSPTV)+0)))); 
}
// End Translate
// Begin Translate preRTIMESP:=RTIMESP;
{
*((float*)((bool*)(pHead->H_PRERTIMESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RTIMESP)+0)))); 
}
// End Translate
// Begin Translate preRRATSP:=RRATSP;
{
*((float*)((bool*)(pHead->H_PRERRATSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_RRATSP)+0)))); 
}
// End Translate
// Begin Translate preSP:=SP;
{
*((float*)((bool*)(pHead->H_PRESP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))); 
}
// End Translate
// Begin Translate preSP1:=SP1;
{
*((float*)((bool*)(pHead->H_PRESP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
// Begin Translate IFPIDTYPE=2ANDMODE=2THENINTERSP:=sp1;END_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) ) 
 { 
	// Begin Translate INTERSP:=sp1;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFGIVERAT<=0ORGIVERAT>100THENGIVERAT:=10;END_IF
{
if(((fabs((*(float*)((float*)((bool*)(pHead->H_GIVERAT)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_GIVERAT)+0)))<(0) )) |((*(float*)((float*)((bool*)(pHead->H_GIVERAT)+0)))>(100)) ) 
 { 
	// Begin Translate GIVERAT:=10;
{
*((float*)((bool*)(pHead->H_GIVERAT)+0)) = (10); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFOUTRAT<=0OROUTRAT>100THENOUTRAT:=5;END_IF
{
if(((fabs((*(float*)((float*)((bool*)(pHead->H_OUTRAT)+0))) - ((0))) <= 1.175494351e-38F ||(*(float*)((float*)((bool*)(pHead->H_OUTRAT)+0)))<(0) )) |((*(float*)((float*)((bool*)(pHead->H_OUTRAT)+0)))>(100)) ) 
 { 
	// Begin Translate OUTRAT:=5;
{
*((float*)((bool*)(pHead->H_OUTRAT)+0)) = (5); 
}
// End Translate
} 
}
// End Translate
// Begin Translate RealGiveRat:=GIVERAT*CYC;
{
*((float*)((bool*)(pHead->H_REALGIVERAT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_GIVERAT)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))); 
}
// End Translate
// Begin Translate RealOutRat:=OUTRAT*CYC;
{
*((float*)((bool*)(pHead->H_REALOUTRAT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUTRAT)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYC)+0)))); 
}
// End Translate
// Begin Translate IFTRKENANDTRKSWTHENIF(NOT(MODE=4))THENpreRM:=MODE;MODE:=4;END_IFELSEIF(NOT(preRM=4))THENIFTRKMODE=FALSETHENMODE:=0;ELSEMODE:=preRM;END_IFpreRM:=4;END_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_TRKEN)+0)))&(*(bool*)((bool*)((bool*)(pHead->H_TRKSW)+0)))) 
 { 
	// Begin Translate IF(NOT(MODE=4))THENpreRM:=MODE;MODE:=4;END_IF
{
if(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (4)))) 
 { 
	// Begin Translate preRM:=MODE;
{
*((uint16_t*)((bool*)(pHead->H_PRERM)+0)) = ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))); 
}
// End Translate
// Begin Translate MODE:=4;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (4); 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate IF(NOT(preRM=4))THENIFTRKMODE=FALSETHENMODE:=0;ELSEMODE:=preRM;END_IFpreRM:=4;END_IF
{
if(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PRERM)+0)))  ==  (4)))) 
 { 
	// Begin Translate IFTRKMODE=FALSETHENMODE:=0;ELSEMODE:=preRM;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_TRKMODE)+0)))  ==  (0)) 
 { 
	// Begin Translate MODE:=0;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate MODE:=preRM;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PRERM)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate preRM:=4;
{
*((uint16_t*)((bool*)(pHead->H_PRERM)+0)) = (4); 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(PIDTYPE=1AND((NOT(AUXMODE=2))OR(AUXMODE=2AND((AUXOVEAND16#08)=8))))THENOUT:=AUXCOMP;ek:=sp1-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFIFMODE=0ORMODE=3ORMODE=4THENek:=sp1-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IFEND_IFukout:=AUXCOMP;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFELSIFMODE=3ORMODE=4THENIFOUTOPT=1THENduout:=TRKVAL;duout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);OUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEukout:=TRKVAL;ukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);OUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IFek:=sp1-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFIF(PIDTYPE=2ANDTRKOPT)THENINTERSP:=PV-INCOMP;INTERSP:=MIN(SPU,INTERSP);INTERSP:=MAX(SPL,INTERSP);ELSEIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IFEND_IFELSIFMODE=0THENRCMD:=0;IFPMSW=1THENIFOUTOPT=1THENIF(MOLSW)THENduout:=MIN(OUTU,PMOUT);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,PMOUT);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIF(MOLSW)THENukout:=MIN(OUTU,PMOUT);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,PMOUT);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IFELSEIFOUTOPT=1THENIFOMANOPTTHENCASEMANMODEOF1:duout:=MANF;2:duout:=-MANF;3:duout:=MANS;4:duout:=-MANS;ELSEduout:=0;END_CASE;ELSECASEMANMODEOF1:duout:=0.01*MANF*(ENGU-ENGL);2:duout:=-0.01*MANF*(ENGU-ENGL);3:duout:=0.01*MANS*(ENGU-ENGL);4:duout:=-0.01*MANS*(ENGU-ENGL);ELSEduout:=0;END_CASE;END_IFIF(MOLSW)THENduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,duout);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIFOMANOPTTHENCASEMANMODEOF1:ukout:=lastukout+MANF;2:ukout:=lastukout-MANF;3:ukout:=lastukout+MANS;4:ukout:=lastukout-MANS;ELSEukout:=lastukout;END_CASE;ELSECASEMANMODEOF1:ukout:=lastukout+0.01*MANF*(ENGU-ENGL);2:ukout:=lastukout-0.01*MANF*(ENGU-ENGL);3:ukout:=lastukout+0.01*MANS*(ENGU-ENGL);4:ukout:=lastukout-0.01*MANS*(ENGU-ENGL);ELSEukout:=lastukout;END_CASE;END_IFIF(MOLSW)THENukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,ukout);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IFMANMODE:=0;END_IFek:=sp1-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFIF(PIDTYPE=2ANDTRKOPT)THENINTERSP:=PV-INCOMP;INTERSP:=MIN(SPU,INTERSP);INTERSP:=MAX(SPL,INTERSP);ELSEIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);SP1:=SP;IF(PIDTYPE=3ANDMODE=0)THENSP1:=SP;END_IFEND_IFEND_IFELSEIFPIDTYPE=2AND(MODE=2ORMODE=1)ANDCTRBP=1ANDpreCTRBP=1THENIFACTOPTTHENOUT:=(SP-PVL)/(PVU-PVL)*(ENGU-ENGL)+ENGL;ELSEOUT:=ENGU-(SP-PVL)/(PVU-PVL)*(ENGU-ENGL);END_IFOUT:=MIN(OUTU,OUT);OUT:=MAX(OUTL,OUT);RCMD:=0;IF(ABS(OUT-lastOUT)>0.01*RealOutRat*(ENGU-ENGL))THENIF(OUT>lastOUT)THENOUT:=lastOUT+0.01*RealOutRat*(ENGU-ENGL);ELSEOUT:=lastOUT-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(OUT>OUTUOR(ABS(OUT-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(OUT>OUTUOR(ABS(OUT-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFELSEIF(ABS((sp1-SPCAL)/(PVU-PVL))>RealGiveRat*0.01)THENIF(sp1>SPCAL)THENSPCAL:=SPCAL+(PVU-PVL)*RealGiveRat*0.01;ELSESPCAL:=SPCAL-(PVU-PVL)*RealGiveRat*0.01;END_IFELSESPCAL:=sp1;END_IFek:=SPCAL-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFcycletime:=CYC;IFPK=0THENIFEQN=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(ek-EK_1)/DT1);dudd:=DK-D1;D1:=DK;ELSIFEQN=1OREQN=2THENIFACTOPT=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);ELSEDK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);END_IFdudd:=DK-D1;D1:=DK;END_IFIF((ABS(ek)<=DeadInterval)AND(DD=1)OR((((AUXOVEAND16#05)=1)ANDEK>0)OR(((AUXOVEAND16#06)=2)ANDEK<0)OR(((AUXOVEAND16#05)=5)ANDEK<0)OR(((AUXOVEAND16#06)=6)ANDEK>0)))THENdu:=0;DK:=0;D1:=0;dudd:=0;ELSEIF(ABS(ek)<=DeadIntervalANDDD=0)THENDD:=1;ELSEDD:=0;END_IFIF(ABS(ek)<=SV1)THENsi:=1;ELSEsi:=0;END_IFIFTI=0ORsi=0THENIFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IFEND_IFIFTI<>0ANDsi=1THENIFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IFEND_IFIF((EK<0ORABS(EK)<0.000001)ANDABS(OUT-OUTL)<0.000001)THENdu:=0;END_IFIF((EK>0ORABS(EK)<0.000001)ANDABS(OUT-OUTU)<0.000001)THENdu:=0;END_IFEND_IFEND_IFIF(PK=0ORPK=1)THENIFOUTOPT=1THENIFOCTYP=0THENduout:=du+OUTCOMP+DK;ELSIFOCTYP=1THENduout:=(du+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLSAND(duout>OUTUORduout<OUTL))THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IFIF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);MOFLAG:=FALSE;END_IFIF(ABS(duout-lastduout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFOUT:=duout;ELSEIF(ORSTSAND16#1)=16#1THENIF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF;END_IF;uk:=U1+du;IFOCTYP=0THENIF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IFukout:=uk+OUTCOMP+DK;ELSIFOCTYP=1THENIFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IFukout:=(uk+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLS)AND(ukout>OUTUORukout<OUTL)THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IFIF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);MOFLAG:=FALSE;END_IFIF(ABS(ukout-lastukout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(ukout>OUTUOR(ABS(ukout-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(ukout<OUTLOR(ABS(ukout-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFOUT:=ukout;END_IFEND_IFEND_IFEND_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (1)) &((0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_AUXMODE)+0)))  ==  (2)))) |(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_AUXMODE)+0)))  ==  (2)) &(( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(8) )  ==  (8)) ) ) ) 
 { 
	// Begin Translate OUT:=AUXCOMP;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_AUXCOMP)+0))));}
  
}
// End Translate
// Begin Translate ek:=sp1-PV;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate ek:=-ek-INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = (( -(*(float*)((float*)((bool*)(pHead->H_EK)+0))) )-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ek:=ek+INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))+(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate IFMODE=0ORMODE=3ORMODE=4THENek:=sp1-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IFEND_IF
{
if((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (3)) ) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (4)) ) 
 { 
	// Begin Translate ek:=sp1-PV;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate ek:=-ek-INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = (( -(*(float*)((float*)((bool*)(pHead->H_EK)+0))) )-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ek:=ek+INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))+(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate IFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_TRKOPT)+0)))) 
 { 
	// Begin Translate SP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
// Begin Translate SP:=MIN(SPU,SP);
{
{
	float arr_670_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MIN_FLOAT(arr_670_10, 2));
}
 
}
// End Translate
// Begin Translate SP:=MAX(SPL,SP);
{
{
	float arr_671_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MAX_FLOAT(arr_671_10, 2));
}
 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate ukout:=AUXCOMP;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_AUXCOMP)+0)))); 
}
// End Translate
// Begin Translate IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate uk:=ukout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate uk:=ukout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,679);
 return ;   
} 
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
else if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (3)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (4)) ) 
 { 
	// Begin Translate IFOUTOPT=1THENduout:=TRKVAL;duout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);OUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEukout:=TRKVAL;ukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);OUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OUTOPT)+0)))  ==  (1)) 
 { 
	// Begin Translate duout:=TRKVAL;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_TRKVAL)+0)))); 
}
// End Translate
// Begin Translate duout:=MIN(OUTU,duout);
{
{
	float arr_686_18[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_686_18, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(OUTL,duout);
{
{
	float arr_687_12[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_687_12, 2));
}
 
}
// End Translate
// Begin Translate OUT:=duout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate du:=duout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate du:=duout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,693);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate ukout:=TRKVAL;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_TRKVAL)+0)))); 
}
// End Translate
// Begin Translate ukout:=MIN(OUTU,ukout);
{
{
	float arr_700_12[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_700_12, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(OUTL,ukout);
{
{
	float arr_701_12[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_701_12, 2));
}
 
}
// End Translate
// Begin Translate OUT:=ukout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate uk:=ukout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate uk:=ukout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,707);
 return ;   
} 
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
// Begin Translate ek:=sp1-PV;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate ek:=-ek-INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = (( -(*(float*)((float*)((bool*)(pHead->H_EK)+0))) )-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ek:=ek+INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))+(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(PIDTYPE=2ANDTRKOPT)THENINTERSP:=PV-INCOMP;INTERSP:=MIN(SPU,INTERSP);INTERSP:=MAX(SPL,INTERSP);ELSEIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IFEND_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &(*(bool*)((bool*)((bool*)(pHead->H_TRKOPT)+0)))) 
 { 
	// Begin Translate INTERSP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
// Begin Translate INTERSP:=MIN(SPU,INTERSP);
{
{
	float arr_720_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))};
*((float*)((bool*)(pHead->H_INTERSP)+0)) = (H_MIN_FLOAT(arr_720_14, 2));
}
 
}
// End Translate
// Begin Translate INTERSP:=MAX(SPL,INTERSP);
{
{
	float arr_721_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))};
*((float*)((bool*)(pHead->H_INTERSP)+0)) = (H_MAX_FLOAT(arr_721_14, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_TRKOPT)+0)))) 
 { 
	// Begin Translate SP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
// Begin Translate SP:=MIN(SPU,SP);
{
{
	float arr_725_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MIN_FLOAT(arr_725_10, 2));
}
 
}
// End Translate
// Begin Translate SP:=MAX(SPL,SP);
{
{
	float arr_726_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MAX_FLOAT(arr_726_10, 2));
}
 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
} 
else if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) 
 { 
	// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate IFPMSW=1THENIFOUTOPT=1THENIF(MOLSW)THENduout:=MIN(OUTU,PMOUT);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,PMOUT);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIF(MOLSW)THENukout:=MIN(OUTU,PMOUT);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,PMOUT);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IFELSEIFOUTOPT=1THENIFOMANOPTTHENCASEMANMODEOF1:duout:=MANF;2:duout:=-MANF;3:duout:=MANS;4:duout:=-MANS;ELSEduout:=0;END_CASE;ELSECASEMANMODEOF1:duout:=0.01*MANF*(ENGU-ENGL);2:duout:=-0.01*MANF*(ENGU-ENGL);3:duout:=0.01*MANS*(ENGU-ENGL);4:duout:=-0.01*MANS*(ENGU-ENGL);ELSEduout:=0;END_CASE;END_IFIF(MOLSW)THENduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,duout);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIFOMANOPTTHENCASEMANMODEOF1:ukout:=lastukout+MANF;2:ukout:=lastukout-MANF;3:ukout:=lastukout+MANS;4:ukout:=lastukout-MANS;ELSEukout:=lastukout;END_CASE;ELSECASEMANMODEOF1:ukout:=lastukout+0.01*MANF*(ENGU-ENGL);2:ukout:=lastukout-0.01*MANF*(ENGU-ENGL);3:ukout:=lastukout+0.01*MANS*(ENGU-ENGL);4:ukout:=lastukout-0.01*MANS*(ENGU-ENGL);ELSEukout:=lastukout;END_CASE;END_IFIF(MOLSW)THENukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,ukout);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IFMANMODE:=0;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_PMSW)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTOPT=1THENIF(MOLSW)THENduout:=MIN(OUTU,PMOUT);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,PMOUT);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIF(MOLSW)THENukout:=MIN(OUTU,PMOUT);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,PMOUT);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OUTOPT)+0)))  ==  (1)) 
 { 
	// Begin Translate IF(MOLSW)THENduout:=MIN(OUTU,PMOUT);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,PMOUT);duout:=MAX(ENGL,duout);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOLSW)+0)))) 
 { 
	// Begin Translate duout:=MIN(OUTU,PMOUT);
{
{
	float arr_735_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_PMOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_735_13, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(OUTL,duout);
{
{
	float arr_736_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_736_13, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate duout:=MIN(ENGU,PMOUT);
{
{
	float arr_738_22[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_PMOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_738_22, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(ENGL,duout);
{
{
	float arr_739_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_739_13, 2));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate OUT:=duout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate du:=duout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate du:=duout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,746);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate IF(MOLSW)THENukout:=MIN(OUTU,PMOUT);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,PMOUT);ukout:=MAX(ENGL,ukout);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOLSW)+0)))) 
 { 
	// Begin Translate ukout:=MIN(OUTU,PMOUT);
{
{
	float arr_751_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_PMOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_751_13, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(OUTL,ukout);
{
{
	float arr_752_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_752_13, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate ukout:=MIN(ENGU,PMOUT);
{
{
	float arr_754_22[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_PMOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_754_22, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(ENGL,ukout);
{
{
	float arr_755_13[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_755_13, 2));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate OUT:=ukout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate uk:=ukout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate uk:=ukout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,762);
 return ;   
} 
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate IFOUTOPT=1THENIFOMANOPTTHENCASEMANMODEOF1:duout:=MANF;2:duout:=-MANF;3:duout:=MANS;4:duout:=-MANS;ELSEduout:=0;END_CASE;ELSECASEMANMODEOF1:duout:=0.01*MANF*(ENGU-ENGL);2:duout:=-0.01*MANF*(ENGU-ENGL);3:duout:=0.01*MANS*(ENGU-ENGL);4:duout:=-0.01*MANS*(ENGU-ENGL);ELSEduout:=0;END_CASE;END_IFIF(MOLSW)THENduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,duout);duout:=MAX(ENGL,duout);END_IFOUT:=duout;IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IFELSEIFOMANOPTTHENCASEMANMODEOF1:ukout:=lastukout+MANF;2:ukout:=lastukout-MANF;3:ukout:=lastukout+MANS;4:ukout:=lastukout-MANS;ELSEukout:=lastukout;END_CASE;ELSECASEMANMODEOF1:ukout:=lastukout+0.01*MANF*(ENGU-ENGL);2:ukout:=lastukout-0.01*MANF*(ENGU-ENGL);3:ukout:=lastukout+0.01*MANS*(ENGU-ENGL);4:ukout:=lastukout-0.01*MANS*(ENGU-ENGL);ELSEukout:=lastukout;END_CASE;END_IFIF(MOLSW)THENukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,ukout);ukout:=MAX(ENGL,ukout);END_IFOUT:=ukout;IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OUTOPT)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOMANOPTTHENCASEMANMODEOF1:duout:=MANF;2:duout:=-MANF;3:duout:=MANS;4:duout:=-MANS;ELSEduout:=0;END_CASE;ELSECASEMANMODEOF1:duout:=0.01*MANF*(ENGU-ENGL);2:duout:=-0.01*MANF*(ENGU-ENGL);3:duout:=0.01*MANS*(ENGU-ENGL);4:duout:=-0.01*MANS*(ENGU-ENGL);ELSEduout:=0;END_CASE;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OMANOPT)+0)))) 
 { 
	// Begin Translate CASEMANMODEOF1:duout:=MANF;2:duout:=-MANF;3:duout:=MANS;4:duout:=-MANS;ELSEduout:=0;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (1))
{
// Begin Translate duout:=MANF;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_MANF)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (2))
{
// Begin Translate duout:=-MANF;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (-(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (3))
{
// Begin Translate duout:=MANS;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_MANS)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (4))
{
// Begin Translate duout:=-MANS;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (-(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))); 
}
// End Translate
}else 
 {// Begin Translate duout:=0;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (0); 
}
// End Translate
 
 }
}
// End Translate
} 
else  
 { 
	// Begin Translate CASEMANMODEOF1:duout:=0.01*MANF*(ENGU-ENGL);2:duout:=-0.01*MANF*(ENGU-ENGL);3:duout:=0.01*MANS*(ENGU-ENGL);4:duout:=-0.01*MANS*(ENGU-ENGL);ELSEduout:=0;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (1))
{
// Begin Translate duout:=0.01*MANF*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (2))
{
// Begin Translate duout:=-0.01*MANF*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((-(0.01f))*(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (3))
{
// Begin Translate duout:=0.01*MANS*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (4))
{
// Begin Translate duout:=-0.01*MANS*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((-(0.01f))*(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else 
 {// Begin Translate duout:=0;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (0); 
}
// End Translate
 
 }
}
// End Translate
}
}
// End Translate
// Begin Translate IF(MOLSW)THENduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);ELSEduout:=MIN(ENGU,duout);duout:=MAX(ENGL,duout);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOLSW)+0)))) 
 { 
	// Begin Translate duout:=MIN(OUTU,duout);
{
{
	float arr_790_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_790_14, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(OUTL,duout);
{
{
	float arr_791_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_791_14, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate duout:=MIN(ENGU,duout);
{
{
	float arr_793_23[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_793_23, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(ENGL,duout);
{
{
	float arr_794_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_794_14, 2));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate OUT:=duout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENdu:=duout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate du:=duout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENdu:=duout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate du:=duout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,801);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFOMANOPTTHENCASEMANMODEOF1:ukout:=lastukout+MANF;2:ukout:=lastukout-MANF;3:ukout:=lastukout+MANS;4:ukout:=lastukout-MANS;ELSEukout:=lastukout;END_CASE;ELSECASEMANMODEOF1:ukout:=lastukout+0.01*MANF*(ENGU-ENGL);2:ukout:=lastukout-0.01*MANF*(ENGU-ENGL);3:ukout:=lastukout+0.01*MANS*(ENGU-ENGL);4:ukout:=lastukout-0.01*MANS*(ENGU-ENGL);ELSEukout:=lastukout;END_CASE;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OMANOPT)+0)))) 
 { 
	// Begin Translate CASEMANMODEOF1:ukout:=lastukout+MANF;2:ukout:=lastukout-MANF;3:ukout:=lastukout+MANS;4:ukout:=lastukout-MANS;ELSEukout:=lastukout;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (1))
{
// Begin Translate ukout:=lastukout+MANF;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))+(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (2))
{
// Begin Translate ukout:=lastukout-MANF;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (3))
{
// Begin Translate ukout:=lastukout+MANS;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))+(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (4))
{
// Begin Translate ukout:=lastukout-MANS;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))); 
}
// End Translate
}else 
 {// Begin Translate ukout:=lastukout;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))); 
}
// End Translate
 
 }
}
// End Translate
} 
else  
 { 
	// Begin Translate CASEMANMODEOF1:ukout:=lastukout+0.01*MANF*(ENGU-ENGL);2:ukout:=lastukout-0.01*MANF*(ENGU-ENGL);3:ukout:=lastukout+0.01*MANS*(ENGU-ENGL);4:ukout:=lastukout-0.01*MANS*(ENGU-ENGL);ELSEukout:=lastukout;END_CASE
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (1))
{
// Begin Translate ukout:=lastukout+0.01*MANF*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (2))
{
// Begin Translate ukout:=lastukout-0.01*MANF*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANF)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (3))
{
// Begin Translate ukout:=lastukout+0.01*MANS*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_MANMODE)+0))))== (4))
{
// Begin Translate ukout:=lastukout-0.01*MANS*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_MANS)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}else 
 {// Begin Translate ukout:=lastukout;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))); 
}
// End Translate
 
 }
}
// End Translate
}
}
// End Translate
// Begin Translate IF(MOLSW)THENukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);ELSEukout:=MIN(ENGU,ukout);ukout:=MAX(ENGL,ukout);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOLSW)+0)))) 
 { 
	// Begin Translate ukout:=MIN(OUTU,ukout);
{
{
	float arr_825_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_825_14, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(OUTL,ukout);
{
{
	float arr_826_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_826_14, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate ukout:=MIN(ENGU,ukout);
{
{
	float arr_828_23[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_828_23, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(ENGL,ukout);
{
{
	float arr_829_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_829_14, 2));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate OUT:=ukout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0))));}
  
}
// End Translate
// Begin Translate IFOCTYP=0THENuk:=ukout-OUTCOMP;ELSIFOCTYP=1THENIFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate uk:=ukout-OUTCOMP;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENuk:=ukout/OUTCOMP;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate uk:=ukout/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,836);
 return ;   
} 
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
// Begin Translate MANMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_MANMODE)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate ek:=sp1-PV;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate ek:=-ek-INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = (( -(*(float*)((float*)((bool*)(pHead->H_EK)+0))) )-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ek:=ek+INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))+(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(PIDTYPE=2ANDTRKOPT)THENINTERSP:=PV-INCOMP;INTERSP:=MIN(SPU,INTERSP);INTERSP:=MAX(SPL,INTERSP);ELSEIFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);SP1:=SP;IF(PIDTYPE=3ANDMODE=0)THENSP1:=SP;END_IFEND_IFEND_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &(*(bool*)((bool*)((bool*)(pHead->H_TRKOPT)+0)))) 
 { 
	// Begin Translate INTERSP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_INTERSP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
// Begin Translate INTERSP:=MIN(SPU,INTERSP);
{
{
	float arr_851_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))};
*((float*)((bool*)(pHead->H_INTERSP)+0)) = (H_MIN_FLOAT(arr_851_14, 2));
}
 
}
// End Translate
// Begin Translate INTERSP:=MAX(SPL,INTERSP);
{
{
	float arr_852_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))};
*((float*)((bool*)(pHead->H_INTERSP)+0)) = (H_MAX_FLOAT(arr_852_14, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFTRKOPTTHENSP:=PV-INCOMP;SP:=MIN(SPU,SP);SP:=MAX(SPL,SP);SP1:=SP;IF(PIDTYPE=3ANDMODE=0)THENSP1:=SP;END_IFEND_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_TRKOPT)+0)))) 
 { 
	// Begin Translate SP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_SP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
// Begin Translate SP:=MIN(SPU,SP);
{
{
	float arr_856_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MIN_FLOAT(arr_856_10, 2));
}
 
}
// End Translate
// Begin Translate SP:=MAX(SPL,SP);
{
{
	float arr_857_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_SPL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_SP)+0)))};
*((float*)((bool*)(pHead->H_SP)+0)) = (H_MAX_FLOAT(arr_857_10, 2));
}
 
}
// End Translate
// Begin Translate SP1:=SP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))); 
}
// End Translate
// Begin Translate IF(PIDTYPE=3ANDMODE=0)THENSP1:=SP;END_IF
{
if(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (3)) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) ) 
 { 
	// Begin Translate SP1:=SP;
{
*((float*)((bool*)(pHead->H_SP1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP)+0)))); 
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate IFPIDTYPE=2AND(MODE=2ORMODE=1)ANDCTRBP=1ANDpreCTRBP=1THENIFACTOPTTHENOUT:=(SP-PVL)/(PVU-PVL)*(ENGU-ENGL)+ENGL;ELSEOUT:=ENGU-(SP-PVL)/(PVU-PVL)*(ENGU-ENGL);END_IFOUT:=MIN(OUTU,OUT);OUT:=MAX(OUTL,OUT);RCMD:=0;IF(ABS(OUT-lastOUT)>0.01*RealOutRat*(ENGU-ENGL))THENIF(OUT>lastOUT)THENOUT:=lastOUT+0.01*RealOutRat*(ENGU-ENGL);ELSEOUT:=lastOUT-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(OUT>OUTUOR(ABS(OUT-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(OUT>OUTUOR(ABS(OUT-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFELSEIF(ABS((sp1-SPCAL)/(PVU-PVL))>RealGiveRat*0.01)THENIF(sp1>SPCAL)THENSPCAL:=SPCAL+(PVU-PVL)*RealGiveRat*0.01;ELSESPCAL:=SPCAL-(PVU-PVL)*RealGiveRat*0.01;END_IFELSESPCAL:=sp1;END_IFek:=SPCAL-PV;IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IFcycletime:=CYC;IFPK=0THENIFEQN=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(ek-EK_1)/DT1);dudd:=DK-D1;D1:=DK;ELSIFEQN=1OREQN=2THENIFACTOPT=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);ELSEDK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);END_IFdudd:=DK-D1;D1:=DK;END_IFIF((ABS(ek)<=DeadInterval)AND(DD=1)OR((((AUXOVEAND16#05)=1)ANDEK>0)OR(((AUXOVEAND16#06)=2)ANDEK<0)OR(((AUXOVEAND16#05)=5)ANDEK<0)OR(((AUXOVEAND16#06)=6)ANDEK>0)))THENdu:=0;DK:=0;D1:=0;dudd:=0;ELSEIF(ABS(ek)<=DeadIntervalANDDD=0)THENDD:=1;ELSEDD:=0;END_IFIF(ABS(ek)<=SV1)THENsi:=1;ELSEsi:=0;END_IFIFTI=0ORsi=0THENIFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IFEND_IFIFTI<>0ANDsi=1THENIFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IFEND_IFIF((EK<0ORABS(EK)<0.000001)ANDABS(OUT-OUTL)<0.000001)THENdu:=0;END_IFIF((EK>0ORABS(EK)<0.000001)ANDABS(OUT-OUTU)<0.000001)THENdu:=0;END_IFEND_IFEND_IFIF(PK=0ORPK=1)THENIFOUTOPT=1THENIFOCTYP=0THENduout:=du+OUTCOMP+DK;ELSIFOCTYP=1THENduout:=(du+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLSAND(duout>OUTUORduout<OUTL))THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IFIF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);MOFLAG:=FALSE;END_IFIF(ABS(duout-lastduout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFOUT:=duout;ELSEIF(ORSTSAND16#1)=16#1THENIF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF;END_IF;uk:=U1+du;IFOCTYP=0THENIF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IFukout:=uk+OUTCOMP+DK;ELSIFOCTYP=1THENIFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IFukout:=(uk+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLS)AND(ukout>OUTUORukout<OUTL)THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IFIF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);MOFLAG:=FALSE;END_IFIF(ABS(ukout-lastukout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(ukout>OUTUOR(ABS(ukout-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(ukout<OUTLOR(ABS(ukout-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFOUT:=ukout;END_IFEND_IFEND_IF
{
if(((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) &(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) ) ) &((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))  ==  (1)) ) &((*(bool*)((bool*)((bool*)(pHead->H_PRECTRBP)+0)))  ==  (1)) ) 
 { 
	// Begin Translate IFACTOPTTHENOUT:=(SP-PVL)/(PVU-PVL)*(ENGU-ENGL)+ENGL;ELSEOUT:=ENGU-(SP-PVL)/(PVU-PVL)*(ENGU-ENGL);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))) 
 { 
	// Begin Translate OUT:=(SP-PVL)/(PVU-PVL)*(ENGU-ENGL)+ENGL;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,870);
 return ;   
} 
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )+(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))));}
  
}
// End Translate
} 
else  
 { 
	// Begin Translate OUT:=ENGU-(SP-PVL)/(PVU-PVL)*(ENGU-ENGL);
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,872);
 return ;   
} 
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-( (*(float*)((float*)((bool*)(pHead->H_SP)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) ));}
  
}
// End Translate
}
}
// End Translate
// Begin Translate OUT:=MIN(OUTU,OUT);
{
{
	float arr_874_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_OUT)+0)))};
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = (H_MIN_FLOAT(arr_874_10, 2));}
 
}
 
}
// End Translate
// Begin Translate OUT:=MAX(OUTL,OUT);
{
{
	float arr_875_10[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_OUT)+0)))};
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = (H_MAX_FLOAT(arr_875_10, 2));}
 
}
 
}
// End Translate
// Begin Translate RCMD:=0;
{
*((uint8_t*)((bool*)(pHead->H_RCMD)+0)) = (0); 
}
// End Translate
// Begin Translate IF(ABS(OUT-lastOUT)>0.01*RealOutRat*(ENGU-ENGL))THENIF(OUT>lastOUT)THENOUT:=lastOUT+0.01*RealOutRat*(ENGU-ENGL);ELSEOUT:=lastOUT-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IF
{
if((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_LASTOUT)+0))))>(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )) 
 { 
	// Begin Translate IF(OUT>lastOUT)THENOUT:=lastOUT+0.01*RealOutRat*(ENGU-ENGL);ELSEOUT:=lastOUT-0.01*RealOutRat*(ENGU-ENGL);END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_LASTOUT)+0)))) 
 { 
	// Begin Translate OUT:=lastOUT+0.01*RealOutRat*(ENGU-ENGL);
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTOUT)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) ));}
  
}
// End Translate
} 
else  
 { 
	// Begin Translate OUT:=lastOUT-0.01*RealOutRat*(ENGU-ENGL);
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTOUT)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) ));}
  
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(OUT>OUTUOR(ABS(OUT-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(OUT>OUTUOR(ABS(OUT-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate OVE:=OVEAND16#FD;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(253)); 
}
// End Translate
// Begin Translate OVE:=OVEOR16#01;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(1)); 
}
// End Translate
} 
else if(((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate OVE:=OVEAND16#FE;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(254)); 
}
// End Translate
// Begin Translate OVE:=OVEOR16#02;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(2)); 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate IF(ABS((sp1-SPCAL)/(PVU-PVL))>RealGiveRat*0.01)THENIF(sp1>SPCAL)THENSPCAL:=SPCAL+(PVU-PVL)*RealGiveRat*0.01;ELSESPCAL:=SPCAL-(PVU-PVL)*RealGiveRat*0.01;END_IFELSESPCAL:=sp1;END_IF
{
if((float)fabs(( (*(float*)((float*)((bool*)(pHead->H_SP1)+0)))-(*(float*)((float*)((bool*)(pHead->H_SPCAL)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) ))>(*(float*)((float*)((bool*)(pHead->H_REALGIVERAT)+0)))*(0.01f)) 
 { 
	// Begin Translate IF(sp1>SPCAL)THENSPCAL:=SPCAL+(PVU-PVL)*RealGiveRat*0.01;ELSESPCAL:=SPCAL-(PVU-PVL)*RealGiveRat*0.01;END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))>(*(float*)((float*)((bool*)(pHead->H_SPCAL)+0)))) 
 { 
	// Begin Translate SPCAL:=SPCAL+(PVU-PVL)*RealGiveRat*0.01;
{
*((float*)((bool*)(pHead->H_SPCAL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPCAL)+0)))+( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*(*(float*)((float*)((bool*)(pHead->H_REALGIVERAT)+0)))*(0.01f)); 
}
// End Translate
} 
else  
 { 
	// Begin Translate SPCAL:=SPCAL-(PVU-PVL)*RealGiveRat*0.01;
{
*((float*)((bool*)(pHead->H_SPCAL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPCAL)+0)))-( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*(*(float*)((float*)((bool*)(pHead->H_REALGIVERAT)+0)))*(0.01f)); 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate SPCAL:=sp1;
{
*((float*)((bool*)(pHead->H_SPCAL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate ek:=SPCAL-PV;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SPCAL)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFACTOPT=0THENek:=-ek-INCOMP;ELSEek:=ek+INCOMP;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate ek:=-ek-INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = (( -(*(float*)((float*)((bool*)(pHead->H_EK)+0))) )-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ek:=ek+INCOMP;
{
*((float*)((bool*)(pHead->H_EK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))+(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate cycletime:=CYC;
{
*((float*)((bool*)(pHead->H_CYCLETIME)+0)) = ((*(float*)((float*)((bool*)(pHead->H_CYC)+0)))); 
}
// End Translate
// Begin Translate IFPK=0THENIFEQN=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(ek-EK_1)/DT1);dudd:=DK-D1;D1:=DK;ELSIFEQN=1OREQN=2THENIFACTOPT=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);ELSEDK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);END_IFdudd:=DK-D1;D1:=DK;END_IFIF((ABS(ek)<=DeadInterval)AND(DD=1)OR((((AUXOVEAND16#05)=1)ANDEK>0)OR(((AUXOVEAND16#06)=2)ANDEK<0)OR(((AUXOVEAND16#05)=5)ANDEK<0)OR(((AUXOVEAND16#06)=6)ANDEK>0)))THENdu:=0;DK:=0;D1:=0;dudd:=0;ELSEIF(ABS(ek)<=DeadIntervalANDDD=0)THENDD:=1;ELSEDD:=0;END_IFIF(ABS(ek)<=SV1)THENsi:=1;ELSEsi:=0;END_IFIFTI=0ORsi=0THENIFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IFEND_IFIFTI<>0ANDsi=1THENIFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IFEND_IFIF((EK<0ORABS(EK)<0.000001)ANDABS(OUT-OUTL)<0.000001)THENdu:=0;END_IFIF((EK>0ORABS(EK)<0.000001)ANDABS(OUT-OUTU)<0.000001)THENdu:=0;END_IFEND_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_PK)+0)))  ==  (0)) 
 { 
	// Begin Translate IFEQN=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(ek-EK_1)/DT1);dudd:=DK-D1;D1:=DK;ELSIFEQN=1OREQN=2THENIFACTOPT=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);ELSEDK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);END_IFdudd:=DK-D1;D1:=DK;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (0)) 
 { 
	// Begin Translate DK:=(TD/(KD*cycletime+TD))*(D1+KD*(ek-EK_1)/DT1);
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,914);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,914);
 return ;   
} 
*((float*)((bool*)(pHead->H_DK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_TD)+0)))/( (*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_D1)+0)))+(*(float*)((float*)((bool*)(pHead->H_KD)+0)))*( (*(float*)((float*)((bool*)(pHead->H_EK)+0)))-(*(float*)((float*)((bool*)(pHead->H_EK_1)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0))) )); 
}
// End Translate
// Begin Translate dudd:=DK-D1;
{
*((float*)((bool*)(pHead->H_DUDD)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DK)+0)))-(*(float*)((float*)((bool*)(pHead->H_D1)+0)))); 
}
// End Translate
// Begin Translate D1:=DK;
{
*((float*)((bool*)(pHead->H_D1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DK)+0)))); 
}
// End Translate
} 
else if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (1)) |((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (2)) ) 
 { 
	// Begin Translate IFACTOPT=0THENDK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);ELSEDK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate DK:=(TD/(KD*cycletime+TD))*(D1+KD*(PV-prePV)/DT1);
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,919);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,919);
 return ;   
} 
*((float*)((bool*)(pHead->H_DK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_TD)+0)))/( (*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_D1)+0)))+(*(float*)((float*)((bool*)(pHead->H_KD)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PREPV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0))) )); 
}
// End Translate
} 
else  
 { 
	// Begin Translate DK:=(TD/(KD*cycletime+TD))*(D1+KD*(prePV-PV)/DT1);
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,921);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,921);
 return ;   
} 
*((float*)((bool*)(pHead->H_DK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_TD)+0)))/( (*(float*)((float*)((bool*)(pHead->H_KD)+0)))*(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))+(*(float*)((float*)((bool*)(pHead->H_TD)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_D1)+0)))+(*(float*)((float*)((bool*)(pHead->H_KD)+0)))*( (*(float*)((float*)((bool*)(pHead->H_PREPV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0))) )); 
}
// End Translate
}
}
// End Translate
// Begin Translate dudd:=DK-D1;
{
*((float*)((bool*)(pHead->H_DUDD)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DK)+0)))-(*(float*)((float*)((bool*)(pHead->H_D1)+0)))); 
}
// End Translate
// Begin Translate D1:=DK;
{
*((float*)((bool*)(pHead->H_D1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DK)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((ABS(ek)<=DeadInterval)AND(DD=1)OR((((AUXOVEAND16#05)=1)ANDEK>0)OR(((AUXOVEAND16#06)=2)ANDEK<0)OR(((AUXOVEAND16#05)=5)ANDEK<0)OR(((AUXOVEAND16#06)=6)ANDEK>0)))THENdu:=0;DK:=0;D1:=0;dudd:=0;ELSEIF(ABS(ek)<=DeadIntervalANDDD=0)THENDD:=1;ELSEDD:=0;END_IFIF(ABS(ek)<=SV1)THENsi:=1;ELSEsi:=0;END_IFIFTI=0ORsi=0THENIFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IFEND_IFIFTI<>0ANDsi=1THENIFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IFEND_IFIF((EK<0ORABS(EK)<0.000001)ANDABS(OUT-OUTL)<0.000001)THENdu:=0;END_IFIF((EK>0ORABS(EK)<0.000001)ANDABS(OUT-OUTU)<0.000001)THENdu:=0;END_IFEND_IF
{
if((((fabs((float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0)))) - ((*(float*)((float*)((bool*)(pHead->H_DEADINTERVAL)+0))))) <= 1.175494351e-38F ||(float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0))))<(*(float*)((float*)((bool*)(pHead->H_DEADINTERVAL)+0))) )) &((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_DD)+0)))  ==  (1)) ) |(((((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(5) )  ==  (1)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) |((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(6) )  ==  (2)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) ) |((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(5) )  ==  (5)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) ) |((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_AUXOVE)+0)))&(6) )  ==  (6)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) ) ) 
 { 
	// Begin Translate du:=0;
{
*((float*)((bool*)(pHead->H_DU)+0)) = (0); 
}
// End Translate
// Begin Translate DK:=0;
{
*((float*)((bool*)(pHead->H_DK)+0)) = (0); 
}
// End Translate
// Begin Translate D1:=0;
{
*((float*)((bool*)(pHead->H_D1)+0)) = (0); 
}
// End Translate
// Begin Translate dudd:=0;
{
*((float*)((bool*)(pHead->H_DUDD)+0)) = (0); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IF(ABS(ek)<=DeadIntervalANDDD=0)THENDD:=1;ELSEDD:=0;END_IF
{
if(((fabs((float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0)))) - ((*(float*)((float*)((bool*)(pHead->H_DEADINTERVAL)+0))))) <= 1.175494351e-38F ||(float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0))))<(*(float*)((float*)((bool*)(pHead->H_DEADINTERVAL)+0))) )) &((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_DD)+0)))  ==  (0)) ) 
 { 
	// Begin Translate DD:=1;
{
*((uint8_t*)((bool*)(pHead->H_DD)+0)) = (1); 
}
// End Translate
} 
else  
 { 
	// Begin Translate DD:=0;
{
*((uint8_t*)((bool*)(pHead->H_DD)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(ABS(ek)<=SV1)THENsi:=1;ELSEsi:=0;END_IF
{
if((fabs((float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0)))) - ((*(float*)((float*)((bool*)(pHead->H_SV1)+0))))) <= 1.175494351e-38F ||(float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0))))<(*(float*)((float*)((bool*)(pHead->H_SV1)+0))) )) 
 { 
	// Begin Translate si:=1;
{
*((uint16_t*)((bool*)(pHead->H_SI)+0)) = (1); 
}
// End Translate
} 
else  
 { 
	// Begin Translate si:=0;
{
*((uint16_t*)((bool*)(pHead->H_SI)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate IFTI=0ORsi=0THENIFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IFEND_IF
{
if(((fabs((*(float*)((float*)((bool*)(pHead->H_TI)+0))) - ((0))) <= 1.175494351e-38F )) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_SI)+0)))  ==  (0)) ) 
 { 
	// Begin Translate IFEQN=0OREQN=1THENdu:=(ek-EK_1)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IFEND_IF
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (0)) |((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (1)) ) 
 { 
	// Begin Translate du:=(ek-EK_1)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,948);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_EK)+0)))-(*(float*)((float*)((bool*)(pHead->H_EK_1)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (2)) 
 { 
	// Begin Translate IFACTOPT=0THENdu:=(PV-prePV)/DT1;ELSEdu:=(prePV-PV)/DT1;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate du:=(PV-prePV)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,951);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PREPV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate du:=(prePV-PV)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,953);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_PREPV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IFTI<>0ANDsi=1THENIFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IFEND_IF
{
if(((fabs((*(float*)((float*)((bool*)(pHead->H_TI)+0))) - ((0))) > 1.175494351e-38F )) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_SI)+0)))  ==  (1)) ) 
 { 
	// Begin Translate IFEQN=0OREQN=1THENdu:=(ek-EK_1+cycletime*ek/TI)/DT1;ELSIFEQN=2THENIFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IFEND_IF
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (0)) |((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (1)) ) 
 { 
	// Begin Translate du:=(ek-EK_1+cycletime*ek/TI)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_TI)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,959);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,959);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( ( (*(float*)((float*)((bool*)(pHead->H_EK)+0)))-(*(float*)((float*)((bool*)(pHead->H_EK_1)+0))) )+(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))*(*(float*)((float*)((bool*)(pHead->H_EK)+0)))/(*(float*)((float*)((bool*)(pHead->H_TI)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_EQN)+0)))  ==  (2)) 
 { 
	// Begin Translate IFACTOPT=0THENdu:=(PV-prePV+cycletime*ek/TI)/DT1;ELSEdu:=(prePV-PV+cycletime*ek/TI)/DT1;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))  ==  (0)) 
 { 
	// Begin Translate du:=(PV-prePV+cycletime*ek/TI)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_TI)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,962);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,962);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( ( (*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PREPV)+0))) )+(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))*(*(float*)((float*)((bool*)(pHead->H_EK)+0)))/(*(float*)((float*)((bool*)(pHead->H_TI)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate du:=(prePV-PV+cycletime*ek/TI)/DT1;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_TI)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,964);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_DT1)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,964);
 return ;   
} 
*((float*)((bool*)(pHead->H_DU)+0)) = (( ( (*(float*)((float*)((bool*)(pHead->H_PREPV)+0)))-(*(float*)((float*)((bool*)(pHead->H_PV)+0))) )+(*(float*)((float*)((bool*)(pHead->H_CYCLETIME)+0)))*(*(float*)((float*)((bool*)(pHead->H_EK)+0)))/(*(float*)((float*)((bool*)(pHead->H_TI)+0))) )/(*(float*)((float*)((bool*)(pHead->H_DT1)+0)))); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((EK<0ORABS(EK)<0.000001)ANDABS(OUT-OUTL)<0.000001)THENdu:=0;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0))))<(0.000001f)) ) &((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate du:=0;
{
*((float*)((bool*)(pHead->H_DU)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((EK>0ORABS(EK)<0.000001)ANDABS(OUT-OUTU)<0.000001)THENdu:=0;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_EK)+0))))<(0.000001f)) ) &((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate du:=0;
{
*((float*)((bool*)(pHead->H_DU)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(PK=0ORPK=1)THENIFOUTOPT=1THENIFOCTYP=0THENduout:=du+OUTCOMP+DK;ELSIFOCTYP=1THENduout:=(du+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLSAND(duout>OUTUORduout<OUTL))THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IFIF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);MOFLAG:=FALSE;END_IFIF(ABS(duout-lastduout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFOUT:=duout;ELSEIF(ORSTSAND16#1)=16#1THENIF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF;END_IF;uk:=U1+du;IFOCTYP=0THENIF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IFukout:=uk+OUTCOMP+DK;ELSIFOCTYP=1THENIFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IFukout:=(uk+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLS)AND(ukout>OUTUORukout<OUTL)THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IFIF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);MOFLAG:=FALSE;END_IFIF(ABS(ukout-lastukout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(ukout>OUTUOR(ABS(ukout-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(ukout<OUTLOR(ABS(ukout-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFOUT:=ukout;END_IFEND_IF
{
if(((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_PK)+0)))  ==  (0)) |((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_PK)+0)))  ==  (1)) ) 
 { 
	// Begin Translate IFOUTOPT=1THENIFOCTYP=0THENduout:=du+OUTCOMP+DK;ELSIFOCTYP=1THENduout:=(du+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLSAND(duout>OUTUORduout<OUTL))THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IFIF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);MOFLAG:=FALSE;END_IFIF(ABS(duout-lastduout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFOUT:=duout;ELSEIF(ORSTSAND16#1)=16#1THENIF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF;END_IF;uk:=U1+du;IFOCTYP=0THENIF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IFukout:=uk+OUTCOMP+DK;ELSIFOCTYP=1THENIFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IFukout:=(uk+DK)*OUTCOMP;END_IFIF(nowRM=0ANDLMBLS)AND(ukout>OUTUORukout<OUTL)THENMOFLAG:=TRUE;END_IFIF(MOFLAGANDLMBLS)THENIF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IFIF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);MOFLAG:=FALSE;END_IFIF(ABS(ukout-lastukout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IFIF(ukout>OUTUOR(ABS(ukout-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(ukout<OUTLOR(ABS(ukout-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IFOUT:=ukout;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_OUTOPT)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOCTYP=0THENduout:=du+OUTCOMP+DK;ELSIFOCTYP=1THENduout:=(du+DK)*OUTCOMP;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate duout:=du+OUTCOMP+DK;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_DU)+0)))+(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) )+(*(float*)((float*)((bool*)(pHead->H_DK)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate duout:=(du+DK)*OUTCOMP;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_DU)+0)))+(*(float*)((float*)((bool*)(pHead->H_DK)+0))) )*(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(nowRM=0ANDLMBLSAND(duout>OUTUORduout<OUTL))THENMOFLAG:=TRUE;END_IF
{
if((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_NOWRM)+0)))  ==  (0)) &(*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))) &(((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) ) ) 
 { 
	// Begin Translate MOFLAG:=TRUE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (1); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(MOFLAGANDLMBLS)THENIF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IFIF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEduout:=MIN(OUTU,duout);duout:=MAX(OUTL,duout);MOFLAG:=FALSE;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOFLAG)+0)))&(*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))) 
 { 
	// Begin Translate IF(((duout>OUTU)AND(duout>lastduout))OR((duout<OUTL)AND(duout<lastduout)))THENduout:=lastduout;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) &((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))) ) |(((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) &((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))) ) ) 
 { 
	// Begin Translate duout:=lastduout;
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((duout<OUTUOR(ABS(duout-OUTU)<1.0E-6))AND(duout>OUTLOR(ABS(duout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(1.0E-6f)) ) &(((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(1.0E-6f)) ) ) 
 { 
	// Begin Translate MOFLAG:=FALSE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate duout:=MIN(OUTU,duout);
{
{
	float arr_1004_15[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MIN_FLOAT(arr_1004_15, 2));
}
 
}
// End Translate
// Begin Translate duout:=MAX(OUTL,duout);
{
{
	float arr_1005_15[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))};
*((float*)((bool*)(pHead->H_DUOUT)+0)) = (H_MAX_FLOAT(arr_1005_15, 2));
}
 
}
// End Translate
// Begin Translate MOFLAG:=FALSE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(ABS(duout-lastduout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IF
{
if((float)fabs((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0))))>(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )) 
 { 
	// Begin Translate IF(duout>lastduout)THENduout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);ELSEduout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))) 
 { 
	// Begin Translate duout:=lastduout+0.01*RealOutRat*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
} 
else  
 { 
	// Begin Translate duout:=lastduout-0.01*RealOutRat*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_DUOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTDUOUT)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate OUT:=duout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DUOUT)+0))));}
  
}
// End Translate
} 
else  
 { 
	// Begin Translate IF(ORSTSAND16#1)=16#1THENIF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF;END_IF
{
if(( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_ORSTS)+0)))&(1) )  ==  (1)) 
 { 
	// Begin Translate IF((ORSTSAND16#2)=16#2ANDEK>0)OR((ORSTSAND16#2)=16#0ANDEK<0)THENU1:=ORFB;ELSEU1:=ORFB+EK/(PVU-PVL)*100/KP*100;END_IF
{
if(((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_ORSTS)+0)))&(2) )  ==  (2)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))>(0)) ) |((( (*(uint8_t*)((uint8_t*)((bool*)(pHead->H_ORSTS)+0)))&(2) )  ==  (0)) &((*(float*)((float*)((bool*)(pHead->H_EK)+0)))<(0)) ) ) 
 { 
	// Begin Translate U1:=ORFB;
{
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_ORFB)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate U1:=ORFB+EK/(PVU-PVL)*100/KP*100;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1023);
 return ;   
} 
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_KP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1023);
 return ;   
} 
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_ORFB)+0)))+(*(float*)((float*)((bool*)(pHead->H_EK)+0)))/( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )*(100)/(*(float*)((float*)((bool*)(pHead->H_KP)+0)))*(100)); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate uk:=U1+du;
{
*((float*)((bool*)(pHead->H_UK)+0)) = ((*(float*)((float*)((bool*)(pHead->H_U1)+0)))+(*(float*)((float*)((bool*)(pHead->H_DU)+0)))); 
}
// End Translate
// Begin Translate IFOCTYP=0THENIF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IFukout:=uk+OUTCOMP+DK;ELSIFOCTYP=1THENIFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IFukout:=(uk+DK)*OUTCOMP;END_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate IF(NOTLMBLS)THENuk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);END_IF
{
if(0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))))) 
 { 
	// Begin Translate uk:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);
{
{
	float arr_1030_25[] = {(float)( (*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))+( (*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) ) )-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MIN_FLOAT(arr_1030_25, 2));
}
 
}
// End Translate
// Begin Translate uk:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)-OUTCOMP,uk);
{
{
	float arr_1031_20[] = {(float)( (*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))-( (*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) ) )-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MAX_FLOAT(arr_1031_20, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate uk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);
{
{
	float arr_1033_29[] = {(float)( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))+( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) ) )-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MIN_FLOAT(arr_1033_29, 2));
}
 
}
// End Translate
// Begin Translate uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)-OUTCOMP,uk);
{
{
	float arr_1034_20[] = {(float)( (*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))-( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) ) )-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MAX_FLOAT(arr_1034_20, 2));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate ukout:=uk+OUTCOMP+DK;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_UK)+0)))+(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) )+(*(float*)((float*)((bool*)(pHead->H_DK)+0)))); 
}
// End Translate
} 
else if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOUTCOMP<>0THENIF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IFEND_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate IF(NOTLMBLS)THENuK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);ELSEuk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);END_IF
{
if(0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))))) 
 { 
	// Begin Translate uK:=MIN(OUTU+(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);
{
{
	float arr_1040_26[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))+( (*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) )/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MIN_FLOAT(arr_1040_26, 2));
}
 
}
// End Translate
// Begin Translate uK:=MAX(OUTL-(OUTU-OUTL)*(SATDB/100.00)/OUTCOMP,uk);
{
{
	float arr_1041_21[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))-( (*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) )/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MAX_FLOAT(arr_1041_21, 2));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate uk:=MIN(ENGU+(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);
{
{
	float arr_1043_30[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))+( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) )/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MIN_FLOAT(arr_1043_30, 2));
}
 
}
// End Translate
// Begin Translate uk:=MAX(ENGL-(ENGU-ENGL)*(SATDB/100.00)/OUTCOMP,uk);
{
{
	float arr_1044_21[] = {(float)(*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))-( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_SATDB)+0)))/(100.00f) )/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UK)+0)))};
*((float*)((bool*)(pHead->H_UK)+0)) = (H_MAX_FLOAT(arr_1044_21, 2));
}
 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate ukout:=(uk+DK)*OUTCOMP;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_UK)+0)))+(*(float*)((float*)((bool*)(pHead->H_DK)+0))) )*(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(nowRM=0ANDLMBLS)AND(ukout>OUTUORukout<OUTL)THENMOFLAG:=TRUE;END_IF
{
if((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_NOWRM)+0)))  ==  (0)) &(*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))) &(((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) ) ) 
 { 
	// Begin Translate MOFLAG:=TRUE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (1); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(MOFLAGANDLMBLS)THENIF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IFIF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IFELSEukout:=MIN(OUTU,ukout);ukout:=MAX(OUTL,ukout);MOFLAG:=FALSE;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_MOFLAG)+0)))&(*(bool*)((bool*)((bool*)(pHead->H_LMBLS)+0)))) 
 { 
	// Begin Translate IF((ukout>OUTU)AND(ukout>lastukout))OR((ukout<OUTL)AND(ukout<lastukout))THENukout:=lastukout;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) &((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))) ) |(((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) &((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))) ) ) 
 { 
	// Begin Translate ukout:=lastukout;
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF((ukout<OUTUOR(ABS(ukout-OUTU)<1.0E-6))AND(ukout>OUTLOR(ABS(ukout-OUTL)<1.0E-6)))THENMOFLAG:=FALSE;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(1.0E-6f)) ) &(((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(1.0E-6f)) ) ) 
 { 
	// Begin Translate MOFLAG:=FALSE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
} 
else  
 { 
	// Begin Translate ukout:=MIN(OUTU,ukout);
{
{
	float arr_1065_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MIN_FLOAT(arr_1065_14, 2));
}
 
}
// End Translate
// Begin Translate ukout:=MAX(OUTL,ukout);
{
{
	float arr_1066_14[] = {(float)(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))),(float)(*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))};
*((float*)((bool*)(pHead->H_UKOUT)+0)) = (H_MAX_FLOAT(arr_1066_14, 2));
}
 
}
// End Translate
// Begin Translate MOFLAG:=FALSE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (0); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(ABS(ukout-lastukout)>0.01*RealOutRat*(ENGU-ENGL))THENIF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IFEND_IF
{
if((float)fabs((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0))))>(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )) 
 { 
	// Begin Translate IF(ukout>lastukout)THENukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);ELSEukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);END_IF
{
if((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))) 
 { 
	// Begin Translate ukout:=lastukout+0.01*RealOutRat*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))+(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
} 
else  
 { 
	// Begin Translate ukout:=lastukout-0.01*RealOutRat*(ENGU-ENGL);
{
*((float*)((bool*)(pHead->H_UKOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_LASTUKOUT)+0)))-(0.01f)*(*(float*)((float*)((bool*)(pHead->H_REALOUTRAT)+0)))*( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(ukout>OUTUOR(ABS(ukout-OUTU)<0.000001))THENOVE:=OVEAND16#FD;OVE:=OVEOR16#01;ELSIF(ukout<OUTLOR(ABS(ukout-OUTL)<0.000001))THENOVE:=OVEAND16#FE;OVE:=OVEOR16#02;END_IF
{
if(((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate OVE:=OVEAND16#FD;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(253)); 
}
// End Translate
// Begin Translate OVE:=OVEOR16#01;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(1)); 
}
// End Translate
} 
else if(((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(0.000001f)) ) 
 { 
	// Begin Translate OVE:=OVEAND16#FE;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(254)); 
}
// End Translate
// Begin Translate OVE:=OVEOR16#02;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(2)); 
}
// End Translate
} 
}
// End Translate
// Begin Translate OUT:=ukout;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_OUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_OUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_OUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UKOUT)+0))));}
  
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
// Begin Translate IF((OUT<OUTUORABS(OUT-OUTU)<1.0E-6)AND(OUT>OUTLORABS(OUT-OUTL)<1.0E-6))THENMOFLAG:=FALSE;END_IF
{
if((((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))<(*(float*)((float*)((bool*)(pHead->H_OUTU)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTU)+0))))<(1.0E-6f)) ) &(((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))>(*(float*)((float*)((bool*)(pHead->H_OUTL)+0)))) |((float)fabs((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTL)+0))))<(1.0E-6f)) ) ) 
 { 
	// Begin Translate MOFLAG:=FALSE;
{
*((bool*)((bool*)(pHead->H_MOFLAG)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(PMSW<>1)THENPMOUT:=OUT;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_PMSW)+0)))  !=  (1)) 
 { 
	// Begin Translate PMOUT:=OUT;
{
	//The mandatory variable for this variable 
 	if( VarAddrIsInvalid((float*)((bool*)(pHead->H_PMOUT)+0)) || !(*((bool*)((float*)((bool*)(pHead->H_PMOUT)+0))+uiFORCE_OFFSET))) 
{
*((float*)((bool*)(pHead->H_PMOUT)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0))));}
  
}
// End Translate
} 
}
// End Translate
// Begin Translate almerror:=ek;
{
*((float*)((bool*)(pHead->H_ALMERROR)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))); 
}
// End Translate
// Begin Translate IFNOT(INHDAL)ANDDALLV>0ANDALMOPTTHENIFABS(almerror)>DevalmLimitTHENDA:=1;AM:=B_WRITE(AM,7,TRUE);ELSEDA:=0;AM:=B_WRITE(AM,7,FALSE);END_IFELSEDA:=0;AM:=B_WRITE(AM,7,FALSE);END_IF
{
if(((0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_INHDAL)+0)))))) &((int32_t)((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_DALLV)+0))))  >  (0)) ) &(*(bool*)((bool*)((bool*)(pHead->H_ALMOPT)+0)))) 
 { 
	// Begin Translate IFABS(almerror)>DevalmLimitTHENDA:=1;AM:=B_WRITE(AM,7,TRUE);ELSEDA:=0;AM:=B_WRITE(AM,7,FALSE);END_IF
{
if((float)fabs((*(float*)((float*)((bool*)(pHead->H_ALMERROR)+0))))>(*(float*)((float*)((bool*)(pHead->H_DEVALMLIMIT)+0)))) 
 { 
	// Begin Translate DA:=1;
{
*((bool*)((bool*)(pHead->H_DA)+0)) = (1); 
}
// End Translate
// Begin Translate AM:=B_WRITE(AM,7,TRUE);
{
{
int16_t  constVar1105151  =7;
bool  constVar1105152  =1;
struct  __AT__B_WRITE   Head110515 ;
Head110515.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head110515.H_WB = (int16_t*)&constVar1105151;
Head110515.H_IN = (bool*)&constVar1105152;
uint16_t  Var110515 = 0  ;
Head110515.H_B_WRITE=(uint16_t*)&Var110515; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head110515, uiFORCE_OFFSET), Var110515));
}
 
}
// End Translate
} 
else  
 { 
	// Begin Translate DA:=0;
{
*((bool*)((bool*)(pHead->H_DA)+0)) = (0); 
}
// End Translate
// Begin Translate AM:=B_WRITE(AM,7,FALSE);
{
{
int16_t  constVar1108151  =7;
bool  constVar1108152  =0;
struct  __AT__B_WRITE   Head110815 ;
Head110815.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head110815.H_WB = (int16_t*)&constVar1108151;
Head110815.H_IN = (bool*)&constVar1108152;
uint16_t  Var110815 = 0  ;
Head110815.H_B_WRITE=(uint16_t*)&Var110815; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head110815, uiFORCE_OFFSET), Var110815));
}
 
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate DA:=0;
{
*((bool*)((bool*)(pHead->H_DA)+0)) = (0); 
}
// End Translate
// Begin Translate AM:=B_WRITE(AM,7,FALSE);
{
{
int16_t  constVar1112141  =7;
bool  constVar1112142  =0;
struct  __AT__B_WRITE   Head111214 ;
Head111214.H_VALUE = (uint16_t*)((bool*)(pHead->H_AM)+0);
Head111214.H_WB = (int16_t*)&constVar1112141;
Head111214.H_IN = (bool*)&constVar1112142;
uint16_t  Var111214 = 0  ;
Head111214.H_B_WRITE=(uint16_t*)&Var111214; 
 *((uint16_t*)((bool*)(pHead->H_AM)+0)) = ((H_B_WRITE(&Head111214, uiFORCE_OFFSET), Var111214));
}
 
}
// End Translate
}
}
// End Translate
// Begin Translate MANMODE:=0;
{
*((uint8_t*)((bool*)(pHead->H_MANMODE)+0)) = (0); 
}
// End Translate
// Begin Translate IF(CTRBP=1)THENIFOCTYP=0THENU1:=OUT-OUTCOMP;I1:=OUT-OUTCOMP;ELSEIFOUTCOMP<>0THENU1:=OUT/OUTCOMP;I1:=OUT/OUTCOMP;ELSEU1:=0;I1:=0;END_IFEND_IFELSEU1:=uk;I1:=du;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))  ==  (1)) 
 { 
	// Begin Translate IFOCTYP=0THENU1:=OUT-OUTCOMP;I1:=OUT-OUTCOMP;ELSEIFOUTCOMP<>0THENU1:=OUT/OUTCOMP;I1:=OUT/OUTCOMP;ELSEU1:=0;I1:=0;END_IFEND_IF
{
if((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OCTYP)+0)))  ==  (0)) 
 { 
	// Begin Translate U1:=OUT-OUTCOMP;
{
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
// Begin Translate I1:=OUT-OUTCOMP;
{
*((float*)((bool*)(pHead->H_I1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate IFOUTCOMP<>0THENU1:=OUT/OUTCOMP;I1:=OUT/OUTCOMP;ELSEU1:=0;I1:=0;END_IF
{
if((fabs((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0))) - ((0))) > 1.175494351e-38F )) 
 { 
	// Begin Translate U1:=OUT/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1127);
 return ;   
} 
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
// Begin Translate I1:=OUT/OUTCOMP;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1128);
 return ;   
} 
*((float*)((bool*)(pHead->H_I1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_OUT)+0)))/(*(float*)((float*)((bool*)(pHead->H_OUTCOMP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate U1:=0;
{
*((float*)((bool*)(pHead->H_U1)+0)) = (0); 
}
// End Translate
// Begin Translate I1:=0;
{
*((float*)((bool*)(pHead->H_I1)+0)) = (0); 
}
// End Translate
}
}
// End Translate
}
}
// End Translate
} 
else  
 { 
	// Begin Translate U1:=uk;
{
*((float*)((bool*)(pHead->H_U1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_UK)+0)))); 
}
// End Translate
// Begin Translate I1:=du;
{
*((float*)((bool*)(pHead->H_I1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_DU)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate EK_2:=EK_1;
{
*((float*)((bool*)(pHead->H_EK_2)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK_1)+0)))); 
}
// End Translate
// Begin Translate EK_1:=ek;
{
*((float*)((bool*)(pHead->H_EK_1)+0)) = ((*(float*)((float*)((bool*)(pHead->H_EK)+0)))); 
}
// End Translate
// Begin Translate prePV:=PV;
{
*((float*)((bool*)(pHead->H_PREPV)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))); 
}
// End Translate
// Begin Translate IFPIDTYPE=2THENCOMP:=INTERSP;ELSECOMP:=PV-INCOMP;END_IF
{
if((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) 
 { 
	// Begin Translate COMP:=INTERSP;
{
*((float*)((bool*)(pHead->H_COMP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_INTERSP)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate COMP:=PV-INCOMP;
{
*((float*)((bool*)(pHead->H_COMP)+0)) = ((*(float*)((float*)((bool*)(pHead->H_PV)+0)))-(*(float*)((float*)((bool*)(pHead->H_INCOMP)+0)))); 
}
// End Translate
}
}
// End Translate
// Begin Translate IF(CTRBP=1ANDNOTpreCTRBPANDPIDTYPE=2AND(MODE=2ORMODE=1ORMODE=0))THENOVE:=OVEOR16#08;MODE:=2;IFACTOPTTHENCOMP:=(OUT-ENGL)/(ENGU-ENGL)*(PVU-PVL)+PVL;ELSECOMP:=(ENGU-OUT)/(ENGU-ENGL)*(PVU-PVL)+PVL;END_IFEND_IF
{
if(((((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))  ==  (1)) &(0x1 & (~((*(bool*)((bool*)((bool*)(pHead->H_PRECTRBP)+0)))))) ) &((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_PIDTYPE)+0)))  ==  (2)) ) &((((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) ) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (0)) ) ) 
 { 
	// Begin Translate OVE:=OVEOR16#08;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(8)); 
}
// End Translate
// Begin Translate MODE:=2;
{
*((uint16_t*)((bool*)(pHead->H_MODE)+0)) = (2); 
}
// End Translate
// Begin Translate IFACTOPTTHENCOMP:=(OUT-ENGL)/(ENGU-ENGL)*(PVU-PVL)+PVL;ELSECOMP:=(ENGU-OUT)/(ENGU-ENGL)*(PVU-PVL)+PVL;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))) 
 { 
	// Begin Translate COMP:=(OUT-ENGL)/(ENGU-ENGL)*(PVU-PVL)+PVL;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1153);
 return ;   
} 
*((float*)((bool*)(pHead->H_COMP)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_OUT)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )+(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))); 
}
// End Translate
} 
else  
 { 
	// Begin Translate COMP:=(ENGU-OUT)/(ENGU-ENGL)*(PVU-PVL)+PVL;
{
	 	 if ( (0 ==((*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0)))) )) 
		{ //Call divide by 0 protection function 
 AT_FillPOUErrorData(1,1155);
 return ;   
} 
*((float*)((bool*)(pHead->H_COMP)+0)) = (( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_OUT)+0))) )/( (*(float*)((float*)((bool*)(pHead->H_ENGU)+0)))-(*(float*)((float*)((bool*)(pHead->H_ENGL)+0))) )*( (*(float*)((float*)((bool*)(pHead->H_PVU)+0)))-(*(float*)((float*)((bool*)(pHead->H_PVL)+0))) )+(*(float*)((float*)((bool*)(pHead->H_PVL)+0)))); 
}
// End Translate
}
}
// End Translate
} 
}
// End Translate
// Begin Translate preCTRBP:=CTRBP;
{
*((bool*)((bool*)(pHead->H_PRECTRBP)+0)) = ((*(bool*)((bool*)((bool*)(pHead->H_CTRBP)+0)))); 
}
// End Translate
// Begin Translate IF(ACTOPT)THENOVE:=OVEAND16#FB;ELSEOVE:=OVEOR16#04;END_IF
{
if((*(bool*)((bool*)((bool*)(pHead->H_ACTOPT)+0)))) 
 { 
	// Begin Translate OVE:=OVEAND16#FB;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))&(251)); 
}
// End Translate
} 
else  
 { 
	// Begin Translate OVE:=OVEOR16#04;
{
*((uint8_t*)((bool*)(pHead->H_OVE)+0)) = ((*(uint8_t*)((uint8_t*)((bool*)(pHead->H_OVE)+0)))|(4)); 
}
// End Translate
}
}
// End Translate
// Begin Translate nowRM:=MODE;
{
*((uint16_t*)((bool*)(pHead->H_NOWRM)+0)) = ((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))); 
}
// End Translate
// Begin Translate IF((NOT(MODE=1))AND(NOT(MODE=2)))THENDK:=0;D1:=0;END_IF
{
if((0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)))) &(0x1 & (~((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)))) ) 
 { 
	// Begin Translate DK:=0;
{
*((float*)((bool*)(pHead->H_DK)+0)) = (0); 
}
// End Translate
// Begin Translate D1:=0;
{
*((float*)((bool*)(pHead->H_D1)+0)) = (0); 
}
// End Translate
} 
}
// End Translate
// Begin Translate IF(NOT((MODE=1)OR(MODE=2)))THENSPCAL:=sp1;END_IF
{
if(0x1 & (~(((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (1)) |((*(uint16_t*)((uint16_t*)((bool*)(pHead->H_MODE)+0)))  ==  (2)) ))) 
 { 
	// Begin Translate SPCAL:=sp1;
{
*((float*)((bool*)(pHead->H_SPCAL)+0)) = ((*(float*)((float*)((bool*)(pHead->H_SP1)+0)))); 
}
// End Translate
} 
}
// End Translate
}
