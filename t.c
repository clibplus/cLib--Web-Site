#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <str.h>
#include <Net/web.h>

#include "main.h"

String IP;
void err_n_exit(const char *msg) { printf("%s\n", msg); exit(0); }

void IndexHandler(cWS *web, cWR *r, WebRoute *route, int socket) {
	Map new_headers = NewMap();
    new_headers.Append(&new_headers, "Content-Type", "text/html; charset=UTF-8");
    new_headers.Append(&new_headers, "Connection", "close");

	SendResponse(web, socket, OK, new_headers, ((Map){}), "Hello World!");
}

int main() {
	IP = NewString("");
	cWS *api = StartWebServer(IP, 80, 0);
	if(!api) {
	    api->Destruct(api);
		err_n_exit("[ x ] Error, Unable to start web server....!\n");
    }

	api->CFG.Err404 = "Err404\n\n";
	AddRoutes(api, (WebRoute *[]){
		&(WebRoute){
			.Name 		= "index",
			.Path 		= "/",
			.Handler 	= IndexHandler
		},
		NULL
	});

	printf("Loaded %ld Routes...!\n", api->CFG.RouteCount);
	api->Run(api, 999, NULL);

	char *BUFFER[1024];
	fgets((char *)&BUFFER, 1024, stdin);

	api->Destruct(api);
	return 0;
}
