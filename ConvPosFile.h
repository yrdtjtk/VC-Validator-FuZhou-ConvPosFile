 // ConvPosFile.h : main header file for the CONVPOSFILE application
//

#if !defined(AFX_CONVPOSFILE_H__3F940627_ED2C_4BEC_8DE7_D25C568E1119__INCLUDED_)
#define AFX_CONVPOSFILE_H__3F940627_ED2C_4BEC_8DE7_D25C568E1119__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#ifndef tk_uint8
	#define tk_uint8 unsigned char
#endif

//记录种类定义
#define RecKind_M1_Consume 0x01
#define RecKind_CPU_Consume 0x21
//交易类型定义
#define tk_PUR_SUB_NOR  0  //钱包消费正常记录  normal
#define tk_PUR_SUB_GRY  1  //钱包消费灰记录 grey
#define tk_MON_SUB_NOR  2  //月票消费正常记录  normal
#define tk_MON_SUB_GRY  3  //月票消费灰记录 grey
#define CollectRecType	0xEB
#define OpOnDutyRecType	0xE1
#define ConsumeRecType	0x00

#define RecordLen 65

//操作员上班
typedef struct
{
tk_uint8	FixedValue   	 	  	 	;	//  0   0  1 固定值
tk_uint8	RecType      	 	  	 	;	//  1   1  1 记录种类
tk_uint8	TranType     	 	  	 	;	//  2   2  1 交易类型
tk_uint8	TransSeqNo   	[	2 	]	;	//  3   3  2 机具交易流水号
tk_uint8	Card_CSN     	[	4 	]	;	//  5   5  4 消费卡卡号
tk_uint8	CardCityNo   	[	2 	]	;	//  9   9  2 发卡城市代码
tk_uint8	CardIndustryNo	[	2 	]	;	//  B  11  2 应用行业代码
tk_uint8	CardIssueNo  	[	4 	]	;	//  D  13  4 发卡流水号
tk_uint8	CardAuth     	[	4 	]	;	// 11  17  4 卡认证码
tk_uint8	CardType     	 	  	 	;	// 15  21  1 卡类型
tk_uint8	MakeType     	 	  	 	;	// 16  22  1 记录生成方式
tk_uint8	BusType      	 	  	 	;	// 17  23  1 车辆类型
tk_uint8	BasePrice    	[	2 	]	;	// 18  24  2 基本票价
tk_uint8	CommonDiscount	 	  	 	;	// 1A  26  1 通用折扣率
tk_uint8	UTC          	[	4 	]	;	// 1B  27  4 交易时间
tk_uint8	AppSerialNo  	[	10	]	;	// 1F  31 10 应用单位序列号
tk_uint8	AirconFee    	[	2 	]	;	// 29  41  2 空调费
tk_uint8	TransPosID   	[	4 	]	;	// 2B  43  4 消费POS机号
tk_uint8	PosSoftVersion	 	  	 	;	// 2F  47  1 机具软件版本号
tk_uint8	PosSoftDate  	[	3 	]	;	// 30  48  3 机具软件日期
tk_uint8	BlackVer     	[	3 	]	;	// 33  51  3 黑名单版本
tk_uint8	RecNoCycTimes	 	  	 	;	// 36  54  1 交易流水号循环次数
tk_uint8	RFU          	[	9 	]	;	// 37  55  9 Rfu.
tk_uint8	CheckCode    	 	  	 	;	// 40  64  1 校验码
}OP_BENWORK_STRUCT;
//钱包消费记录
typedef struct
{
tk_uint8	FixedValue      	 	  	 	;	//  0   0  1 固定值
tk_uint8	RecType         	 	  	 	;	//  1   1  1 记录种类
tk_uint8	TranType        	 	  	 	;	//  2   2  1 交易类型
tk_uint8	TransSeqNo      	[	2 	]	;	//  3   3  2 机具交易流水号
tk_uint8	Card_CSN        	[	4 	]	;	//  5   5  4 消费卡卡号
tk_uint8	CardCityNo      	[	2 	]	;	//  9   9  2 发卡城市代码
tk_uint8	CardIndustryNo  	[	2 	]	;	//  B  11  2 应用行业代码
tk_uint8	CardIssueNo     	[	4 	]	;	//  D  13  4 发卡流水号
tk_uint8	CardAuth        	[	4 	]	;	// 11  17  4 卡认证码
tk_uint8	CardType        	 	  	 	;	// 15  21  1 卡类型
tk_uint8	ChangePeakNightType	 	  	 	;	// 16  22  1 换乘高峰夜间方式
tk_uint8	InitAmt         	[	4 	]	;	// 17  23  4 原额（分）
tk_uint8	UTC             	[	4 	]	;	// 1B  27  4 交易时间UTC
tk_uint8	DeitAmt         	[	3 	]	;	// 1F  31  3 交易金额（分）
tk_uint8	PurTransCnt     	[	2 	]	;	// 22  34  2 钱包累计交易次数
tk_uint8	PurAddCnt       	[	2 	]	;	// 24  36  2 钱包充值计数器
tk_uint8	TransTAC        	[	4 	]	;	// 26  38  4 TAC交易认证码
tk_uint8	AddTermNo       	[	4 	]	;	// 2A  42  4 充值终端编号
tk_uint8	OpRecNo         	[	2 	]	;	// 2E  46  2 驾驶员交易流水号
tk_uint8	Rfu             	 	  	 	;	// 30  48  1 RFU
tk_uint8	AddUTC          	[	4 	]	;	// 31  49  4 充值交易时间
tk_uint8	TransCityNo     	[	2 	]	;	// 35  53  2 消费城市代码
tk_uint8	LastTradeTime   	[	4 	]	;	// 37  55  4 前次交易日期时间UTC
tk_uint8	LastTradeTerminal	[	2 	]	;	// 3B  59  2 前次交易终端代码
tk_uint8	LastTradeMoney  	[	3 	]	;	// 3D  61  3 前次交易金额（分）
tk_uint8	CheckCode       	 	  	 	;	// 40  64  1 校验码
}PUR_SUB_STRUCT;
//月票消费记录
typedef struct
{
tk_uint8	FixedValue      	 	  	 	;	//  0   0  1 固定值
tk_uint8	RecType         	 	  	 	;	//  1   1  1 记录种类
tk_uint8	TranType        	 	  	 	;	//  2   2  1 交易类型
tk_uint8	TransSeqNo      	[	2 	]	;	//  3   3  2 机具交易流水号
tk_uint8	Card_CSN        	[	4 	]	;	//  5   5  4 消费卡卡号
tk_uint8	CardCityNo      	[	2 	]	;	//  9   9  2 发卡城市代码
tk_uint8	CardIndustryNo  	[	2 	]	;	//  B  11  2 应用行业代码
tk_uint8	CardIssueNo     	[	4 	]	;	//  D  13  4 发卡流水号
tk_uint8	CardAuth        	[	4 	]	;	// 11  17  4 卡认证码
tk_uint8	CardType        	 	  	 	;	// 15  21  1 卡类型
tk_uint8	ChangePeakNightType	 	  	 	;	// 16  22  1 换乘高峰夜间方式
tk_uint8	InitAmt         	[	4 	]	;	// 17  23  4 原额（分）
tk_uint8	UTC             	[	4 	]	;	// 1B  27  4 交易时间UTC
tk_uint8	DeitAmt         	[	3 	]	;	// 1F  31  3 交易金额（分）
tk_uint8	PurTransCnt     	[	2 	]	;	// 22  34  2 钱包累计交易次数
tk_uint8	PurAddCnt       	[	2 	]	;	// 24  36  2 钱包充值计数器
tk_uint8	TransTAC        	[	4 	]	;	// 26  38  4 TAC交易认证码
tk_uint8	AddTermNo       	[	4 	]	;	// 2A  42  4 充值终端编号
tk_uint8	OpRecNo         	[	2 	]	;	// 2E  46  2 驾驶员交易流水号
tk_uint8	Rfu             	 	  	 	;	// 30  48  1 RFU
tk_uint8	AddUTC          	[	4 	]	;	// 31  49  4 充值交易时间
tk_uint8	TransCityNo     	[	2 	]	;	// 35  53  2 消费城市代码
tk_uint8	LastTradeTime   	[	4 	]	;	// 37  55  4 前次交易日期时间UTC
tk_uint8	LastTradeTerminal	[	2 	]	;	// 3B  59  2 前次交易终端代码
tk_uint8	LastTradeMoney  	[	3 	]	;	// 3D  61  3 前次交易金额（分）
tk_uint8	CheckCode       	 	  	 	;	// 40  64  1 校验码

}MONTH_SUB_STRUCT;
//CPU卡 钱包消费记录                          
typedef struct                          
{                                       
tk_uint8	FixedValue    	 	  	 	;	//0	0		1B	                                  
tk_uint8	RecType       	 	  	 	;	//1	记录种类	HEX	1B	0x21                      
tk_uint8	TranType      	 	  	 	;	//2	交易类型	HEX	1B	                          
tk_uint8	TransSeqNo    	[	2	]	;	//3-4	地址索引	HEX	2B	                        
tk_uint8	FaKaFangCode  	[	2	]	;	//5-6	发卡方代码	HEX	2B	                      
tk_uint8	CardCityNo    	[	2	]	;	//7-8	城市代码	HEX	2B	                        
tk_uint8	CardIndustryNo	[	2	]	;	//9-10	行业代码	HEX	2B	                      
tk_uint8	CardAppSerial 	[	8	]	;	//11-18	应用序列号	HEX	8B	                    
tk_uint8	CardType      				;	//19	卡主类型	HEX	1B	                        
tk_uint8	CardType2     	 	  	 	;	//20	卡子类型	HEX	1B	                        
tk_uint8	CardIssueDate 	[	3	]	;	//21-23	发卡日期（应用启动日期）	BCD	3B	YYMMDD
tk_uint8	UTC         	[	4	]	;	//24-27	交易时间	 HEX	4B	UTC                 
tk_uint8	PurAddCnt     	[	2	]	;	//28-29	充值序号	HEX	2B	                      
tk_uint8	AddDate       	[	3	]	;	//30-32	充值日期	BCD	3B	YYMMDD                
tk_uint8	PurTransCnt   	[	2	]	;	//33-34	消费序号	HEX	2B	脱机交易序号          
tk_uint8	InitAmt       	[	4	]	;	//35-38	交易原额	HEX	4B	                      
tk_uint8	DeitAmt       	[	3	]	;	//39-41	交易金额	HEX	3B	                      
tk_uint8	CardUseFlg    				;	//42	卡应用标志	HEX	1B	                      
tk_uint8	Rfu1          	[	3	]	;	//43-45	RFU.	HEX	3B	                          
tk_uint8	OpRecNo       	[	2	] 	;	//46-47	司机记录索引	HEX	2B	                  
tk_uint8	PsamNo        	[	6	]	;	//48-53	PSAM卡终端机编号	HEX	6B	              
tk_uint8	PsamTransCnt  	[	4	]	;	//54-57	PSAM卡终端交易序号	HEX	4B	            
tk_uint8	TransTAC   	[	4	]	;	//58-61	TAC码	HEX	4B	                          
tk_uint8	StopInfo				;	//62	站点信息	HEX	1B	                        
tk_uint8	Rfu2	 	  	 	;	//63	RFU	HEX	1B	                              
tk_uint8	CheckCode  				;	//64	校验码	HEX	1B	CHK                       

}CPU_PUR_SUB_STRUCT;





/////////////////////////////////////////////////////////////////////////////
// CConvPosFileApp:
// See ConvPosFile.cpp for the implementation of this class
//

class CConvPosFileApp : public CWinApp
{
public:
	CConvPosFileApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvPosFileApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CConvPosFileApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVPOSFILE_H__3F940627_ED2C_4BEC_8DE7_D25C568E1119__INCLUDED_)
