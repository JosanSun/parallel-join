parallel:
	@cd ./parallel && make

serial:
	@cd ./serial && make

clean:
	rm -rf ./a.out
	@cd ./serial && make clean
	@cd ./parallel && make clean

.PHONY: parallel
.PHONY: serial
.PHONY: clean
