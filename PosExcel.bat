@echo 正在解析中... ...
@for %%i in (*.pos) do (ConvPosFile.exe %%i) && @echo %%i 解析完成
@echo 解析完成
@pause
@exit 0
