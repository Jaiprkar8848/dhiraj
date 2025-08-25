EXEC_PREFIX = exec
TIME_CMD = /usr/bin/time -f "\nTime: %e seconds\nMemory: %M KB"
NODES = 500 600 700 800 900 1000
ALGORITHMS = DFS BFS REC_DFS

problem1 : $(ALGORITHMS) clean

$(ALGORITHMS) :
	@echo "Compiling with -D$@"
	@g++ -D$@ -DVARM Prob1.cpp -o $(EXEC_PREFIX)_$@
	@for N in $(NODES); do \
		echo "Running $@ with N=$$N"; \
		$(TIME_CMD) ./$(EXEC_PREFIX)_$@ $$N 2>>$@_time.txt; \
	done
	@echo "Calculating Average Time and Memory..."
	@grep 'Time:' $@_time.txt >> $@_time.tmp
	@grep 'Memory:' $@_time.txt >> $@_memory.tmp
	@awk '{totalTime+=$$2;timeCount++} END {print "Average_Time: " totalTime/timeCount}' $@_time.tmp >> $@_avg_time.txt
	@awk '{totalMemory+=$$2;memoryCount++} END {print "Average_Memory: " totalMemory/memoryCount}' $@_memory.tmp >> $@_avg_time.txt

clean :
	@echo "Cleaning generated files..."
	@rm -f *_time.tmp *_memory.tmp $(EXEC_PREFIX)_*


