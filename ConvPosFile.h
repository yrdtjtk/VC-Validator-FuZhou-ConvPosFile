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

//��¼���ඨ��
#define RecKind_M1_Consume 0x01
#define RecKind_CPU_Consume 0x21
//�������Ͷ���
#define tk_PUR_SUB_NOR  0  //Ǯ������������¼  normal
#define tk_PUR_SUB_GRY  1  //Ǯ�����ѻҼ�¼ grey
#define tk_MON_SUB_NOR  2  //��Ʊ����������¼  normal
#define tk_MON_SUB_GRY  3  //��Ʊ���ѻҼ�¼ grey
#define CollectRecType	0xEB
#define OpOnDutyRecType	0xE1
#define ConsumeRecType	0x00

#define RecordLen 65

//����Ա�ϰ�
typedef struct
{
tk_uint8	FixedValue   	 	  	 	;	//  0   0  1 �̶�ֵ
tk_uint8	RecType      	 	  	 	;	//  1   1  1 ��¼����
tk_uint8	TranType     	 	  	 	;	//  2   2  1 ��������
tk_uint8	TransSeqNo   	[	2 	]	;	//  3   3  2 ���߽�����ˮ��
tk_uint8	Card_CSN     	[	4 	]	;	//  5   5  4 ���ѿ�����
tk_uint8	CardCityNo   	[	2 	]	;	//  9   9  2 �������д���
tk_uint8	CardIndustryNo	[	2 	]	;	//  B  11  2 Ӧ����ҵ����
tk_uint8	CardIssueNo  	[	4 	]	;	//  D  13  4 ������ˮ��
tk_uint8	CardAuth     	[	4 	]	;	// 11  17  4 ����֤��
tk_uint8	CardType     	 	  	 	;	// 15  21  1 ������
tk_uint8	MakeType     	 	  	 	;	// 16  22  1 ��¼���ɷ�ʽ
tk_uint8	BusType      	 	  	 	;	// 17  23  1 ��������
tk_uint8	BasePrice    	[	2 	]	;	// 18  24  2 ����Ʊ��
tk_uint8	CommonDiscount	 	  	 	;	// 1A  26  1 ͨ���ۿ���
tk_uint8	UTC          	[	4 	]	;	// 1B  27  4 ����ʱ��
tk_uint8	AppSerialNo  	[	10	]	;	// 1F  31 10 Ӧ�õ�λ���к�
tk_uint8	AirconFee    	[	2 	]	;	// 29  41  2 �յ���
tk_uint8	TransPosID   	[	4 	]	;	// 2B  43  4 ����POS����
tk_uint8	PosSoftVersion	 	  	 	;	// 2F  47  1 ��������汾��
tk_uint8	PosSoftDate  	[	3 	]	;	// 30  48  3 �����������
tk_uint8	BlackVer     	[	3 	]	;	// 33  51  3 �������汾
tk_uint8	RecNoCycTimes	 	  	 	;	// 36  54  1 ������ˮ��ѭ������
tk_uint8	RFU          	[	9 	]	;	// 37  55  9 Rfu.
tk_uint8	CheckCode    	 	  	 	;	// 40  64  1 У����
}OP_BENWORK_STRUCT;
//Ǯ�����Ѽ�¼
typedef struct
{
tk_uint8	FixedValue      	 	  	 	;	//  0   0  1 �̶�ֵ
tk_uint8	RecType         	 	  	 	;	//  1   1  1 ��¼����
tk_uint8	TranType        	 	  	 	;	//  2   2  1 ��������
tk_uint8	TransSeqNo      	[	2 	]	;	//  3   3  2 ���߽�����ˮ��
tk_uint8	Card_CSN        	[	4 	]	;	//  5   5  4 ���ѿ�����
tk_uint8	CardCityNo      	[	2 	]	;	//  9   9  2 �������д���
tk_uint8	CardIndustryNo  	[	2 	]	;	//  B  11  2 Ӧ����ҵ����
tk_uint8	CardIssueNo     	[	4 	]	;	//  D  13  4 ������ˮ��
tk_uint8	CardAuth        	[	4 	]	;	// 11  17  4 ����֤��
tk_uint8	CardType        	 	  	 	;	// 15  21  1 ������
tk_uint8	ChangePeakNightType	 	  	 	;	// 16  22  1 ���˸߷�ҹ�䷽ʽ
tk_uint8	InitAmt         	[	4 	]	;	// 17  23  4 ԭ��֣�
tk_uint8	UTC             	[	4 	]	;	// 1B  27  4 ����ʱ��UTC
tk_uint8	DeitAmt         	[	3 	]	;	// 1F  31  3 ���׽��֣�
tk_uint8	PurTransCnt     	[	2 	]	;	// 22  34  2 Ǯ���ۼƽ��״���
tk_uint8	PurAddCnt       	[	2 	]	;	// 24  36  2 Ǯ����ֵ������
tk_uint8	TransTAC        	[	4 	]	;	// 26  38  4 TAC������֤��
tk_uint8	AddTermNo       	[	4 	]	;	// 2A  42  4 ��ֵ�ն˱��
tk_uint8	OpRecNo         	[	2 	]	;	// 2E  46  2 ��ʻԱ������ˮ��
tk_uint8	Rfu             	 	  	 	;	// 30  48  1 RFU
tk_uint8	AddUTC          	[	4 	]	;	// 31  49  4 ��ֵ����ʱ��
tk_uint8	TransCityNo     	[	2 	]	;	// 35  53  2 ���ѳ��д���
tk_uint8	LastTradeTime   	[	4 	]	;	// 37  55  4 ǰ�ν�������ʱ��UTC
tk_uint8	LastTradeTerminal	[	2 	]	;	// 3B  59  2 ǰ�ν����ն˴���
tk_uint8	LastTradeMoney  	[	3 	]	;	// 3D  61  3 ǰ�ν��׽��֣�
tk_uint8	CheckCode       	 	  	 	;	// 40  64  1 У����
}PUR_SUB_STRUCT;
//��Ʊ���Ѽ�¼
typedef struct
{
tk_uint8	FixedValue      	 	  	 	;	//  0   0  1 �̶�ֵ
tk_uint8	RecType         	 	  	 	;	//  1   1  1 ��¼����
tk_uint8	TranType        	 	  	 	;	//  2   2  1 ��������
tk_uint8	TransSeqNo      	[	2 	]	;	//  3   3  2 ���߽�����ˮ��
tk_uint8	Card_CSN        	[	4 	]	;	//  5   5  4 ���ѿ�����
tk_uint8	CardCityNo      	[	2 	]	;	//  9   9  2 �������д���
tk_uint8	CardIndustryNo  	[	2 	]	;	//  B  11  2 Ӧ����ҵ����
tk_uint8	CardIssueNo     	[	4 	]	;	//  D  13  4 ������ˮ��
tk_uint8	CardAuth        	[	4 	]	;	// 11  17  4 ����֤��
tk_uint8	CardType        	 	  	 	;	// 15  21  1 ������
tk_uint8	ChangePeakNightType	 	  	 	;	// 16  22  1 ���˸߷�ҹ�䷽ʽ
tk_uint8	InitAmt         	[	4 	]	;	// 17  23  4 ԭ��֣�
tk_uint8	UTC             	[	4 	]	;	// 1B  27  4 ����ʱ��UTC
tk_uint8	DeitAmt         	[	3 	]	;	// 1F  31  3 ���׽��֣�
tk_uint8	PurTransCnt     	[	2 	]	;	// 22  34  2 Ǯ���ۼƽ��״���
tk_uint8	PurAddCnt       	[	2 	]	;	// 24  36  2 Ǯ����ֵ������
tk_uint8	TransTAC        	[	4 	]	;	// 26  38  4 TAC������֤��
tk_uint8	AddTermNo       	[	4 	]	;	// 2A  42  4 ��ֵ�ն˱��
tk_uint8	OpRecNo         	[	2 	]	;	// 2E  46  2 ��ʻԱ������ˮ��
tk_uint8	Rfu             	 	  	 	;	// 30  48  1 RFU
tk_uint8	AddUTC          	[	4 	]	;	// 31  49  4 ��ֵ����ʱ��
tk_uint8	TransCityNo     	[	2 	]	;	// 35  53  2 ���ѳ��д���
tk_uint8	LastTradeTime   	[	4 	]	;	// 37  55  4 ǰ�ν�������ʱ��UTC
tk_uint8	LastTradeTerminal	[	2 	]	;	// 3B  59  2 ǰ�ν����ն˴���
tk_uint8	LastTradeMoney  	[	3 	]	;	// 3D  61  3 ǰ�ν��׽��֣�
tk_uint8	CheckCode       	 	  	 	;	// 40  64  1 У����

}MONTH_SUB_STRUCT;
//CPU�� Ǯ�����Ѽ�¼                          
typedef struct                          
{                                       
tk_uint8	FixedValue    	 	  	 	;	//0	0		1B	                                  
tk_uint8	RecType       	 	  	 	;	//1	��¼����	HEX	1B	0x21                      
tk_uint8	TranType      	 	  	 	;	//2	��������	HEX	1B	                          
tk_uint8	TransSeqNo    	[	2	]	;	//3-4	��ַ����	HEX	2B	                        
tk_uint8	FaKaFangCode  	[	2	]	;	//5-6	����������	HEX	2B	                      
tk_uint8	CardCityNo    	[	2	]	;	//7-8	���д���	HEX	2B	                        
tk_uint8	CardIndustryNo	[	2	]	;	//9-10	��ҵ����	HEX	2B	                      
tk_uint8	CardAppSerial 	[	8	]	;	//11-18	Ӧ�����к�	HEX	8B	                    
tk_uint8	CardType      				;	//19	��������	HEX	1B	                        
tk_uint8	CardType2     	 	  	 	;	//20	��������	HEX	1B	                        
tk_uint8	CardIssueDate 	[	3	]	;	//21-23	�������ڣ�Ӧ���������ڣ�	BCD	3B	YYMMDD
tk_uint8	UTC         	[	4	]	;	//24-27	����ʱ��	 HEX	4B	UTC                 
tk_uint8	PurAddCnt     	[	2	]	;	//28-29	��ֵ���	HEX	2B	                      
tk_uint8	AddDate       	[	3	]	;	//30-32	��ֵ����	BCD	3B	YYMMDD                
tk_uint8	PurTransCnt   	[	2	]	;	//33-34	�������	HEX	2B	�ѻ��������          
tk_uint8	InitAmt       	[	4	]	;	//35-38	����ԭ��	HEX	4B	                      
tk_uint8	DeitAmt       	[	3	]	;	//39-41	���׽��	HEX	3B	                      
tk_uint8	CardUseFlg    				;	//42	��Ӧ�ñ�־	HEX	1B	                      
tk_uint8	Rfu1          	[	3	]	;	//43-45	RFU.	HEX	3B	                          
tk_uint8	OpRecNo       	[	2	] 	;	//46-47	˾����¼����	HEX	2B	                  
tk_uint8	PsamNo        	[	6	]	;	//48-53	PSAM���ն˻����	HEX	6B	              
tk_uint8	PsamTransCnt  	[	4	]	;	//54-57	PSAM���ն˽������	HEX	4B	            
tk_uint8	TransTAC   	[	4	]	;	//58-61	TAC��	HEX	4B	                          
tk_uint8	StopInfo				;	//62	վ����Ϣ	HEX	1B	                        
tk_uint8	Rfu2	 	  	 	;	//63	RFU	HEX	1B	                              
tk_uint8	CheckCode  				;	//64	У����	HEX	1B	CHK                       

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
