SET SourceFile=D:\GameCode\SheeEngine\bin\Debug-x64\SheeEngine\SheeEngine.dll
SET GenFile=D:\GameCode\SheeEngine\bin\Debug-x64\Game\
 
if not exist %GenFile% (
        md %GenFile%
        copy %SourceFile% %GenFile%
    ) else (
        copy %SourceFile% %GenFile%
    )
