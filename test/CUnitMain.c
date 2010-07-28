/**
 * @file   CUnitMain.c
 * @brief  Program main routine
 *
 * @author Junsei Takahashi
 * @date last update 2010-07-29 00:48:18
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "macro.h"
/*
 * CUnit
 */
#include "CUnit.h"
#include "Basic.h"
#include "Automated.h"
/*
 * test suites
 */
#include "TestSuites.h"

#define VERSION "1.0.0"
/*
 * Program main routine
 */
int
MAIN(int argc, char* argv[])
{
  CU_ErrorCode errorCode;
  int32_t f_xml = FALSE;
  int i;
  /**
   * - コマンドラインオプションの設定
   */
  for(i=1; i<argc; i++)
  {
    if((strcmp(argv[i],"-h") == 0) || (strcmp(argv[i],"--help") == 0))
    {
      fprintf(stdout, "Usage : [option]¥n");
      fprintf(stdout, "Option:¥n");
      fprintf(stdout, "¥t--help             : display Usage.¥n");
      fprintf(stdout, "¥t--version          : display version.¥n");
      fprintf(stdout, "¥t--xml              : output to xml.¥n");
      exit(EXIT_SUCCESS);
    }
    else if((strcmp(argv[i],"-v") == 0) || (strcmp(argv[i],"--version") == 0))
    {
      fprintf(stdout, "version:  %s¥n", VERSION);
      exit(EXIT_SUCCESS);
    }
    else if(strcmp(argv[i],"--xml") == 0)
    {
      f_xml = TRUE;
    }
    else
    {
      fprintf(stderr,"See '%s --help'¥n", argv[0]);
      exit(EXIT_SUCCESS);
    }
  }
  /**
   * - CUnit設定
   */
  CU_initialize_registry();
  errorCode = CU_register_suites(suites_array);
  /**
   * - XML出力
   */
  if(f_xml){
    CU_set_output_filename(argv[2]);
    CU_automated_run_tests();
    CU_list_tests_to_file();
  }else{
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
  }
  CU_cleanup_registry();

  return 0;
}
