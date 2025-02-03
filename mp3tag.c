#include<stdio.h>
#include<string.h>
#include"mp3tag.h"
#include"types.h"
#include"mp3edit.h"

status select_operation_valid(int argc,char *argv[],tag *mp3tag)
{
       
    
   if(strcmp(argv[1],"-v")==0)
   {
      
      return view;
   }
   else if(strcmp(argv[1],"-e")==0)
   {
      return Edit;
   }
   else{
         return failure;
   }
  
}
status view_validation(int argc,char *argv[],tag *mp3tag)
{
    char *ch;
    if(ch=strstr(argv[2],".mp3"))
    {
        mp3tag->mp3_fname=argv[2];
        
       
    }
 return success;
    
}
status do_view_opration(tag *mp3tag)
{
    open_file(mp3tag->mp3_fptr,mp3tag);
    //
    read_header(mp3tag->mp3_fptr,mp3tag);
    //
   read_from_frame_header(mp3tag->mp3_fptr,mp3tag,mp3tag->frame_reader,mp3tag->frame_tag,mp3tag->namesize);
    //
  read_from_frame_header(mp3tag->mp3_fptr,mp3tag,mp3tag->frame_reader,mp3tag->frame_tag,mp3tag->namesize);
  //
   read_from_frame_header(mp3tag->mp3_fptr,mp3tag,mp3tag->frame_reader,mp3tag->frame_tag,mp3tag->namesize);
   //
   read_from_frame_header(mp3tag->mp3_fptr,mp3tag,mp3tag->frame_reader,mp3tag->frame_tag,mp3tag->namesize);
   //
   read_from_frame_header(mp3tag->mp3_fptr,mp3tag,mp3tag->frame_reader,mp3tag->frame_tag,mp3tag->namesize);
   //
   Comm_tag(mp3tag->mp3_fptr,mp3tag);
   
   for(int i=0;i<40;i++)
   {
    printf("--");
   }
   printf("\n");

}
status open_file(FILE *mp3_fptr,tag *mp3tag)
{
    mp3tag->mp3_fptr=fopen(mp3tag->mp3_fname,"rb+");
    if(mp3tag->mp3_fname==NULL)
    {
        fprintf(stderr,"Unable to open %s",mp3tag->mp3_fname);
        return 1;
    }
    
    return success;

}

status read_header(FILE *mp3_fptr,tag *mp3tag)
{
     
  for(int i=0;i<40;i++)
   {
    printf("--");
   }
   printf("\n");
    printf("  MP3 Tag Reader and Editor for ");
    char buffer[3];
    char buffer1[2];
    int i;
  

       int read=fread(buffer,1,3,mp3tag->mp3_fptr);

        if(read != 3)
        {
            printf("Not read 3 byte :\n");
            return 1;
        }
         for(int i=0; i<read;i++)
         {
            printf("%c",buffer[i]);
         }
         printf(".v");
       int ret=fread(buffer1,1,2,mp3tag->mp3_fptr);

       for(int i=0; i<ret;i++)
         {
            printf("%x",buffer1[i]);
         }
         printf("\n");
  for(int i=0;i<40;i++)
   {
    printf("--");
   }
   printf("\n");
        fseek(mp3tag->mp3_fptr,5,SEEK_CUR);
        int seek=ftell(mp3tag->mp3_fptr);
       
    return success;
}
status read_from_frame_header(FILE *mp3_fptr,tag *mp3tag,char *frame_reader,char *frame_tag,int namesize)
{
    //reading tag
   char buffer[4];
    fread(buffer,1,4,mp3tag->mp3_fptr);
   
         
          mp3tag->frame_tag=buffer;
          
         
         //reading frame 4 byte contant size
         char contnt[4];
        fread(contnt,1,4,mp3tag->mp3_fptr);
        
        
         int seek=contnt[3];
       

        if(seek==31||seek==47||seek==33||seek==9||seek==5){
          
           seek=seek-1;
          }
//skip frame flag 3 bytes
        fseek(mp3tag->mp3_fptr,3,SEEK_CUR);
       
        char read[seek-1];
    
        fread(read,1,seek,mp3tag->mp3_fptr);
         read[seek]='\0';
     
        mp3tag->frame_reader=read;
       if(strcmp(mp3tag->frame_tag,"TIT2")==0){
        printf("Title\t\t:\t%s\n",mp3tag->frame_reader);
       mp3tag->namesize=strlen(mp3tag->frame_reader);
      
        
       }
       if(strcmp(mp3tag->frame_tag,"TPE1")==0){
        printf("Artist\t\t:\t%s\n",mp3tag->frame_reader);
       }
       if(strcmp(mp3tag->frame_tag,"TALB")==0){
        printf("Album\t\t:\t%s\n",mp3tag->frame_reader);
       }
       if(strcmp(mp3tag->frame_tag,"TYER")==0){
        printf("Year\t\t:\t%s\n",mp3tag->frame_reader);
       }
      if(strcmp(mp3tag->frame_tag,"TCON")==0){
        printf("Content type\t:\t%s\n",mp3tag->frame_reader);
       }
      
       
}
status Comm_tag(FILE *mp3_fptr,tag *mp3tag)
{
char buffer[4];
    fread(buffer,1,4,mp3tag->mp3_fptr);
   
         
          mp3tag->frame_tag=buffer;
          
         
         //reading frame 4 byte contant size
    char contnt[4];
        fread(contnt,1,4,mp3tag->mp3_fptr);
        
         int size=contnt[3];
         size=size-1;
     
//skip frame flag 3 bytes
        fseek(mp3tag->mp3_fptr,3,SEEK_CUR);
       
        char read[size-1];
        
     printf("Content down\t:\t");
        fread(read,1,size,mp3tag->mp3_fptr);
         read[size]='\0';
         for(int i=0;i<size;i++)
         {
         printf("%c",read[i]);
         }
         printf("\n");

          
}
     
