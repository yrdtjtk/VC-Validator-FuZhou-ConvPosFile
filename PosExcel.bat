@echo ���ڽ�����... ...
@for %%i in (*.pos) do (ConvPosFile.exe %%i) && @echo %%i �������
@echo �������
@pause
@exit 0
