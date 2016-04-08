SUBDIR = ./pubfun \
	 ./server
	 
	 
all:
	@for subdir in ${SUBDIR}; do \
	echo "====================================Making in $$subdir===================================";\
	${MAKE} -C $${subdir} || exit 2;\
	done
clean:
	@for subdir in ${SUBDIR}; do \
        echo "===================================Making in $$subdir====================================";\
	${MAKE} -C $${subdir} clean || exit 2;\
        done

