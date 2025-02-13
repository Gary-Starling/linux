
#include <stdio.h> //--список объявлений и используемых нами готовых библиотек Cи
#include <string.h> //--подробно о каждой библиотеке можно узнать в man
#include <sys/stat.h> //--например man stdio и.т.д
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <resolv.h>
#include <errno.h>

#define PORT_CON 6823 //--определяем порт который будет прослушивать наш эхо сервер

struct sockaddr_in client_name;//--структура sockaddr_in клиентской машины (параметры ее нам неизвестны. Мы не знаем какая машина к нам будет подключаться)
int size = sizeof(client_name);//--размер структуры (тоже пока неизвестен)
int client_socket_fd;          //--идентификатор клиентского сокета


        char sockbuff[1024]; //--наш буфер обмена информацией с клиентом
        time_t now;
        struct tm *ptr;
        char tbuf[80];                                 



char* getTime();

int daemon(void);


int main(int argc, char* argv[]) //--это наша главная процедура с которой начинается программа
    {
          pid_t parpid;

          if((parpid = fork())<0) //--здесь мы пытаемся создать дочерний процесс главного процесса (масло масляное в прямом смысле) 
            {                   //--точную копию исполняемой программы
             printf("\ncan't fork"); //--если нам по какойлибо причине это сделать не удается выходим с ошибкой.
             exit(1);                //--здесь, кто не совсем понял нужно обратится к man fork
            }
          else if (parpid!=0) //--если дочерний процесс уже существует
          exit(0);            //--генерируем немедленный выход из программы(зачем нам еще одна копия программы)
          setsid();           //--перевод нашего дочернего процесса в новую сесию
          daemon();           //--ну а это вызов нашего демона с нужным нам кодом (код будет приведен далее)
          return 0;
    }



        char * getTime() //--функция определения времени в нужном формате
        {
         char *ret;
         ret=(char*)malloc(100);
         bzero(ret,100);
         time(&now);
         ptr = localtime(&now);
         strftime(tbuf,80,"%Y-%B-%e %H:%M:%S",ptr);
         ret=tbuf;
         return (ret);
        }    


        int daemon(void)
        {

          FILE *logfile; //--лог для подключившихся клиентов причем для каждого будет свой
          int socket_fd,nbytes; //--объявляем идентификатор сокета нашего сервера
          char host[20];
          char *namlog;
          void sig_child(int);//--объявление функции ожидания завершения дочернего процесса
          pid_t pid;
          struct sockaddr_in name;//--структура sockaddr_in для нашего сервера на сей раз ее придется заполнить

          namlog = (char*)malloc(25);
          socket_fd = socket(PF_INET,SOCK_STREAM,0); //--создаем сокет сервера в данном случае TCP, если бы мы использовали флаг SOCK_DTGRAM то получили бы сокет UDP
          name.sin_family = AF_INET; //--говорим что сокет принадлежит к семейству интернет
          name.sin_addr.s_addr = INADDR_ANY; //--наш серверный сокет принимает запросы от любых машин с любым IP-адресом
          name.sin_port = htons(PORT_CON); //--и прослушивает порт 6823

          if(bind(socket_fd, &name, sizeof(name))==-1) //Присвоить сокету имя
          {
            perror("bind"); //--ну если не может,то выдается предупреждение 
            exit(0); //--соответственно выход из программы
          }
          listen(socket_fd,20); //--перевод сокета сервера в режим прослушивания с очередью в 20 позиций
          for(;;) 
          {

             signal(SIGCHLD,sig_child); //--если клиент уже поработал и отключился ждем завершение его дочернего процесса
             client_socket_fd = accept (socket_fd,&client_name,&size); //--подключение нашего клиента
             if (client_socket_fd>0) //--если подключение прошло успешно
             {
               if ((pid=fork())==0) //--то мы создаем копию нашего сервера для работы с другим клиентом
                  {
                      inet_ntop(AF_INET,&client_name.sin_addr,host,sizeof(host)); //--в переменную host заносим IP-клиента
                      bzero(namlog,25);
                      strcpy(namlog,host);
                      strncat(namlog,"\0",1);
                      strcat(namlog,".log"); //--для каждого соединения делаем свой лог
                      if(freopen(logfile,namlog,"a+")!=NULL); //--создаем лог файл подключившегося клиента
                      {
                      fprintf(logfile,"%s Connected client:%s in port: %d\n",getTime(),host,ntohs(client_name.sin_port));
                      fflush(logfile);
                      fclose(logfile);
                      }                
                      do
                      {
                       bzero(sockbuff,1024); //--чистим 
                       nbytes=read(client_socket_fd,sockbuff,1024); 
                       strncat(sockbuff,"\0",1); 
                       if(freopen(logfile,namlog,"a+")!=NULL);
                       {
                        fprintf(logfile,"%s Client send to Server:%s\n",getTime(),sockbuff);
                        fflush(logfile); 
                        fclose(logfile); 
                       }
                       sendto(client_socket_fd,sockbuff,strlen(sockbuff),0,&client_socket_fd,size);           
                       if(freopen(logfile,namlog,"a+")!=NULL);
                       {
                        fprintf(logfile,"%s Server answer to client:%s\n",getTime(),sockbuff);
                        fflush(logfile);
                        fclose(logfile);
                       } 
                       }
                      while(nbytes > 0 && strncmp("bye",sockbuff,3)!=0);
                      if(freopen(logfile,namlog,"a+")!=NULL);
                      {
                      fprintf(logfile,"%s Close session on client:%s\n",getTime(),host);
                      fflush(logfile);
                      fclose(logfile);
                      }
                      close(client_socket_fd); 
                      exit(0); 
                   }
                   else if (pid > 0)
                   close(client_socket_fd);
              }
          }
        }





        void sig_child(int sig) //--функция ожидания завершения дочернего процесса
        {
         pid_t pid;
         int stat;
         while ((pid=waitpid(-1,&stat,WNOHANG))>0)
         {
          }
          return;
        }






