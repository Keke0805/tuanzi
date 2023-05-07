

#include "unzip.h"

static int32_t mkdirs(char *dir)
{
    char *p;
	p = dir;

    while(p != NULL)
    {
        p = strchr(p+1, '/');
        if(p == NULL)
            break;

        *p = 0;
        mkdir(dir, 0777);

        *p = '/';
    }
	return 0;
}

int unzip(char *file_url, char *path)
{
    unz_file_info64 FileInfo;
    unzFile zFile;
    unz_global_info64 gi;
    ZPOS64_T i;
    int ret;
    char file[256];
    char data[4096];
    char zip_path[1024];
    FILE *fp = NULL;
    ZPOS64_T size_readed;
    ZPOS64_T total_size = 0;
    ZPOS64_T total_readed = 0;
    int size;
    int zip_file_open = 0;
	
    zFile = unzOpen64(file_url);
    if(NULL == zFile)
    {
        printf("open zip file fail: %s\n", file_url);
        goto ERROUT;
    }
	
    if (unzGetGlobalInfo64(zFile, &gi) != UNZ_OK)
    {
        printf("get zip file info fail: %s\n", file_url);
        goto ERROUT;
    }
    for (i = 0; i < gi.number_entry; i++)
    {
        ret = unzGetCurrentFileInfo64(zFile, &FileInfo, NULL, 0, NULL, 0, NULL, 0);
        if (ret != UNZ_OK)
        {
            printf("unzip get current file info fail\n");
            goto ERROUT;
        }

        total_size += FileInfo.uncompressed_size;
        if ((i + 1) < gi.number_entry)
        {
            ret = unzGoToNextFile(zFile);
            if (ret != UNZ_OK)
            {
                printf("error %d with zipfile in unzGoToNextFile\n",ret);
                goto ERROUT;
            }
        }
    }
    ret = unzGoToFirstFile (zFile);
    if (ret != UNZ_OK)
    {
        printf("unzip fail\n");
        goto ERROUT;
    }
    //print_cj("line=%d, func=%s, total size=%lld\n", __LINE__, __func__, total_size);
    
    for (i = 0; i < gi.number_entry; i++)
    {
        file[0] = 0;
        ret = unzGetCurrentFileInfo64(zFile, &FileInfo, file, sizeof(file), NULL, 0, NULL, 0);
        if (ret != UNZ_OK)
        {
            printf("unzip get current file info fail\n");
            goto ERROUT;
        }
       // print_cj("file: %s, file size=%lld, %lld/%lld\n",
        //    file, FileInfo.uncompressed_size, i+1, gi.number_entry);

        snprintf(zip_path, 1024, "%s%s", path, file);
        //print_cj("zip_path: %s\n", zip_path);
        mkdirs(zip_path);
        if(zip_path[strlen(zip_path) - 1] == '/')
            goto NEXT;

        //打开文件
        ret = unzOpenCurrentFile(zFile);/* 无密码 */
        if(ret != UNZ_OK)
        {
            printf("unzip open current file fail\n");
            goto ERROUT;
        }
        
        //读取内容
        zip_file_open = 1;
        fp = fopen(zip_path, "wb");
        if(fp == NULL)
        {
            printf("creat file fail: %s\n", zip_path);
            goto ERROUT;
        }

        size_readed = 0;
        while(size_readed < FileInfo.uncompressed_size)
        {
            size = unzReadCurrentFile(zFile, data, sizeof(data));
            if(size <= 0)
            {
                printf("zip file read fail: %lld/%lld, ret=%d\n",
                    size_readed, FileInfo.uncompressed_size, size);
                goto ERROUT;
            }

            ret = fwrite(data, 1, size, fp);
            if(ret != size)
            {
                printf("write fail, ret=%d, size=%d\n", ret, size);
                goto ERROUT;
            }

            size_readed += ret;
            total_readed += ret;
        }
        fclose(fp);

        //关闭当前文件
        zip_file_open = 0;
        unzCloseCurrentFile(zFile);

NEXT:
        if ((i + 1) < gi.number_entry)
        {
            ret = unzGoToNextFile(zFile);
            if (ret != UNZ_OK)
            {
                printf("error %d with zipfile in unzGoToNextFile\n",ret);
                goto ERROUT;
            }
        }
    }
    
    unzClose(zFile);
    unlink(file_url);
    //gelin_app_checksum_build(file_url);
    sync();
    //print_cj("unzip finish\n");
    
    return 1;

ERROUT:
    if(zip_file_open == 1)
        unzCloseCurrentFile(zFile);
    if(zFile != NULL)
        unzClose(zFile);
    if(fp != NULL)
        fclose(fp);
	return -1;
}

