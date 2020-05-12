#i set default time and type
time = 5
type = txt
#mmin is the modificaiton time
.PHONY : all	
all:
	@echo the modification time is lower $(time) minutes
	@find -name '*.$(type)' -mmin -$(time)
