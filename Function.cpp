#include "StdAfx.h"

#include "BasicExcelVC6.h"


//下面的代码用于GSM MODEM AT指令下的STRING到UNICDE码的转换。
CString ExchangeMsg(CString msg)
{
   CString retstr;
   
   char aa[500]="";
   int len=msg.GetLength();
   BSTR x=msg. AllocSysString();
   long num=*((long*)x-1);   
   for(int i=0;i<num;i+=1)
   {
    if(i>=len)
     break;
     char cc[10]="";
  if((*x>>8)==0)
  {
   sprintf(aa,"%s00%x",aa,*x);
     msg=msg.Right (msg.GetLength ()-1);
   
  }
  else
  {
   sprintf(aa,"%s%x",aa,*x);
   msg=msg.Right (msg.GetLength ()-2);
   i=i+1;
  }
  SysFreeString(x); 
 
  x=msg. AllocSysString();
   }
  SysFreeString(x);
   char bb[10]="";
   int len1=strlen(aa);
   char txt[500]="";
   if(len1%4!=0)
   {
    memcpy(txt,aa,(len1-3)); 
   }
   else
   {
    memcpy(txt,aa,len1);
   }
   if(num<=0x0f)
   {
    sprintf(bb,"0%x",num);
   }
   else
   {
    sprintf(bb,"%x",num);
   }
   retstr.Format ("%s%s",bb,txt);
   retstr.MakeUpper ();
   int msglth=retstr.GetLength();  
   return retstr;
}


char VerifyLeapYear(int year)
{
	char Leap;
	if(year%4==0){
		if(year%100==0){
			if(year%400==0){
				Leap=1;
			}
			else{
				Leap=0;
			}
		}
		else{
			Leap=1;
		}
	}
	else{
		Leap=0;
	}
	return Leap;		
}
//UTCtoDateTime:date_time:BCD YYYYMMDDHHMMSS
void UTCtoDateTime(unsigned long ulUTC,unsigned char *date_time)
{
	int i,iRemDays,iCurYearDays,iCurMonDays,iCurrYear,iCurrMonth,iCurrDate;
	char cLeapF;
	char caMonthDate[14]="\x00\x1f\x1c\x1f\x1e\x1f\x1e\x1f\x1f\x1e\x1f\x1e\x1f";
					      /*0   1   2   3   4   5   6   7   8   9   10  11 12*/	
	unsigned long ulRemSecs;
	int iHour,iMinute,iSecond;
	unsigned char ucTmp;
	
	ulRemSecs=ulUTC%(24*60*60);

	iRemDays=ulUTC/(24*60*60);
	iCurrYear=1970;

	
	while(1)
	{
		cLeapF=VerifyLeapYear(iCurrYear);
		iCurYearDays=365+cLeapF;
		if(iRemDays<iCurYearDays)
		{
			for(i=1;i<=12;i++)
			{
				iCurMonDays=caMonthDate[i];
				if(i==2)
				{
					iCurMonDays+=cLeapF;
				}
				if(iRemDays<iCurMonDays)
				{
					iCurrMonth=i;
					iCurrDate=iRemDays+1;
					goto OutSide;
				}
				else
				{
					iRemDays-=iCurMonDays;
				}
			}
		}
/*
		else if(iRemDays==iCurYearDays)
		{
			iCurrYear++;
			iCurrMonth=1;
			iCurrDate=1;
			break;
		}
*/
		else
		{
			iRemDays-=iCurYearDays;
			iCurrYear++;
		}
		
	} 
OutSide:
	iHour=ulRemSecs/(60*60);
	ulRemSecs-=iHour*3600;
	iMinute=ulRemSecs/60;
	iSecond=ulRemSecs%60;

	ucTmp=iCurrYear/100;
	date_time[0]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iCurrYear%100;
	date_time[1]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iCurrMonth;
	date_time[2]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iCurrDate;
	date_time[3]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iHour;
	date_time[4]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iMinute;
	date_time[5]=((ucTmp/10)<<4)|(ucTmp%10);
	ucTmp=iSecond;
	date_time[6]=((ucTmp/10)<<4)|(ucTmp%10);
}







