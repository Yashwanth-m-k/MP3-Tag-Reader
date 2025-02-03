#ifndef MP3TAG_H
#define MP3TAG_H
#include"types.h"

typedef struct Tagread
{
    char *mp3_fname;
    FILE *mp3_fptr;

    char *frame_reader;
    char *frame_tag;

  int namesize;


}tag;
  

status select_operation_valid(int argc,char *argv[],tag *mp3tag);
//
status view_validation(int argc,char *argv[],tag *mp3tag);
//
status do_view_opration(tag *mp3tag);
//
status open_file(FILE *mp3_fptr,tag *mp3tag);
//
status read_header(FILE *mp3_fptr,tag *mp3tag);
//
status read_from_frame_header(FILE *mp3_fptr,tag *mp3tag,char *frame_reader,char *frame_tag,int namesize);

//
status print_the_detaile_Info(FILE *mp3_fptr,tag *mp3tag,char *frame_reader,char *frame_tag);
//

status Comm_tag(FILE *mp3_fptr,tag *mp3tag);
//
#endif