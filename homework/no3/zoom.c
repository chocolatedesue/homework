#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<math.h> 
//�ļ�ͷ
typedef struct tagBITMAPFILEHEADER {
	//unsigned short bfType;	  // ����ͼƬ���ͣ���ȡʱ��Ҫע�͵����ı���ʶ��ֻ�ܵ������ж�д
    unsigned int   bfSize;        // �ļ���С
    unsigned short bfReserved1;   // ����������Ϊ0
    unsigned short bfReserved2;   // ����������Ϊ0
    unsigned int   bfOffBits;     // ���ļ�ͷ��ʵ�ʵ�ͼ������֮����ֽڵ�ƫ����(û��ɫ��Ļ���54)
}BITMAPFILEHEADER;
//��Ϣͷ
typedef struct tagBITMAPINFOHEADER {
    unsigned int    biSize;          // �˽ṹ��Ĵ�С
    unsigned int    biWidth;         // ͼ��Ŀ�
    unsigned int    biHeight;        // ͼ��ĸ�
    unsigned short  biPlanes;        // ��ɫƽ���� ��Ϊ1
    unsigned short  biBitCount;      // һ������ռ��λ�� Windowsϵͳ��8,16,24 
    unsigned int    biCompression;   // ˵��ͼ������ѹ�������ͣ�0Ϊ��ѹ��
    unsigned int    biSizeImage;     // ͼ���С, ֵ���������ļ�ͷ�ṹ��bfSize-bfOffBits
    int             biXPelsPerMeter; // ˵��ˮƽ�ֱ��ʣ�������/�ױ�ʾ һ��Ϊ0 
    int             biYPelsPerMeter; // ˵����ֱ�ֱ��ʣ�������/�ױ�ʾ һ��Ϊ0 
    unsigned int    biClrUsed;       // ˵��λͼʵ��ʹ�õĲ�ɫ���е���ɫ����������Ϊ0�Ļ�����˵��ʹ�����е�ɫ���
    unsigned int    biClrImportant;  // ˵����ͼ����ʾ����ҪӰ�����ɫ��������Ŀ �����0��ʾ����Ҫ
}BITMAPINFOHEADER;
//��ɫ��
typedef struct tagRGBQUAND{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char rgbReserved;
}RGBQUAND;