/*
#include <iostream>

using namespace std ;

#import "C:\Program Files\Common Files\Microsoft Shared\OFFICE11\mso.dll" rename("RGB", "MSRGB")

#import "C:\Program Files\Common Files\Microsoft Shared\VBA\VBA6\VBE6EXT.OLB" raw_interfaces_only, \
rename("Reference", "ignorethis"), rename("VBE", "JOEVBE")

#import "d:\Program Files\Microsoft Office\OFFICE11\excel.exe" exclude("IFont", "IPicture") \
rename("RGB", "ignorethis"), rename("DialogBox", "ignorethis"), rename("VBE", "JOEVBE"), \
rename("ReplaceText", "JOEReplaceText"), rename("CopyFile","JOECopyFile"), \
rename("FindText", "JOEFindText"), rename("NoPrompt", "JOENoPrompt")

using namespace Office;
using namespace VBIDE;
using namespace Excel ;


int ExportExcelFile()
{
     _ApplicationPtr pApplication = NULL ;
     _WorkbookPtr pThisWorkbook = NULL ;
     _WorksheetPtr pThisWorksheet = NULL ;
     SheetsPtr pThisSheets = NULL ;
     RangePtr pThisRange = NULL ;
     _variant_t vt ;
     Excel::XlFileFormat vFileFormat ;
     Excel::XlSaveAsAccessMode vSaveAsAccessMode ;
     Excel::XlSaveConflictResolution vSaveConflictResolution ;

     pApplication.CreateInstance("Excel.Application");
     pApplication->PutVisible (0,VARIANT_TRUE);
     pThisWorkbook = pApplication->GetWorkbooks()->Add() ;
     pThisSheets = pThisWorkbook->GetWorksheets() ;
     pThisWorksheet = pThisSheets->GetItem((short)1);
     // 设置整个sheet的填充色为白色
     pThisWorksheet->GetCells()->GetInterior()->PutColor(RGB(255, 255, 255));
     pThisWorksheet->GetCells()->ClearContents() ;
     pThisRange = pThisWorksheet->GetRange("A1:C5") ;
     pThisRange->ClearFormats() ;
     // 如果有不会的，可以在debug文件夹的excel.tlh里找找
     //pThisRange->GetItem(1,1) ;
     pThisRange->PutItem(1, 1, _variant_t("哈尔滨市平房区")) ;
     pThisRange->PutItem(1, 2, _variant_t("高宏伟")) ;
     pThisRange->PutItem(1, 3, _variant_t("QQ:21807822")) ;
     pThisRange->PutItem(2, 1, _variant_t("1")) ;
     pThisRange->PutItem(3, 1, _variant_t("2")) ;
     pThisRange->PutItem(4, 1, _variant_t("3")) ;
     pThisRange->PutItem(5, 1, _variant_t("4")) ;
     // 为Range的四周和内部加上边框
     pThisRange->GetBorders()->GetItem(xlEdgeLeft)->PutLineStyle(xlContinuous) ;
     pThisRange->GetBorders()->GetItem(xlEdgeTop)->PutLineStyle(xlContinuous) ;
     pThisRange->GetBorders()->GetItem(xlEdgeRight)->PutLineStyle(xlContinuous) ;
     pThisRange->GetBorders()->GetItem(xlEdgeBottom)->PutLineStyle(xlContinuous) ;
     pThisRange->GetBorders()->GetItem(xlInsideHorizontal)->PutLineStyle(xlContinuous) ;
     pThisRange->GetBorders()->GetItem(xlInsideVertical)->PutLineStyle(xlContinuous) ;
     // 设置第一行的格式（背景色、粗体、颜色、列宽）
     pThisRange->GetRange("A1:C1")->GetInterior()->ColorIndex = 47 ;
     pThisRange->GetRange("A1:C1")->GetInterior()->Pattern = xlPatternSolid ;
     pThisRange->GetRange("A1:C1")->GetFont()->ColorIndex = 6 ;
     pThisRange->GetRange("A1:C1")->GetFont()->Bold = TRUE ;
     pThisRange->GetEntireColumn()->ColumnWidth = 18.63 ;
     pThisRange->GetRange("A2:C5")->GetInterior()->ColorIndex = 16 ;
     pThisRange->GetRange("A2:C5")->GetInterior()->Pattern = xlPatternSolid ;
     pThisRange->GetRange("A2:C5")->GetFont()->ColorIndex = 2 ;
     // 冻结窗格
     pApplication->ActiveWindow->FreezePanes = FALSE ;
     pApplication->Range["A2"]->Select() ;
     pApplication->ActiveWindow->FreezePanes = TRUE ;

     // 存盘退出
     vSaveAsAccessMode = xlNoChange ;
     vFileFormat = xlWorkbookNormal ;
     vSaveConflictResolution = xlLocalSessionChanges ;
     pThisWorkbook->SaveAs(_variant_t("D:\\Visual Studio Projects\\VCReportDemo\\joe.xls"), vFileFormat,_variant_t(""),_variant_t(""), _variant_t(false),
     _variant_t(false), vSaveAsAccessMode, vSaveConflictResolution, _variant_t(false)) ;
     pThisWorkbook->Close();
     pApplication->Quit();

     return 0 ;
}
*/
