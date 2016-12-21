cd\
copy alasunsmscon.ocx %SystemRoot%\system32\alasunsmscon.ocx
copy mscomm32.ocx %SystemRoot%\system32\mscomm32.ocx
REGSVR32 alasunsmscon.ocx
REGSVR32 mscomm32.ocx