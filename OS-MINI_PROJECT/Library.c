#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int insertflag=0;
char newString[10][10];
int ctr;
//Admin Functions
void Splitter(char str1[]){
     int i,j;
    
    j=0; ctr=0;
    for(i=0;i<=(strlen(str1));i++)
    {
        // if space or NULL found, assign NULL into newString[ctr]
        if(str1[i]=='~'||str1[i]=='\n'|| str1[i]==' ')
        {
            newString[ctr][j]='\0';
            ctr++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            newString[ctr][j]=str1[i];
            j++;
        }
    }
}
int check(char ch[]){
    int flag=0;
    for(int i=0;i < ctr;i++)
    if(strcmp(ch,newString[i])==0)
    {flag=1;break;}
    return flag;
}
void insert(char data[50]){
    FILE *fp;
    if(insertflag==0)
    {fp=fopen("Library.txt","w");fseek(fp,0,SEEK_SET);insertflag=1;}
    else
    fp=fopen("Library.txt","a");
    if(strlen(data)>0){
        fputs(data,fp);
        fputs("\n",fp);

    }
    fclose(fp);
}

void display(){
    FILE *fp;
    char disp[50];
    fp=fopen("Library.txt","r");
    fseek(fp,0,SEEK_SET);
    while(fgets(disp,50,fp)!=NULL)
    {
        printf("%s",disp);
   }
   fclose(fp);
}

/*
void displaytemp(){
    FILE *fp;
    char disp[50];
    fp=fopen("temp.txt","r");
    fseek(fp,0,SEEK_SET);
    while(fgets(disp,50,fp)!=NULL)
    {
        printf("%s",disp);
   }
   fclose(fp);
}
*/
void renamenremove(){
     if(remove("Library.txt")==0)
    {
        printf("File romoved successfully.\n");
    }
    else
    {
        printf("Unable to remove files. Please check files exist and you have permissions to modify files.\n");
    }
    
     if (rename("temp.txt","Library.txt") == 0)
    {
        printf("File renamed successfully.\n");
    }
    else
    {
        printf("Unable to rename files. Please check files exist and you have permissions to modify files.\n");
    }

   
}
void removefile(){

    if(remove("temp.txt")==0)
    {
        printf("File romoved successfully.\n");
    }
    else
    {
        printf("Unable to remove files. Please check files exist and you have permissions to modify files.\n");
    }
}     
void append(char detail[],char till[]){
   
    FILE *fr,*fw;
    char disp[50],temp[50];
    fr=fopen("Library.txt","r");
    fw=fopen("temp.txt","w");
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp(till,tokden)!=0 )
    {
        
        
      fputs(disp,fw); 
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
      
     
   }
    fputs(disp,fw);
   fputs(detail,fw);
   fputs("\n",fw);
   fgets(disp,50,fr);
   strcpy(temp,disp);
     tokden = strtok(temp, "\n");

    while(strcmp("EndOfInput",tokden)!=0 )
    {

      fputs(disp,fw); 
      fgets(disp,50,fr);
      strcpy(temp,disp);
    tokden = strtok(temp, "\n");
      
     
   }
   fputs(disp,fw);
   fclose(fr);
   fclose(fw);
renamenremove();
}
void delete(char search[],char till[])
{//){
    FILE *fr,*fw;
    char disp[50],temp[50];
    fr=fopen("Library.txt","r");
    fw=fopen("temp.txt","w");
    fseek(fr,0,SEEK_SET);
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp(till,tokden)!=0 )
    {
        
        
      fputs(disp,fw); 
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
     
   }
    fputs(disp,fw);
   fgets(disp,50,fr);
   Splitter(disp);
   

    while(check("EndOfInput")==0 )
    {
      if(check(search)==0)
      {
      fputs(disp,fw); 
      }
          fgets(disp,50,fr);
          Splitter(disp);
      
      
     
   }
   fputs(disp,fw);
      fclose(fr);
        fclose(fw);
    renamenremove();
}

