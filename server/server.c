#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 80

void send_html(int socket, char *page, int status)
{
  FILE *html = fopen(page, "r");

  char line[1024];
  char response[8192] = {0};

  char http_200[] = "HTTP/1.1 200\nContent-type: text/html;\r\n\n";
  char http_404[] = "HTTP/1.1 404\nContent-type: text/html;\r\n\n";

  while (fgets(line, 1024, html) != 0)
  {
    strcat(response, line);
  }

  if (status == 200)
  {
    strcat(http_200, response);
    send(socket, http_200, strlen(http_200), 0);
    close(socket);
  }

  if (status == 404)
  {
    strcat(http_404, response);
    send(socket, http_404, strlen(http_404), 0);
    close(socket);
  }

  fclose(html);
}

int main(int argc, char const *argv[])
{
  // Show server port on boot
  printf("Server running on port: %d\n", PORT);

  // Create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Set socket options
  int opt = 1;
  setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

  // Configure server address
  struct sockaddr_in server_address;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(PORT);

  // Bind socket to local address
  bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

  // Mark socket to listen for incoming connectios, max of 10
  if (listen(server_socket, 10) < 0)
  {
    perror(("Socket not listening!"));
    exit(EXIT_FAILURE);
  }

  int client_socket;
  int address_length = sizeof(server_address);

  char income_request[1024] = {0};

  // Loop for handling requests to server
  while (1)
  {
    if ((client_socket = accept(server_socket, (struct sockaddr *)&server_address, (socklen_t *)&address_length)) < 0)
    {
      perror("Error on accept");
      exit(EXIT_FAILURE);
    }

    read(client_socket, income_request, sizeof(income_request));

    // Parse request
    char *first_line = strtok(income_request, "\n");
    char *path;
    char *leftover = first_line;

    for (int i = 0; i < 2; i++)
    {
      path = strtok_r(leftover, " ", &leftover);

      if (i != 1)
        continue;

      // Index
      if ((strcmp(path, "/") == 0) || strcmp(path, "/index.html") == 0)
      {
        printf("Index\n");
        send_html(client_socket, "./public/index.html", 200);
        break;
      }

      // client
      if (strcmp(path, "/client.html") == 0)
      {
        printf("Client\n");
        send_html(client_socket, "./public/client.html", 200);
        break;
      }

      // Error 404 page not found
      printf("Not Found\n");
      send_html(client_socket, "./public/not_found.html", 404);
    }
  }

  return 0;
}
