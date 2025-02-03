#include<stdio.h>
#include"mp3tag.h"
#include"types.h"
#include"mp3edit.h"
#include <string.h>

int main(int argc,char *argv[])
{
    
        tag *mp3tag_var;
        edit *mp3edit_var;
  if(argc == 1){
   printf("ERROR:./a.out : INVALID ArGUMENTS\nUSAGE :\n");  
  printf("To view please pass linke : ./a.out -v mp3filename\nTo edit please pass linke : ./a.out -e -t/-a/-A/-m/-y/-c mp3filename\n");
  return 0;}
  if(strcmp(argv[1],"-h")==0)
  {
      printf("$ mp3tag --help\nusage: mp3tag [tTaAycg] 'value' file1\n    mp3tag -v\n");
      printf("-t Modifies a Title tag\n-T Modifies a Track tag\n-a Modifies an Artist tag\n-A Modifies an Album tag\n-y Modifies a Year tag\n");
      printf("-C Modifies a Comment tag\n-g Modifies a Genre tag\n-h Displays this help info\n-v Prints version info\n");
  }
  int  res=select_operation_valid(argc,argv,mp3tag_var);
  
   if(res==view)
   {
        int ret=view_validation(argc,argv,mp3tag_var);
        if(ret==success)
        {
           
            
            do_view_opration(mp3tag_var);
        }
        else
        {
           return failure;
        }
   }
   if(res==Edit)
   {
      
      
      do_EDIT_opration(mp3edit_var,argc,argv);

   }

}