// NON ADMIN FUNCTIONS
void displaybooks(){
    FILE *fp;
    char disp[50],temp[50];
    fp=fopen("Library.txt","r");
    fseek(fp,0,SEEK_SET);fgets(disp,50,fp);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");

    while(strcmp(tokden,"Borrowers")!=0)
    {
        printf("%s",disp);
        fgets(disp,50,fp);
         strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
   }
   fclose(fp);
}
void request(char usr[],char book[]){
    char requst[100];
    strcpy(requst,usr);
    strcat(requst,"~");
    strcat(requst,book);
    append(requst,"Requests");

}
char* returnaccesion(char user[]){
    FILE *fr;
    char disp[50],temp[50];
    fr=fopen("Library.txt","r");
   
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp("Checkouts",tokden)!=0 )
    {
        
        
      
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
      
     
   }
    fgets(disp,50,fr);
   Splitter(disp);

    while(check("EndOfInput")==0 )
    {
      if(check(user)!=0)
      {     
          
          return(newString[1]);
      }
          fgets(disp,50,fr);
          Splitter(disp);
      
      
     
   }
   
     
       
    return(NULL);
}

 char* returndate(char user[]){
     FILE *fr;
    char disp[50],temp[50];
    char *date;
    date = (char*)malloc(15);
    strcpy(date,"");
   

     fr=fopen("Library.txt","r");
    
    fseek(fr,0,SEEK_SET);
    
    fgets(disp,50,fr);
    
   fgets(disp,50,fr);
   strcpy(temp,disp);
    char * tokden = strtok(temp, "~");
    while(strcmp("Checkouts",tokden)!=0 )
    {
        
        
    
      fgets(disp,50,fr);
      strcpy(temp,disp);
         tokden = strtok(temp, "\n");
     
   }
    fgets(disp,50,fr);
   strcpy(temp,disp);
     tokden = strtok(temp, "~");
    while (strcmp(tokden,user)!=0)
    {
       
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "~");
     
    }
    Splitter(disp);
    
    
    strcpy(date,newString[2]);
    
        
   
    
 
    return(char*) date;
  
}
/*
const char* readsname(char search[]){
     FILE *fr;
    char disp[50],temp[50];
    char * book;
    book = (char*)malloc(15);
    

     fr=fopen("Library.txt","r");
    
    fseek(fr,0,SEEK_SET);
    
   fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp("Borrowers",tokden)!=0 )
    {
        
        
    
      fgets(disp,50,fr);
      strcpy(temp,disp);
        tokden = strtok(temp, "\n");
      
     
   }

    
   fgets(disp,50,fr);
   strcpy(temp,disp);
     tokden = strtok(temp, "~");
    while (strcmp(tokden,search)!=0)
    {
       
      fgets(disp,50,fr);
      strcpy(temp,disp);
       tokden = strtok(temp, "~");
     
    }
    Splitter(disp);
    
    for(int i=1;i< ctr;++i)
    {strcat(book,newString[i]);
    strcat(book," ");
    }
        
   
     fclose(fr);
 
        return(char *)book;
  
  
}
*/
 char* readsbooks(char search[]){
     FILE *fr;
    char disp[50],temp[50];
    char * book;
    book = (char*)malloc(15);
    strcpy(book,"");

     fr=fopen("Library.txt","r");
    
    fseek(fr,0,SEEK_SET);
    
    fgets(disp,50,fr);
    
   fgets(disp,50,fr);
   strcpy(temp,disp);
    char * tokden = strtok(temp, "~");
    while (strcmp(tokden,search)!=0)
    {
       
      fgets(disp,50,fr);
      strcpy(temp,disp);
        tokden = strtok(temp, "~");
     
    }
    Splitter(disp);
    
    for(int i=1;i< ctr;++i)
    {strcat(book,newString[i]);
    strcat(book," ");
    }
        
   
     //fclose(fr);
 
        return(char *)book;
  
  
}

int checkifnonadmin(char user[]){
    int flag=0;
     
    FILE *fr;
    char disp[50],temp[50];
    fr=fopen("Library.txt","r");
   
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp("Borrowers",tokden)!=0 )
    {
        
        
      
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
      
     
   }
    fgets(disp,50,fr);
   Splitter(disp);

    while(check("EndOfInput")==0 )
    {
      if(check(user)!=0)
      {     
          
         flag=1;
      }
          fgets(disp,50,fr);
          Splitter(disp);
      
      
     
   }
   
     
       
    return(flag);
  
}

