
#include <stdio.h>  
#include <string.h>  
#include<io.h>    
#include <opencv2\opencv.hpp>  
#define IMGNUM 20000 //图片所在文件夹中图片的最大数量    
char img_files[IMGNUM][1000];  
  
using namespace cv;  
int getFiles(char *path)  
{  
    int num_of_img = 0;  
    long   hFile = 0;  
    struct _finddata_t fileinfo;  
    char p[700] = { 0 };  
    strcpy(p, path);  
    strcat(p, "/*");  
    if ((hFile = _findfirst(p, &fileinfo)) != -1)  
    {  
        do  
        {  
            if ((fileinfo.attrib & _A_SUBDIR))  
            {  
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)  
                    continue;  
            }  
            else  
            {  
                strcpy(img_files[num_of_img], path);  
                strcat(img_files[num_of_img], "/");  
                strcat(img_files[num_of_img++], fileinfo.name);  
            }  
        } while (_findnext(hFile, &fileinfo) == 0);  
        _findclose(hFile);  
    }  
    return num_of_img;  
}  
int test13(int argc, char *argv[])  
{  
    char path[] = "G:/F/MTCNN/mtcnn-master2/vehicle-车辆训练样本/images";                               //source image  
    char dstpath[] = "G:/F/MTCNN/mtcnn-master2/vehicle-车辆训练样本/imagesResult";                            //destination image  
    int num = getFiles(path);  
    int i;  
    char order[1000];  
    FILE *fp = fopen("train.txt", "w");  
    for (i = 0; i<num; ++i)  
    {  
        printf("%s\n", img_files[i]);  
        IplImage *pSrc = cvLoadImage(img_files[i]);  
        sprintf(order, "DstImage\\%05d.jpg", i);  
        fprintf(fp, "%05d\n", i);  
        cvSaveImage(order, pSrc);  
        printf("Saving %s!\n", order);  
        cvReleaseImage(&pSrc);  
    }  
    fclose(fp);  
    return 0;  
}  