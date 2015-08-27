 // ConvPosFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConvPosFile.h"
#include "ConvPosFileDlg.h"

#include "Function.h"

#include "BasicExcelVC6.h"
using namespace YExcel;

typedef struct tagStStatics{
	CString strDate;
	int iTimes;
}Struct_Statics;

#include <vector>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


BOOL ConvPos2Txt(CString sPath)
{
	BOOL bRet;
	CString ss,sTemp;
	int i,iTemp;
	byte bBuf[RecordLen];
	union 
	{
		byte uc[4];
		ULONG ul;
	}ul_uc_uni;
	union 
	{
		byte uc[2];
		USHORT ui;
	}ui_uc_uni;
	UINT Fen_Val;
	ULONG Yuan_Val;
	BYTE bRecFlags[2][4];
	OP_BENWORK_STRUCT OpRecSt;
	PUR_SUB_STRUCT* pPurSubSt;
	CPU_PUR_SUB_STRUCT* pCpuPurSubSt;
	MONTH_SUB_STRUCT* pMonSubSt;
	byte temp[16];
	CStdioFile m_PosFile;
	CStdioFile m_SSFile;

// 	typedef struct tagStStatics{
// 		CString strDate;
// 		int iTimes;
// 	}Struct_Statics;
	vector<Struct_Statics> vStatics;
	Struct_Statics tmpStatic;

	bRet=m_PosFile.Open(sPath,CFile::modeRead|CFile::typeBinary);
	if(!bRet)
	{
		return FALSE;
	}
//	ss=m_PosFile.GetFileName();
//	AfxMessageBox(ss);
	ss=m_PosFile.GetFilePath();
//	AfxMessageBox(ss);
//	(_tcsrchr(ss, _T('.')))[0] = 0;
//	AfxMessageBox(ss);
	iTemp=ss.Find(TEXT("."),0);
	ss.Format(ss.Left(iTemp));
	ss+=TEXT(".txt");
//	AfxMessageBox(ss);
	bRet=m_SSFile.Open(ss,CFile::modeCreate|CFile::modeWrite|CFile::typeText);

	memset(bRecFlags,0x00,sizeof(bRecFlags));
	while(TRUE)
	{
		iTemp=m_PosFile.Read(bBuf,RecordLen);
		if(iTemp<RecordLen)
		{
			break;
		}
		if(bBuf[2]>=tk_PUR_SUB_NOR && bBuf[2]<=tk_MON_SUB_GRY)
		{
			if(RecKind_M1_Consume == bBuf[1])
			{
				bRecFlags[0][bBuf[2]] = 1;
			}
			else if(RecKind_CPU_Consume == bBuf[1])
			{
				bRecFlags[1][bBuf[2]] = 1;
			}
		}
	}

	if (bRecFlags[0][tk_PUR_SUB_NOR] || bRecFlags[0][tk_PUR_SUB_GRY] || bRecFlags[1][tk_PUR_SUB_NOR] || bRecFlags[1][tk_PUR_SUB_GRY])//m1或cpu卡钱包记录
	{
		m_PosFile.SeekToBegin();
		memset( & OpRecSt,0x00,sizeof(OpRecSt));
		m_SSFile.WriteString(TEXT("[钱包消费记录]\n"));
		m_SSFile.WriteString(TEXT("状态,序号,卡芯片号,卡号,卡认证码,卡类,原额,交易金额,交易日期,TAC,钱包累计交易次数,钱包充值计数器,消费城市代码,"\
			"司机记录索引,基本票价,通用折扣率,公司,线路,车辆号\n"));
		while(TRUE)
		{
			ss.Format("");
			iTemp=m_PosFile.Read(bBuf,RecordLen);
			if(iTemp<RecordLen)
			{
				break;
			}
			if(RecKind_M1_Consume == bBuf[1] && OpOnDutyRecType == bBuf[2]) //上班记录
			{
				CopyMemory( & OpRecSt,bBuf,RecordLen);
			}
			else if((RecKind_M1_Consume == bBuf[1] && tk_PUR_SUB_NOR == bBuf[2])||(RecKind_M1_Consume == bBuf[1] && tk_PUR_SUB_GRY == bBuf[2])) //m1卡钱包记录
			{
				pPurSubSt = (PUR_SUB_STRUCT*)bBuf;
				//灰记录标志
				if (tk_PUR_SUB_GRY == pPurSubSt->TranType)
				{
					ss+="灰";
				tmpStatic.iTimes = 0;
				}
				else
				{
					ss+=" ";
				tmpStatic.iTimes = 1;
				}
				ss+=",";
				//序号
				ui_uc_uni.uc[0]=pPurSubSt->TransSeqNo[1];
				ui_uc_uni.uc[1]=pPurSubSt->TransSeqNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//卡芯片号
				CopyMemory(ul_uc_uni.uc, pPurSubSt->Card_CSN,4);
				sTemp.Format("%lu,",ul_uc_uni.ul);
				ss+=sTemp;
				//卡号
				for(i=0;i<8;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pPurSubSt->CardCityNo))+i));
					ss+=sTemp;
				}
				ss+=",";
				//卡认证码
				for(i=0;i<4;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pPurSubSt->CardAuth))+i));
					ss+=sTemp;
				}
				ss+=",";
				//卡类
				sTemp.Format("%u,",pPurSubSt->CardType);
				ss+=sTemp;
				//原额
				ul_uc_uni.uc[0]=pPurSubSt->InitAmt[3];
				ul_uc_uni.uc[1]=pPurSubSt->InitAmt[2];
				ul_uc_uni.uc[2]=pPurSubSt->InitAmt[1];
				ul_uc_uni.uc[3]=pPurSubSt->InitAmt[0];
				Yuan_Val=ul_uc_uni.ul/100;
				Fen_Val=ul_uc_uni.ul%100;
				sTemp.Format("%lu.%02u,",Yuan_Val,Fen_Val);
				ss+=sTemp;
				//交易金额
				ul_uc_uni.uc[0]=pPurSubSt->DeitAmt[2];
				ul_uc_uni.uc[1]=pPurSubSt->DeitAmt[1];
				ul_uc_uni.uc[2]=pPurSubSt->DeitAmt[0];
				ul_uc_uni.uc[3]=0;
				Yuan_Val=ul_uc_uni.ul/100;
				Fen_Val=ul_uc_uni.ul%100;
				sTemp.Format("%lu.%02u,",Yuan_Val,Fen_Val);
				ss+=sTemp;
				//交易日期
				ul_uc_uni.uc[0]=pPurSubSt->UTC[3];
				ul_uc_uni.uc[1]=pPurSubSt->UTC[2];
				ul_uc_uni.uc[2]=pPurSubSt->UTC[1];
				ul_uc_uni.uc[3]=pPurSubSt->UTC[0];
				UTCtoDateTime(ul_uc_uni.ul,temp);
				sTemp.Format("%02x%02x-%02x-%02x %02x:%02x:%02x,",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6]);
				ss+=sTemp;
			if (sTemp.Left(10).Compare(tmpStatic.strDate))
			{
				tmpStatic.strDate = sTemp.Left(10);
				vStatics.push_back(tmpStatic);
			}
			else
			{
				vStatics[vStatics.size()-1].iTimes += tmpStatic.iTimes;
			}

				//TAC
				for(i=0;i<4;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pPurSubSt->TransTAC))+i));
					ss+=sTemp;
				}
				ss+=",";
				//钱包累计交易次数
				ui_uc_uni.uc[0]=pPurSubSt->PurTransCnt[1];
				ui_uc_uni.uc[1]=pPurSubSt->PurTransCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//钱包充值计数器
				ui_uc_uni.uc[0]=pPurSubSt->PurAddCnt[1];
				ui_uc_uni.uc[1]=pPurSubSt->PurAddCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//消费城市代码
				for(i=0;i<2;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pPurSubSt->TransCityNo))+i));
					ss+=sTemp;
				}
				ss+=",";
				//司机记录索引
				ui_uc_uni.uc[0]=pPurSubSt->OpRecNo[1];
				ui_uc_uni.uc[1]=pPurSubSt->OpRecNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//基本票价
				ui_uc_uni.uc[0]=OpRecSt.BasePrice[1];
				ui_uc_uni.uc[1]=OpRecSt.BasePrice[0];
				sTemp.Format("%u.%02u,",ui_uc_uni.ui/100,ui_uc_uni.ui%100);
				ss+=sTemp;
				//通用折扣率
				sTemp.Format("%02u%%,",OpRecSt.CommonDiscount);
				ss+=sTemp;
				//公司
				sTemp.Format("%x,",OpRecSt.AppSerialNo[2]);
				sTemp.TrimLeft("0");
				ss+=sTemp;
				//线路
				for(i=0;i<2;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[5]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+=",";
				//车辆号
				for(i=0;i<3;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[7]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+="\n";
				m_SSFile.WriteString(ss);
			}
			else if((RecKind_CPU_Consume == bBuf[1] && tk_PUR_SUB_NOR == bBuf[2])||(RecKind_CPU_Consume == bBuf[1] && tk_PUR_SUB_GRY == bBuf[2])) //cpu卡钱包记录
			{
				pCpuPurSubSt = (CPU_PUR_SUB_STRUCT*)bBuf;
				//灰记录标志
				if (tk_PUR_SUB_GRY == pCpuPurSubSt->TranType)
				{
					ss+="灰";
				tmpStatic.iTimes = 0;
				}
				else
				{
					ss+=" ";
				tmpStatic.iTimes = 1;
				}
				ss+=",";
				//序号
				ui_uc_uni.uc[0]=pCpuPurSubSt->TransSeqNo[1];
				ui_uc_uni.uc[1]=pCpuPurSubSt->TransSeqNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//卡芯片号
				sTemp.Format(" ,");
				ss+=sTemp;
				//卡号
				for(i=0;i<8;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pCpuPurSubSt->CardAppSerial))+i));
					ss+=sTemp;
				}
				ss+=",";
				//卡认证码
				ss+=" ,";
				//卡类
				sTemp.Format("%u,",pCpuPurSubSt->CardType);
				ss+=sTemp;
				//原额
				ul_uc_uni.uc[0]=pCpuPurSubSt->InitAmt[3];
				ul_uc_uni.uc[1]=pCpuPurSubSt->InitAmt[2];
				ul_uc_uni.uc[2]=pCpuPurSubSt->InitAmt[1];
				ul_uc_uni.uc[3]=pCpuPurSubSt->InitAmt[0];
				Yuan_Val=ul_uc_uni.ul/100;
				Fen_Val=ul_uc_uni.ul%100;
				sTemp.Format("%lu.%02u,",Yuan_Val,Fen_Val);
				ss+=sTemp;
				//交易金额
				ul_uc_uni.uc[0]=pCpuPurSubSt->DeitAmt[2];
				ul_uc_uni.uc[1]=pCpuPurSubSt->DeitAmt[1];
				ul_uc_uni.uc[2]=pCpuPurSubSt->DeitAmt[0];
				ul_uc_uni.uc[3]=0;
				Yuan_Val=ul_uc_uni.ul/100;
				Fen_Val=ul_uc_uni.ul%100;
				sTemp.Format("%lu.%02u,",Yuan_Val,Fen_Val);
				ss+=sTemp;
				//交易日期
				ul_uc_uni.uc[0]=pCpuPurSubSt->UTC[3];
				ul_uc_uni.uc[1]=pCpuPurSubSt->UTC[2];
				ul_uc_uni.uc[2]=pCpuPurSubSt->UTC[1];
				ul_uc_uni.uc[3]=pCpuPurSubSt->UTC[0];
				UTCtoDateTime(ul_uc_uni.ul,temp);
				sTemp.Format("%02x%02x-%02x-%02x %02x:%02x:%02x,",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6]);
				ss+=sTemp;
			if (sTemp.Left(10).Compare(tmpStatic.strDate))
			{
				tmpStatic.strDate = sTemp.Left(10);
				vStatics.push_back(tmpStatic);
			}
			else
			{
				vStatics[vStatics.size()-1].iTimes += tmpStatic.iTimes;
			}
				//TAC
				for(i=0;i<4;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pCpuPurSubSt->TransTAC))+i));
					ss+=sTemp;
				}
				ss+=",";
				//钱包累计交易次数
				ui_uc_uni.uc[0]=pCpuPurSubSt->PurTransCnt[1];
				ui_uc_uni.uc[1]=pCpuPurSubSt->PurTransCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//钱包充值计数器
				ui_uc_uni.uc[0]=pCpuPurSubSt->PurAddCnt[1];
				ui_uc_uni.uc[1]=pCpuPurSubSt->PurAddCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//消费城市代码
				ss+=" ,";
				//司机记录索引
				ui_uc_uni.uc[0]=pCpuPurSubSt->OpRecNo[1];
				ui_uc_uni.uc[1]=pCpuPurSubSt->OpRecNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//基本票价
				ui_uc_uni.uc[0]=OpRecSt.BasePrice[1];
				ui_uc_uni.uc[1]=OpRecSt.BasePrice[0];
				sTemp.Format("%u.%02u,",ui_uc_uni.ui/100,ui_uc_uni.ui%100);
				ss+=sTemp;
				//通用折扣率
				sTemp.Format("%02u%%,",OpRecSt.CommonDiscount);
				ss+=sTemp;
				//公司
				sTemp.Format("%x,",OpRecSt.AppSerialNo[2]);
				sTemp.TrimLeft("0");
				ss+=sTemp;
				//线路
				for(i=0;i<2;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[5]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+=",";
				//车辆号
				for(i=0;i<3;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[7]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+="\n";
				m_SSFile.WriteString(ss);
			}

		}
	}

	if (bRecFlags[0][tk_MON_SUB_NOR] || bRecFlags[0][tk_MON_SUB_GRY] || bRecFlags[1][tk_MON_SUB_NOR] || bRecFlags[1][tk_MON_SUB_GRY])//m1或cpu卡月票记录
	{
		m_PosFile.SeekToBegin();
		memset( & OpRecSt,0x00,sizeof(OpRecSt));
		m_SSFile.WriteString(TEXT("[月票消费记录]\n"));
		m_SSFile.WriteString(TEXT("状态,序号,卡芯片号,卡号,卡认证码,卡类,原次,交易次数,交易日期,TAC,月票累计交易次数,月票充值计数器,消费城市代码,"\
			"司机记录索引,基本票价,通用折扣率,公司,线路,车辆号\n"));
		while(TRUE)
		{
			ss.Format("");
			iTemp=m_PosFile.Read(bBuf,RecordLen);
			if(iTemp<RecordLen)
			{
				break;
			}
			if(RecKind_M1_Consume == bBuf[1] && OpOnDutyRecType == bBuf[2]) //上班记录
			{
				CopyMemory( & OpRecSt,bBuf,RecordLen);
			}
			else if((RecKind_M1_Consume == bBuf[1] && tk_MON_SUB_NOR == bBuf[2])||(RecKind_M1_Consume == bBuf[1] && tk_MON_SUB_GRY == bBuf[2])) //m1卡月票记录(cpu卡也使用M1卡格式)
			{
				pMonSubSt = (MONTH_SUB_STRUCT*)bBuf;
				//灰记录标志
				if (tk_MON_SUB_GRY == pMonSubSt->TranType)
				{
					ss+="灰";
				tmpStatic.iTimes = 0;
				}
				else
				{
					ss+=" ";
				tmpStatic.iTimes = 1;
				}
				ss+=",";
				//序号
				ui_uc_uni.uc[0]=pMonSubSt->TransSeqNo[1];
				ui_uc_uni.uc[1]=pMonSubSt->TransSeqNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//卡芯片号
				CopyMemory(ul_uc_uni.uc, pMonSubSt->Card_CSN,4);
				sTemp.Format("%lu,",ul_uc_uni.ul);
				ss+=sTemp;
				//卡号
				for(i=0;i<8;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pMonSubSt->CardCityNo))+i));
					ss+=sTemp;
				}
				ss+=",";
				//卡认证码
				for(i=0;i<4;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pMonSubSt->CardAuth))+i));
					ss+=sTemp;
				}
				ss+=",";
				//卡类
				sTemp.Format("%u,",pMonSubSt->CardType);
				ss+=sTemp;
				//原次
				ul_uc_uni.uc[0]=pMonSubSt->InitAmt[3];
				ul_uc_uni.uc[1]=pMonSubSt->InitAmt[2];
				ul_uc_uni.uc[2]=pMonSubSt->InitAmt[1];
				ul_uc_uni.uc[3]=pMonSubSt->InitAmt[0];
				sTemp.Format("%lu,",ul_uc_uni.ul);
				ss+=sTemp;
				//交易次数
				ul_uc_uni.uc[0]=pMonSubSt->DeitAmt[2];
				ul_uc_uni.uc[1]=pMonSubSt->DeitAmt[1];
				ul_uc_uni.uc[2]=pMonSubSt->DeitAmt[0];
				ul_uc_uni.uc[3]=0;
				sTemp.Format("%lu,",ul_uc_uni.ul);
				ss+=sTemp;
				//交易日期
				ul_uc_uni.uc[0]=pMonSubSt->UTC[3];
				ul_uc_uni.uc[1]=pMonSubSt->UTC[2];
				ul_uc_uni.uc[2]=pMonSubSt->UTC[1];
				ul_uc_uni.uc[3]=pMonSubSt->UTC[0];
				UTCtoDateTime(ul_uc_uni.ul,temp);
				sTemp.Format("%02x%02x-%02x-%02x %02x:%02x:%02x,",temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6]);
				ss+=sTemp;
			for (i=0;i<vStatics.size();i++)
			{
				if (sTemp.Left(10).Compare(vStatics[i].strDate) == 0)
				{
					break;
				}
			}
			if (i<vStatics.size())
			{
				vStatics[i].iTimes += tmpStatic.iTimes;
			} 
			else
			{
				tmpStatic.strDate = sTemp.Left(10);
				vStatics.push_back(tmpStatic);
			}
				//TAC
				for(i=0;i<4;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pMonSubSt->TransTAC))+i));
					ss+=sTemp;
				}
				ss+=",";
				//月票累计交易次数
				ui_uc_uni.uc[0]=pMonSubSt->PurTransCnt[1];
				ui_uc_uni.uc[1]=pMonSubSt->PurTransCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//月票充值计数器
				ui_uc_uni.uc[0]=pMonSubSt->PurAddCnt[1];
				ui_uc_uni.uc[1]=pMonSubSt->PurAddCnt[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//消费城市代码
				for(i=0;i<2;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)(pMonSubSt->TransCityNo))+i));
					ss+=sTemp;
				}
				ss+=",";
				//司机记录索引
				ui_uc_uni.uc[0]=pMonSubSt->OpRecNo[1];
				ui_uc_uni.uc[1]=pMonSubSt->OpRecNo[0];
				sTemp.Format("%u,",ui_uc_uni.ui);
				ss+=sTemp;
				//基本票价
				ui_uc_uni.uc[0]=OpRecSt.BasePrice[1];
				ui_uc_uni.uc[1]=OpRecSt.BasePrice[0];
				sTemp.Format("%u.%02u,",ui_uc_uni.ui/100,ui_uc_uni.ui%100);
				ss+=sTemp;
				//通用折扣率
				sTemp.Format("%02u%%,",OpRecSt.CommonDiscount);
				ss+=sTemp;
				//公司
				sTemp.Format("%x,",OpRecSt.AppSerialNo[2]);
				sTemp.TrimLeft("0");
				ss+=sTemp;
				//线路
				for(i=0;i<2;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[5]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+=",";
				//车辆号
				for(i=0;i<3;i++)
				{
					sTemp.Format("%02X",*(((unsigned char*)( & OpRecSt.AppSerialNo[7]))+i));
					sTemp.TrimLeft("0");
					ss+=sTemp;
				}
				ss+="\n";
				m_SSFile.WriteString(ss);
			}

		}
	}


	m_SSFile.WriteString(TEXT("[汇总]\n"));
	m_SSFile.WriteString(TEXT("日期,交易笔数\n"));
	for (i=0;i<vStatics.size();i++)
	{
		ss.Format(TEXT("%s,%d\n"),vStatics[i].strDate,vStatics[i].iTimes);
		m_SSFile.WriteString(ss);
	}

	m_PosFile.Close();
	m_SSFile.Close();
	return TRUE;
}

