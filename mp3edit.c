#include<stdio.h>
#include<string.h>
#include"mp3tag.h"
#include"types.h"
#include"mp3edit.h"
#include <stdlib.h>



//--------------------------------EDIT--------------------------
status edit_vaild_fname(int argc,char *argv[], FILE *mp3edit_fptr,edit *mp3edit)
{
     char *ch;
    if(ch=strstr(argv[4],".mp3"))
    {
        mp3edit->mp3edit_fname=argv[4]; 
    }
    mp3edit->title_name=argv[3];
    
    mp3edit->tag_read= argv[2];
    
}
status do_EDIT_opration(edit *mp3edit,int argc,char *argv[])
{
  
    edit_vaild_fname(argc,argv,mp3edit->mp3edit_fptr,mp3edit);
    open_for_file(mp3edit->mp3edit_fptr,mp3edit);
    open_duplicate_file(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit);
    For_Edit_nametag(argc,argv,mp3edit->mp3edit_fptr,mp3edit);
   
    
}
status open_for_file(FILE *mp3edit_fptr,edit *mp3edit)
{
    mp3edit->mp3edit_fptr=fopen(mp3edit->mp3edit_fname,"rb+");
    if(mp3edit->mp3edit_fname==NULL)
    {
        fprintf(stderr,"Unable to open %s",mp3edit->mp3edit_fname);
        return 1;
    }
    
    return success;

}
status For_Edit_nametag(int argc,char *argv[], FILE *mp3edit_fptr,edit *mp3edit)
{
  printf("--------------------------------- Selected Edit Option --------------------------------\n");
   
    fseek (mp3edit->mp3edit_fptr, 0L, SEEK_SET);
    fseek (mp3edit->duplicate_mp3_ptr, 0L, SEEK_SET);
    
    if(strcmp(mp3edit->tag_read,"-t")==0)
    {
        printf("------------------------------ Selected Title change Option ------------------------------\n");
          char buffer[4];
          char read[10];

        fread(read,1,10,mp3edit->mp3edit_fptr);
        fwrite(read,1,10,mp3edit->duplicate_mp3_ptr);
       
        fread(buffer,1,4,mp3edit->mp3edit_fptr);
        char *title=buffer;
        fwrite(buffer,1,4,mp3edit->duplicate_mp3_ptr);
         buffer[4]='\0';
        
      printf("              Title : %s\n",mp3edit->title_name);
        if(strcmp(title,"TIT2")==0)
        {
            char contnt[4];
            fread(contnt,1,4,mp3edit->mp3edit_fptr);
           
            int size=strlen(mp3edit->title_name);
         //   printf("len - > %d",size);

            int seek=contnt[3];

         //  printf("name size-> %d",seek);
            for(int i=0;i<3;i++)
            {
                fwrite(&contnt[i],1,1,mp3edit->duplicate_mp3_ptr);
            }
            fwrite(&size,1,1,mp3edit->duplicate_mp3_ptr);
            
          read[3];
         fread(read,1,3,mp3edit->mp3edit_fptr);
         fwrite(read,1,3,mp3edit->duplicate_mp3_ptr);
            
            char name[size];
            strcpy(name,mp3edit->title_name);
           
           for(int i=0;i<size;i++)
            {
                fwrite(&name[i],1,1,mp3edit->duplicate_mp3_ptr);
            }
       
               if(seek == 47){
             fseek(mp3edit->mp3edit_fptr,seek-1,SEEK_CUR);}
             else
              fseek(mp3edit->mp3edit_fptr,seek,SEEK_CUR);
            reaming_data(mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
        
        copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit); 
         printf("------------------------------ Title Change Successfully ------------------------------\n");
        }    
    }
    else if(strcmp(mp3edit->tag_read, "-a") == 0) {
      printf("------------------------------ Selected  Artist Name change Option ----------------------------\n");
    unsigned char buffer[4];  // A buffer to read data in chunks
    size_t bytesRead;
    int found ;
    int tag_size=0;
    char read[70];
    char tag_name[5];

        fseek(mp3edit_fptr, 17, SEEK_SET);
         fread(&tag_size, 1,1, mp3edit->mp3edit_fptr);
       //  printf("tag txt len: %d\n", tag_size);
        //make it has function upto 1st tag
         if(tag_size==47){tag_size=tag_size-1;}

        fseek(mp3edit_fptr,3+tag_size, SEEK_CUR);
        found=ftell(mp3edit_fptr);

       // printf("current position %d\n", found);
        rewind(mp3edit_fptr);
        
        read[found];
         fread(read,1,found,mp3edit->mp3edit_fptr);
        fwrite(read,1,found,mp3edit->duplicate_mp3_ptr);
        found=ftell(mp3edit_fptr);
       // printf("current position %d\n", found);
        fread(tag_name,1,4,mp3edit->mp3edit_fptr);
        fwrite(tag_name,1,4,mp3edit->duplicate_mp3_ptr);
        tag_name[4]='\0';
       // printf("->%s",tag_name);
        char *tag=tag_name;
       // printf("->%s",tag);
       printf("                  Artist : %s\n",mp3edit->title_name);
     if(strcmp(tag,"TPE1")==0)
     {
           copy_tag_name(found,mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
        
           copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit);
         printf("-----------------------------  Artist Name Change Successfully ----------------------------\n");
     }
     
    }
    else if(strcmp(mp3edit->tag_read, "-A") == 0)
    {
      printf("---------------------------- Selected  Album Name change Option ----------------------------\n");
        unsigned char buffer[4];  // A buffer to read data in chunks
    size_t bytesRead;
    int found ;
    int tag_size1 = 0,tag_size2=0;
    char read[200];
    char tag_name[5];

        fseek(mp3edit_fptr, 17, SEEK_SET);
         fread(&tag_size1, 1,1, mp3edit->mp3edit_fptr);
       //  printf("Adjusted length: %d\n", tag_size1);
        if(tag_size1==47){tag_size1=tag_size1-1;}

        fseek(mp3edit_fptr,3+tag_size1+7, SEEK_CUR);
         fread(&tag_size2,1,1,mp3edit->mp3edit_fptr);

         if(tag_size2==33){tag_size2=tag_size2-1;}
    
          fseek(mp3edit_fptr,3+tag_size2, SEEK_CUR);
        //  printf("tag2_size-> %d ",tag_size2);

        found=ftell(mp3edit_fptr);
      //  printf("current position %d\n", found);

        rewind(mp3edit_fptr);
        
        read[found];
         fread(read,1,found,mp3edit->mp3edit_fptr);
        fwrite(read,1,found,mp3edit->duplicate_mp3_ptr);
        found=ftell(mp3edit_fptr);

     // printf("current position %d\n", found);
       fread(tag_name,1,4,mp3edit->mp3edit_fptr);
         fwrite(tag_name,1,4,mp3edit->duplicate_mp3_ptr);
         tag_name[4]='\0';
       //  printf("->%s\n",tag_name);
        char *tag=tag_name;
       // printf("->%s\n",tag);
printf("                     Album : %s\n",mp3edit->title_name);
    if((strcmp(tag,"TALB"))==0)
     {
        copy_tag_name(found,mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
          copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit);
           printf("------------------------------  Album Name Change Successfully ------------------------------\n");
     }

    }
    else if(strcmp(mp3edit->tag_read,"-y") == 0)
    {
       printf("--------------------------------- Selected  year change Option --------------------------------\n");
        unsigned char buffer[4];  // A buffer to read data in chunks
    size_t bytesRead;
    int found ;
    int tag_size1 = 0,tag_size2=0,tag_size3=0;
    char read[200];
    char tag_name[5];

        fseek(mp3edit_fptr, 17, SEEK_SET);
         fread(&tag_size1, 1,1, mp3edit->mp3edit_fptr);
       //  printf("Adjusted length: %d\n", tag_size1);
        if(tag_size1==47){tag_size1=tag_size1-1;}

        fseek(mp3edit_fptr,3+tag_size1+7, SEEK_CUR);
         fread(&tag_size2,1,1,mp3edit->mp3edit_fptr);
         if(tag_size2==33){tag_size2=tag_size2-1;}
    
          fseek(mp3edit_fptr,3+tag_size2+7, SEEK_CUR);
         // printf("tag2_size-> %d ",tag_size2);

            fread(&tag_size3,1,1,mp3edit->mp3edit_fptr);
         
         if(tag_size3==9){tag_size3=tag_size3-1;}
         
         fseek(mp3edit_fptr,3+tag_size3, SEEK_CUR);
       //   printf("tag2_size-> %d ",tag_size3);

        
        found=ftell(mp3edit_fptr);
       // printf("current position %d\n", found);

        rewind(mp3edit_fptr);
        
        read[found];
         fread(read,1,found,mp3edit->mp3edit_fptr);
        fwrite(read,1,found,mp3edit->duplicate_mp3_ptr);
        found=ftell(mp3edit_fptr);

     // printf("current position %d\n", found);
       fread(tag_name,1,4,mp3edit->mp3edit_fptr);
         fwrite(tag_name,1,4,mp3edit->duplicate_mp3_ptr);
         tag_name[4]='\0';
       //  printf("->%s\n",tag_name);
        char *tag=tag_name;
       // printf("->%s\n",tag);
printf("                     Year : %s\n",mp3edit->title_name);
        if((strcmp(tag,"TYER"))==0)
     {
        
        copy_tag_name(found,mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
          copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit);
           printf("-------------------------------  Year Changed Successfully ----------------------------\n");
     }

    }
    else if(strcmp(mp3edit->tag_read,"-g") == 0)
    {
      printf("------------------------------ Selected  Genre change Option -----------------------------\n");
        unsigned char buffer[4];  // A buffer to read data in chunks
    size_t bytesRead;
    int found ;
    int tag_size1 = 0,tag_size2=0,tag_size3=0,tag_size4=0;
    char read[200];
    char tag_name[5];

        fseek(mp3edit_fptr, 17, SEEK_SET);
         fread(&tag_size1, 1,1, mp3edit->mp3edit_fptr);
        // printf("Adjusted length: %d\n", tag_size1);
        if(tag_size1==47){tag_size1=tag_size1-1;}

        fseek(mp3edit_fptr,3+tag_size1+7, SEEK_CUR);
         fread(&tag_size2,1,1,mp3edit->mp3edit_fptr);
         if(tag_size2==33){tag_size2=tag_size2-1;}
    
          fseek(mp3edit_fptr,3+tag_size2+7, SEEK_CUR);
         // printf("tag2_size-> %d ",tag_size2);

            fread(&tag_size3,1,1,mp3edit->mp3edit_fptr);
         
         if(tag_size3==9){tag_size3=tag_size3-1;}
         
         fseek(mp3edit_fptr,3+tag_size3+7, SEEK_CUR);
        //  printf("tag2_size-> %d ",tag_size3);

            fread(&tag_size4,1,1,mp3edit->mp3edit_fptr);

            if(tag_size4==31){tag_size4=tag_size4-1;}

          fseek(mp3edit_fptr,3+tag_size4, SEEK_CUR);
       //   printf("tag2_size-> %d ",tag_size3);
        
        found=ftell(mp3edit_fptr);
     //   printf("current position %d\n", found);

        rewind(mp3edit_fptr);
        
        read[found];
         fread(read,1,found,mp3edit->mp3edit_fptr);
        fwrite(read,1,found,mp3edit->duplicate_mp3_ptr);
        found=ftell(mp3edit_fptr);

     // printf("current position %d\n", found);
       fread(tag_name,1,4,mp3edit->mp3edit_fptr);
         fwrite(tag_name,1,4,mp3edit->duplicate_mp3_ptr);
         tag_name[4]='\0';
       //  printf("->%s\n",tag_name);
        char *tag=tag_name;
       // printf("->%s\n",tag);
      printf("                     Genre : %s\n",mp3edit->title_name);

          if((strcmp(tag,"TCON"))==0)
     {
        
        copy_tag_name(found,mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
          copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit);
          printf("---------------------------------  Genre Changed Successfully --------------------------------\n");
     }
    
}
else if(strcmp(mp3edit->tag_read,"-c") == 0)
    {
      printf("---------------------------------Comment change option --------------------------------\n");
        unsigned char buffer[4];  // A buffer to read data in chunks
    size_t bytesRead;
    int found ;
    int tag_size1 = 0,tag_size2=0,tag_size3=0,tag_size4=0,tag_size5=0;
    char read[200];
    char tag_name[5];

        fseek(mp3edit_fptr, 17, SEEK_SET);
         fread(&tag_size1, 1,1, mp3edit->mp3edit_fptr);
       //  printf("tag 1 %d\n", tag_size1);
        if(tag_size1==47){tag_size1=tag_size1-1;}

        fseek(mp3edit_fptr,3+tag_size1+7, SEEK_CUR);
         fread(&tag_size2,1,1,mp3edit->mp3edit_fptr);
         if(tag_size2==33){tag_size2=tag_size2-1;}
    
          fseek(mp3edit_fptr,3+tag_size2+7, SEEK_CUR);
        //  printf("tag2_size-> %d ",tag_size2);

            fread(&tag_size3,1,1,mp3edit->mp3edit_fptr);
         
         if(tag_size3==9){tag_size3=tag_size3-1;}
         
         fseek(mp3edit_fptr,3+tag_size3+7, SEEK_CUR);
         // printf("tag3_size-> %d ",tag_size3);

            fread(&tag_size4,1,1,mp3edit->mp3edit_fptr);

            if(tag_size4==31){tag_size4=tag_size4-1;}

          fseek(mp3edit_fptr,3+tag_size4+7, SEEK_CUR);
         // printf("tag4_size-> %d ",tag_size4);
        
       fread(&tag_size5,1,1,mp3edit->mp3edit_fptr);
       if(tag_size5==31){tag_size5=tag_size5-1;}

        fseek(mp3edit_fptr,3+tag_size5, SEEK_CUR);
       //   printf("tag5_size-> %d ",tag_size5);

        found=ftell(mp3edit_fptr);
       // printf("current position %d\n", found);

        rewind(mp3edit_fptr);
        
        read[found];
         fread(read,1,found,mp3edit->mp3edit_fptr);
        fwrite(read,1,found,mp3edit->duplicate_mp3_ptr);
        found=ftell(mp3edit_fptr);

     // printf("current position %d\n", found);
       fread(tag_name,1,4,mp3edit->mp3edit_fptr);
         fwrite(tag_name,1,4,mp3edit->duplicate_mp3_ptr);
         tag_name[4]='\0';
       //  printf("->%s\n",tag_name);
        char *tag=tag_name;
       // printf("->%s\n",tag);
        printf("                  Comment : %s\n",mp3edit->title_name);
          if((strcmp(tag,"COMM"))==0)
     {
        copy_tag_name(found,mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
       
           copyALL_datato_mainmp3(mp3edit->duplicate_fname,mp3edit->duplicate_mp3_ptr,mp3edit_fptr,mp3edit);
           printf("---------------------------------  Comment Changed Successfully --------------------------------\n");
     }
    }

}
status open_duplicate_file(char *duplicate_fname,FILE *duplicate_mp3_ptr,edit *mp3edit)
{
    mp3edit->duplicate_fname="duplicate.mp3";
    mp3edit->duplicate_mp3_ptr=fopen(mp3edit->duplicate_fname,"wb+");
    if(mp3edit->duplicate_mp3_ptr==NULL)
    {
        printf("unable to open file ");
        return 1;
    }
   

    return success;
    
}
status reaming_data(char *duplicate_fname,FILE *mp3edit_fptr,FILE *duplicate_mp3_ptr,edit *mp3edit)
{
     
    
      size_t bytesRead;
    char buffer1[1]; // Buffer to hold one byte
   
    // Read and write one byte at a time
    while ((bytesRead = fread(&buffer1, 1, 1,mp3edit->mp3edit_fptr )) > 0) {
        
        fwrite(buffer1,1,1,mp3edit->duplicate_mp3_ptr);
        
    }
}
status copyALL_datato_mainmp3(char *duplicate_fname,FILE *duplicate_mp3_ptr,FILE *mp3edit_fptr,edit *mp3edit)
{
    fseek (mp3edit->mp3edit_fptr, 0L, SEEK_SET);
    fseek (mp3edit->duplicate_mp3_ptr, 0L, SEEK_SET);
    // Buffer for copying data
   size_t bytesRead;
    char buffer[1]; // Buffer to hold one byte
   
    // Read and write one byte at a time
    while ((bytesRead = fread(&buffer, 1, 1,mp3edit->duplicate_mp3_ptr)) > 0) {
        
        fwrite(buffer,1,1,mp3edit->mp3edit_fptr);
        
    }
    // Close files
    int tell=ftell(mp3edit->duplicate_mp3_ptr); 

   // printf("nobyte->%u",tell);
    int tell1=ftell(mp3edit->mp3edit_fptr);
   // printf("nobyte->%u",tell1);
            fclose( duplicate_mp3_ptr);
            fclose(mp3edit_fptr);

    


}
status copy_tag_name(char found,char *duplicate_fname,FILE *duplicate_mp3_ptr,FILE *mp3edit_fptr,edit *mp3edit)
{
    char contnt[4];
            fread(contnt,1,4,mp3edit->mp3edit_fptr);
            int size=strlen(mp3edit->title_name);
            contnt[4]='\0';
            
            int seek=contnt[3];
            
        
            //printf("txt size >%d",seek);

             for(int i=0;i<3;i++)
            {
                fwrite(&contnt[i],1,1,mp3edit->duplicate_mp3_ptr);
            }
            fwrite(&size,1,1,mp3edit->duplicate_mp3_ptr);
            
        char  read[3];
         fread(read,1,3,mp3edit->mp3edit_fptr);
        fwrite(read,1,3,mp3edit->duplicate_mp3_ptr);
            
            char name[size];
            strcpy(name,mp3edit->title_name);
           
           for(int i=0;i<size;i++)
            {
                fwrite(&name[i],1,1,mp3edit->duplicate_mp3_ptr);
            }
          
            if(seek==31||seek==47||seek==33||seek==9||seek==5){
          fseek(mp3edit->mp3edit_fptr,found+4+4+3+seek-1,SEEK_SET);}
          else{
            fseek(mp3edit->mp3edit_fptr,found+4+4+3+seek,SEEK_SET);
          }
          reaming_data(mp3edit->duplicate_fname,mp3edit_fptr,mp3edit->duplicate_mp3_ptr,mp3edit);
         
}


