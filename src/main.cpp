#include <stdio.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <errno.h>

#include <iostream>

#define PORT 8080

int main() 
{
   int server_fd, new_socket;
   long valread;
   struct sockaddr_in address;
   int addrlen = sizeof(address);       

   if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
   {
      perror("In sockets");
      exit(EXIT_FAILURE);
   }

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   address.sin_port = htons(PORT);

   memset(address.sin_zero, '\0', sizeof address.sin_zero);

   if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) 
   {
      perror("In bind");
      close(server_fd);
      exit(EXIT_FAILURE);
   }
   if (listen(server_fd, 10) < 0) 
   {
      perror("In listen");
      exit(EXIT_FAILURE);
   }

   std::cout << "Waiting for connections..." << std::endl;

   while(true) 
   {
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
      {
         perror("In accept");
         exit(EXIT_FAILURE);
      }

      char buffer[1024] = {0};
      long valread = read(new_socket, buffer, 1024);

      std::cout << "Request received:\n" << buffer << std::endl;

      const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello World!";

      send(new_socket, response, strlen(response), 0);

      close(new_socket);
   }

   return 0; 
}
 