//**********************************
void deletetemp(char search[],char till[])
{//){
    FILE *fr,*fw;
    char disp[50],temp[50];
    int flag=0;
    fr=fopen("Library.txt","r");
    fw=fopen("temp.txt","w");
    fseek(fr,0,SEEK_SET);
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp(till,tokden)!=0 )
    {
        
        
      fputs(disp,fw); 
      fgets(disp,50,fr);
      strcpy(temp,disp);
        tokden = strtok(temp, "\n");
     
   }
    fputs(disp,fw);
   fgets(disp,50,fr);
    strcpy(temp,disp);
   tokden = strtok(temp, "~");
   while(strcmp(search,tokden)!=0){
       fputs(disp,fw); 
      
          fgets(disp,50,fr);
          strcpy(temp,disp);
    tokden = strtok(temp, "~");
   }
   fgets(disp,50,fr);
    strcpy(temp,disp);
   tokden = strtok(temp, "\n");
    while(strcmp(tokden,"EndOfInput")!=0 )
    {
     
      fputs(disp,fw); 
      
          fgets(disp,50,fr);
           strcpy(temp,disp);
   tokden = strtok(temp, "\n");
          
    }
  fputs(disp,fw);
      fclose(fr);
        fclose(fw);
    
}
int  checkfromanoter(char user[]){
   int flag=0;
   deletetemp(user,"Checkouts");
   
    FILE *fr;
    char disp[50],temp[50];
    fr=fopen("temp.txt","r");
   
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp("Checkouts",tokden)!=0 )
    {
        
        
      
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
      
     
   }
    fgets(disp,50,fr);
   Splitter(disp);

    while(check("EndOfInput")==0 )
    {
      if(check(user)!=0)
      {     
          
         flag=1;
      }
          fgets(disp,50,fr);
          Splitter(disp);
      
      
     
   }
   
     
       
    return(flag);
} 

char* returnaccesiontemp(char user[]){
    FILE *fr;
    char disp[50],temp[50];
    fr=fopen("temp.txt","r");
   
    fgets(disp,50,fr);
    strcpy(temp,disp);
    char * tokden = strtok(temp, "\n");
    while(strcmp("Checkouts",tokden)!=0 )
    {
        
        
      
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "\n");
      
     
   }
    fgets(disp,50,fr);
   Splitter(disp);

    while(check("EndOfInput")==0 )
    {
      if(check(user)!=0)
      {     
          
          return(newString[1]);
      }
          fgets(disp,50,fr);
          Splitter(disp);
      
      
     
   }
   
     
       
    return(NULL);
}

 char* returndatetemp(char user[]){
     FILE *fr;
    char disp[50],temp[50];
    char *date;
    date = (char*)malloc(15);
    strcpy(date,"");

     fr=fopen("temp.txt","r");
    
    fseek(fr,0,SEEK_SET);
    
    fgets(disp,50,fr);
    
   fgets(disp,50,fr);
   strcpy(temp,disp);
    char * tokden = strtok(temp, "~");
    while(strcmp("Checkouts",tokden)!=0 )
    {
        
        
    
      fgets(disp,50,fr);
      strcpy(temp,disp);
         tokden = strtok(temp, "\n");
     
   }
    fgets(disp,50,fr);
   strcpy(temp,disp);
     tokden = strtok(temp, "~");
    while (strcmp(tokden,user)!=0)
    {
       
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "~");
     
    }
    Splitter(disp);
    
    
    strcpy(date,newString[2]);
    
        
   
    
 
    return(char*) date;
  
}

 char* readsbookstemp(char search[]){
     FILE *fr;
    char disp[50],temp[50];
    char * book;
    book = (char*)malloc(15);
    strcpy(book,"");

     fr=fopen("temp.txt","r");
    
    fseek(fr,0,SEEK_SET);
    
    fgets(disp,50,fr);
    
   fgets(disp,50,fr);
   strcpy(temp,disp);
    char * tokden = strtok(temp, "~");
    while (strcmp(tokden,search)!=0)
    {
       
      fgets(disp,50,fr);
      strcpy(temp,disp);
        char * tokden = strtok(temp, "~");
     
    }
    Splitter(disp);
    
    for(int i=1;i< ctr;++i)
    {strcat(book,newString[i]);
    strcat(book," ");
    }
        
   
     //fclose(fr);
 
        return(char *)book;
  
  
}
//*********************************
/*
void delete2(){
    FILE *fr,*fw,*current;
    char disp[50];
    int deleteflag=0,length;
    fr=fopen("Library.txt","r");
    fseek(fr,0,SEEK_SET);
    while(fgets(disp,50,fr)!=NULL)
    {
        //printf("%s",disp);
        char * tokden = strtok(disp, "~");
       // printf("%s\n",tokden);
         current = SEEK_CUR;
        if(strcmp(tokden,"SLY2303")==0){
            length=strlen(disp);

                break;
            }
    }

                fw=fopen("Library.txt","a");
                fseek(fw,0,current);

                while(fgets(disp,50,fr)!=NULL)
    {
       
        if(strlen(disp)>0){
        fputs(disp,fw);
        fputs("\n",fw);

   }
        }
        

    }   

*/
void printdetail(char s[]){
    printf("Welcome %s\n",readsbooks(s));
    if(returnaccesion(s)!=NULL){
    printf("Name of the book is %s\n",readsbooks(returnaccesion(s)));
    printf("Due date is %s\n",returndate(s));
    if(checkfromanoter(s)==1){
        printf("Name of the book is %s\n",readsbookstemp(returnaccesiontemp(s)));
        printf("Due date is %s\n",returndatetemp(s));
        removefile();
    }}
    else{
        printf("u have't took any books");
    }
}