BOOL ConvTxt2Excel(CString sPath)
{
	int iRet,iCommaPos,iLstCommaPos,iLineLen,iRow,iCol;
	int iSheetNo;
	BOOL bRet;
	CString ss,sTemp;
	WCHAR sheetName[32];

	BSTR bstr;

	BasicExcel e;

	CStdioFile m_PosFile;
	CStdioFile m_SSFile;


	e.New(1);
	BasicExcelWorksheet* sheet;
	BasicExcelCell* cell;

	bRet=m_SSFile.Open(sPath,CFile::modeRead|CFile::typeText);
	if(!bRet)
	{
		return FALSE;
	}
	iRow=iCol=0;
	iSheetNo = 0;
	while (1) 
	{
		iRet=m_SSFile.ReadString(ss);
		if(iRet==0)	break;
		if (ss.Left(1).Compare("[") == 0)
		{
			sTemp = ss.Mid(1,ss.Find("]")-1);
			iRet = MultiByteToWideChar(CP_ACP,0,sTemp.GetBuffer(sTemp.GetLength()),sTemp.GetLength(),sheetName,32);
			sheetName[iRet] = 0;
			if(0 == iSheetNo++)
			{
				e.RenameWorksheet((size_t)0, sheetName);
			}
			else
			{
				e.AddWorksheet(sheetName);
			}
// 			TRACE1("插入Sheet%ls",sheetName);
			sheet = e.GetWorksheet(sheetName);
			iRow = 0;
		} 
		else
		{
			iLineLen=ss.GetLength();
			iLstCommaPos=iCommaPos=0;
			iCol=0;
			while (1) 
			{
				iRet=ss.Find(',',iCommaPos);
				if(iRet==-1) 
				{
					sTemp=ss.Right(iLineLen-iLstCommaPos);
					bstr=sTemp.AllocSysString();
					cell=sheet->Cell(iRow,iCol);
					cell->SetWString(bstr);
					break;
				}
				iCommaPos=iRet;
				if(iCommaPos+1>=iLineLen)
				{
					break;
				}
				sTemp=ss.Mid(iLstCommaPos,iCommaPos-iLstCommaPos);
				bstr=sTemp.AllocSysString();

				iCommaPos++;
				iLstCommaPos=iCommaPos;

				cell=sheet->Cell(iRow,iCol);
				cell->SetWString(bstr);
// 				TRACE3("cell(%d,%d)=%s",iRow,iCol,sTemp);

				iCol++;
			}
			iRow++;
		}
	}

	if(iRow)
	{
		ss.Format("%s.xls",sPath.Left(sPath.ReverseFind('.')));
		e.SaveAs(ss);
	}
	m_SSFile.Close();
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvPosFileDlg dialog

CConvPosFileDlg::CConvPosFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvPosFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvPosFileDlg)
	m_strPosFilePath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConvPosFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvPosFileDlg)
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_strPosFilePath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConvPosFileDlg, CDialog)
	//{{AFX_MSG_MAP(CConvPosFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERT, OnConvert)
	ON_BN_CLICKED(IDC_BTN_SELFILE, OnBtnSelfile)
	ON_BN_CLICKED(IDC_BTN_EXPORT, OnBtnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvPosFileDlg message handlers

BOOL CConvPosFileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
// WCHAR s[32];
// int ret;
// 	ret = MultiByteToWideChar(CP_ACP,0,"弹弓法医",8,s,32);
// 	MessageBoxW(NULL,s,NULL,0);

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConvPosFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConvPosFileDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConvPosFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CConvPosFileDlg::OnConvert() 
{
	// TODO: Add your control notification handler code here
	ConvPos2Txt(m_strPosFilePath);

	MessageBox("POS文件解析完成！");

/*
//00110280-20081203073100.pos 111591
	long lg=0;

	lg+=0x00382F;
	lg+=0x003ABA;
	lg+=0x000777;
	lg+=0x00161C;
	lg+=0x000CDD;
	lg+=0x0080C0;
	lg+=0x001DF6;
	lg+=0x0004BA;
	lg+=0x002AD2;
	lg+=0x0004CE;
	lg+=0x0036CF;
	lg+=0x000CAF;

	CString ss;
	ss.Format("%ld",lg);


	lg+=0x000BED;
	lg+=0x001B58;
	lg+=0x0008B8;
	lg+=0x002723;
	lg+=0x0021C7;
	lg+=0x0016E4;
	lg+=0x000D68;
	lg+=0x004BAA;
	lg+=0x000A14;
	lg+=0x00116C;
	lg+=0x005843;
	lg+=0x002621;
	lg+=0x001828;
	CString ss;
	ss.Format("%ld",lg);

//00110285-20081203074916.pos 105193
*/

}

void CConvPosFileDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CConvPosFileDlg::OnBtnSelfile() 
{
	// TODO: Add your control notification handler code here
	int iRet;
	CFileDialog FDlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"消费文件(*.pos)|*.pos|所有文件(*.*)|*.*");
	iRet=FDlg.DoModal();
	if(iRet==IDOK)
	{
		m_strPosFilePath=FDlg.GetPathName();
		UpdateData(FALSE);
	}
}


void CConvPosFileDlg::OnBtnExport() 
{
	// TODO: Add your control notification handler code here
	CString ss,strSSFilePath;
	int iTemp;
	iTemp=m_strPosFilePath.Find(TEXT("."),0);
	ss.Format(m_strPosFilePath.Left(iTemp));
	ss+=TEXT(".txt");
	strSSFilePath = ss;
	ConvTxt2Excel(strSSFilePath);
	MessageBox("Excel文件导出完成！");

}
