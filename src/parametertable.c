#include "parametertable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

/** キーと値との間の分割文字 */
#define DELIM           ":"
#define MAX_PARAM_FILE_LINE_LEN (MAX_KEY_SIZE + 256)
/**
 * @struct data_map_t
 * @brief キーと値のペアでの情報管理構造体
 */
typedef struct
{
    char*       key;            /** キー */
    int32_t     val;            /** 値 */
}data_map_t;
/**
 * @struct parametertable_t
 * @brief オブジェクトの内部パラメーター
 */
typedef struct
{
    data_map_t* p_map;          /** data_map_t型ポインタ */
    int32_t     n_map;          /** p_mapの個数 */
    int32_t     n_store;
}parametertable_t;

/**
 * @brief parametertable_t型構造体のデータ内からkey文字列に該当する
 *        data_map_t型構造体データを検索します。
 *
 * @param[in] table   parametertable_t型構造体データ
 * @param[in] key     キー
 *
 * @retval NULL以外 data_map_t型構造体ポインタ
 * @retval NULL キーに該当するものが見つからなかった
 */
static data_map_t* getDataMap(parametertable_t* table,const char* key);

static data_map_t* getDataMap(parametertable_t* table,const char* key)
{
    int i;
    for(i = 0;i < table->n_store;i++)
    {
        if(strcmp(table->p_map[i].key,key) == 0)
        {
            return &table->p_map[i];
        }
    }
    return NULL;
}


ParameterTable_Handle ParameterTable_create(int n_key)
{
    parametertable_t* This;
    This = (parametertable_t*)malloc(sizeof(parametertable_t));
    if(This != NULL)
    {
        This->p_map = (data_map_t*)malloc(sizeof(data_map_t) * n_key);
        if(This->p_map != NULL)
        {
            This->n_map   = n_key;
            This->n_store = 0;
            return (ParameterTable_Handle)This;
        }
        SAFE_FREE(This);
    }
    return NULL;
}

void      ParameterTable_delete(ParameterTable_Handle h_obj)
{
    parametertable_t* This = (parametertable_t*)h_obj;
    ParameterTable_initialize(h_obj);
    SAFE_FREE(This->p_map);
    SAFE_FREE(This);
}

void      ParameterTable_initialize(ParameterTable_Handle h_obj)
{
    parametertable_t* This = (parametertable_t*)h_obj;
    int               i;

    for(i = 0;i < This->n_store;i++)
    {
        SAFE_FREE(This->p_map[i].key);
    }
    This->n_store = 0;
}

int32_t    ParameterTable_store(ParameterTable_Handle h_obj,
                                const char*           key,
                                int32_t               val)
{
    parametertable_t* This = (parametertable_t*)h_obj;
    int32_t           ret  = FAILURE;
    if(This->n_store < This->n_map)
    {
        int32_t ref;
        if(ParameterTable_fetch(h_obj,key,&ref) == SUCCESS)
        {
            data_map_t* p_map = getDataMap(This,key);
            p_map->val        = val;
            ret               = SUCCESS;
        }
        else
        {
            data_map_t* p_map = &This->p_map[This->n_store];
            p_map->key        = (char*)malloc(strlen(key) + 1);
            if(p_map->key != NULL)
            {
                strcpy(p_map->key,key);
                p_map->val = val;
                This->n_store++;
                ret        = SUCCESS;
            }
        }
    }
    return ret;
}


int32_t    ParameterTable_fetch(ParameterTable_Handle h_obj,
                                  const char*           key,
                                  int32_t*              val)
{
    parametertable_t* This  = (parametertable_t*)h_obj;
    int32_t           ret   = FAILURE;
    data_map_t*       p_map = getDataMap(This,key);

    if(p_map != NULL)
    {
        *val = p_map->val;
        ret  = SUCCESS;
    }
    return ret;
}

int32_t    ParameterTable_writeFile(ParameterTable_Handle h_obj,
                                    const char*           file)
{
    parametertable_t* This = (parametertable_t*)h_obj;
    int               i;
    int32_t           ret  = FAILURE;
    FILE*             fp;
    fp                     = fopen(file,"w");
    if(fp != NULL)
    {
        for(i = 0;i < This->n_store;i++)
        {
            fprintf(fp,"%s%s%d\n",This->p_map[i].key,DELIM,This->p_map[i].val);
        }
        fclose(fp);
        ret = SUCCESS;
    }
    return ret;
}

int32_t    ParameterTable_readFile(ParameterTable_Handle h_obj,
                                   const char*           file)
{
    int32_t ret = FAILURE;
    FILE*   fp  = fopen(file,"r");
    if(fp != NULL)
    {
        char buffer[MAX_PARAM_FILE_LINE_LEN];
        while(fgets(buffer,sizeof(buffer),fp) != NULL)
        {
            char first[MAX_KEY_SIZE];
            char second[MAX_PARAM_FILE_LINE_LEN - MAX_KEY_SIZE];
            if(splitString(buffer,DELIM,first,second) == SUCCESS)
            {
                ParameterTable_store(h_obj,first,atoi(second));
            }
        }
        fclose(fp);
        ret = SUCCESS;
    }
    return ret;
}