void NONADMINUI(char user[]){
    int ch=1,back=0;
    char book[15],temp;
   // printf("Press 1 to Show ur details\nPress 2 to See the book list\nPress 3 to request a book\nPress 4 to exit\n");
    while (ch!=4)
    {
         printf("Press 1 to Show ur details\nPress 2 to See the book list\nPress 3 to request a book\nPress 4 to exit\n");
         scanf("%d",&ch);
    if(back==0){    
    switch (ch)
    {
    case 1:
        printdetail(user);
        back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        break;
    case 2:
        displaybooks();
         back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        
        break;
    case 3:
         printf("Enter the name of the book");
        scanf("%c",&temp); // temp statement to clear buffer
	    scanf("%[^\n]",book);
        request(user,book);
         back=1;

        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        
    default:
        printf("wrong in put tri again ");
        break;
    }
    }
    }
}

void ADMINUI(){
   
    int ch=1,back=0;
    char data[50],user[10],section[10],d[50],temp;
    strcpy(data,"");
   // printf("Press 1 to Show ur details\nPress 2 to See the book list\nPress 3 to request a book\nPress 4 to exit\n");
    while (ch!=5)
    {
         printf("Press 1 to Display the database\nPress 2 to add something in the database\nPress 3 to delete something\nPress 4 to Reset the database\nPress 5 to exit\n");
         scanf("%d",&ch);
    if(back==0){    
    switch (ch)
    {
    case 1:
        display();
        back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        break;
    case 2:
        printf("Enter the section at which data is to appended");
        scanf("%s\n",section);
        printf("Enter the data to be inserted");
        scanf("%s",d);
        append(d,section);
         back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        
        break;
    case 3:
        printf("Enter the userid to be deleted And Enter the section ");
        scanf("%s\t%s",user,section);
        delete(user,section);
         back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        break;
    case 4:
        printf("Start inserting\n");
       while(strcmp(data,"EndOfInput")!=0){
        

            /* code */
            scanf("%c",&temp); // temp statement to clear buffer
	    scanf("%[^\n]",data);
            insert(data);
        }
         back=1;
        printf("Press 0 if u wanna go back\t 1 if exit");
        scanf("%d",&back);
        break;
    default:
        printf("wrong in put tri again ");
        break;
    }
    }
    }
}

void main(){
    char data[50],username[10],temp;int ch=1;
   
    while(ch!=3){
         printf("Press 1 in ur Admin\nPress 2 if ur non admin\npress 3 to exit\n");
         scanf("%d",&ch);
        switch (ch)
        {
        case 1:
            /* if(password()==1){
              }*/  ADMINUI();
            
            break;
        case 2:
            printf("Enter your username");
            scanf("%s",username);
            if(checkifnonadmin(username)==1){
                NONADMINUI(username);
            }
            else
            {
                printf("Enter the username proply");
            }
            
            break;
        default:
            break;
        }
    }
    

   
    

    
    

}
