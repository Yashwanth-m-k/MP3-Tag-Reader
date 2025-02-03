#ifndef MP3EDIT_H
#define MP3EDIT_H

#include "types.h"

typedef struct EDIT
{
    char *tag_read;
     char *mp3edit_fname;
     FILE *mp3edit_fptr;

    FILE *duplicate_mp3_ptr;
    char *duplicate_fname;
    char *for_edit_title;

    char *title_name;
   

}edit;



            //--------------------------EDIT----------------//
status edit_vaild_fname(int argc,char *argv[], FILE *mp3edit_fptr,edit *mp3edit);
//
status open_for_file(FILE *mp3edit_fptr,edit *mp3edit);
//
status For_Edit_nametag(int argc,char *argv[],FILE *mp3edit_fptr,edit *mp3edit);
//
status do_EDIT_opration(edit *mp3edit,int argc,char *argv[]);
//
status open_duplicate_file(char *duplicate_fname,FILE *duplicate_mp3_ptr,edit *mp3edit);
//
status edit_title(edit *mp3edit);
//
status reaming_data(char *duplicate_fname,FILE *mp3edit_fptr,FILE *duplicate_mp3_ptr,edit *mp3edit);
//
status copyALL_datato_mainmp3(char *duplicate_fname,FILE *duplicate_mp3_ptr,FILE *mp3edit_fptr,edit *mp3edit);
//
status copy_tag_name(char found,char *duplicate_fname,FILE *duplicate_mp3_ptr,FILE *mp3edit_fptr,edit *mp3edit);
#endif