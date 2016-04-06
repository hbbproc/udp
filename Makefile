.PHONY:All
All:udp_server udp_client

udp_server:udp_server.c
	gcc -o $@ $^
udp_client:udp_client.c
	gcc -o $@ $^
.PHONY:clean
clean:
	rm -rf udp_server udp_client
