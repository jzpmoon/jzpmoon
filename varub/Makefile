bin=varub.so
obj=test.o vr_slist.o vr_queue.o vr_stack.o vr_bitree.o vr_rbtree.o vr_list.o
$(bin):$(obj)
	gcc -shared -o $(bin) $(obj)
.c.o:
	gcc -c -fPIC -fvisibility=hidden -o $@ $<
clean:
	rm $(obj) $(bin)
