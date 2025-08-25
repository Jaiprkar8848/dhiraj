TIME_CMD = /usr/bin/time -f "\nTime_Taken: %e seconds\nMemory_Used: %M KB"
VERTICES = 400 600 800 1000 1200 
ALGO = RECURSIVE_DFS DFS BFS 

prob1 : $(ALGO)

$(ALGO) :
	@echo "Compiling with -D$@"
	@g++ -D$@ -DGENERATE_VARM Prob1Changed.cpp -o EXEC_$@
	@for V in $(VERTICES); do \
		echo "Running $@ with V=$$V"; \
		$(TIME_CMD) ./EXEC_$@ $$V 2>>$@_time.txt; \
	done
	@echo "Calculating Average Time and Average Memory :"
	@grep 'Time_Taken:' $@_time.txt >> $@_time.tmp
	@awk '{totalT+=$$2;tcount++} END {print "Average_Time: " totalT/tcount}' $@_time.tmp >> $@_average_time.txt
	@grep 'Memory_Used:' $@_time.txt >> $@_memory.tmp
	@awk '{totalM+=$$2;mcount++} END {print "Average_Memory: " totalM/mcount}' $@_memory.tmp >> $@_average_time.txt
	@rm -f $@time.tmp $@_memory.tmp EXEC$@
