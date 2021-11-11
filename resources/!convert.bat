@ECHO OFF
IF NOT DEFINED GFX2NEXT_HOME SET GFX2NEXT_HOME=..\..\..\..\NextTools\Gfx2Next\bin
%GFX2NEXT_HOME%\gfx2next.exe -font -z80asm -bank-sections=BANK_25 font.png
%GFX2NEXT_HOME%\gfx2next.exe -bitmap -bitmap-y -pal-std -pal-none -bank-16k -bank-sections=BANK_20,BANK_21,BANK_22,BANK_23,BANK_24 -z80asm -asm-sequence chessboard.png
%GFX2NEXT_HOME%\gfx2next.exe -sprites -pal-ext -colors-4bit -z80asm -bank-sections=BANK_25,BANK_25 chessmen.png
move *.spr ..\binary >nul
move *.nxi ..\binary >nul
move *.nxp ..\binary >nul
move *.asm ..\src >nul
move *.h ..\src >nul