int main(int argc, char* argv[]){
	//��ͼƬ 
	char *oldPhoto = argv[1], *newPhoto = argv[3];
	FILE *fp1 = fopen(oldPhoto, "rb"), *fp2 = fopen(newPhoto, "wb");
	double pzoom = atof(argv[2]) / 100.0;
	if (fp1 == NULL || fp2 == NULL) {
		printf("Opening photos failed!\n");
		if(fp1 == NULL)	fclose(fp1);
		if(fp2 == NULL)	fclose(fp2);
		return -1;
	}
	
	//������ȡbmpͼƬ�ı���ʶ��0x4d42
	unsigned short fileType;
	fread(&fileType, sizeof(unsigned short), 1, fp1);
	if(fileType != 0x4d42){//������ǵĻ�֤������bmpͼƬ 
		printf("The photo is not of bmp type��\n");
		return -1;
	} 
	
	//��ȡԭͼ��Ϣ
	BITMAPFILEHEADER fileHeader;	// ԭͼ�ļ�ͷ
	BITMAPINFOHEADER infoHeader;	// ԭͼ��Ϣͷ 
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp1);
	fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp1);
	int byte = infoHeader.biBitCount / 8;//ÿ�����ص��ֽ��� 
	RGBQUAND *palette = (RGBQUAND*)malloc((int)pow(2, infoHeader.biBitCount) * 4);//�����ɫ��ռ� 
	if(infoHeader.biBitCount != 24)//�����24λͼ��û�е�ɫ�� 
		fread(palette, sizeof(RGBQUAND), (int)pow(2, infoHeader.biBitCount), fp1);
	
	//�õ�ԭͼ��ߺ��޸ĺ�Ŀ��
	unsigned int oldWidth, oldHeight, newWidth, newHeight;
	oldWidth = infoHeader.biWidth;
	oldHeight = infoHeader.biHeight;
	printf("Oldphoto's height:%d\n", oldHeight);
	printf("Oldphoto's width:%d\n", oldWidth);
	//ͼ����ʾ������ԭ������ͼ�񳤻����4�ı��� ������һ�����Ա�֤�õ��Ŀ����4�ı���
	newHeight = ((int)(oldHeight * pzoom) + 3) / 4 * 4;
	newWidth = ((int)(oldWidth * pzoom) + 3) / 4 * 4;
	printf("Newphoto's height:%d\n", newHeight);
	printf("Newphoto's width:%d\n", newWidth);
	unsigned int oldsize = oldWidth * oldHeight * byte, newsize = newWidth * newHeight * byte;
		
	//��ȡԭͼλͼ����
	unsigned char *sourceData = (unsigned char*)malloc(oldsize);
	if(infoHeader.biBitCount == 24){//�޵�ɫ��ʱ 
		fseek(fp1, 54, SEEK_SET);//�ļ�ָ��ָ���ļ��ĵ�54���ֽ� 
		fread(sourceData, oldsize, 1, fp1); 
	}else if(infoHeader.biBitCount == 8){//�е�ɫ����Ҫ���Ϸ����ɫ������Ҫ�Ŀռ� 
		fseek(fp1, 1078, SEEK_SET);//�ļ�ָ��ָ���ļ��ĵ�54+2^8*4=1078���ֽ� 
		fread(sourceData, oldsize, 1, fp1); 
	}
	
	//�޸�����header�����ݲ����޸ĺ��header(����ɫ����Ϣ)д����ͼƬ�� 
	infoHeader.biWidth = newWidth;
	infoHeader.biHeight = newHeight;
	if(infoHeader.biBitCount == 24){
		fileHeader.bfSize = 54 + newsize;
		infoHeader.biSizeImage = newsize;
	}else if(infoHeader.biBitCount == 8){
		fileHeader.bfSize = 1078 + newsize;
		infoHeader.biSizeImage = newsize;
	}	 
	fwrite(&fileType, sizeof(unsigned short), 1, fp2);
	fwrite(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp2);
	fwrite(&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp2);
	if(infoHeader.biBitCount!=24)	fwrite(palette,sizeof(RGBQUAND),pow(2,infoHeader.biBitCount),fp2);
	 
	//ʹ��˫���Բ�ֵ������ͼƬ����	
	double p,q;
	unsigned int x1, y1, x2, y2;				//ԭͼ�������ص�Ŀ��
	unsigned int X, Y; 			 
 	unsigned char *pDestination; 				//�޸����ص�λ�ã����ֽ�ƫ������ 
	unsigned char *pSource1,*pSource2;			//��ȡ���ص�λ�ã����ֽ�ƫ������
	unsigned char *destinationData = (unsigned char*)malloc(newsize);//������ͼƬ��λͼ��������ռ� 
	for(Y = 0; Y < newHeight; Y++){
		y1 = Y / pzoom;
		y2 = Y / pzoom + 1;
		q = Y / pzoom - y1;
		pDestination = destinationData + Y * newWidth * byte;
		pSource1 = sourceData + y1 * oldWidth * byte;
		pSource2 = sourceData + y2 * oldWidth * byte;
		for(X = 0; X < newWidth; X++){
	 		x1 = X / pzoom;
	 		x2 = X / pzoom + 1;
	 		p = X / pzoom - x1;
	 		if(byte == 3){
			*(pDestination + X*byte) = *(pSource1 + x1*byte) * (1-p) * (1-q) +
									   *(pSource1 + x2*byte) * p * (1-q) +
									   *(pSource2 + x1*byte) * (1-p) * q + 
									   *(pSource2 + x2*byte) * p * q;

			*(pDestination + X*byte+1) = *(pSource1 + x1*byte+1) * (1-p) * (1-q) + 
										 *(pSource1 + x2*byte+1) * p * (1-q) + 
										 *(pSource2 + x1*byte+1) * (1-p) * q + 
										 *(pSource2 + x2*byte+1) * p * q;
									 
			*(pDestination + X*byte+2) =*(pSource1 + x1*byte+2) * (1-p) * (1-q) + 
									 	*(pSource1 + x2*byte+2) * p * (1-q) + 
										*(pSource2 + x1*byte+2) * (1-p) * q + 
										*(pSource2 + x2*byte+2) * p * q;
			}
			else if(byte == 1){
				*(pDestination + X*byte) = *(pSource1 + x1*byte) * (1-p) * (1-q) +
										   *(pSource1 + x2*byte) * p * (1-q) +
										   *(pSource2 + x1*byte) * (1-p) * q +
										   *(pSource2 + x2*byte) * p * q;
			}
		}
	}	

	//��λͼ����д���µ�ͼƬ�����к�������
	fwrite(destinationData, newsize, 1, fp2);	
	printf("success��\n");
	free(destinationData);
	free(sourceData);
	free(palette);
	fclose(fp1); 
	fclose(fp2);
	return 0;
}
